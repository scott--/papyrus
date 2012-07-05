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
#include "circle.h"

#include <cmath>
#include <sstream>
#include <iostream>

namespace Papyrus
{

  Circle::Circle ( const Glib::ustring& id, double radius, Fill::pointer fill, Stroke::pointer stroke ) :
      Shape ( id, fill, stroke ),
      m_radius ( radius )
  {
  }

  Circle::Circle ( const AttributeValueMap& avmap ):
      m_radius( 0.0 )
  {
    this->set ( avmap );
  }

  Circle::pointer Circle::create ( double radius, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Circle ( Glib::ustring(), radius, fill, stroke ) );
  }

  Circle::pointer Circle::create ( const Glib::ustring& id, double radius, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Circle ( id, radius, fill, stroke ) );
  }

  Circle::pointer Circle::create( const AttributeValueMap& avmap )
  {
    PAPYRUS_CREATE( Circle( avmap ) );
  }

  Circle::~Circle() {}

  void Circle::set( const AttributeValueMap& avmap )
  {
    Shape::set( avmap );

    AttributeValueMap::const_iterator i;
    for ( i = avmap.begin(); i != avmap.end(); i++ )
    {
      if      ( strcaseeq( i->first, "cx" ) )  this->set_x( atof( i->second.c_str() ) );
      else if ( strcaseeq( i->first, "cy" ) )  this->set_y( atof( i->second.c_str() ) );
      else if ( strcaseeq( i->first, "r" ) )   this->set_radius( atof( i->second.c_str() ) );
    }
  }

  double Circle::radius() const
  {
    return m_radius;
  }

  void Circle::set_radius ( double r )
  {
    m_radius = r;
    this->shape_changed();
    m_signal_radius.emit();
  }

  void Circle::draw_shape( Context& cairo ) const
  {
    if ( m_radius != 0 ) cairo->arc ( 0.0, 0.0, m_radius, 0.0, 2.0*M_PI );
  }

  sigc::signal<void> Circle::signal_radius()
  {
    return m_signal_radius;
  }

  Glib::ustring Circle::svg ( unsigned depth )
  {
    std::ostringstream s;

    s << svg_spacing ( depth ) << "<circle " << svg_id();

    s << svg_transform();

    s << svg_fill();

    s << " cx=\"" << x() << "\" cy=\"" << y() << "\" r=\"" << m_radius << "\" />\n";

    return s.str();
  }

  Region Circle::calculate_extents(const Matrix & m, ExtentsPerformance ep) const
  {
    if ( ep == EXTENTS_QUICK )
    {
      double x, y;
      Region result;
      const double samples = 16.0;
      double r = m_radius;

      if ( m_stroke ) r += m_stroke->width();

      for ( double angle = 0.0; angle <= 2.0*M_PI; angle += M_PI / (samples / 2.0) )
      {
        x = r * cos(angle);
        y = r * sin(angle);
        m.transform_point( x, y );
        result.include( x, y );
      }

      return result;
    }
    else
      return Shape::calculate_extents(m, ep);
  }

}
