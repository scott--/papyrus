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
#include "hilbert.h"

namespace Papyrus
{

  Hilbert::Hilbert ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke ) :
      Polyline ( id, Vertices(), fill, stroke ),
      m_level ( level ),
      m_size ( size )
  {
    this->create_vertices();
  }


  Hilbert::pointer Hilbert::create ( unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Hilbert ( Glib::ustring(), level, size, fill, stroke ) );
  }

  Hilbert::pointer Hilbert::create ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Hilbert ( id, level, size, fill, stroke ) );
  }

  Hilbert::~Hilbert()
  {}

  unsigned Hilbert::level( )
  {
    return m_level;
  }

  void Hilbert::set_level ( unsigned level )
  {
    m_level = level;
    this->create_vertices();
  }

  double Hilbert::size( )
  {
    return m_size;
  }

  void Hilbert::set_size ( double size )
  {
    m_size = size;
    this->create_vertices();
  }

  void Hilbert::create_vertices( )
  {
    m_vertices.clear();

    m_lsize = m_size;
    for ( unsigned i=0; i < m_level; i++ )
      m_lsize /= 2.0;

    m_vertices.push_back ( Vertex ( m_lsize/2.0, m_lsize/2.0 ) );

    this->hilbert_a ( m_level );

    this->on_vertices_changed();
  }

  void Hilbert::hilbert_a ( unsigned level )
  {
    if ( level > 0 )
    {
      this->hilbert_b ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, m_lsize, true ) );
      this->hilbert_a ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, 0.0, true ) );
      this->hilbert_a ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, -m_lsize, true ) );
      this->hilbert_c ( level-1 );
    }
  }

  void Hilbert::hilbert_b ( unsigned level )
  {
    if ( level > 0 )
    {
      this->hilbert_a ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, 0.0, true ) );
      this->hilbert_b ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, m_lsize, true ) );
      this->hilbert_b ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, 0.0, true ) );
      this->hilbert_d ( level-1 );
    }
  }

  void Hilbert::hilbert_c ( unsigned level )
  {
    if ( level > 0 )
    {
      this->hilbert_d ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, 0.0, true ) );
      this->hilbert_c ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, -m_lsize, true ) );
      this->hilbert_c ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize, 0.0, true ) );
      this->hilbert_a ( level-1 );
    }
  }

  void Hilbert::hilbert_d ( unsigned level )
  {
    if ( level > 0 )
    {
      this->hilbert_c ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, -m_lsize, true ) );
      this->hilbert_d ( level-1 );
      m_vertices.push_back ( Vertex ( -m_lsize, 0.0, true ) );
      this->hilbert_d ( level-1 );
      m_vertices.push_back ( Vertex ( 0.0, m_lsize, true ) );
      this->hilbert_b ( level-1 );
    }
  }

}
