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
#include "kochsnowflake.h"

namespace Papyrus
{

  KochSnowflake::KochSnowflake ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke ) :
      Polyline ( id, Vertices(), fill, stroke ),
      m_level ( level ), m_size ( size )
  {
    this->create_vertices();
  }

  KochSnowflake::pointer KochSnowflake::create ( unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( KochSnowflake ( Glib::ustring(), level, size, fill, stroke ) );
  }

  KochSnowflake::pointer KochSnowflake::create ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( KochSnowflake ( id, level, size, fill, stroke ) );
  }

  KochSnowflake::~KochSnowflake()
  {}

  unsigned KochSnowflake::level( )
  {
    return m_level;
  }

  void KochSnowflake::set_level ( unsigned level )
  {
    m_level = level;
    this->create_vertices();
  }

  double KochSnowflake::size( )
  {
    return m_size;
  }

  void KochSnowflake::set_size ( double size )
  {
    m_size = size;
    this->create_vertices();
  }

  void KochSnowflake::create_vertices( )
  {
    static const double pi3 = M_PI / 3.0;

    m_vertices.clear();

    m_lsize = m_size;
    for ( unsigned i=0; i < m_level; i++ )
      m_lsize /= 3.0;

    m_angle = 0.0;

    m_vertices.push_back ( Vertex ( 0.0, m_size*sin ( M_PI/3.0 ) /3.0 ) );

    this->kochsnowflake ( m_level );
    m_vertices.push_back ( Vertex ( m_lsize*cos ( m_angle ), m_lsize*sin ( m_angle ), true ) );

    m_angle += pi3 + pi3;
    this->kochsnowflake ( m_level );
    m_vertices.push_back ( Vertex ( m_lsize*cos ( m_angle ), m_lsize*sin ( m_angle ), true ) );

    m_angle += pi3 + pi3;
    this->kochsnowflake ( m_level );
    m_vertices.push_back ( Vertex ( m_lsize*cos ( m_angle ), m_lsize*sin ( m_angle ), true ) );

    this->on_vertices_changed();
  }

  void KochSnowflake::kochsnowflake ( unsigned level )
  {
    static const double pi3 = M_PI / 3.0;

    if ( level > 0 )
    {
      this->kochsnowflake ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize*cos ( m_angle ), m_lsize*sin ( m_angle ), true ) );
      m_angle -= pi3;
      this->kochsnowflake ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize*cos ( m_angle ), m_lsize*sin ( m_angle ), true ) );
      m_angle += pi3 + pi3;
      this->kochsnowflake ( level-1 );
      m_vertices.push_back ( Vertex ( m_lsize*cos ( m_angle ), m_lsize*sin ( m_angle ), true ) );
      m_angle -= pi3;
      this->kochsnowflake ( level-1 );
    }
  }

}
