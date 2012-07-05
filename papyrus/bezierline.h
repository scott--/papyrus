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
#ifndef PAPYRUSBEZIERLINE_H
#define PAPYRUSBEZIERLINE_H

#include <vector>

#include <papyrus/shape.h>
#include <papyrus/marker.h>
#include <papyrus/polyline.h>

/**
 * \page guide_bezierline Bezierlines
 *
 * A bezierline is drawn as a series of cubic bezier curves and defined by a set of ordered
 * bezier vertices. A cubic bezier curve is defined by four points; p0, p1, p2 and p3. The
 * cubic bezier curve starts at p0 and heads toward p1 before moving to p3 from the direction
 * of p2.
 *
 * A bezier vertex consists of three points, p0, p1 and p2. p1 represents the point on the line,
 * while p0 represents the preceeding control point and p2 represents the subsequent control point.
 * Thus, a curve heading into p1 will arrive from the direction of p0 and leave in the direction of
 * p2.
 *
 * Two bezier vertices, v0 and v1, are needed to define a bezier line segment or curve. This
 * results in a total of six points (three points for each vertex):
 * \code
 *    v0p0   v0p1   v0p2   v1p0   v1p1   v1p2
 * \endcode
 *
 * The cubic bezier curve from v0p1 to v1p1 will only use four of these points. It will leave v0p1
 * heading in the direction of v0p2 and arrive from the direction of v1p0 at v1p1. If you place the
 * points in the previous sentence in the order they are mentioned you get:
 * \code
 *           v0p1   v0p2   v1p0   v1p1
 * \endcode
 * which is the same sequence as above.
 *
 * If this bezier line contained a third vertex, the following points would be present to define
 * the following bezierline segments:
 * \code
 *    v0p0   v0p1   v0p2   v1p0   v1p1   v1p2   v2p0   v2p1   v2p2
 *           |------ segment 1 ------|
 *                                |------ segment 2 ------|
 * \endcode
 *
 * \image html bezierline.png "Filled Bezierline"
 *
 * Bezierlines may be filled or unfilled. An unfilled bezierline is more
 * conceptually familiar with what is implied by a bezierline. A filled bezierline
 * is essentially an unclosed beziergon.
 *
 */

namespace Papyrus
{

  class BezierVertex : public Vertex
  {
    public:
      BezierVertex ( double vx = 0.0, double vy = 0.0, double vc1x = 0.0, double vc1y = 0.0, double vc2x = 0.0, double vc2y = 0.0, bool vrelative = false ) :
          Vertex ( vx, vy, vrelative ), c1x ( vc1x ), c1y ( vc1y ), c2x ( vc2x ), c2y ( vc2y )
      {}

      virtual ~BezierVertex()
      { }

      double c1x, c1y, c2x, c2y;
  };

  typedef std::vector<BezierVertex> BezierVertices;

  /**
   * \image html bezierline.png "Bezierline"
   *
   * @author Rick L Vinyard Jr
   */
  class Bezierline : public Shape
  {
    protected:

      Bezierline ( const Glib::ustring& id, BezierVertices vertices = BezierVertices() );

    public:
      PAPYRUS_DRAWABLE(Bezierline);

      /** Creates a polyline from a specified set of vertices */
      static pointer create ( BezierVertices vertices = BezierVertices() );

      /** Creates a polyline from a specified set of vertices */
      static pointer create ( const Glib::ustring& id, BezierVertices vertices = BezierVertices() );

      virtual ~Bezierline();

      Bezierline& operator= ( const Bezierline& other );

      BezierVertex get_vertex ( unsigned n );

      const BezierVertices& get_vertices();

      void add_vertex ( BezierVertex v );

      void add_vertex ( double x, double y, double c1x, double c1y, double c2x, double c2y );

      void set_vertex ( unsigned n, BezierVertex v );

      void set_vertex ( unsigned n, double x, double y, double c1x, double c1y, double c2x, double c2y );

      void set_vertices ( BezierVertices vertices );

      virtual Drawable::pointer start_marker();

      virtual void set_start_marker ( Drawable::pointer );

      virtual Drawable::pointer end_marker();

      virtual void set_end_marker ( Drawable::pointer );

      virtual Drawable::pointer vertex_marker();

      virtual void set_vertex_marker ( Drawable::pointer );

      virtual void draw ( Context& cairo ) const;

      /** Draws on the provided context */
      virtual void draw_shape( Context& cairo ) const;

      sigc::signal<void, unsigned>& signal_vertex();
      sigc::signal<void>& signal_vertices();
      sigc::signal<void> signal_start_marker();
      sigc::signal<void> signal_end_marker();
      sigc::signal<void> signal_vertex_marker();

    protected:
      BezierVertices m_vertices;
      Drawable::pointer m_start_marker, m_end_marker, m_vertex_marker;

      sigc::signal<void, unsigned> m_signal_vertex;
      sigc::signal<void> m_signal_vertices;
      sigc::signal<void> m_signal_start_marker;
      sigc::signal<void> m_signal_end_marker;
      sigc::signal<void> m_signal_vertex_marker;

      virtual void on_vertex_changed ( int n );

      virtual void on_vertices_changed();

  };

}

#endif
