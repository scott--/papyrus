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
#include "translator.h"

namespace Papyrus
{

  Translator::Translator ( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned transforms ) :
      AffineController ( id, drawables ),
      m_transforms ( transforms )
  {
    m_original_position[ 0 ] = 0.0;
    m_original_position[ 1 ] = 0.0;
    m_grid[ 0 ] = 0.0;
    m_grid[ 1 ] = 0.0;
    this->recalculate_matrix();
  }

  Translator::pointer Translator::create ( unsigned transforms )
  {
    PAPYRUS_CREATE ( Translator ( Glib::ustring(), DrawableSet::pointer(), transforms ) );
  }

  Translator::pointer Translator::create ( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned transforms )
  {
    PAPYRUS_CREATE ( Translator ( id, drawables, transforms ) );
  }

  Translator::pointer Translator::create ( const Glib::ustring& id, unsigned transforms )
  {
    PAPYRUS_CREATE ( Translator ( id, DrawableSet::pointer(), transforms ) );
  }

  Translator::pointer Translator::create ( DrawableSet::pointer drawables, unsigned transforms )
  {
    PAPYRUS_CREATE ( Translator ( Glib::ustring(), drawables, transforms ) );
  }

  Translator::~Translator()
  {}

  unsigned Translator::transforms()
  {
    return m_transforms;
  }

  void Translator::set_transforms ( unsigned transforms )
  {
    m_transforms = transforms;
  }

  void Translator::enable_transforms ( unsigned transforms )
  {
    m_transforms |= transforms;
  }

  void Translator::disable_transforms ( unsigned transforms )
  {
    m_transforms &= ~transforms;
  }

  void Translator::grid ( double & x, double & y )
  {
    x = m_grid[ 0 ];
    y = m_grid[ 1 ];
  }

  void Translator::set_grid ( double x, double y )
  {
    m_grid[ 0 ] = x;
    m_grid[ 1 ] = y;
  }

  void Translator::set_grid_x ( double x )
  {
    m_grid[ 0 ] = x;
  }

  void Translator::set_grid_y ( double y )
  {
    m_grid[ 1 ] = y;
  }

  bool Translator::on_button_press ( const Event::ButtonPress& event )
  {
    m_last_position[0] = m_original_position[ 0 ] = event.x;
    m_last_position[1] = m_original_position[ 1 ] = event.y;
    return true;
  }

  bool Translator::on_motion ( const Event::Motion & event )
  {
    double tx = 0.0, ty = 0.0;

    if ( m_transforms & TRANSLATE_X )
    {
      tx = event.x - m_last_position[ 0 ];
      if ( m_grid[ 0 ] > 0.0 )
        tx = round ( tx / m_grid[ 0 ] ) * m_grid[ 0 ];
    }

    if ( m_transforms & TRANSLATE_Y )
    {
      ty = event.y - m_last_position[ 1 ];
      if ( m_grid[ 1 ] > 0.0 )
        ty = round ( ty / m_grid[ 1 ] ) * m_grid[ 1 ];
    }

    if ( tx != 0.0 && ty != 0.0 )
    {
      this->translate ( tx, ty );
      m_last_position[ 0 ] = event.x;
      m_last_position[ 1 ] = event.y;
    }
    else if ( tx != 0.0 )
    {
      this->translate ( tx, 0.0 );
      m_last_position[ 0 ] = event.x;
    }
    else if ( ty != 0.0 )
    {
      this->translate ( 0.0, ty );
      m_last_position[ 1 ] = event.y;
    }

    return true;
  }



}
