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
#ifndef PAPYRUSBEZIERGON_H
#define PAPYRUSBEZIERGON_H

#include <papyrus/bezierline.h>

/**
 * \page guide_beziergon Beziergon
 *
 * A beziergon is drawn as a series of cubic bezier curves and defined by a set of ordered
 * bezier vertices. A beziergon differs from a Papyrus::Bezierline in that the beziergon will
 * be closed by drawing a cubic bezier curve from the last vertex to the first vertex.
 *
 * For a discussion of bezier vertices and how the cubic bezier curves are defined see
 * Papyrus::Bezierline.
 *
 * If this beziergon contained three vertices, the following points would be present to define
 * the following \b bezierline segments:
 * \code
 *    v0p0   v0p1   v0p2   v1p0   v1p1   v1p2   v2p0   v2p1   v2p2
 *           |------ segment 1 ------|
 *                                |------ segment 2 ------|
 *
 * \endcode
 *
 * The beziergon would complete the shape by drawing a third bezier curve from v2p1 to v0p1 using
 * v2p2 and v0p0 as control points.
 *
 * \image html beziergon.png "Filled Beziergon"
 *
 */

namespace Papyrus
{

  /**
   * \image html beziergon.png "Beziergon"
   *
   * @author Rick L Vinyard Jr
   */
  class Beziergon : public Bezierline
  {
    protected:

      Beziergon ( const Glib::ustring& id, BezierVertices vertices=BezierVertices() );

    public:
      PAPYRUS_DRAWABLE(Beziergon);

      static pointer create ( BezierVertices vertices=BezierVertices() );

      static pointer create ( const Glib::ustring& id, BezierVertices vertices=BezierVertices() );

      virtual ~Beziergon();

      virtual void draw_shape ( Context& cairo ) const;

  };

}

#endif
