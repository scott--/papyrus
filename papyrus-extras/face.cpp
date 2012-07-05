/***************************************************************************
*   Copyright (C) 2004,2009 by Rick L. Vinyard, Jr.                        *
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
#include "face.h"

#include <cmath>

namespace Papyrus
{

  Face::Face ( const Glib::ustring& id, double size, TYPE type ) :
      Drawable ( id ),
      m_type ( type ),
      m_size ( size )
  {
  }

  Face::pointer Face::create ( double size, TYPE type )
  {
    PAPYRUS_CREATE ( Face ( Glib::ustring(), size, type ) );
  }

  Face::pointer Face::create ( const Glib::ustring& id, double size, TYPE type )
  {
    PAPYRUS_CREATE ( Face ( id, size, type ) );
  }

  Face::~Face() { }

  void Face::draw ( Context& cairo ) const
  {
    cairo->arc ( 0.0, 0.0, m_size, 0.0, 2*M_PI );
    cairo->set_source ( Cairo::SolidPattern::create_rgba ( 1.0, 1.0, 0.0, 1.0 ) );
    cairo.fill();

    cairo->arc ( -m_size/3.0, -m_size/3.0, m_size/6.0, 0.0, 2*M_PI );
    cairo->set_source ( Cairo::SolidPattern::create_rgba ( 0.0, 0.0, 0.0, 1.0 ) );
    cairo.fill();

    cairo->arc ( m_size/3.0, -m_size/3.0, m_size/6.0, 0.0, 2*M_PI );
    cairo->set_source ( Cairo::SolidPattern::create_rgba ( 0.0, 0.0, 0.0, 1.0 ) );
    cairo.fill();

    cairo->set_line_width ( m_size/6.0 );
    cairo->set_line_cap ( Cairo::LINE_CAP_ROUND );
    cairo->move_to ( -m_size/2.0, m_size/3.0 );
    cairo->curve_to ( -m_size/4.0, m_size/3.0*2.0, m_size/4.0, m_size/3.0*2.0, m_size/2.0, m_size/3.0 );
    cairo->set_source ( Cairo::SolidPattern::create_rgba ( 0.0, 0.0, 0.0, 1.0 ) );
    cairo.stroke();
  }

  Face::TYPE Face::type()
  {
    return m_type;
  }

  void Face::set_type ( TYPE type )
  {
    m_type = type;
    this->redraw();
  }

  double Face::size()
  {
    return m_size;
  }

  void Face::set_size ( double size )
  {
    m_size = size;
    this->invalidate_extents();
    this->redraw();
  }

  void Face::set_size_type ( double size, TYPE type )
  {
    m_size = size;
    m_type = type;
    this->invalidate_extents();
    this->redraw();
  }

}
