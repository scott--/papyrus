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
#include "canvas.h"

#include <cstdlib>
#include <math.h>

#include <iostream>

#include <assert.h>

namespace Papyrus
{

  Canvas::Canvas ( const Glib::ustring& id, double width, double height, double scale ) :
      Group ( id ),
      m_width ( width ),
      m_height ( height ),
      m_scale ( scale ),
      m_scroll_anchor ( SCROLL_ANCHOR_CENTER ),
      m_scroll_x(0.0),
      m_scroll_y(0.0),
      m_units( UNIT_PIXEL ),
      m_display_x_resolution( 96.0 ),
      m_display_y_resolution( 96.0 )
  {
    // Ensures that compositing against the background is done correctly
    m_intermediate_drawing_enabled = true;
    
    if ( m_scale < 0.0 ) m_scale = 0.0;
    this->update_scroll_anchor_offsets();
  }

  Canvas::pointer Canvas::create ( double width, double height, double scale )
  {
    PAPYRUS_CREATE ( Canvas ( Glib::ustring(), width, height, scale ) );
  }

  Canvas::pointer Canvas::create ( const Glib::ustring& id, double width, double height, double scale )
  {
    PAPYRUS_CREATE ( Canvas ( id, width, height, scale ) );
  }

  Canvas::~Canvas()
  {}

  double Canvas::width( ) const
  {
    return m_width;
  }

  double Canvas::height( ) const
  {
    return m_height;
  }

  void Canvas::size ( double & width, double & height ) const
  {
    width = m_width;
    height = m_height;
  }

  void Canvas::set_width ( double width )
  {
    m_width = width;
    this->update_scroll_anchor_offsets();
    this->invalidate_extents();
    m_signal_size_changed.emit();
    this->redraw();
  }

  void Canvas::set_height ( double height )
  {
    m_height = height;
    this->update_scroll_anchor_offsets();
    this->invalidate_extents();
    m_signal_size_changed.emit();
    this->redraw();
  }

  void Canvas::set_size ( double width, double height )
  {
    m_width = width;
    m_height = height;
    this->update_scroll_anchor_offsets();
    this->invalidate_composed_matrix();
    m_signal_size_changed.emit();
    this->redraw();
  }

  Units Canvas::units() const
  {
    return m_units;
  }

  void Canvas::set_units( Units u )
  {
    m_units = u;
    this->invalidate_extents();
    m_signal_units.emit(u);
    this->redraw();
  }

  void Canvas::device_resolution( double& x, double& y ) const
  {
    x = m_display_x_resolution;
    y = m_display_y_resolution;
  }

  bool Canvas::set_device_resolution( double x, double y )
  {
    if ( x <= 0.0 || y <= 0.0 )
      return false;
    m_display_x_resolution = x;
    m_display_y_resolution = y;
    this->invalidate_extents();
    m_signal_display_resolution.emit(x, y);
    this->redraw();
    return true;
  }

  Paint::pointer Canvas::background() const
  {
    return m_background;
  }

  void Canvas::set_background ( Paint::pointer background )
  {
    m_background = background;
    this->redraw();
  }

  void Canvas::scroll_to ( double x, double y )
  {
    m_scroll_x = x;
    m_scroll_y = y;
    this->invalidate_composed_matrix();
    m_signal_scrolled.emit( m_scroll_x, m_scroll_y );
    this->redraw();
  }

  void Canvas::scroll_to_x ( double x )
  {
    m_scroll_x = x;
    this->invalidate_composed_matrix();
    m_signal_scrolled.emit( m_scroll_x, m_scroll_y );
    this->redraw();
  }

  void Canvas::scroll_to_y ( double y )
  {
    m_scroll_y = y;
    this->invalidate_composed_matrix();
    m_signal_scrolled.emit( m_scroll_x, m_scroll_y );
    this->redraw();
  }

  void Canvas::scroll_to_center( )
  {
    this->scroll_to( 0.0, 0.0 );
  }

  void Canvas::scroll_position ( double& x, double& y ) const
  {
    x = m_scroll_x;
    y = m_scroll_y;
  }

  double Canvas::scroll_x() const
  {
    return m_scroll_x;
  }

  double Canvas::scroll_y() const
  {
    return m_scroll_y;
  }

  void Canvas::set_scroll_anchor ( ScrollAnchor scroll_anchor )
  {
    if ( scroll_anchor == m_scroll_anchor ) return ;

    m_scroll_anchor = scroll_anchor;
    this->invalidate_composed_matrix();
    m_signal_scroll_anchor_changed.emit( m_scroll_anchor );
    this->redraw();
  }

  ScrollAnchor Canvas::scroll_anchor( ) const
  {
    return m_scroll_anchor;
  }

  void Canvas::scroll_anchor_offsets(double & x, double & y) const
  {
    x = m_scroll_anchor_offset_x;
    y = m_scroll_anchor_offset_y;
  }

