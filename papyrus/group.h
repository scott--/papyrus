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
#ifndef PAPYRUSGROUP_H
#define PAPYRUSGROUP_H

#include <list>
#include <map>
#include <vector>

#include <papyrus/drawable.h>
#include <papyrus/fill.h>
#include <papyrus/rgba.h>
#include <papyrus/stroke.h>

/**
 * \page guide_group Groups
 *
 * A group is a container for ordered collections of shapes, with the shapes
 * at the top (front of the container) drawn last and the shapes at the
 * bottom drawn first (end of the container).
 *
 * The current implementation is very simplistic, and doesn't even try to
 * do anything smart like taking into account occlusion or anything else. Instead
 * all objects are simply drawn and it is left to cairo to take care of
 * efficiency. At the current time there are no plans to improve this behavior,
 * since it runs 'fast enough' for now.
 *
 * Groups are also useful since transforms upon the group are also applied
 * to the contained objects. Thus, scaling, translating or rotating a group
 * has the same effect as performing those operations upon each member of
 * the group.
 *
 * The following contains an example that adds several shapes to a group,
 * then rotates the entire group by 45 degrees counter-clockwise.
 *
 * \image html group.png "Group and shapes drawn by example code below"
 *
 * \dontinclude factory.cpp
 * \skip example_group
 * \until }
 *
 */

namespace Papyrus
{

  typedef std::vector<Drawable::pointer> Selection;

  /**
   * A group is a container for ordered collections of shapes, with the shapes
   * at the top (front of the container) drawn last and the shapes at the
   * bottom drawn first (end of the container).
   *
   * The current implementation is very simplistic, and doesn't even try to
   * do anything smart like taking into account occlusion or anything else. Instead
   * all objects are simply drawn and it is left to cairo to take care of
   * efficiency. At the current time there are no plans to improve this behavior,
   * since it runs 'fast enough' for now.
   *
   * Groups are also useful since transforms upon the group are also applied
   * to the contained objects. Thus, scaling, translating or rotating a group
   * has the same effect as performing those operations upon each member of
   * the group.
   *
   * \image html group.png "Group contain an ordered set of shapes"
   *
   * @author Rick L Vinyard Jr
   */
  class Group : public Drawable
  {
    protected:

      Group(const Glib::ustring& id=Glib::ustring());

      Group(const AttributeValueMap& avmap);

    public:
      PAPYRUS_DRAWABLE(Group);

      static pointer create(const Glib::ustring& id=Glib::ustring());

      static pointer create(const AttributeValueMap& avmap);

      /**
       * A layer is a list of child items.
       * The children are drawn starting with the last item in the
       * list, proceeding forward to the first item. Thus, the first
       * item in the list will be drawn on top of all 'lower' items.
       */
      typedef std::list<Drawable::pointer> Layer;

      /**
       * Layers are drawn starting for the lowest numbered
       * layer to the highest layer.
       */
      typedef std::map<int,Layer> Layers;

      friend class Canvas;

      virtual ~Group();

      const Glib::ustring& title() const;

      void set_title( const Glib::ustring& t );

      sigc::signal<void>& signal_title_changed();

      const Glib::ustring& description() const;

      void set_description( const Glib::ustring& d );

      sigc::signal<void>& signal_description_changed();
      
      /**
       * Reimplements Drawable::freeze() to also freeze children using the
       * m_frozen_by_parent flag
       */
      virtual void freeze();
      
      /**
       * Reimplements Drawable::thaw() to also thaw children using the
       * m_frozen_by_parent flag
       * 
       * @todo Thawing of children could be made more efficient by a group update
       */
      virtual void thaw(bool force_redraw=false);

      virtual bool is_intermediate_drawing_enabled();

      virtual void enable_intermediate_drawing(bool enabled=true);

      virtual void set( const AttributeValueMap& avmap );

      /**
       * Adds a child to a given layer.
       * Layer 0 is the default layer.
       * Layers are drawn from the most negative to the most positive. Thus,
       * layer 0 is on top of layer -1, and layer 1 is on top of layer 0.
       */
      virtual bool add( Drawable::pointer item, int layer=0 );

      /**
       * Removes the object from the group.
       */
      virtual bool remove( Drawable::pointer object );

      /**
       * The main purpose of this method is so that a child may use the
       * this pointer to remove itself on destruction.
       */
      virtual bool remove( Drawable* object );

