/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
#include "lineargradient.h"

#include <iostream>

namespace Papyrus
{

  LinearGradient::LinearGradient(const Vector& v):
      m_vector(v)
  {
  }


  LinearGradient::~LinearGradient()
  {
  }
  
  LinearGradient::pointer LinearGradient::create(double x0, double y0, double x1, double y1, Quantity q)
  {
    return pointer( new LinearGradient( Vector(x0, y0, x1, y1, q) ) );
  }

  LinearGradient::pointer LinearGradient::create( const Papyrus::Point& p0, const Papyrus::Point& p1, Quantity q )
  {
    return pointer( new LinearGradient( Vector(p0, p1, q) ) );
  }
  
  LinearGradient::pointer LinearGradient::create( const Point& p0, const Point& p1 )
  {
    return pointer( new LinearGradient( Vector(p0, p1) ) );
  }

  LinearGradient::pointer LinearGradient::create( const Vector& v )
  {
    return pointer( new LinearGradient( v ) );
  }

  const LinearGradient::Vector& LinearGradient::vector() const
  {
    return m_vector;
  }

  void LinearGradient::set_vector( const Vector& v )
  {
    m_vector = v;
    m_signal_changed.emit();
  }
  
  void LinearGradient::render(Context& cairo) const
  {
    Cairo::RefPtr<Cairo::LinearGradient> gradient;
    Vector v = m_vector;
    double fx0, fy0, fx1, fy1, w, h;
    
    if ( v.has_percent() )
    {
      if ( cairo.is_flag_set(RENDER_HINT_STROKE) )
        cairo->get_stroke_extents( fx0, fy0, fx1, fy1 );
      else
        cairo->get_fill_extents( fx0, fy0, fx1, fy1 );
      w = fx1 - fx0;
      h = fy1 - fy0;
      if ( v[0].quantity_x==PERCENT ) v[0].x = fx0 + w * v[0].x;
      if ( v[0].quantity_y==PERCENT ) v[0].y = fy0 + h * v[0].y;
      if ( v[1].quantity_x==PERCENT ) v[1].x = fx0 + w * v[1].x;
      if ( v[1].quantity_y==PERCENT ) v[1].y = fy0 + h * v[1].y;
    }
    
    // Get the units using the accessor to potentially climb the parent chain
//     GradientUnits units = this->units();
//     switch ( units )
//     {
//       case GRADIENT_UNITS_NONE:
//       case GRADIENT_UNITS_OBJECT:
//           std::cout << "Gradient fill extents: " << fx0 << ", " << fy0 << ", " << fx1 << ", " << fy1 << std::endl;
//           break;
//       case GRADIENT_UNITS_USER_SPACE:
//           break;
//     }
    
    gradient = Cairo::LinearGradient::create( v[0].x, v[0].y, v[1].x, v[1].y );
    
    // Get the stops reference using the accessor to potentially climb the parent chain
    const Stops& stops = this->stops();
    Stops::const_iterator siter;
    
    for ( siter = stops.begin(); siter != stops.end(); siter++ )
    {
      cairo_pattern_add_color_stop_rgba( gradient->cobj(), siter->offset(), siter->red(), siter->green(), siter->blue(), siter->alpha() );
    }
    
    // Get the spread using the accessor to potentially climb the parent chain
    GradientSpread spread = this->spread();
    
    if ( spread == GRADIENT_SPREAD_NONE )
      cairo_pattern_set_extend( gradient->cobj(), (cairo_extend_t)GRADIENT_SPREAD_PAD );
    else
      cairo_pattern_set_extend( gradient->cobj(), (cairo_extend_t)spread );
    
    cairo->set_source(gradient);
  }

}

