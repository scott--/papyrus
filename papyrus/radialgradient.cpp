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
#include "radialgradient.h"

namespace Papyrus
{

  RadialGradient::RadialGradient(const Circle& outer, const Circle& inner):
      m_outer_circle(outer),
      m_inner_circle(inner)
  {
  }

  RadialGradient::pointer RadialGradient::create(double ox, double oy, double orad, Quantity q )
  {
    return pointer( new RadialGradient(Circle(ox,oy,orad,q), Circle(NAN)) );
  }

  RadialGradient::pointer RadialGradient::create( const Circle& outer )
  {
    return pointer( new RadialGradient(outer, Circle(NAN)) );
  }

  RadialGradient::pointer RadialGradient::create( const Circle& outer, const Circle& inner )
  {
    return pointer( new RadialGradient(outer, inner) );
  }

  RadialGradient::~RadialGradient()
  {
  }

  const RadialGradient::Circle & RadialGradient::outer_circle() const
  {
    return m_outer_circle;
  }

  void RadialGradient::set_outer_circle(const Circle & outer)
  {
    m_outer_circle = outer;
    m_signal_changed.emit();
  }

  const RadialGradient::Circle & RadialGradient::inner_circle() const
  {
    return m_inner_circle;
  }

  void RadialGradient::set_inner_circle(const Circle & inner)
  {
    m_inner_circle = inner;
    m_signal_changed.emit();
  }

  void RadialGradient::set_circles(const Circle & outer, const Circle & inner)
  {
    m_outer_circle = outer;
    m_inner_circle = inner;
    m_signal_changed.emit();
  }

  void RadialGradient::render(Context& cairo) const
  {
    Cairo::RefPtr<Cairo::RadialGradient> gradient;
    Circle outer = m_outer_circle, inner = m_inner_circle;
    double fx0, fy0, fx1, fy1, w, h;
    
    if ( outer.has_percent() or inner.has_percent() )
    {
      if ( cairo.is_flag_set(RENDER_HINT_STROKE) )
        cairo->get_stroke_extents( fx0, fy0, fx1, fy1 );
      else
        cairo->get_fill_extents( fx0, fy0, fx1, fy1 );
      w = fx1 - fx0;
      h = fy1 - fy0;
      if ( outer ) {
        if ( outer.quantity_x==PERCENT ) outer.x = fx0 + w * outer.x;
        if ( outer.quantity_y==PERCENT ) outer.y = fy0 + h * outer.y;
        if ( outer.quantity_r==PERCENT ) outer.r = std::max(w,h) * outer.r;
      }
      else {
        outer.x = fx0 + w / 2.0;
        outer.y = fx0 + h / 2.0;
        outer.r = std::max(w,h) / 2.0;
      }
      
      if ( inner ) {
        if ( inner.quantity_x==PERCENT ) inner.x = fx0 + w * inner.x;
        if ( inner.quantity_y==PERCENT ) inner.y = fy0 + h * inner.y;
        if ( inner.quantity_r==PERCENT ) inner.r = std::max(w,h) * inner.r;
      }
      else {
        inner.x = outer.x;
        inner.y = outer.y;
        inner.r = 0.0;
      }
    }

    gradient = Cairo::RadialGradient::create( inner.x, inner.y, inner.r,
                                              outer.x, outer.y, outer.r );

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

