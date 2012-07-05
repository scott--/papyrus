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
#include "grid.h"

namespace Papyrus
{

  const double Grid::infinity = 1.5e4;

  Grid::Grid ( const Glib::ustring& id, double xmin, double xmax, double ymin, double ymax ) :
      Drawable ( id ),
      m_x_min ( xmin ),
      m_x_max ( xmax ),
      m_y_min ( ymin ),
      m_y_max ( ymax ),
      m_x_interval ( 0.0 ),
      m_y_interval ( 0.0 ),
      m_enabled_axes ( X_AXIS | Y_AXIS ),
      m_enabled_borders ( 0 )
  {}

  Grid::pointer Grid::create ( double xmin, double xmax, double ymin, double ymax )
  {
    PAPYRUS_CREATE ( Grid ( Glib::ustring(), xmin, xmax, ymin, ymax ) );
  }

  Grid::pointer Grid::create ( const Glib::ustring& id, double xmin, double xmax, double ymin, double ymax )
  {
    PAPYRUS_CREATE ( Grid ( id, xmin, xmax, ymin, ymax ) );
  }

  Grid::~Grid()
  {}

  double Grid::x_min( )
  {
    return m_x_min;
  }

  void Grid::set_x_min ( double min )
  {
    m_x_min = min;
    this->redraw();
  }

  double Grid::x_max( )
  {
    return m_x_max;
  }

  void Grid::set_x_max ( double max )
  {
    m_x_max = max;
    this->redraw();
  }

  void Grid::x_min_max ( double & min, double & max )
  {
    min = m_x_min;
    max = m_x_max;
  }

  void Grid::set_x_min_max ( double min, double max )
  {
    m_x_min = min;
    m_x_max = max;
    this->redraw();
  }

  double Grid::y_min( )
  {
    return m_y_min;
  }

  void Grid::set_y_min ( double min )
  {
    m_y_min = min;
    this->redraw();
  }

  double Grid::y_max( )
  {
    return m_y_max;
  }

  void Grid::set_y_max ( double max )
  {
    m_y_max = max;
    this->redraw();
  }

  void Grid::y_min_max ( double & min, double & max )
  {
    min = m_y_min;
    max = m_y_max;
  }

  void Grid::set_y_min_max ( double min, double max )
  {
    m_y_min = min;
    m_y_max = max;
    this->redraw();
  }

  void Grid::xy_min_max ( double & x_min, double & x_max, double & y_min, double & y_max )
  {
    x_min = m_x_min;
    x_max = m_x_max;
    y_min = m_y_min;
    y_max = m_y_max;
  }

  void Grid::set_xy_min_max ( double x_min, double x_max, double y_min, double y_max )
  {
    m_x_min = x_min;
    m_x_max = x_max;
    m_y_min = y_min;
    m_y_max = y_max;
    this->redraw();
  }

  void Grid::enable_axis ( unsigned which )
  {
    unsigned int old_enabled = m_enabled_axes;
    m_enabled_axes |= which;
    if ( old_enabled != m_enabled_axes )
      this->redraw();
  }

  void Grid::disable_axis ( unsigned which )
  {
    unsigned int old_enabled = m_enabled_axes;
    m_enabled_axes &= ~which;
    if ( old_enabled != m_enabled_axes )
      this->redraw();
  }

  void Papyrus::Grid::set_xy_axis_stroke ( Stroke::pointer stroke )
  {
    m_y_axis_stroke = m_x_axis_stroke = stroke;
    this->redraw();
  }

  Stroke::pointer Papyrus::Grid::x_axis_stroke( ) const
  {
    return m_x_axis_stroke;
  }

  void Papyrus::Grid::set_x_axis_stroke ( Stroke::pointer stroke )
  {
    m_x_axis_stroke = stroke;
    this->redraw();
  }

  Stroke::pointer Grid::y_axis_stroke( ) const
  {
    return m_y_axis_stroke;
  }