  double Canvas::scroll_anchor_x_offset() const
  {
    return m_scroll_anchor_offset_x;
  }

  double Canvas::scroll_anchor_y_offset() const
  {
    return m_scroll_anchor_offset_y;
  }

  void Canvas::window_to_canvas ( double& x, double& y ) const
  {
    cairo_matrix_t inverse = this->composed_matrix();
    cairo_matrix_invert ( &inverse );
    cairo_matrix_transform_point ( &inverse, &x, &y );
  }

  void Canvas::canvas_to_window ( double& x, double& y ) const
  {
    cairo_matrix_t m = this->composed_matrix();
    cairo_matrix_transform_point ( &m, &x, &y );
  }

  Selection Canvas::select ( double x, double y, unsigned depth )
  {
    Layers::iterator ilayer;
    std::vector<Drawable::pointer> result, intermediate;
    Group::pointer g;

    if ( depth == 0 ) return result;
    
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

  sigc::signal<void> Canvas::signal_size_changed()
  {
    return m_signal_size_changed;
  }

  sigc::signal<void,Units> Canvas::signal_units()
  {
    return m_signal_units;
  }

  sigc::signal<void,double,double> Canvas::signal_display_resolution()
  {
    return m_signal_display_resolution;
  }

  sigc::signal< void, double, double > Canvas::signal_scrolled()
  {
    return m_signal_scrolled;
  }

  sigc::signal< void, ScrollAnchor > Canvas::signal_scroll_anchor_changed()
  {
    return m_signal_scroll_anchor_changed;
  }

  void Canvas::draw ( Context& cairo ) const
  {
    if ( m_background )
    {
      m_background->render( cairo );
      cairo.paint();
    }
    
    Group::draw ( cairo );
  }

  Matrix Canvas::global_matrix() const
  {
    if ( m_parent )
      return m_parent->global_matrix() * Drawable::calculate_composed_matrix();
    else
      return Drawable::calculate_composed_matrix();
  }

  Region Canvas::global_extents() const
  {
    Matrix m;
    
    if ( m_parent ) m = m_parent->global_matrix();

    m *= Drawable::calculate_composed_matrix();

    Region r;

    r = this->calculate_extents( m );

    return r;
  }

  Region Canvas::anchor_extents() const
  {
    double l, r, t, b;

    l = 0.0 - m_scroll_anchor_offset_x;
    r = m_width - m_scroll_anchor_offset_x;
    t = 0.0 - m_scroll_anchor_offset_y;
    b = m_height - m_scroll_anchor_offset_y;

    Region ve;
    ve.set_lrtb( l, r, t, b );
    return ve;
  }

  Matrix Canvas::calculate_composed_matrix( ) const
  {
    Matrix m;
    
    m.set_identity();
    
    m.translate( m_scroll_anchor_offset_x-m_scroll_x, m_scroll_anchor_offset_y-m_scroll_y );

    m.translate( x() + centroid_x(), y() + centroid_y() );
    m.rotate( get_rotation() );
    m.translate( -centroid_x(), -centroid_y() );
    m.skew( get_skew_x(), get_skew_y() );
    m.scale( get_scale_x(), get_scale_y() );

    this->apply_external_matrices( m );

    return m;

//     switch ( m_units )
//     {
//       case UNIT_PIXEL:
//         // In this case, we'll have a no-op
//         break;
//       case UNIT_POINTS:
//         m_matrix.scale( m_display_x_resolution / 72.0, m_display_y_resolution / 72.0 );
//         break;
//       case UNIT_INCH:
//         m_matrix.scale( m_display_x_resolution, m_display_y_resolution );
//         break;
//       case UNIT_MM:
//         m_matrix.scale( m_display_x_resolution / 25.4, m_display_y_resolution / 25.4 );
//         break;
//     }
  }

  void Canvas::update_scroll_anchor_offsets( )
  {
    switch ( m_scroll_anchor )
    {
      case SCROLL_ANCHOR_CENTER:
        m_scroll_anchor_offset_x = m_width / 2.0;
        m_scroll_anchor_offset_y = m_height / 2.0;
        break;
      case SCROLL_ANCHOR_TOP_LEFT:
        m_scroll_anchor_offset_x = 0.0;
        m_scroll_anchor_offset_y = 0.0;
        break;
      case SCROLL_ANCHOR_TOP_RIGHT:
        m_scroll_anchor_offset_x = m_width;
        m_scroll_anchor_offset_y = 0.0;
        break;
      case SCROLL_ANCHOR_BOTTOM_LEFT:
        m_scroll_anchor_offset_x = 0.0;
        m_scroll_anchor_offset_y = m_height;
        break;
      case SCROLL_ANCHOR_BOTTOM_RIGHT:
        m_scroll_anchor_offset_x = m_width;
        m_scroll_anchor_offset_y = m_height;
        break;
    }
  }

//   void Canvas::calculate_raw_extents()
//   {
//     this->set_extents(0.0, 0.0, m_width, m_height);
//   }

}



