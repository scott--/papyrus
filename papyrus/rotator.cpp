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
#include "rotator.h"

namespace Papyrus
{

  Rotator::Rotator ( const Glib::ustring& id, DrawableSet::pointer drawables, double radian_interval ):
      AffineController( id, drawables ),
      m_radian_interval ( radian_interval )
  {
    m_original_position[ 0 ] = 0.0;
    m_original_position[ 1 ] = 0.0;
    m_centroid[ 0 ] = 0.0;
    m_centroid[ 1 ] = 0.0;
    this->recalculate_matrix();
  }

  Rotator::pointer Rotator::create ( double radian_interval )
  {
    PAPYRUS_CREATE( Rotator ( Glib::ustring(), DrawableSet::pointer(), radian_interval ) );
  }

  Rotator::pointer Rotator::create ( const Glib::ustring& id, DrawableSet::pointer drawables, double radian_interval )
  {
    PAPYRUS_CREATE( Rotator ( id, drawables, radian_interval ) );
  }

  Rotator::pointer Rotator::create ( const Glib::ustring& id, double radian_interval )
  {
    PAPYRUS_CREATE( Rotator ( id, DrawableSet::pointer(), radian_interval ) );
  }

  Rotator::pointer Rotator::create ( DrawableSet::pointer drawables, double radian_interval )
  {
    PAPYRUS_CREATE( Rotator ( Glib::ustring(), drawables, radian_interval ) );
  }

  Rotator::~Rotator()
  {}

//   double Rotator::radian_interval()
//   {
//     return m_radian_interval;
//   }
//
//   void Rotator::set_radian_interval( double radian_interval )
//   {
//     m_radian_interval = radian_interval;
//   }

  bool Rotator::on_button_press ( const Event::ButtonPress& event )
  {
    Region ext;
    m_original_position[ 0 ] = event.x;
    m_original_position[ 1 ] = event.y;
    m_last_position[ 0 ] = event.x;
    m_last_position[ 1 ] = event.y;
    m_centroid[0] = 0.0;
    m_centroid[1] = 0.0;
    if ( this->size() > 0 )
    {
      ext = this->extents();
      m_centroid[0] = ext.left() + ext.width() / 2.0;
      m_centroid[1] = ext.top() + ext.height() / 2.0;
    }
    m_last_angle = atan2 ( event.y - m_centroid[1], event.x - m_centroid[0] );
    return true;
  }

  bool Rotator::on_motion ( const Event::Motion & event )
  {
    double this_angle;

    if ( this->size() == 0 )
      return false;

    this_angle = atan2 ( event.y - m_centroid[1], event.x - m_centroid[0] );

    this->rotate ( this_angle - m_last_angle );

    m_last_angle = this_angle;

    return true;
  }



}
