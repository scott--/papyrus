/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This file is part of the papyrus library.                             *
 *                                                                         *
 *   papyrus is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU Lesser General Public License           *
 *   version 3.0 as published by the Free Software Foundation.             *
 *                                                                         *
 *   papyrus is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License version 3.0 for more details.       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with the papyrus library. If not, see                   *
 *   <http://www.gnu.org/licenses/>.                                       *
 ***************************************************************************/
#include "group.h"
#include "shape.h"

#include <assert.h>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <exception>


namespace Papyrus
{

  Group::Group ( const Glib::ustring& id ) :
      Drawable ( id ),
      m_size ( 0 ),
      m_intermediate_drawing_enabled(false)
  {
    set_selectable ( false );
  }

  Group::Group( const AttributeValueMap& avmap ):
      m_size(0)
  {
    this->set( avmap );
  }

  Group::pointer Group::create ( const Glib::ustring& id )
  {
    PAPYRUS_CREATE ( Group ( id ) );
  }

  Group::pointer Group::create ( const AttributeValueMap& avmap )
  {
    PAPYRUS_CREATE ( Group ( avmap ) );
  }

  Group::~Group()
  {
//     Layers::iterator ilayer;
//     Layer::iterator ichild;
//     Connections::iterator conniter;

//     for ( conniter = m_redraw_connections.begin(); conniter != m_redraw_connections.end(); conniter++ )
//       conniter->second.disconnect();

//     for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
//       for ( ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++ )
//       {
//         ( *ichild ) ->m_parent = NULL;
//       }
  }

  const Glib::ustring & Group::title() const
  {
    return m_title;
  }

  void Group::set_title( const Glib::ustring& t )
  {
    m_title = t;
    m_signal_title_changed.emit();
  }

  sigc::signal<void>& Group::signal_title_changed()
  {
    return m_signal_title_changed;
  }

  const Glib::ustring & Group::description() const
  {
    return m_description;
  }

  void Group::set_description( const Glib::ustring& d )
  {
    m_description = d;
    m_signal_description_changed.emit();
  }

  sigc::signal<void>& Group::signal_description_changed()
  {
    return m_signal_description_changed;
  }

  void Group::freeze()
  {
    m_frozen = true;
    this->freeze_children();
  }

  void Group::thaw(bool force_redraw)
  {
    m_frozen = false;
    if ( not m_frozen_by_parent )
    {
      this->thaw_children( force_redraw );
      if ( m_need_redraw ) m_signal_changed.emit();
    }    
  }


  bool Group::is_intermediate_drawing_enabled()
  {
    return m_intermediate_drawing_enabled;
  }

  void Group::enable_intermediate_drawing(bool enabled)
  {
    m_intermediate_drawing_enabled = enabled;
    this->redraw();
  }

  void Group::set( const AttributeValueMap& avmap )
  {
    Drawable::set( avmap );
    
    AttributeValueMap::const_iterator i;
    Fill::pointer fill;
    Stroke::pointer stroke;
    double stroke_width = -1.0;

    for ( i = avmap.begin(); i != avmap.end(); i++ )
    {
      if      ( strcaseeq( i->first, "fill" ) )         fill = Fill::create( i->second );
      else if ( strcaseeq( i->first, "stroke" ) )       stroke = Stroke::create( i->second );
      else if ( strcaseeq( i->first, "stroke-width" ) ) stroke_width = atof( i->second.c_str() );
    }

    if ( stroke_width >= 0.0 )
    {
      if ( stroke ) stroke->set_width( stroke_width );
      else stroke = Stroke::create( stroke_width );
    }

    if ( fill ) this->set_fill( fill );
    if ( stroke ) this->set_stroke( stroke );
  }