      /**
       * Clears all layers and children from the group.
       */
      virtual bool clear();

      /**
       * Returns the first child named \e id or a null pointer if no child found
       *
       * @param id is case sensitive
       */
      Drawable::pointer child( const Glib::ustring& id ) const;

      /**
       * Returns the first child named \e id dynamically typecast to the template
       * parameter type or a null pointer of the template parameter type if no
       * child found of the requested type.
       *
       * This template form makes this possible:
       * \code
       * Group::pointer g = Group::create();
       * g->add( Rectangle::create( "my_rectangle", 100, 50 );
       * 
       * Rectangle rect;
       * rect = group->child\<Rectangle\>("my_rectangle");
       * \endcode
       */
      template <class T>
      PapyrusPointer<T> child( const Glib::ustring& id ) const
      {
        Layers::const_iterator ilayer;
        Layer::const_reverse_iterator ichild;
  
        for ( ilayer = m_layers.begin(); ilayer != m_layers.end(); ilayer++ )
        {
          for ( ichild = ilayer->second.rbegin(); ichild != ilayer->second.rend(); ichild++ )
          {
            if ( (*ichild)->id() == id )
            {
              PapyrusPointer<T> ptr;
              try {
                ptr = papyrus_dynamic_pointer_cast<T>(*ichild);
                return ptr;
              }
              catch ( std::bad_cast )
              {
              }
            }
          }
        }

        return PapyrusPointer<T>();
      }

      /**
       * Raises the item up n steps in its layer.
       * If steps < 0, the effect is a lower operation.
       */
      virtual bool raise( Drawable::pointer item, int steps=1 );

      /** Raises the item up to the top of its layer */
      virtual bool raise_to_top( Drawable::pointer item );

      /**
       * Lowers the item down n steps in its layer.
       * If steps < 0, the effect is a raise operation.
       */
      virtual bool lower( Drawable::pointer item, int steps=1 );
      
      /**
       * Lowers the item up to the bottom of its layer.
       * Returns true if the item is lowered or already at the bottom,
       * and false if the item cannot be found.
       */
      virtual bool lower_to_bottom( Drawable::pointer item );

      /**
       * Moves an item to a specific layer.
       * The item must already be in this group or no action will be taken.
       */
      virtual bool move_to_layer( int layer, Drawable::pointer item );

      /** Returns the number of children in the group */
      size_t size() const;

      /** Returns the layers in this group. */
      const Layers& layers() const;

      /**
       * Returns the requested layer l or throws std::out_of_range
       * if the layer doesn't exist.
       *
       * To avoid throwing an error, check has_layer() before calling.
       */
      const Layer& layer(int l) const throw (std::out_of_range);

      /** True if this group has layer l. */
      bool has_layer( int l );

      /** True if this group has the specified drawable in any layer */
      bool has( Drawable::pointer d ) const;

      /**
       * Overrides parent method for determining whether (x,y) is inside the drawable.
       * If the group itself is selectable, performs a simple extents test.
       * If the group is not selectable, performs a test on each of the children, returning
       * true if any of the children are selectable.
       */
      virtual bool inside( double x, double y );

      virtual Selection select( double x, double y, unsigned depth = 1 );

      sigc::signal<void, Drawable::pointer>& signal_child_added();

      sigc::signal<void, Drawable::pointer>& signal_child_removed();

      virtual bool is_group();

      /**
       * The default fill that is applied to all children derived from Shape.
       */
      Fill::pointer fill();

      /**
       * Sets the default fill for all children derived from Shape.
       * The fill is only applied to children that do not already have a fill.
       * The fill will be applied to all children contained by this group when this
       * method is called, and to all subsequent children added to the group.
       */
      void set_fill( Fill::pointer fill );

      void set_fill ( Paint::pointer paint );

      void set_fill( const RGBA& color );

      void set_fill( const Glib::ustring& fill );

      /**
       * The default stroke that is applied to all children derived from Shape.
       */
      Stroke::pointer stroke();

      /**
       * Sets the default stroke for all children derived from Shape.
       * The stroke is only applied to children that do not already have a stroke.
       * The stroke will be applied to all children contained by this group when this
       * method is called, and to all subsequent children added to the group.
       */
      void set_stroke( Stroke::pointer stroke );

      void set_stroke ( Paint::pointer paint );

