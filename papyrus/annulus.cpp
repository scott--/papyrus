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
#include "annulus.h"

#include <cmath>

namespace Papyrus
{

  Annulus::Annulus (
      const Glib::ustring& id,
      double outer_radius,
      double inner_radius,
      double angle_start,
      double angle_end,
      Fill::pointer fill,
      Stroke::pointer stroke
  ) :
      Shape ( id, fill, stroke ),
      m_outer_radius ( outer_radius ),
      m_inner_radius( inner_radius ),
      m_angle_start ( angle_start ),
      m_angle_end ( angle_end )
  {
    if ( angle_start > angle_end )
    {
      m_angle_start = angle_start;
      m_angle_end = angle_end;
    }

  }

  Annulus::pointer Annulus::create ( double outer_radius,
                                     double inner_radius,
                                     double angle_start,
                                     double angle_end,
                                     Fill::pointer fill,
                                     Stroke::pointer stroke
                                   )
  {
    PAPYRUS_CREATE ( Annulus ( Glib::ustring(), outer_radius, inner_radius, angle_start, angle_end, fill, stroke ) );
  }

  Annulus::pointer Annulus::create ( const Glib::ustring& id,
                                     double outer_radius,
                                     double inner_radius,
                                     double angle_start,
                                     double angle_end,
                                     Fill::pointer fill,
                                     Stroke::pointer stroke
                                   )
  {
    PAPYRUS_CREATE ( Annulus ( id, outer_radius, inner_radius, angle_start, angle_end, fill, stroke ) );
  }

  Annulus::~Annulus() {}

  double Annulus::outer_radius() const
  {
    return m_outer_radius;
  }

  double Annulus::inner_radius() const
  {
    return m_inner_radius;
  }

  void Annulus::set_outer_radius ( double r )
  {
    m_outer_radius = r;
    this->shape_changed();
    m_signal_outer_radius.emit();
  }

  void Annulus::set_inner_radius ( double r )
  {
    m_inner_radius = r;
    this->shape_changed();
    m_signal_inner_radius.emit();
  }

  void Annulus::set_radii ( double outer, double inner )
  {
    m_outer_radius = outer;
    m_inner_radius = inner;
    this->shape_changed();
    m_signal_outer_radius.emit();
    m_signal_inner_radius.emit();
  }

  void Annulus::draw_shape ( Context& cairo ) const
  {
    cairo->arc ( 0.0, 0.0, m_outer_radius, m_angle_start, m_angle_end );
    if ( m_angle_end - m_angle_start >= M_PI * 2.0 ) cairo->move_to( m_inner_radius, 0.0 );
    cairo->arc_negative ( 0.0, 0.0, m_inner_radius, m_angle_end, m_angle_start );
    if ( m_angle_end - m_angle_start < M_PI * 2.0 ) cairo->close_path();
  }

  double Annulus::start_angle( ) const
  {
    return m_angle_start;
  }

  double Annulus::end_angle( ) const
  {
    return m_angle_end;
  }

  void Annulus::set_angles ( double start, double end )
  {
    if ( start < end )
    {
      m_angle_start = start;
      m_angle_end = end;
    }
    else
    {
      m_angle_start = end;
      m_angle_end = start;
    }
    this->shape_changed();
    m_signal_angle.emit();
  }

  sigc::signal<void> Annulus::signal_outer_radius()
  {
    return m_signal_outer_radius;
  }

  sigc::signal<void> Annulus::signal_inner_radius()
  {
    return m_signal_inner_radius;
  }

  sigc::signal<void> Annulus::signal_angle()
  {
    return m_signal_angle;
  }

}