  bool Group::add ( Drawable::pointer item, int layer )
  {
    // We must have a valid pointer
    if ( ! item ) return false;

    // we can't add an item to itself, otherwise we'll end up with recursive problems
    if ( item.get() == this ) return false;

    // if we're already the parent, we're done
    if ( item->m_parent == this ) return true;

    // if it already has a parent, we'll remove it
    if ( item->m_parent ) item->m_parent->remove(item);
      
    // this group becomes the new parent
    item->m_parent = this;

    // we need the redraw signal connected
    m_redraw_connections[ item ] =
        item->signal_redraw().connect ( sigc::bind ( sigc::mem_fun ( *this, &Group::on_child_redraw ), item ) );

    // Connect to the changed signal
    m_changed_connections[ item ] =
        item->signal_changed().connect ( sigc::bind ( sigc::mem_fun ( *this, &Group::on_child_changed_proxy ), item ) );

    // Add this object to the list of children
    m_layers[layer].push_front ( item );

    m_size++;

    if ( not item->exclude_from_extents() )
    {
      // Include the child's extents in this group's raw extents
      m_pre_viewbox_extents.include ( item->extents() );

      // Changing the raw extents invalidates the transformed extents
      m_extents_invalid = true;
      m_signal_extents_changed.emit();
    }

    // Notify anyone connected to the child_added signal
    m_signal_child_added.emit ( item );

    // We'll need a redraw of course
    this->redraw();

    return true;
  }

  bool Group::remove ( Drawable::pointer item )
  {
    bool layer_found = false;
    Layers::iterator ilayer;
    Layer::iterator ichild;
    Connections::iterator i;

    // We must have a valid pointer
    if ( not item ) return false;

    // If we're not the parent we can't remove the item
    if ( item->m_parent != this ) return false;

    // Let's find which layer the child is in
    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      ichild = std::find ( ilayer->second.begin(), ilayer->second.end(), item );
      if ( ichild != ilayer->second.end() )
      {
        ilayer->second.erase ( ichild );
        m_size--;
        if ( ilayer->second.size() == 0 )
          m_layers.erase ( ilayer );
        layer_found = true;
        break;
      }
    }

    // If we didn't find the child in any layer then we'll raise an exception
    // since we shouldn't have gotten here
    if ( not layer_found ) throw(1);

    // Let's find out if we have a redraw signal for it
    i = m_redraw_connections.find ( item );
    if ( i != m_redraw_connections.end() )
    {
      // if we do, let's disconnect and remove the connection
      i->second.disconnect();
      m_redraw_connections.erase ( i );
    }

    // Let's find out if we have a changed signal connection
    i = m_changed_connections.find ( item );
    if ( i != m_changed_connections.end() )
    {
      // if we do, let's disconnect and remove the connection
      i->second.disconnect();
      m_changed_connections.erase ( i );
    }

    item->m_parent = NULL;

    this->invalidate_extents();
    
    m_signal_child_removed.emit ( item );

    this->redraw();

