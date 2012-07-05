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
#include "polyline.h"

namespace Papyrus
{

  Polyline::Polyline ( const Glib::ustring& id, const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke ) :
      Shape ( id, fill, stroke ),
      m_vertices ( vertices )
  {}

  Polyline::pointer Polyline::create ( const Vertices& vertices, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Polyline ( Glib::ustring(), vertices, Fill::pointer(), stroke ) );
  }

  Polyline::pointer Polyline::create ( const Vertices& vertices, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Polyline ( Glib::ustring(), vertices, fill, stroke ) );
  }

  Polyline::pointer Polyline::create ( const Glib::ustring& id, Vertices vertices, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Polyline ( id, vertices, Fill::pointer(), stroke ) );
  }

  Polyline::pointer Polyline::create ( const Glib::ustring& id, Vertices vertices, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Polyline ( id, vertices, fill, stroke ) );
  }

  Polyline::~Polyline() {}

  Polyline & Polyline::operator = ( const Polyline & other )
  {
    Shape::operator= ( other );
    m_vertices = other.m_vertices;

    for ( int i=0; i < 3; i++ )
    {
      if ( other.m_markers[i] )
        m_markers[i] = papyrus_dynamic_pointer_cast<Marker>(other.m_markers[i]->clone());
      else
        m_markers[i] = Marker::pointer();
    }

    m_signal_vertices.emit();
    return *this;
  }

  Vertex Polyline::vertex ( unsigned n ) const
  {
    if ( n < m_vertices.size() )
      return m_vertices[n];
    else
      return Vertex();
  }

  const Vertices& Polyline::vertices() const
  {
    return m_vertices;
  }

  void Polyline::add_vertex ( Vertex v )
  {
    m_vertices.push_back ( v );
    this->on_vertex_changed ( m_vertices.size()-1 );
  }

  void Polyline::add_vertex ( double x, double y )
  {
    m_vertices.push_back ( Vertex ( x,y ) );
    this->on_vertex_changed ( m_vertices.size()-1 );
  }

  void Polyline::set_vertex ( unsigned n, Vertex v )
  {
    if ( n < m_vertices.size() )
    {
      m_vertices[n] = v;
      this->on_vertex_changed ( n );
    }
  }

  void Polyline::set_vertex ( unsigned n, double x, double y )
  {
    if ( n < m_vertices.size() )
    {
      m_vertices[n] = Vertex ( x, y );
      this->on_vertex_changed ( n );
    }
  }

  void Polyline::set_vertices ( const Vertices& vertices )
  {
    m_vertices = vertices;
    this->on_vertices_changed();
  }

  Marker::pointer Polyline::marker ( MarkerPosition which )
  {
    if ( which < 0 or which > END_MARKER ) return Marker::pointer();
    return m_markers[which];
  }

  bool Polyline::set_marker ( MarkerPosition which, Marker::pointer marker )
  {
    if ( which < 0 or which > END_MARKER ) return false;

    if ( m_marker_changed_connections[which] ) m_marker_changed_connections[which].disconnect();

    m_markers[which] = marker;
    if ( m_markers[which] )
      m_marker_changed_connections[which] =
          marker->signal_changed().connect(sigc::bind(sigc::mem_fun(*this, &Polyline::on_marker_changed), which));

    this->shape_changed();
    return true;
  }

  void Polyline::draw ( Context& cairo ) const
  {
    if ( m_fill )
    {
      this->draw_shape ( cairo );
      m_fill->render ( cairo );
      cairo.fill();
    }

    if ( m_stroke )
    {
      this->draw_stroke_path( cairo );
      m_stroke->render( cairo );
      cairo.stroke();
    }

    if ( m_vertices.size() < 1 ) return;

    Vertices::const_iterator i1, i2;
    Vertices::const_reverse_iterator ri1, ri2;

    if ( m_markers[START_MARKER] )
    {
      m_marker_changed_connections[START_MARKER].block();
      i1 = m_vertices.begin();
      i2 = m_vertices.begin() + 1;
      m_markers[START_MARKER]->set_xy( i1->x, i1->y );
      if ( i2 != m_vertices.end() )
        m_markers[START_MARKER]->set_rotation (
            atan ( ( i2->y - i1->y ) /
                   ( i2->x - i1->x )
                 ) );
      if ( cairo.is_flag_unset(RENDER_SUPPRESS_MATRIX) ) 
        m_markers[START_MARKER]->render(cairo);
      m_marker_changed_connections[START_MARKER].unblock();
    }

//     if ( m_markers[VERTEX_MARKER] )
//     {}

    if ( m_markers[END_MARKER] )
    {
      m_marker_changed_connections[END_MARKER].block();
      ri1 = m_vertices.rbegin();
      ri2 = m_vertices.rbegin() + 1;
      m_markers[END_MARKER]->set_xy( ri1->x, ri1->y );
      if ( ri2 != m_vertices.rend() )
        m_markers[END_MARKER]->set_rotation (
            atan ( ( ri2->y - ri1->y ) /
                   ( ri2->x - ri1->x )
                 ) );
      if ( cairo.is_flag_unset(RENDER_SUPPRESS_MATRIX) )
        m_markers[END_MARKER]->render(cairo);
      m_marker_changed_connections[END_MARKER].unblock();
    }

  }

  void Polyline::draw_shape ( Context& cairo ) const
  {
    if ( m_vertices.size() < 2 )
      return;
    cairo->move_to ( m_vertices[0].x, m_vertices[0].y );
    for ( Vertices::const_iterator i = m_vertices.begin() +1; i != m_vertices.end(); i++ )
    {
      if ( i->relative )
        cairo->rel_line_to ( i->x, i->y );
      else
        cairo->line_to ( i->x, i->y );
    }
  }

  sigc::signal<void, unsigned> Polyline::signal_vertex()
  {
    return m_signal_vertex;
  }

  sigc::signal<void> Polyline::signal_vertices()
  {
    return m_signal_vertices;
  }

  void Polyline::on_vertex_changed ( int n )
  {
    this->shape_changed();
    m_signal_vertex.emit ( n );
    m_signal_vertices.emit();
  }

  void Polyline::on_vertices_changed()
  {
    this->shape_changed();
    m_signal_vertices.emit();
  }

  Region Polyline::calculate_pre_viewbox_extents(const Matrix& m) const
  {
    Region e;
    e = Shape::calculate_extents(m);
//     if ( m_markers[START_MARKER] ) e.include ( m_markers[START_MARKER]->calculate_extents(m) );
//     if ( m_markers[END_MARKER] ) e.include ( m_markers[END_MARKER]->calculate_extents(m) );
    return e;
  }

  void Polyline::update_marker_position ( MarkerPosition n )
  {
  }

  void Polyline::on_marker_changed(MarkerPosition which)
  {
    this->shape_changed();
  }


}

