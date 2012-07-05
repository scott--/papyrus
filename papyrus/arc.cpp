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
#include "arc.h"

#include <cmath>

namespace Papyrus
{

  Arc::Arc ( const Glib::ustring& id,
             double radius,
             double angle_start,
             double angle_end,
             Fill::pointer fill,
             Stroke::pointer stroke
           ) :
      Shape ( id, fill, stroke ),
      m_radius ( radius ),
      m_angle_start ( angle_start ),
      m_angle_end ( angle_end )
  {
    if ( angle_start > angle_end )
    {
      m_angle_start = angle_start;
      m_angle_end = angle_end;
    }
  }

  Arc::pointer Arc::create ( double radius,
                             double angle_start,
                             double angle_end,
                             Fill::pointer fill,
                             Stroke::pointer stroke
                           )
  {
    PAPYRUS_CREATE ( Arc ( Glib::ustring(), radius, angle_start, angle_end, fill, stroke ) );
  }

  Arc::pointer Arc::create ( const Glib::ustring& id,
                             double radius,
                             double angle_start,
                             double angle_end,
                             Fill::pointer fill,
                             Stroke::pointer stroke
                           )
  {
    PAPYRUS_CREATE ( Arc ( id, radius, angle_start, angle_end, fill, stroke ) );
  }

  Arc::~Arc() {}

  double Arc::radius() const
  {
    return m_radius;
  }

  void Arc::set_radius ( double r )
  {
    m_radius = r;
    this->shape_changed();
    m_signal_radius.emit();
  }

  void Arc::draw_shape ( Context& cairo ) const
  {
    if ( m_angle_end - m_angle_start < M_PI * 2.0 ) cairo->move_to( 0.0, 0.0 );
    cairo->arc ( 0.0, 0.0, m_radius, m_angle_start, m_angle_end );
    if ( m_angle_end - m_angle_start < M_PI * 2.0 ) cairo->close_path();
  }

  double Arc::start_angle( ) const
  {
    return m_angle_start;
  }

  double Arc::end_angle( ) const
  {
    return m_angle_end;
  }

  void Arc::set_angles ( double start, double end )
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

  sigc::signal<void> Arc::signal_radius()
  {
    return m_signal_radius;
  }

  sigc::signal<void> Arc::signal_angle()
  {
    return m_signal_angle;
  }

}

