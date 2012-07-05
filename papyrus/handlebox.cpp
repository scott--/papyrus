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
#include "handlebox.h"

#include <climits>
#include "circle.h"
#include "rgba.h"

namespace Papyrus
{

  Handlebox::Handlebox ( const Glib::ustring& id, Handles handles ) : Boxed ( id ), m_initializing ( true )
  {
    // Initialize the handle shape arrays
    for (int i=0; i<8; i++) 
    {
      m_handle_shape[i] = Drawable::pointer();
      m_handle_active[i] = false;
    }
    
    Rectangle::pointer rectangle =
        Rectangle::create ( 7, 7, Fill::create ( RGBA ( 0.0, 1.0, 0.0, 1.0 ) ), Stroke::create ( RGBA ( 0.0, 0.0, 0.0, 1.0 ),1 ) );

    rectangle->hide();
    rectangle->set_exclude_from_extents ( true );

    this->set_handle_shape ( ALL_HANDLES, rectangle, false );

    m_initializing = false;

    this->activate_handle ( handles );

  }

  Handlebox::~Handlebox()
  {}

  Handlebox::pointer Handlebox::create ( Handles handles )
  {
    PAPYRUS_CREATE ( Handlebox ( Glib::ustring(), handles ) );
  }

  Handlebox::pointer Handlebox::create ( const Glib::ustring& id, Handles handles )
  {
    PAPYRUS_CREATE ( Handlebox ( id, handles ) );
  }

  void Handlebox::set_handle_shape ( Position p, Drawable::pointer shape, bool activate )
  {
    if ( ! shape ) return;
    // TODO fix
//     if ( m_handle_shape[p] ) this->remove ( m_handle_shape[p] );
    m_handle_shape[p] = shape->clone();
    m_handle_shape[p]->hide();
    m_handle_shape[p]->set_exclude_from_extents ( true );
    // TODO fix
//     this->add ( m_handle_shape[p], INT_MAX );
    this->activate_handle ( p, activate );
  }

  void Handlebox::set_handle_shape ( Handles h, Drawable::pointer shape, bool activate )
  {
    int i;

    if ( ! shape ) return;

    switch ( h )
    {
      case NO_HANDLES:
        break;
      case CORNER_HANDLES:
        for ( i=TOP_RIGHT; i <= TOP_LEFT; i+=2 )
          this->set_handle_shape ( ( Position ) i, shape, activate );
        break;
      case ALL_HANDLES:
        for ( i=START_POSITION; i < END_POSITION; i++ )
          this->set_handle_shape ( ( Position ) i, shape, activate );
        break;
    }
  }

  Drawable::pointer Handlebox::get_handle_shape ( Position p )
  {
    return m_handle_shape[p];
  }

  void Handlebox::activate_handle ( Position p, bool activate )
  {
    if ( !activate ) 
    {
      this->deactivate_handle ( p );
      return;
    }

    m_handle_active[p] = true;
    if ( this->size() > 9 ) m_handle_shape[p]->show();
  }

  void Handlebox::activate_handle ( Handles h, bool activate )
  {
    int i;

    if ( !activate )
      this->deactivate_handle ( h );

    switch ( h )
    {
      case NO_HANDLES:
        break;
      case CORNER_HANDLES:
        for ( i=TOP_RIGHT; i <= TOP_LEFT; i+=2 )
          this->activate_handle ( ( Position ) i, activate );
        break;
      case ALL_HANDLES:
        for ( i=START_POSITION; i < END_POSITION; i++ )
          this->activate_handle ( ( Position ) i, activate );
        break;
    }
  }

  void Handlebox::deactivate_handle ( Position p )
  {
    m_handle_active[p] = false;
    m_handle_shape[p]->hide();
  }

  void Handlebox::deactivate_handle ( Handles h )
  {
    int i;
    switch ( h )
    {
      case NO_HANDLES:
        break;
      case CORNER_HANDLES:
        for ( i=TOP_RIGHT; i <= TOP_LEFT; i+=2 )
          this->deactivate_handle ( ( Position ) i );
        break;
      case ALL_HANDLES:
        for ( i=START_POSITION; i < END_POSITION; i++ )
          this->deactivate_handle ( ( Position ) i );
        break;
    }
  }

  bool Handlebox::is_active ( Position p )
  {
    return m_handle_active[p];
  }