    return true;
  }

  bool Group::remove ( Drawable* object )
  {
    Layers::iterator ilayer;
    Layer::iterator ichild;

    // We must have a valid pointer
    if ( object == NULL )
      return false;

    // Let's look for the pointer and then call the remove method with the smart pointer
    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++ )
      {
        if ( ichild->get() == object )
          return this->remove ( *ichild );
      }
    }
    return false;
  }

  bool Group::clear()
  {
    Layers::iterator ilayer;
    Layer::iterator ichild;
    Connections::iterator iconn;

    while ( m_layers.size() > 0 )
      remove ( m_layers.begin()->second.front() );

    // Let's start by disconnecting all the child signals
    for (iconn = m_redraw_connections.begin(); iconn != m_redraw_connections.end(); iconn++) {
      iconn->second.disconnect();
    }
    m_redraw_connections.clear();
    
    for (iconn = m_changed_connections.begin(); iconn != m_changed_connections.end(); iconn++) {
      iconn->second.disconnect();
    }
    m_changed_connections.clear();
    
    // Now, let's clear the parent values in all the children
    for (ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++) {
      for (ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++) {
        (*ichild)->m_parent = NULL;
      }
    }

    // Set the size of the group to zero
    m_size = 0;

    // Before we emit any signals we need to clear the layers, but before we
    // clear the layers we need to make a copy. Otherwise the pointers could
    // all be released before we emit the signal.
    Layers temp_layers = m_layers;
    m_layers.clear();

    // Now, let's emit the removed signal for each child
    for (ilayer = temp_layers.begin(); ilayer != temp_layers.end(); ilayer++) {
      for (ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++) {
        m_signal_child_removed.emit(*ichild);
      }
    }

    this->invalidate_extents();
    this->redraw();
    return true;
  }

  Drawable::pointer Group::child(const Glib::ustring & id) const
  {
    Layers::const_iterator ilayer;
    Layer::const_reverse_iterator ichild;
  
    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( ichild = ilayer->second.rbegin(); ichild != ilayer->second.rend(); ichild++ )
      {
        if ( (*ichild)->id() == id ) return *ichild;
      }
    }

    return Drawable::pointer();
  }

  void Group::draw ( Context& cairo ) const
  {
    Layers::const_iterator ilayer;
    Layer::const_reverse_iterator ichild;

    if ( m_intermediate_drawing_enabled ) cairo->push_group();

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( ichild = ilayer->second.rbegin(); ichild != ilayer->second.rend(); ichild++ )
      {
        (*ichild)->render(cairo);
      }
    }

    if ( m_intermediate_drawing_enabled )
    {
      cairo->pop_group_to_source();
      cairo.paint();
    }
  }
  
  void Papyrus::Group::freeze_children()
  {
    Layers::const_iterator ilayer;
    Layer::const_reverse_iterator ichild;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( ichild = ilayer->second.rbegin(); ichild != ilayer->second.rend(); ichild++ )
      {
        (*ichild)->m_frozen_by_parent = true;
        if ( (*ichild)->is_group() )
        {
          Group::pointer child_group = papyrus_dynamic_pointer_cast<Group>(*ichild);
          child_group->freeze_children();
        }
      }
    }    
  }

  void Group::thaw_children(bool force_redraw)
  {
    Layers::const_iterator ilayer;
    Layer::const_reverse_iterator ichild;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( ichild = ilayer->second.rbegin(); ichild != ilayer->second.rend(); ichild++ )
      {
        (*ichild)->m_frozen_by_parent = false;
        if ( not (*ichild)->is_frozen() )
        {
          if ( (*ichild)->is_group() )
          {
            Group::pointer child_group = papyrus_dynamic_pointer_cast<Group>(*ichild);
            child_group->thaw_children(force_redraw);
          }
          if ( force_redraw or (*ichild)->m_need_redraw )
          {
            (*ichild)->redraw();
            (*ichild)->m_signal_changed.emit();
          }
        }
      }
    }    
  }

  void Group::on_child_redraw ( double x, double y, double w, double h, Drawable::pointer child )
  {
    Region region ( x, y, w, h );
    region.transform ( this->composed_matrix() );
    region.xywh ( x, y, w, h );
    m_signal_redraw.emit ( x, y, w, h );
  }

  bool Group::raise ( Drawable::pointer item, int steps )
  {
    Layers::iterator ilayer;
    Layer::iterator ichild1, ichild2;

    if ( steps < 0 ) return this->lower ( item, -steps );
    if ( steps == 0 ) return true;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      ichild2 = std::find ( ilayer->second.begin(), ilayer->second.end(), item );
      if ( ichild2 != ilayer->second.end() )
      {
        ichild1 = ichild2;
        for ( int i=0; i<steps && ichild1 != ilayer->second.begin(); i++ )
          ichild1--;
        ilayer->second.erase ( ichild2 );
        ilayer->second.insert ( ichild1, item );
        item->redraw();
        return true;
      }
    }
    return false;
  }

  bool Group::raise_to_top ( Drawable::pointer item )
  {
    Layers::iterator ilayer;
    Layer::iterator ichild;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      ichild = std::find ( ilayer->second.begin(), ilayer->second.end(), item );
      if ( ichild != ilayer->second.end() && ichild != ilayer->second.begin() )
      {
        ilayer->second.erase ( ichild );
        ilayer->second.push_front ( item );
        item->redraw();
        return true;
      }
    }
    return false;
  }

  bool Group::lower ( Drawable::pointer item, int steps )
  {
    Layers::iterator ilayer;
    Layer::iterator ichild1, ichild2;

    if ( steps < 0 ) return this->lower ( item, -steps );
    if ( steps == 0 ) return true;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      ichild2 = std::find ( ilayer->second.begin(), ilayer->second.end(), item );
      if ( ichild2 != ilayer->second.end() )
      {
        ichild1 = ichild2;
        for ( int i=0; i<steps+1 && ichild1 != ilayer->second.end(); i++ )
          ichild1++;
        ilayer->second.erase ( ichild2 );
        ilayer->second.insert ( ichild1, item );
        item->redraw();
        return true;
      }
    }
    return false;
  }

  bool Group::lower_to_bottom ( Drawable::pointer item )
  {
    Layers::iterator ilayer;
    Layer::iterator ichild;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      ichild = std::find ( ilayer->second.begin(), ilayer->second.end(), item );
      // is it in this layer?
      if ( ichild != ilayer->second.end() )
      {
        if ( ++ichild == ilayer->second.end() )
        {
          // it's already at the bottom... nothing to do
          return true;
        }
        else
        {
          --ichild; // decrement the iterator back to the item
          ilayer->second.erase ( Layer::iterator ( ichild ) );
          ilayer->second.push_back ( item );
          item->redraw();
          return true;
        }
      }
    }
    return false;
  }

  bool Group::move_to_layer ( int layer, Drawable::pointer item )
  {
    Layer::iterator ichild;

    for ( Layers::iterator ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      ichild = std::find ( ilayer->second.begin(), ilayer->second.end(), item );
      if ( ichild != ilayer->second.end() )
      {
        if ( ilayer->first == layer ) return true;
        ilayer->second.erase ( ichild );
        if ( ilayer->first > layer )
          m_layers[layer].push_front ( item );
        else
          m_layers[layer].push_back ( item );
        this->redraw();
        return true;
      }
    }

    return false;
  }

  bool Group::inside ( double x, double y )
  {
    Layers::iterator ilayer;
    
    // Transform the point in question by the CTM
    this->matrix().transform_point_inverse(x, y);

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( Layer::iterator ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++ )
        if ( (*ichild)->is_visible() and (*ichild)->inside(x, y) )
          return true;
    }
    return false;
  }

  Glib::ustring Group::svg(unsigned depth)
  {
    Glib::ustring s;
    
    s += svg_spacing(depth) + "<g " + svg_id() + " " + svg_transform();

    if ( m_fill ) s += m_fill->svg();
    
    s += ">\n";
    
    Layers::iterator ix;
    Layer::reverse_iterator iy;
    for (ix = m_layers.begin(); ix != m_layers.end(); ix++ )
    {
      for ( iy = ix->second.rbegin(); iy != ix->second.rend(); iy++ )
      {
        s += (*iy)->svg(depth+1);
      }
    }

    s += svg_spacing(depth) + "</g>\n";

    return s;
  }
  
  sigc::signal<void, Drawable::pointer>& Group::signal_child_added()
  {
    return m_signal_child_added;
  }

  sigc::signal<void, Drawable::pointer>& Group::signal_child_removed()
  {
    return m_signal_child_removed;
  }

  bool Group::is_group()
  {
    return true;
  }

  Fill::pointer Group::fill()
  {
    if ( m_fill ) return m_fill;
    if ( m_parent ) return m_parent->fill();
    return Fill::pointer();
  }

  void Group::set_fill ( Fill::pointer fill )
  {
    m_fill = fill;
    this->redraw();
  }

  void Group::set_fill ( Paint::pointer paint )
  {
    this->set_fill ( Fill::create ( paint ) );
  }

  void Group::set_fill( const RGBA& color )
  {
    Fill::pointer fill = color;
    this->set_fill( fill );
  }

  void Group::set_fill( const Glib::ustring& fill )
  {
    this->set_fill( Fill::create(fill) );
  }

  Stroke::pointer Group::stroke()
  {
    if ( m_stroke ) return m_stroke;
    if ( m_parent ) return m_parent->stroke();
    return Stroke::pointer();
  }

  void Group::set_stroke ( Stroke::pointer stroke )
  {
    m_stroke = stroke;
    this->redraw();
  }

  void Group::set_stroke ( Paint::pointer paint )
  {
    this->set_stroke ( Stroke::create ( paint ) );
  }

  void Group::set_stroke( const RGBA& color )
  {
    Stroke::pointer stroke = color;
    this->set_stroke(stroke);
  }
  
  void Group::set_stroke( const Glib::ustring& stroke )
  {
    this->set_stroke( Stroke::create(stroke) );
  }
  
  const PaintDictionary & Group::paint_dictionary() const
  {
    return m_paint_dictionary;
  }

  Paint::pointer Group::lookup_paint(const Glib::ustring & name) const
  {
    PaintDictionary::const_iterator i;
    i = m_paint_dictionary.find( name );
    if ( i != m_paint_dictionary.end() ) return i->second;
    if ( m_parent ) return m_parent->lookup_paint(name);
    return Paint::pointer();
  }

  void Group::add_paint_to_dictionary(const Glib::ustring & name, Paint::pointer paint)
  {
    if ( not paint ) return;
    m_paint_dictionary[name] = paint;
    m_signal_paint_added_to_dictionary.emit(name);
  }

  void Group::remove_paint_from_dictionary(const Glib::ustring& name)
  {
    PaintDictionary::iterator i;
    i = m_paint_dictionary.find( name );
    if ( i == m_paint_dictionary.end() ) return;
    m_paint_dictionary.erase(i);
    m_signal_paint_removed_from_dictionary.emit(name);
  }

  void Group::clear_paint_dictionary()
  {
    PaintDictionary::iterator i;
    for ( i = m_paint_dictionary.begin(); i != m_paint_dictionary.end(); i++ )
      m_signal_paint_removed_from_dictionary.emit(i->first);
    m_paint_dictionary.clear();
  }

  sigc::signal<void, const Glib::ustring& >& Group::signal_paint_added_to_dictionary()
  {
    return m_signal_paint_added_to_dictionary;
  }

  sigc::signal<void, const Glib::ustring& >& Group::signal_paint_removed_from_dictionary()
  {
    return m_signal_paint_removed_from_dictionary;
  }

  const DrawableDictionary& Group::drawable_dictionary() const
  {
    return m_drawable_dictionary;
  }

  Drawable::pointer Group::lookup_drawable( const Glib::ustring& name ) const
  {
    // Look in the dictionary
    DrawableDictionary::const_iterator i;
    i = m_drawable_dictionary.find( name );
    if ( i != m_drawable_dictionary.end() ) return i->second;

    // Look in the children
    Drawable::pointer c = this->child(name);
    if ( c ) return c;

    // Look to ancestors dictionaries and children
    if ( m_parent ) return m_parent->lookup_drawable(name);

    return Drawable::pointer();
  }
  
  void Group::add_drawable_to_dictionary( const Glib::ustring& name, Drawable::pointer d )
  {
    DrawableDictionary::iterator i;
    if ( not d ) return;
    m_drawable_dictionary[name] = d;
    d->m_parent = this;
    m_signal_drawable_added_to_dictionary.emit(name);
  }
  
  void Group::remove_drawable_from_dictionary( const Glib::ustring& name )
  {
    DrawableDictionary::iterator i;
    i = m_drawable_dictionary.find( name );
    if ( i == m_drawable_dictionary.end() ) return;
    m_drawable_dictionary.erase(i);
    m_signal_drawable_removed_from_dictionary.emit(name);
  }
  
  void Group::clear_drawable_dictionary()
  {
    DrawableDictionary::iterator i;
    for ( i = m_drawable_dictionary.begin(); i != m_drawable_dictionary.end(); i++ )
      m_signal_drawable_removed_from_dictionary.emit(i->first);
    m_drawable_dictionary.clear();
  }
  
  sigc::signal<void, const Glib::ustring& >& Group::signal_drawable_added_to_dictionary()
  {
    return m_signal_drawable_added_to_dictionary;
  }
  
  sigc::signal<void, const Glib::ustring& >& Group::signal_drawable_removed_from_dictionary()
  {
    return m_signal_drawable_removed_from_dictionary;
  }
  
  Selection Group::select ( double x, double y, unsigned depth )
  {
    Layers::iterator ilayer;
    std::vector<Drawable::pointer> result, intermediate;
    Group::pointer g;

    if ( depth == 0 ) return result;
    
    // transform the points according to the group
    // affine matrix and check each of the children
    this->matrix().transform_point_inverse( x, y );
    
    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( Layer::iterator ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++ )
      {
        if ( ( *ichild ) ->inside ( x, y ) )
        {
          if ( ( *ichild ) ->is_group() )
          {
            g = papyrus_dynamic_pointer_cast<Group> ( ( *ichild ) );
            if ( g->is_selectable() )
            {
              result.push_back ( g );
              depth--;
            }
            intermediate = g->select ( x, y, depth );
            result.insert ( result.end(), intermediate.begin(), intermediate.end() );
          }
          else
          {
            result.push_back ( *ichild );
            depth--;
          }
        }
        if ( depth == 0 )
          break;
      }
    }
    return result;
  }

  Region Group::calculate_extents(const Matrix& m, ExtentsPerformance ep) const
  {
    Region group_extents;
    Layers::const_iterator ilayer;

    for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
    {
      for ( Layer::const_iterator ichild = ilayer->second.begin(); ichild != ilayer->second.end(); ichild++ )
      {
        if ( ( *ichild )->exclude_from_extents() or not ( *ichild )->is_visible() )
          continue;

        Region child_extents;

        child_extents = (*ichild)->extents(m, ep);

        group_extents.include( child_extents );
      }
    }

    return group_extents;
  }

  void Group::on_child_changed ( Drawable::pointer child )
  {
    this->invalidate_extents();
  }

  size_t Group::size() const
  {
    return m_size;
  }

  const Group::Layers& Group::layers( ) const
  {
    return m_layers;
  }

  const Group::Layer& Group::layer ( int l ) const throw ( std::out_of_range )
  {
    Layers::const_iterator ilayer = m_layers.find ( l );
    if ( ilayer == m_layers.end() )
    {
      std::ostringstream sout;
      sout << "Papyrus::Group::layer() Group does not have requested layer "
      << l;
      throw std::out_of_range ( sout.str() );
    }
    return ilayer->second;
  }

  bool Group::has_layer ( int l )
  {
    if ( m_layers.find ( l ) == m_layers.end() ) return false;
    return true;
  }

  bool Group::has(Drawable::pointer d) const
  {
    Layers::const_iterator il;
    Layer::const_iterator id;

    for ( il = m_layers.begin(); il != m_layers.end(); il++ )
    {
      for ( id = il->second.begin(); id != il->second.end(); id++ )
      {
        if ( *id == d ) return true;
      }
    }
    return false;
  }

  void Group::on_child_changed_proxy(Drawable::pointer child)
  {
    this->on_child_changed(child);
  }

}


