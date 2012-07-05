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
#include "sierpinski.h"

namespace Papyrus
{

  Sierpinski::Sierpinski ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke ) :
      Polyline ( id, Vertices(), fill, stroke ),
      m_level ( level ),
      m_size ( size )
  {
    this->create_vertices();
  }


  Sierpinski::pointer Sierpinski::create ( unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Sierpinski ( Glib::ustring(), level, size, fill, stroke ) );
  }

  Sierpinski::pointer Sierpinski::create ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Sierpinski ( id, level, size, fill, stroke ) );
  }

  Sierpinski::~Sierpinski()
  {}

  unsigned Sierpinski::level( )
  {
    return m_level;
  }

  void Sierpinski::set_level ( unsigned level )
  {
    m_level = level;
    this->create_vertices();
  }

  double Sierpinski::size( )
  {
    return m_size;
  }

  void Sierpinski::set_size ( double size )
  {
    m_size = size;
    this->create_vertices();
  }

  void Sierpinski::create_vertices( )
  {
    m_vertices.clear();

    m_lsize = m_size/4.0;
    for ( unsigned i=0; i < m_level; i++ )
      m_lsize /= 2.0;

    m_vertices.push_back ( Vertex ( 2.0*m_lsize, m_lsize ) );
    this->sierpinski_a ( m_level );
    m_vertices.push_back ( Vertex ( m_lsize, m_lsize, true ) );
    this->sierpinski_b ( m_level );
    m_vertices.push_back ( Vertex ( -m_lsize, m_lsize, true ) );
    this->sierpinski_c ( m_level );
    m_vertices.push_back ( Vertex ( -m_lsize, -m_lsize, true ) );
    this->sierpinski_d ( m_level );
    m_vertices.push_back ( Vertex ( m_lsize, -m_lsize, true ) );

    this->on_vertices_changed();
  }

  void Sierpinski::sierpinski_a ( unsigned level )
  {
    if ( level > 0 )
    {
      this->sierpinski_a ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, m_lsize, true ) );
      this->sierpinski_b ( level-1 );
      m_vertices.push_back ( Vertex ( 2.0*m_lsize, 0.0, true ) );
      this->sierpinski_d ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, -m_lsize, true ) );
      this->sierpinski_a ( level-1 );
    }
  }

  void Sierpinski::sierpinski_b ( unsigned level )
  {
    if ( level > 0 )
    {
      this->sierpinski_b ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, m_lsize, true ) );
      this->sierpinski_c ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, 2.0*m_lsize, true ) );
      this->sierpinski_a ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, m_lsize, true ) );
      this->sierpinski_b ( level-1 );
    }
  }

  void Sierpinski::sierpinski_c ( unsigned level )
  {
    if ( level > 0 )
    {
      this->sierpinski_c ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, -m_lsize, true ) );
      this->sierpinski_d ( level-1 );
      m_vertices.push_back ( Vertex ( -2.0*m_lsize, 0.0, true ) );
      this->sierpinski_b ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, m_lsize, true ) );
      this->sierpinski_c ( level-1 );
    }
  }

  void Sierpinski::sierpinski_d ( unsigned level )
  {
    if ( level > 0 )
    {
      this->sierpinski_d ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, -m_lsize, true ) );
      this->sierpinski_a ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, -2.0*m_lsize, true ) );
      this->sierpinski_c ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, -m_lsize, true ) );
      this->sierpinski_d ( level-1 );
    }
  }

}
