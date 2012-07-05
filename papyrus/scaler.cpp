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
#include "scaler.h"

namespace Papyrus
{

  Scaler::Scaler( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned sides ):
      AffineController( id, drawables ),
      m_sides( sides )
  {
    m_matrix_level = 1;
    m_original_position[ 0 ] = 0.0;
    m_original_position[ 1 ] = 0.0;
    m_grid[ 0 ] = 0.0;
    m_grid[ 1 ] = 0.0;
    this->recalculate_matrix();
  }

  Scaler::pointer Scaler::create( unsigned sides )
  {
    PAPYRUS_CREATE( Scaler( Glib::ustring(), DrawableSet::pointer(), sides ) );
  }

  Scaler::pointer Scaler::create( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned sides )
  {
    PAPYRUS_CREATE( Scaler( id, drawables, sides ) );
  }

  Scaler::pointer Scaler::create( const Glib::ustring& id, unsigned sides )
  {
    PAPYRUS_CREATE( Scaler( id, DrawableSet::pointer(), sides ) );
  }

  Scaler::pointer Scaler::create( DrawableSet::pointer drawables, unsigned sides )
  {
    PAPYRUS_CREATE( Scaler( Glib::ustring(), drawables, sides ) );
  }

  Scaler::~Scaler()
  {}

  unsigned Scaler::sides()
  {
    return m_sides;
  }

  void Scaler::set_sides( unsigned sides )
  {
    m_sides = sides;
  }

  void Scaler::enable_sides( unsigned sides )
  {
    m_sides |= sides;
  }

  void Scaler::disable_sides( unsigned sides )
  {
    m_sides &= ~sides;
  }

// //   void Scaler::grid( double & x, double & y )
// //   {
// //     x = m_grid[ 0 ];
// //     y = m_grid[ 1 ];
// //   }
// //
// //   void Scaler::set_grid( double x, double y )
// //   {
// //     m_grid[ 0 ] = x;
// //     m_grid[ 1 ] = y;
// //   }
// //
// //   void Scaler::set_grid_x( double x )
// //   {
// //     m_grid[ 0 ] = x;
// //   }
// //
// //   void Scaler::set_grid_y( double y )
// //   {
// //     m_grid[ 1 ] = y;
// //   }
//
  bool Scaler::on_button_press( const Event::ButtonPress& event )
  {
    int h = -1;
//
//     if ( m_handlebox ) {
//       h = m_handlebox->inside_handle( event.x, event.y );
//
//       switch (h) {
//         case 0:
//           this->set_sides(TOP);
//           break;
//         case 1:
//           this->set_sides(TOP|RIGHT);
//           break;
//         case 2:
//           this->set_sides(RIGHT);
//           break;
//         case 3:
//           this->set_sides(BOTTOM|RIGHT);
//           break;
//         case 4:
//           this->set_sides(BOTTOM);
//           break;
//         case 5:
//           this->set_sides(BOTTOM|LEFT);
//           break;
//         case 6:
//           this->set_sides(LEFT);
//           break;
//         case 7:
//           this->set_sides(TOP|LEFT);
//           break;
//         default:
//           Selector::on_button_press( event );
//           this->set_sides(0);
//           break;
//       }
//     }
//     else
//       Selector::on_button_press( event );

    m_last_position[0] = m_original_position[ 0 ] = event.x;
    m_last_position[1] = m_original_position[ 1 ] = event.y;

    return true;
  }

  bool Scaler::on_motion( const Event::Motion & event )
  {
    double tx = 0.0, ty = 0.0, sx=1.0, sy=1.0;
    double dx, dy, ldx, ldy;
    Region extents, pre_scale_extents, post_scale_extents;

    // calculate the movement
    dx = event.x - m_last_position[0];
    dy = event.y - m_last_position[1];

    // calculate the contained global extents
    extents = this->extents();

    if ( m_sides & RIGHT ) dx = -dx;
    if ( m_sides & ( LEFT | RIGHT ) ) sx = (extents.width() - dx) / extents.width();
    if ( m_sides & BOTTOM ) dy = -dy;
    if ( m_sides & ( TOP | BOTTOM ) ) sy = (extents.height() - dy) / extents.height();

    this->scale( sx, sy );

//     for ( i = m_selection.begin(); i != m_selection.end(); i++ ) {
//       pre_scale_extents = (*i)->local_extents();
//
//       if ( sx != 0.0 && sy != 0.0 ) ( *i ) ->scale( sx, sy );
//       else if ( sx != 0.0 )         ( *i ) ->scale( sx, 1.0 );
//       else if ( sy != 0.0 )         ( *i ) ->scale( 1.0, sy );
//
//       post_scale_extents = (*i)->local_extents();
//
//       if ( m_sides & LEFT && ! (m_sides & RIGHT) )
//         tx = pre_scale_extents.right() - post_scale_extents.right();
//       else if ( ! (m_sides & LEFT) && m_sides & RIGHT )
//         tx = pre_scale_extents.left() - post_scale_extents.left();
//       else if ( m_sides & LEFT && m_sides & RIGHT )
//         tx = ( pre_scale_extents.left() - post_scale_extents.left() + pre_scale_extents.right() - post_scale_extents.right() ) / 2.0;
//
//       if ( m_sides & TOP && ! (m_sides & BOTTOM) )
//         ty = pre_scale_extents.bottom() - post_scale_extents.bottom();
//       else if ( ! (m_sides & TOP) && m_sides & BOTTOM )
//         ty = pre_scale_extents.top() - post_scale_extents.top();
//       else if ( m_sides & TOP && m_sides & BOTTOM )
//         ty = ( pre_scale_extents.top() - post_scale_extents.top() + pre_scale_extents.bottom() - post_scale_extents.bottom() ) / 2.0;
//
//       if ( tx != 0.0 && ty != 0.0 )
//         ( *i ) ->translate( tx, ty );
//       else if ( tx != 0.0 )
//         ( *i ) ->translate( tx, 0.0 );
//       else if ( ty != 0.0 )
//         ( *i ) ->translate( 0.0, ty );
//
//     }

//     extents = this->extents();

    m_last_position[ 0 ] = event.x;
    m_last_position[ 1 ] = event.y;

    return true;
  }

}
