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
#include "shape.h"
#include "group.h"

#include <iostream>

namespace Papyrus
{

  Shape::Shape ( const Glib::ustring& id, Fill::pointer fill, Stroke::pointer stroke ) :
      Drawable ( id ),
      m_fill ( fill ),
      m_stroke ( stroke ),
      m_fill_path ( NULL ),
      m_stroke_path ( NULL )
  {
    if ( m_fill )
      m_fill_changed_connection = m_fill->signal_changed().connect ( sigc::mem_fun ( *this, &Shape::on_fill_changed ) );
    if ( m_stroke )
      m_stroke_changed_connection = m_stroke->signal_changed().connect ( sigc::mem_fun ( *this, &Shape::on_stroke_changed ) );
  }

  Shape::~Shape()
  {
    if ( m_fill_path )
      delete m_fill_path;
    if ( m_stroke_path )
      delete m_stroke_path;
  }

  void Shape::set( const AttributeValueMap& avmap )
  {
    Drawable::set( avmap );
    
    AttributeValueMap::const_iterator i;
    double stroke_width = -1.0;

    for ( i = avmap.begin(); i != avmap.end(); i++ )
    {
      if      ( strcaseeq( i->first, "fill" ) )         this->set_fill( i->second );
      else if ( strcaseeq( i->first, "stroke" ) )       this->set_stroke( i->second );
      else if ( strcaseeq( i->first, "stroke-width" ) ) stroke_width = atof( i->second.c_str() );
    }

    if ( stroke_width >= 0.0 )
    {
      if ( m_stroke ) m_stroke->set_width( stroke_width );
      else this->set_stroke( Stroke::create(Paint::pointer(),stroke_width) );
    }

  }

  void Shape::draw ( Context& cairo ) const
  {
    Fill::pointer fill;
    Stroke::pointer stroke;

    fill = m_fill;
    if ( (not fill) and m_parent ) fill = m_parent->fill();

    if ( fill )
    {
      if ( !m_fill_path )
      {
        this->draw_shape ( cairo );
        m_fill_path = cairo->copy_path();
      }
      else
        cairo->append_path ( *m_fill_path );

      fill->render ( cairo );
      cairo.fill();
    }

    stroke = m_stroke;
    if ( (not m_stroke) and m_parent ) stroke = m_parent->stroke();
    
    if ( stroke )
    {
      if ( !m_stroke_path )
      {
        this->draw_stroke_path ( cairo );
        m_stroke_path = cairo->copy_path();
      }
      else
        cairo->append_path ( *m_stroke_path );

      stroke->render ( cairo );
      cairo.stroke();
    }

    if ( not fill and not stroke )
    {
      this->draw_shape( cairo );
    }
  }

  void Shape::draw_stroke_path ( Context& cairo ) const
  {
    this->draw_shape ( cairo );
  }

  Fill::pointer Shape::fill( )
  {
    return m_fill;
  }

  void Shape::set_fill ( Fill::pointer fill )
  {
    m_fill_changed_connection.disconnect();

    m_fill = fill;

    if ( m_fill )
      m_fill_changed_connection = m_fill->signal_changed().connect ( sigc::mem_fun ( *this, &Shape::on_fill_changed ) );

    this->on_fill_changed();
  }

  void Shape::set_fill ( Paint::pointer paint )
  {
    this->set_fill ( Fill::create ( paint ) );
  }

  void Shape::set_fill ( Cairo::RefPtr<Cairo::Pattern> pattern )
  {
    this->set_fill ( Fill::create ( pattern ) );
  }

  void Shape::set_fill( const RGBA& color )
  {
    this->set_fill( Fill::create(color) );
  }

  void Shape::set_fill( const Glib::ustring& fill )
  {
    const Glib::ustring pattern = "(?i:url\\s*\\(\\s*\\#\\s*(\\w+)\\s*\\)(?:\\s*[|]\\s*(\\w+))?)";

    if ( Glib::Regex::match_simple( pattern, fill ) )
    {
      bool use_secondary_paint = false;
      std::vector<Glib::ustring> split_results = Glib::Regex::split_simple( pattern, fill );
      if ( m_parent )
      {
        Paint::pointer paint = m_parent->lookup_paint( split_results[1] );
        if ( paint )
        {
          this->set_fill( Fill::create(paint) );
        }
        else
        {
          use_secondary_paint = true;
        }
      }
      else
      {
        use_secondary_paint = true;
      }
      if ( use_secondary_paint )
      {
        if ( split_results.size() == 4 )
          this->set_fill( Fill::create( split_results[2] ) );
        else
          this->set_fill( Fill::create("none") );
      }
    }
    else
    {
      this->set_fill( Fill::create(fill) );
    }
  }

  void Shape::set_fill_paint(const Glib::ustring & paint_name)
  {
    if ( not m_parent ) return;
    Paint::pointer paint = m_parent->lookup_paint( paint_name );
    if ( not paint ) return;
    if ( not m_fill ) this->set_fill( Fill::create(paint) );
    else m_fill->set_paint(paint);
  }

  Stroke::pointer Shape::stroke()
  {
    return m_stroke;
  }

  void Shape::set_stroke ( Stroke::pointer stroke )
  {
    m_stroke_changed_connection.disconnect();

    m_stroke = stroke;

    if ( m_stroke )
      m_stroke_changed_connection = m_stroke->signal_changed().connect ( sigc::mem_fun ( *this, &Shape::on_stroke_changed ) );

    this->on_stroke_changed();
  }

  void Shape::set_stroke ( Paint::pointer paint )
  {
    this->set_stroke ( Stroke::create ( paint ) );
  }

  void Shape::set_stroke ( Cairo::RefPtr<Cairo::Pattern> pattern )
  {
    this->set_stroke ( Stroke::create ( pattern ) );
  }

  void Shape::set_stroke( const RGBA& color )
  {
    this->set_stroke( Stroke::create(color) );
  }
  
  void Shape::set_stroke( const Glib::ustring& stroke )
  {
    this->set_stroke( Stroke::create(stroke) );
  }
  
  void Shape::set_stroke_paint(const Glib::ustring & paint_name)
  {
    if ( not m_parent ) return;
    Paint::pointer paint = m_parent->lookup_paint( paint_name );
    if ( not paint ) return;
    if ( not m_stroke ) this->set_stroke( Stroke::create(paint) );
    else m_stroke->set_paint(paint);
  }

  void Shape::operator =(const Shape & other)
  {
    m_fill = other.m_fill;
    m_stroke = other.m_stroke;
    if ( m_fill_path ) delete m_fill_path;
    m_fill_path = NULL;
    if ( m_stroke_path ) delete m_stroke_path;
    m_stroke_path = NULL;
  }

  void Shape::on_fill_changed()
  {
    this->redraw();
  }

  void Shape::on_stroke_changed()
  {
    this->invalidate_extents();
    this->redraw();
  }

  void Shape::shape_changed ( unsigned which )
  {
    this->invalidate_extents();
    if ( which & FILL )
    {
      delete m_fill_path;
      m_fill_path = NULL;
    }
    if ( which & STROKE )
    {
      delete m_stroke_path;
      m_stroke_path = NULL;
    }
    this->redraw();
  }

  Glib::ustring Shape::svg_fill()
  {
    if ( m_fill )
      return m_fill->svg();
    return Glib::ustring();
  }

}


