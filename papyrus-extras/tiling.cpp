/***************************************************************************
 *   Copyright (C) 2004,2009 by Rick L. Vinyard, Jr.                       *
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
#include "tiling.h"

#include <cmath>

#include <papyrus/group.h>

#define m_FILL(__column,__row) m_fill[__row*m_columns+__column]
#define m_FILL_CHANGED_CONNECTION(__column,__row) m_fill_changed_connection[__row*m_columns+__column]

namespace Papyrus
{

  Tiling::Tiling ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length ):
      Drawable(id),
      m_rows(rows),
      m_columns(columns),
      m_side_length(side_length),
      m_fill(NULL),
      m_fill_changed_connection(NULL)
  {
    if ( m_rows > 0 and m_columns > 0 )
    {
      m_fill = (Fill::pointer**)(calloc( m_rows * m_columns, sizeof(Fill::pointer) ) );
      m_fill_changed_connection = (sigc::connection**)(calloc(m_rows * m_columns, sizeof(Fill::pointer) ) );
    }
  }

  Tiling::~ Tiling()
  {
    if ( m_fill )
    {
      for ( size_t i = 0; i < m_rows * m_columns; i++ )
        if ( m_fill[i] != NULL ) delete m_fill[i];
      free( m_fill );
    }
    if ( m_fill_changed_connection )
    {
      for ( size_t i = 0; i < m_rows * m_columns; i++ )
        if ( m_fill_changed_connection[i] != NULL ) delete m_fill_changed_connection[i];
      free(m_fill_changed_connection);
    }
  }

  unsigned Tiling::rows() const
  {
    return m_rows;
  }

  void Tiling::set_rows ( unsigned r )
  {
    if ( m_rows == r ) return;
    m_rows = r;
    this->freeze();
    this->update_centroid_x();
    this->shape_changed();
    this->thaw();
  }

  unsigned Tiling::columns() const
  {
    return m_columns;
  }

  void Tiling::set_columns ( unsigned c )
  {
    if ( m_columns == c ) return;
    m_columns = c;
    this->freeze();
    this->update_centroid_y();
    this->shape_changed();
    this->thaw();
  }

  void Tiling::set_columns_rows ( unsigned c, unsigned r )
  {
    if ( m_columns == c )
    {
      this->set_rows(r);
      return;
    }
    else if ( m_rows == r )
    {
      this->set_columns(c);
      return;
    }
    
    m_rows = r;
    m_columns = c;
    this->freeze();
    this->update_centroid();
    this->shape_changed();
    this->thaw();
  }

  double Tiling::side_length() const
  {
    return m_side_length;
  }

  void Tiling::set_side_length ( double l )
  {
    m_side_length = l;
    if ( m_side_length < 0.0 ) m_side_length = 0.0;
    this->freeze();
    this->update_centroid();
    this->shape_changed();
    this->thaw();
  }

  Fill::pointer Tiling::fill ( unsigned column, unsigned row )
  {
    if ( column >= m_columns or row >= m_rows ) return Fill::pointer();
    
    Fill::pointer* f = m_FILL(column,row);
    
    if ( f == NULL ) return Fill::pointer();
    return *f;
  }

  void Tiling::set_fill ( Fill::pointer fill, unsigned column, unsigned row )
  {
    // Are the column/row parameters out of bounds?
    if ( column >= m_columns or row >= m_rows ) return;
    
    // No matter what, if we were connected to a fill before, we will disconnect now
    if ( m_FILL_CHANGED_CONNECTION(column,row) ) m_FILL_CHANGED_CONNECTION(column,row)->disconnect();
    
    // If this is a null fill we need to delete the previous connection
    // and fill pointer then redraw and return
    if ( not fill )
    {
      if ( m_FILL_CHANGED_CONNECTION(column,row) ) delete m_FILL_CHANGED_CONNECTION(column,row);
      if ( m_FILL(column,row) ) delete m_FILL(column,row);
      this->on_fill_changed(column, row);
      return;
    }
    
    // But, if we made it here we have a valid fill
    
    // We need to make sure we have a connection object and fill pointer
    if ( m_FILL_CHANGED_CONNECTION(column,row) == NULL ) m_FILL_CHANGED_CONNECTION(column,row) = new sigc::connection();
    if ( m_FILL(column,row) == NULL ) m_FILL(column,row) = new Fill::pointer();
    
    // Now let's set the fill object
    *(m_FILL(column,row)) = fill;
    
    *(m_FILL_CHANGED_CONNECTION(column,row)) = 
      fill->signal_changed().connect ( sigc::bind(sigc::mem_fun(*this, &Tiling::on_fill_changed),column,row) );

    this->on_fill_changed(column, row);
  }

  void Tiling::set_fill ( Paint::pointer paint, unsigned column, unsigned row )
  {
    this->set_fill( Fill::create(paint), column, row );
  }

  void Tiling::set_fill ( Cairo::RefPtr< Cairo::Pattern > pattern, unsigned column, unsigned row )
  {
    this->set_fill( Fill::create(pattern), column, row );
  }

  void Tiling::set_fill ( const RGBA & color, unsigned column, unsigned row )
  {
    this->set_fill( Fill::create(color), column, row );
  }

  void Tiling::set_fill ( const Glib::ustring & fill, unsigned column, unsigned row )
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
          this->set_fill( Fill::create(paint), column, row );
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
          this->set_fill( Fill::create( split_results[2] ), column, row );
        else
          this->set_fill( Fill::create("none"), column, row );
      }
    }
    else
    {
      this->set_fill( Fill::create(fill), column, row );
    }
  }

  void Tiling::set_fill_paint ( const Glib::ustring & paint_name, unsigned column, unsigned row )
  {
    if ( not m_parent ) return;
    Paint::pointer paint = m_parent->lookup_paint( paint_name );
    if ( not paint ) return;
    
    Fill::pointer f = this->fill( column, row );
    if ( not f )
      this->set_fill( Fill::create(paint), column, row );
    else 
      f->set_paint(paint);
  }

  Fill::pointer Tiling::fill()
  {
    return m_default_fill;
  }

  void Tiling::set_fill ( Fill::pointer fill )
  {
    m_default_fill_changed_connection.disconnect();

    m_default_fill = fill;

    if ( m_default_fill )
      m_default_fill_changed_connection = 
          m_default_fill->signal_changed().connect ( sigc::mem_fun ( *this, &Tiling::on_default_fill_changed ) );

    this->on_default_fill_changed();
  }

  void Tiling::set_fill ( Paint::pointer paint )
  {
    this->set_fill( Fill::create(paint) );
  }

  void Tiling::set_fill ( Cairo::RefPtr< Cairo::Pattern > pattern )
  {
    this->set_fill( Fill::create(pattern) );
  }

  void Tiling::set_fill ( const RGBA & color )
  {
    this->set_fill( Fill::create(color) );
  }

  void Tiling::set_fill ( const Glib::ustring & fill )
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

  void Tiling::set_fill_paint ( const Glib::ustring & paint_name )
  {
    if ( not m_parent ) return;
    Paint::pointer paint = m_parent->lookup_paint( paint_name );
    if ( not paint ) return;
    if ( not m_default_fill ) this->set_fill( Fill::create(paint) );
    else m_default_fill->set_paint(paint);
  }

  Stroke::pointer Tiling::stroke()
  {
    return m_stroke;
  }

  void Tiling::set_stroke ( Stroke::pointer stroke )
  {
    m_stroke_changed_connection.disconnect();

    m_stroke = stroke;

    if ( m_stroke )
      m_stroke_changed_connection = m_stroke->signal_changed().connect ( sigc::mem_fun ( *this, &Tiling::on_stroke_changed ) );

    this->on_stroke_changed();
  }

  void Tiling::set_stroke ( Paint::pointer paint )
  {
    this->set_stroke ( Stroke::create ( paint ) );
  }

  void Tiling::set_stroke ( Cairo::RefPtr< Cairo::Pattern > pattern )
  {
    this->set_stroke ( Stroke::create ( pattern ) );
  }

  void Tiling::set_stroke ( const RGBA & color )
  {
    this->set_stroke( Stroke::create(color) );
  }

  void Tiling::set_stroke ( const Glib::ustring & stroke )
  {
    this->set_stroke( Stroke::create(stroke) );
  }

  void Tiling::set_stroke_paint ( const Glib::ustring & paint_name )
  {
    if ( not m_parent ) return;
    Paint::pointer paint = m_parent->lookup_paint( paint_name );
    if ( not paint ) return;
    if ( not m_stroke ) this->set_stroke( Stroke::create(paint) );
    else m_stroke->set_paint(paint);
  }

  void Tiling::on_default_fill_changed()
  {
    this->redraw();
  }

  void Tiling::on_fill_changed(unsigned column, unsigned row)
  {
    this->redraw();
  }

  void Tiling::on_stroke_changed()
  {
    this->invalidate_extents();
    this->redraw();
  }

  void Tiling::shape_changed()
  {
    this->invalidate_extents();
//     delete m_path;
    this->redraw();
  }

}

