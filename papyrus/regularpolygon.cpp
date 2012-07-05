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
#include "regularpolygon.h"

#include <cmath>

namespace Papyrus
{

  RegularPolygon::RegularPolygon ( const Glib::ustring& id,
                                   unsigned int sides,
                                   double radius,
                                   Style style,
                                   Fill::pointer fill,
                                   Stroke::pointer stroke )
      : Polygon ( id, Vertices(), fill, stroke ),
      m_sides ( sides ),
      m_style ( style )
  {
    m_radius = fabs ( radius );

    this->create_vertices();
  }

  RegularPolygon::pointer RegularPolygon::create ( unsigned int sides,
          double radius,
          Style style,
          Fill::pointer fill,
          Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( RegularPolygon ( Glib::ustring(), sides, radius, style, fill, stroke ) );
  }

  RegularPolygon::pointer RegularPolygon::create ( const Glib::ustring& id,
          unsigned int sides,
          double radius,
          Style style,
          Fill::pointer fill,
          Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( RegularPolygon ( id, sides, radius, style, fill, stroke ) );
  }

  RegularPolygon::~RegularPolygon() {}

  unsigned int RegularPolygon::sides( )
  {
    return m_sides;
  }

  void RegularPolygon::set_sides ( unsigned int s )
  {
    if ( s < 3 )
      return;

    m_sides = s;
    create_vertices();
    m_signal_sides.emit();
  }

  double RegularPolygon::radius( )
  {
    return m_radius;
  }

  void RegularPolygon::set_radius ( double r )
  {
    m_radius = fabs ( r );
    create_vertices();
    m_signal_size.emit();
  }

  void RegularPolygon::set_sides_radius ( unsigned int s, double r )
  {
    if ( s >= 3 )
    {
      m_sides = s;
    }
    m_radius = fabs ( r );
    create_vertices();
    m_signal_sides.emit();
    m_signal_size.emit();
  }

  double RegularPolygon::edge_length( )
  {
    double angle, edge;
    angle = M_PI / m_sides;
    edge = sin ( angle ) * m_radius * 2.0;
    return edge;
  }

  void RegularPolygon::set_edge_length ( double e )
  {
    double angle;
    angle = M_PI / m_sides;
    m_radius = fabs ( e ) / 2.0 / sin ( angle );
    create_vertices();
    m_signal_size.emit();
  }

  void RegularPolygon::set_sides_edge_length ( unsigned int s, double e )
  {
    double angle;
    if ( s >= 3 )
    {
      m_sides = s;
    }
    angle = M_PI / m_sides;
    m_radius = fabs ( e ) / 2.0 / sin ( angle );
    create_vertices();
    m_signal_sides.emit();
    m_signal_size.emit();
  }

  double RegularPolygon::apothem_length()
  {
    double angle, apothem;
    angle = M_PI / m_sides;
    apothem = cos ( angle ) * m_radius;
    return apothem;
  }

  void RegularPolygon::set_apothem_length ( double a )
  {
    double angle;
    angle = M_PI / m_sides;
    m_radius = fabs ( a ) / cos ( angle );
    create_vertices();
    m_signal_size.emit();
  }

  void RegularPolygon::set_sides_apothem_length ( unsigned int s, double a )
  {
    double angle;
    if ( s >= 3 )
    {
      m_sides = s;
    }
    angle = M_PI / m_sides;
    m_radius = fabs ( a ) / cos ( angle );
    create_vertices();
    m_signal_sides.emit();
    m_signal_size.emit();
  }

  RegularPolygon::Style RegularPolygon::style( )
  {
    return m_style;
  }

  void RegularPolygon::set_style ( Style i )
  {
    m_style = i;
    create_vertices();
    m_signal_style.emit();
  }

  void RegularPolygon::create_vertices( )
  {
    double angle=0.0, x, y;
    m_vertices.clear();

    if ( m_style == ( unsigned int ) ZERO_APOTHEM )
      angle += M_PI / m_sides;

    for ( size_t i=0; i < m_sides; i++ )
    {
      x = cos ( angle ) * m_radius;
      y = sin ( angle ) * m_radius;
      m_vertices.push_back ( Vertex ( x, y ) );
      angle += 2.0 * M_PI / m_sides;
    }
    this->on_vertices_changed();
  }

  sigc::signal<void> RegularPolygon::signal_sides()
  {
    return m_signal_sides;
  }

  sigc::signal<void> RegularPolygon::signal_size()
  {
    return m_signal_size;
  }

  sigc::signal<void> RegularPolygon::signal_style()
  {
    return m_signal_style;
  }

}