  bool Handlebox::is_active ( Handles h )
  {
    int i;
    bool answer = false;

    switch ( h )
    {
      case NO_HANDLES:
        // Let's start with a false
        answer = false;
        for ( i=START_POSITION; i < END_POSITION; i++ )
          // and logically or each handle's state
          answer = answer || m_handle_active[i];
        // if any are active, this is true, which means we should return a
        // false that NO_HANDLE is active
        // and if this is false, it is true that NO_HANDLE is active
        answer = ! answer;
        break;
      case CORNER_HANDLES:
        // start with a true
        answer = true;
        for ( i=TOP_RIGHT; i <= TOP_LEFT; i+=2 )
          // and if any are false, answer becomes false
          answer = answer && m_handle_active[i];
        break;
      case ALL_HANDLES:
        // start with true
        answer = true;
        for ( i=START_POSITION; i < END_POSITION; i++ )
          // and if any are false, answer becomes false
          answer = answer && m_handle_active[i];
        break;
    }

    return answer;
  }

  Region Handlebox::calculate_extents(const Matrix& m, ExtentsPerformance ep) const
  {
    Region e;
    e = Boxed::calculate_extents(m, ep);
    
    if ( not e ) return e;
    
    double left, right, top, bottom, hcenter, vcenter;
    e.lrtb( left, right, top, bottom );
    hcenter = left + (right-left)/2.0;
    vcenter = top + (bottom-top)/2.0;
    
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 0 ], hcenter, top );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 1 ], right, top );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 2 ], right, vcenter );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 3 ], right, bottom );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 4 ], hcenter, bottom );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 5 ], left, bottom );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 6 ], left, vcenter );
    const_cast<Handlebox*>(this)->position_handle ( m_handle_shape[ 7 ], left, top );
      
    for ( int i = 0; i < 8; i++ )
      if ( m_handle_active[ i ] )
        e.include ( m_handle_shape[ i ] ->extents() );

    return e;
  }

//   void Handlebox::update_extents()
//   {
//     Region extents;
//     double x, y, w, h, offset = 0.0, offset_2;
//     int i;
// 
//     this->Group::update_extents();
//     m_extents_valid = false;
//     extents = this->extents();
//     extents.xywh ( x, y, w, h );
//     if ( m_box->stroke() )
//       offset = m_box->stroke()->width();
//     offset_2 = 2.0 * offset;
//     m_changed_connections[m_box].block();
//     m_box->set_xywh ( x - offset, y - offset, w + offset_2, h + offset_2 );
//     m_changed_connections[m_box].unblock();
//     extents.include ( m_box->global_extents() );
// 
//     if ( m_initializing ) return;
// 
//     double left = x - offset;
//     double right = x + w + offset;
//     double hcenter = x + w / 2.0;
//     double top = y - offset;
//     double bottom = y + h + offset;
//     double vcenter = y + h / 2.0;
// 
//     for ( i=0; i<8; i++ ) m_changed_connections[m_handle_shape[i]].block();
// 
//     this->position_handle ( m_handle_shape[ 0 ], hcenter, top );
//     this->position_handle ( m_handle_shape[ 1 ], right, top );
//     this->position_handle ( m_handle_shape[ 2 ], right, vcenter );
//     this->position_handle ( m_handle_shape[ 3 ], right, bottom );
//     this->position_handle ( m_handle_shape[ 4 ], hcenter, bottom );
//     this->position_handle ( m_handle_shape[ 5 ], left, bottom );
//     this->position_handle ( m_handle_shape[ 6 ], left, vcenter );
//     this->position_handle ( m_handle_shape[ 7 ], left, top );
// 
//     for ( i=0; i<8; i++ ) m_changed_connections[m_handle_shape[i]].unblock();
// 
//     for ( i = 0; i < 8; i++ )
//       if ( m_handle_active[ i ] )
//         extents.include ( m_handle_shape[ i ] ->global_extents() );
// 
//     this->set_extents ( extents );
//   }

  void Handlebox::position_handle ( Drawable::pointer drawable, double x, double y )
  {
    double cx, cy;

    if ( !drawable ) return ;
    
    Region ext = drawable->extents();

    // Get the drawable's bounding box center
    drawable->extents().center ( cx, cy );

    // Set the drawable's (x,y) to the desired center, offset by the bounding_box center
    drawable->translate ( x - cx, y - cy );
    return ;
  }

  int Handlebox::inside_handle ( double x, double y )
  {
    for ( int i = 0; i < 8; i++ )
      if ( m_handle_active[i] && m_handle_shape[i]->inside ( x, y ) )
        return i;
    return -1;
  }

  void Handlebox::on_child_added ( Drawable::pointer child )
  {
    Boxed::on_child_added( child );
    if ( this->size() > 9 )
    {
      for ( int i = 0; i < 8; i++ )
        if ( m_handle_active[i] && ! m_handle_shape[i]->is_visible() )
          m_handle_shape[i]->show();
      if ( ! m_box->is_visible() )
        m_box->show();
    }
  }

  void Handlebox::on_child_removed ( Drawable::pointer child )
  {
    Boxed::on_child_removed(child);
    
    if ( this->size() <= 9 )
    {
      for ( int i = 0; i < 8; i++ )
        m_handle_shape[i]->hide();
      m_box->hide();
    }
  }

}
