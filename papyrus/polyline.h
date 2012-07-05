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
#ifndef PAPYRUSPOLYLINE_H
#define PAPYRUSPOLYLINE_H

#include <vector>

#include <papyrus/primitives.h>
#include <papyrus/shape.h>
#include <papyrus/marker.h>

/**
 * \page guide_polyline Polylines
 * A polyline is drawn as a set of ordered vertices relative to the shape's x,y
 * coordinate. Polylines may be filled or unfilled. An unfilled polyline is more
 * conceptually familiar with what is implied by a polyline. A filled polyline
 * is essentially an unclosed polygon.
 *
 * The following contains an example that will add an unfilled polygon to a canvas.
 * The blue lines represent the x and y axes, and show through since an alpha value
 * of 0.9 is used.
 *
 * \image html polyline.png "Unfilled Polyline drawn by example code below"
 *
 * \dontinclude shapes.cpp
 * \skip add_polyline_unfilled
 * \until }
 *
 * The following illustrates the effects of filling a polyline.
 *
 * \image html polyline_filled.png "Filled Polyline drawn by example code below"
 *
 * \dontinclude shapes.cpp
 * \skip add_polyline_filled
 * \until }
 *
 */


namespace Papyrus
{

  /**
   * A simple extension of the point primitive to include an additional value used by polyline
   * to determine whether the vertex is absolute or relative.
   */
  struct Vertex: public Point
  {
    public:
      Vertex ( double vx=0.0, double vy=0.0, bool vrelative=false ) : Point(vx,vy), relative ( vrelative ) {}

      Vertex( const Point& p, bool vrelative=false ): Point(p), relative(vrelative) { }

      Vertex( const Vertex& v ): Point(v.x, v.y), relative(v.relative) { }

      bool relative;
  };

  typedef std::vector<Vertex> Vertices;

  /**
   * A polyline is drawn as a set of ordered vertices relative to the shape's x,y
   * coordinate. Polylines may be filled or unfilled. An unfilled polyline is more
   * conceptually familiar with what is implied by a polyline. A filled polyline
   * is essentially an unclosed polygon.
   *
   * \image html polyline.png "Unfilled Polyline"
   * \image html polyline_filled.png "Filled Polyline"
   *
   * @author Rick L Vinyard Jr
   * TODO change marker handling to allow setting positional markers
   */
  class Polyline : public Shape
  {
    protected:

      Polyline ( const Glib::ustring& id, const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke );

    public:
      PAPYRUS_DRAWABLE(Polyline);

      /** Creates a polyline from a specified set of vertices */
      static pointer create ( const Vertices& vertices = Vertices(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& id, Vertices vertices = Vertices(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& id, Vertices vertices, Fill::pointer fill, Stroke::pointer stroke = Stroke::pointer() );

      virtual ~Polyline();

      Polyline& operator= ( const Polyline& other );

      Vertex vertex ( unsigned n ) const;

      const Vertices& vertices() const;

      void add_vertex ( Vertex v );

      void add_vertex ( double x, double y );

      void set_vertex ( unsigned n, Vertex v );

      void set_vertex ( unsigned n, double x, double y );

      void set_vertices ( const Vertices& vertices );

      virtual Marker::pointer marker(MarkerPosition position);

      /**
       * Sets the specified marker to the provided drawable
       *
       * @return true if successfully set, false otherwise
       */
      virtual bool set_marker ( MarkerPosition position, Marker::pointer marker );

      virtual void draw ( Context& cairo ) const;

      /** Draws on the provided context */
      virtual void draw_shape ( Context& cairo ) const;

      sigc::signal<void, unsigned> signal_vertex();
      sigc::signal<void> signal_vertices();

    protected:
      Vertices m_vertices;
      Marker::pointer m_markers[3];

      sigc::signal<void, unsigned> m_signal_vertex;
      sigc::signal<void> m_signal_vertices;

      virtual void on_vertex_changed ( int n );

      virtual void on_vertices_changed();

      void update_marker_position( MarkerPosition n );

      /**
       * This method extends the parent Shape method by incorporating any marker
       * extents in the raw extents
       */
      virtual Region calculate_pre_viewbox_extents(const Matrix& m = Matrix::Identity) const;

      mutable sigc::connection m_marker_changed_connections[3];
      
      void on_marker_changed(MarkerPosition which);

  };

}

#endif
