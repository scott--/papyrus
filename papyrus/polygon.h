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
#ifndef PAPYRUSPOLYGON_H
#define PAPYRUSPOLYGON_H

#include <papyrus/polyline.h>

/**
 * \page guide_polygon Polygons
 * A polygon is drawn as a set of ordered vertices relative to the shape's x,y
 * coordinate.
 *
 * The following contains an example that will add a star polygon to a canvas.
 * The blue lines represent the x and y axes, and show through since an alpha value
 * of 0.9 is used.
 *
 * \image html polygon_star.png "Star shaped polygon drawn by example code below"
 *
 * \dontinclude shapes.cpp
 * \skip add_polygon_star
 * \until }
 *
 * Note that the major difference between a polygon and a polyline is that
 * a polygon will close the surface on the stroke, while a polyline will not.
 * Below is the image generated from a polyline with vertices in the shape of a
 * U, and following is a polygon with the same vertices.
 *
 * \image html polyline_filled.png "Filled Polyline with U vertices"
 *
 * \image html polygon_u.png "Polygon with U vertices"
 *
 * \dontinclude shapes.cpp
 * \skip add_polygon_u
 * \until }
 *
 */

namespace Papyrus
{

  /**
  @author Rick L Vinyard Jr
  */
  class Polygon : public Polyline
  {
    protected:

      Polygon ( const Glib::ustring& id, const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke );

    public:
      PAPYRUS_DRAWABLE(Polygon);

      static pointer create ( const Vertices& vertices=Vertices(),
                              Fill::pointer fill = Fill::pointer(),
                              Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& id,
                              const Vertices& vertices=Vertices(),
                              Fill::pointer fill = Fill::pointer(),
                              Stroke::pointer stroke = Stroke::pointer() );

      virtual ~Polygon();

      virtual void draw_shape ( Context& cairo ) const;

  };

}

#endif