      void set_stroke ( const RGBA& color );

      void set_stroke ( const Glib::ustring& stroke );

      /** Returns this group's paint dictionary */
      const PaintDictionary& paint_dictionary() const;

      /**
       * Lookup the named paint in the paint dictionary
       *
       * Looks in this group's paint dictionary plus any ancestor's dictionary
       */
      Paint::pointer lookup_paint( const Glib::ustring& name ) const;

      /** Adds or replaces the named paint in the paint dictionary */
      void add_paint_to_dictionary( const Glib::ustring& name, Paint::pointer p );

      /** Removes the named paint from the dictionary */
      void remove_paint_from_dictionary( const Glib::ustring& name );

      /** Clears all paints in the dictionary. Any children already set to a paint will retain their paints. */
      void clear_paint_dictionary();

      /** Signal emitted when a paint is added to the dictionary */
      sigc::signal<void, const Glib::ustring& >& signal_paint_added_to_dictionary();

      /** Signal emitted when a paint is removed from the dictionary */
      sigc::signal<void, const Glib::ustring& >& signal_paint_removed_from_dictionary();

      /** Returns this group's drawable dictionary */
      const DrawableDictionary& drawable_dictionary() const;

      /**
       * Lookup the named drawable
       *
       * Looks first in this drawable's dictionary. If nothing is found, looks through
       * children. If the name is still not found looks through ancestor's dictionaries
       * and children.
       */
      Drawable::pointer lookup_drawable( const Glib::ustring& name ) const;

      /** Adds or replaces the named drawable in the drawable dictionary */
      void add_drawable_to_dictionary( const Glib::ustring& name, Drawable::pointer p );

      /** Removes the named drawable from the dictionary */
      void remove_drawable_from_dictionary( const Glib::ustring& name );

      /**
       * Clears all drawables in the dictionary.
       *
       * Lookups can still succeed if the lookup name is a child or in an ancestor.
       */
      void clear_drawable_dictionary();

      /** Signal emitted when a drawable is added to the dictionary */
      sigc::signal<void, const Glib::ustring& >& signal_drawable_added_to_dictionary();

      /** Signal emitted when a drawable is removed from the dictionary */
      sigc::signal<void, const Glib::ustring& >& signal_drawable_removed_from_dictionary();

      virtual Glib::ustring svg(unsigned depth=0);

    protected:

      // maintaining both items as list for drawing order and connections for quick access
      Layers m_layers;
      size_t m_size;

      typedef std::map<Drawable::pointer, sigc::connection> Connections;
      Connections m_redraw_connections;
      Connections m_changed_connections;

      sigc::signal<void, Drawable::pointer> m_signal_child_added;
      sigc::signal<void, Drawable::pointer> m_signal_child_removed;

      Fill::pointer m_fill;
      Stroke::pointer m_stroke;

      PaintDictionary m_paint_dictionary;
      sigc::signal<void, const Glib::ustring& > m_signal_paint_added_to_dictionary;
      sigc::signal<void, const Glib::ustring& > m_signal_paint_removed_from_dictionary;

      DrawableDictionary m_drawable_dictionary;
      sigc::signal<void, const Glib::ustring& > m_signal_drawable_added_to_dictionary;
      sigc::signal<void, const Glib::ustring& > m_signal_drawable_removed_from_dictionary;

      Glib::ustring m_title;
      sigc::signal<void> m_signal_title_changed;

      Glib::ustring m_description;
      sigc::signal<void> m_signal_description_changed;

      bool m_intermediate_drawing_enabled;



      /**
       * Virtual method called when a child is changed.
       *
       * When a child is added, the child's changed signal is actually connected to the
       * private proxy method, which in turn calls the virtual method. This allows children
       * to implement their own behavior by reimplementing this method without worrying about
       * modifying the add() or remove() methods.
       */
      virtual void on_child_changed( Drawable::pointer child );

      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

      void on_child_redraw( double x, double y, double w, double h, Drawable::pointer child );
      
      virtual void draw( Context& cairo ) const;
      
      void freeze_children();
      
      void thaw_children(bool force_redraw=false);

    private:

      /**
       * When a child is added this is the actual method connected to the child's changed signal
       * and in turn this method calls the virtual method on_child_changed().
       */
      void on_child_changed_proxy( Drawable::pointer child );
      
  };

}

#endif
