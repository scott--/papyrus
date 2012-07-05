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
#include "polygon.h"

namespace Papyrus
{

  Polygon::Polygon ( const Glib::ustring& id, const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke ) :
      Polyline ( id, vertices, fill, stroke )
  {}

  Polygon::pointer Polygon::create ( const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Polygon ( Glib::ustring(), vertices, fill, stroke ) );
  }

  Polygon::pointer Polygon::create ( const Glib::ustring& id, const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Polygon ( id, vertices, fill, stroke ) );
  }

  Polygon::~Polygon() {}

  void Polygon::draw_shape ( Context& cairo ) const
  {

    if ( m_vertices.size() < 3 )
      return;
    cairo->move_to ( m_vertices[0].x, m_vertices[0].y );
    for ( Vertices::const_iterator i = m_vertices.begin() +1; i != m_vertices.end(); i++ )
    {
      if ( i->relative )
        cairo->rel_line_to ( i->x, i->y );
      else
        cairo->line_to ( i->x, i->y );
    }
    cairo->close_path();
  }

}
