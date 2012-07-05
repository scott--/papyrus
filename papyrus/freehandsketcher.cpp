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
#include "freehandsketcher.h"

namespace Papyrus
{

  FreehandSketcher::FreehandSketcher ( const Glib::ustring& id, SKETCH mode, Stroke::pointer stroke ) :
      Controller(id),
      m_mode ( mode ),
      m_stroke ( stroke ),
      m_drawing ( false ),
      m_movement_threshhold ( 3 ) {}


  FreehandSketcher::pointer FreehandSketcher::create ( const Glib::ustring& id, SKETCH mode, Stroke::pointer stroke )
  {
    return pointer ( new FreehandSketcher ( id, mode, stroke ) );
  }

  FreehandSketcher::pointer FreehandSketcher::create ( SKETCH mode, Stroke::pointer stroke )
  {
    return pointer ( new FreehandSketcher ( Glib::ustring(), mode, stroke ) );
  }

  FreehandSketcher::~FreehandSketcher() {}

  const FreehandSketcher::Sketchpads& FreehandSketcher::sketchpads()
  {
    return m_sketchpads;
  }

  void FreehandSketcher::add_sketchpad ( Group::pointer sketchpad )
  {
    Papyrus::Polyline::pointer line;
    m_sketchpads.insert ( sketchpad );
    if ( m_drawing )
    {
      m_lines[ sketchpad ] = papyrus_dynamic_pointer_cast<Polyline> ( m_current_line->clone() );
      sketchpad->add ( m_lines[ sketchpad ] );
    }
  }

  void FreehandSketcher::remove_sketchpad ( Group::pointer sketchpad )
  {
    m_sketchpads.erase ( sketchpad );
    m_lines.erase ( sketchpad );
  }

  SKETCH FreehandSketcher::sketch_mode()
  {
    return m_mode;
  }

  void FreehandSketcher::set_sketch_mode ( SKETCH mode )
  {
    m_mode = mode;
  }

  Stroke::pointer FreehandSketcher::stroke()
  {
    return m_stroke;
  }

  void FreehandSketcher::set_stroke ( Stroke::pointer stroke )
  {
    Lines::iterator i;
    m_stroke = stroke;
    for ( i = m_lines.begin(); i != m_lines.end(); i++ )
      i->second->set_stroke ( stroke );
  }

  Fill::pointer FreehandSketcher::fill( )
  {
    return m_fill;
  }

  void FreehandSketcher::set_fill ( Fill::pointer fill )
  {
    m_fill = fill;
  }

  bool FreehandSketcher::on_button_press ( const Event::ButtonPress& event )
  {
    Papyrus::Polyline::pointer l;
    Sketchpads::iterator i;

    m_drawing = true;

    m_lines.clear();

    switch ( m_mode )
    {
      case SKETCH_LINE:
        m_current_line = Polyline::create();
        break;
      case SKETCH_POLYGON:
        m_current_line = Polygon::create();
        break;
    }

    m_current_line->set_stroke ( m_stroke );
    m_current_line->add_vertex ( event.x, event.y );
    if ( m_fill )
      m_current_line->set_fill( m_fill );

    for ( i = m_sketchpads.begin(); i != m_sketchpads.end(); i++ )
    {
      l = papyrus_dynamic_pointer_cast<Polyline> ( m_current_line->clone() );
      m_lines[ *i ] = l;
      ( *i )->add ( l );
    }

    m_last_position[ 0 ] = event.x;
    m_last_position[ 1 ] = event.y;

    return true;
  }

  bool FreehandSketcher::on_motion ( const Event::Motion& event )
  {
    Lines::iterator i;

    if ( ! m_drawing )
      return false;

    if ( sqrt ( pow ( m_last_position[ 0 ] - event.x, 2 ) + pow ( m_last_position[ 1 ] - event.y, 2 ) ) < m_movement_threshhold )
      return false;

    m_current_line->add_vertex ( event.x, event.y );
    m_last_position[ 0 ] = event.x;
    m_last_position[ 1 ] = event.y;

    for ( i = m_lines.begin(); i != m_lines.end(); i++ )
      i->second->add_vertex ( event.x, event.y );

    return true;
  }


  bool FreehandSketcher::on_button_release ( const Event::ButtonRelease& event )
  {
    Lines::iterator i;

    for ( i = m_lines.begin(); i != m_lines.end(); i++ )
      i->first->remove ( i->second );

    m_current_line.reset();

    return true;
  }

  void FreehandSketcher::set_movement_threshhold ( double t )
  {
    m_movement_threshhold = t;
  }

  double FreehandSketcher::get_movement_threshhold( )
  {
    return m_movement_threshhold;
  }

}
