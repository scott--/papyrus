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
#include "beziergon.h"

namespace Papyrus
{

  Beziergon::Beziergon ( const Glib::ustring& id, BezierVertices vertices ) :
      Bezierline ( id, vertices )
  {}

  Beziergon::pointer Beziergon::create ( BezierVertices vertices )
  {
    PAPYRUS_CREATE ( Beziergon ( Glib::ustring(), vertices ) );
  }

  Beziergon::pointer Beziergon::create ( const Glib::ustring& id, BezierVertices vertices )
  {
    PAPYRUS_CREATE ( Beziergon ( id, vertices ) );
  }

  Beziergon::~Beziergon() {}

  void Beziergon::draw_shape ( Context& cairo ) const
  {

    if ( m_vertices.size() < 3 )
      return;
    cairo->move_to ( m_vertices[0].x, m_vertices[0].y );
    BezierVertices::const_iterator prev=m_vertices.begin(), current=m_vertices.begin() +1;
    while ( current != m_vertices.end() )
    {
      if ( current->relative )
        cairo->rel_curve_to ( prev->c2x, prev->c2y, current->c1x, current->c1y, current->x, current->y );
      else
        cairo->curve_to ( prev->c2x, prev->c2y, current->c1x, current->c1y, current->x, current->y );
      prev = current++;
    }
    current = m_vertices.begin();
    cairo->curve_to ( prev->c2x, prev->c2y, current->c1x, current->c1y, current->x, current->y );
    cairo->close_path();
  }

}