  void Grid::set_y_axis_stroke ( Stroke::pointer stroke )
  {
    m_y_axis_stroke = stroke;
    this->redraw();
  }

  void Grid::draw ( Context& cairo ) const
  {
    double start, stop, current;

    // draw interval
    if ( m_x_interval_stroke and m_x_interval > 0.0 )
    {
      if ( m_x_min < 0.0 )
        start = ceil ( m_x_min / m_x_interval ) * m_x_interval;
      else
        start = floor ( m_x_min / m_x_interval ) * m_x_interval;
      if ( m_x_max < 0.0 )
        stop = ceil ( m_x_max / m_x_interval ) * m_x_interval;
      else
        stop = floor ( m_x_max / m_x_interval ) * m_x_interval;
      m_x_interval_stroke->render ( cairo );
      for ( current = start; current <= stop; current += m_x_interval )
      {
        cairo->move_to ( current, m_y_min );
        cairo->line_to ( current, m_y_max );
      }
      cairo.stroke();
    }

    if ( m_y_interval_stroke and m_y_interval > 0.0 )
    {
      if ( m_y_min < 0.0 )
        start = ceil ( m_y_min / m_y_interval ) * m_y_interval;
      else
        start = floor ( m_y_min / m_y_interval ) * m_y_interval;
      if ( m_y_max < 0.0 )
        stop = ceil ( m_y_max / m_y_interval ) * m_y_interval;
      else
        stop = floor ( m_y_max / m_y_interval ) * m_y_interval;
      m_y_interval_stroke->render ( cairo );
      for ( current = start; current <= stop; current += m_y_interval )
      {
        cairo->move_to ( m_x_min, current );
        cairo->line_to ( m_x_max, current );
      }
      cairo.stroke();
    }

    // draw axes
    if ( m_x_axis_stroke and m_enabled_axes & X_AXIS && m_x_min <= 0.0 && m_x_max >= 0.0 )
    {
      m_x_axis_stroke->render ( cairo );
      cairo->move_to ( 0.0, m_y_min );
      cairo->line_to ( 0.0, m_y_max );
      cairo.stroke();
    }

    if ( m_y_axis_stroke and m_enabled_axes & Y_AXIS && m_y_min <= 0.0 && m_y_max >= 0.0 )
    {
      m_y_axis_stroke->render ( cairo );
      cairo->move_to ( m_x_min, 0.0 );
      cairo->line_to ( m_x_max, 0.0 );
      cairo.stroke();
    }

    // draw borders
    if ( m_border_stroke[0] and m_enabled_borders & TOP )
    {
      m_border_stroke[0]->render ( cairo );
      cairo->move_to ( m_x_min, m_y_min );
      cairo->line_to ( m_x_max, m_y_min );
      // Stroke the line if we're not going to continue drawing in the same stroke
      if ( ! ( m_enabled_borders & RIGHT && m_border_stroke[1] == m_border_stroke[0] ) )
        cairo.stroke();
    }

    if ( m_border_stroke[1] and m_enabled_borders & RIGHT )
    {
      // Do we have a stroke change?
      if ( m_border_stroke[1] != m_border_stroke[0] )
        m_border_stroke[1]->render ( cairo );
      // Did we leave off at the right spot, or do we need to move to it?
      if ( ! m_enabled_borders & TOP )
        cairo->move_to ( m_x_max, m_y_min );
      cairo->line_to ( m_x_max, m_y_max );
      // Stroke the line if we're not going to continue drawing in the same stroke
      if ( ! ( m_enabled_borders & BOTTOM && m_border_stroke[2] == m_border_stroke[1] ) )
        cairo.stroke();
    }

    if ( m_border_stroke[2] and m_enabled_borders & BOTTOM )
    {
      // Do we have a stroke change?
      if ( m_border_stroke[2] != m_border_stroke[1] )
        m_border_stroke[2]->render ( cairo );
      // Did we leave off at the right spot, or do we need to move to it?
      if ( ! m_enabled_borders & RIGHT )
        cairo->move_to ( m_x_max, m_y_max );
      cairo->line_to ( m_x_min, m_y_max );
      // Stroke the line if we're not going to continue drawing in the same stroke
      if ( ! ( m_enabled_borders & LEFT && m_border_stroke[3] == m_border_stroke[2] ) )
        cairo.stroke();
    }

    if ( m_border_stroke[3] and m_enabled_borders & LEFT )
    {
      // Do we have a stroke change?
      if ( m_border_stroke[3] != m_border_stroke[2] )
        m_border_stroke[3]->render( cairo );
      // Did we leave off at the right spot, or do we need to move to it?
      if ( ! m_enabled_borders & BOTTOM )
        cairo->move_to ( m_x_min, m_y_max );
      cairo->line_to ( m_x_min, m_y_min );
      // Should we close the path and make it look nice?
      if ( m_enabled_borders & TOP and m_border_stroke[0] == m_border_stroke[3] )
        cairo->close_path();
      cairo.stroke();
    }

  }

  void Grid::enable_border ( unsigned which )
  {
    unsigned int old_enabled = m_enabled_borders;
    m_enabled_borders |= which;
    if ( old_enabled != m_enabled_borders )
      this->redraw();
  }

  void Grid::disable_border ( unsigned which )
  {
    unsigned int old_enabled = m_enabled_borders;
    m_enabled_borders &= ~which;
    if ( old_enabled != m_enabled_borders )
      this->redraw();
  }

  void Grid::set_border_stroke ( Stroke::pointer stroke, unsigned which )
  {
    if ( which & TOP )
      m_border_stroke[ 0 ] = stroke;
    if ( which & RIGHT )
      m_border_stroke[ 1 ] = stroke;
    if ( which & BOTTOM )
      m_border_stroke[ 2 ] = stroke;
    if ( which & LEFT )
      m_border_stroke[ 3 ] = stroke;
  }

  double Grid::x_interval( )
  {
    return m_x_interval;
  }

  void Grid::set_x_interval ( double x_interval )
  {
    m_x_interval = x_interval;
    this->redraw();
  }

  Stroke::pointer Grid::x_interval_stroke( )
  {
    return m_x_interval_stroke;
  }

  void Grid::set_x_interval_stroke ( Stroke::pointer stroke )
  {
    m_x_interval_stroke = stroke;
    this->redraw();
  }

  double Grid::y_interval( )
  {
    return m_y_interval;
  }

  void Grid::set_y_interval ( double y_interval )
  {
    m_y_interval = y_interval;
    this->redraw();
  }

  Stroke::pointer Grid::y_interval_stroke( )
  {
    return m_y_interval_stroke;
  }

  void Grid::set_y_interval_stroke ( Stroke::pointer stroke )
  {
    m_y_interval_stroke = stroke;
    this->redraw();
  }

  void Grid::xy_interval ( double & x_interval, double & y_interval )
  {
    x_interval = m_x_interval;
    y_interval = m_y_interval;
  }

  void Grid::set_xy_interval ( double interval )
  {
    m_x_interval = m_y_interval = interval;
    this->redraw();
  }

  void Grid::set_xy_interval ( double x_interval, double y_interval )
  {
    m_x_interval = x_interval;
    m_y_interval = y_interval;
    this->redraw();
  }

  void Grid::xy_interval_stroke ( Stroke::pointer x_stroke, Stroke::pointer y_stroke )
  {
    x_stroke = m_x_interval_stroke;
    y_stroke = m_y_interval_stroke;
  }

  void Grid::set_xy_interval_stroke ( Stroke::pointer stroke )
  {
    m_x_interval_stroke = m_y_interval_stroke = stroke;
    this->redraw();
  }

  void Grid::set_xy_interval_stroke ( Stroke::pointer x_stroke, Stroke::pointer y_stroke )
  {
    m_x_interval_stroke = x_stroke;
    m_y_interval_stroke = y_stroke;
    this->redraw();
  }

}
