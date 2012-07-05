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
#include "bezierline.h"

namespace Papyrus
{

  Bezierline::Bezierline ( const Glib::ustring& id, BezierVertices vertices ) :
      Shape ( id ),
      m_vertices ( vertices )
  {}

  Bezierline::pointer Bezierline::create ( BezierVertices vertices )
  {
    PAPYRUS_CREATE ( Bezierline ( Glib::ustring(), vertices ) );
  }

  Bezierline::pointer Bezierline::create ( const Glib::ustring& id, BezierVertices vertices )
  {
    PAPYRUS_CREATE ( Bezierline ( id, vertices ) );
  }

  Bezierline::~Bezierline() {}

  Bezierline & Bezierline::operator = ( const Bezierline & other )
  {
    Shape::operator= ( other );
    m_vertices = other.m_vertices;

    if ( other.m_start_marker )
      m_start_marker = other.m_start_marker->clone();
    else
      m_start_marker = other.m_start_marker;

    if ( other.m_end_marker )
      m_end_marker = other.m_end_marker->clone();
    else
      m_end_marker = other.m_end_marker;

    if ( other.m_vertex_marker )
      m_vertex_marker = other.m_vertex_marker->clone();
    else
      m_vertex_marker = other.m_vertex_marker;

    m_signal_vertices.emit();
    m_signal_start_marker.emit();
    m_signal_end_marker.emit();
    m_signal_vertex_marker.emit();
    
    return *this;
  }

  BezierVertex Bezierline::get_vertex ( unsigned n )
  {
    if ( n < m_vertices.size() )
      return m_vertices[n];
    else
      return BezierVertex();
  }

  const BezierVertices& Bezierline::get_vertices()
  {
    return m_vertices;
  }

  void Bezierline::add_vertex ( BezierVertex v )
  {
    m_vertices.push_back ( v );
    this->on_vertex_changed ( m_vertices.size()-1 );
  }

  void Bezierline::add_vertex ( double x, double y, double c1x, double c1y, double c2x, double c2y )
  {
    m_vertices.push_back ( BezierVertex ( x,y, c1x, c1y, c2x, c2y ) );
    this->on_vertex_changed ( m_vertices.size()-1 );
  }

  void Bezierline::set_vertex ( unsigned n, BezierVertex v )
  {
    if ( n < m_vertices.size() )
    {
      m_vertices[n] = v;
      this->on_vertex_changed ( n );
    }
  }

  void Bezierline::set_vertex ( unsigned n, double x, double y, double c1x, double c1y, double c2x, double c2y )
  {
    if ( n < m_vertices.size() )
    {
      m_vertices[n] = BezierVertex ( x, y, c1x, c1y, c2x, c2y );
      this->on_vertex_changed ( n );
    }
  }

  void Bezierline::set_vertices ( BezierVertices vertices )
  {
    m_vertices = vertices;
    this->on_vertices_changed();
  }

  Drawable::pointer Bezierline::start_marker( )
  {
    return m_start_marker;
  }

  void Bezierline::set_start_marker ( Drawable::pointer marker )
  {
    if ( marker )
      m_start_marker = marker->clone();
    else
      m_start_marker = marker;

    this->shape_changed();
    m_signal_start_marker.emit();
    m_signal_changed.emit();
  }

  Drawable::pointer Bezierline::end_marker( )
  {
    return m_end_marker;
  }

  void Bezierline::set_end_marker ( Drawable::pointer marker )
  {
    if ( marker )
      m_end_marker = marker->clone();
    else
      m_end_marker = marker;

    this->shape_changed();
    m_signal_end_marker.emit();
    m_signal_changed.emit();
  }

  Drawable::pointer Bezierline::vertex_marker( )
  {
    return m_vertex_marker;
  }

  void Bezierline::set_vertex_marker ( Drawable::pointer marker )
  {
    if ( marker )
      m_vertex_marker = marker->clone();
    else
      m_vertex_marker = marker;

    m_signal_vertex_marker.emit();
    m_signal_changed.emit();
  }

  void Bezierline::draw ( Context& cairo ) const
  {
    if ( m_fill )
    {
      m_fill->render ( cairo );
      this->draw_shape ( cairo );
      cairo.fill();
    }

    if ( m_stroke )
    {
      m_stroke->render ( cairo );
      this->draw_stroke_path ( cairo );
      cairo.stroke();
    }

    if ( m_vertices.size() < 1 )
      return;

    BezierVertices::const_iterator i1, i2;
    BezierVertices::const_reverse_iterator ri1, ri2;

    if ( m_start_marker )
    {
      i1 = m_vertices.begin();
      i2 = m_vertices.begin() + 1;
      // TODO fix for new matrix model
//         m_start_marker->set_translate( i1->x, i1->y );
//         if ( i2 != m_vertices.end() )
//           m_start_marker->set_rotate(
//               atan ( ( i2->y - i1->y ) /
//               ( i2->x - i1->x )
//                    ) );
      m_start_marker->render ( cairo );
    }

    if ( m_vertex_marker )
    {}

    if ( m_end_marker )
    {
      ri1 = m_vertices.rbegin();
      ri2 = m_vertices.rbegin() + 1;
      // TODO fix for new matrix model
//         m_end_marker->set_translate( ri1->x, ri1->y );
//         if ( ri2 != m_vertices.rend() )
//           m_end_marker->set_rotate(
//               atan ( ( ri2->y - ri1->y ) /
//               ( ri2->x - ri1->x )
//                    ) );
      m_end_marker->render ( cairo );
    }

  }

  void Bezierline::draw_shape ( Context& cairo ) const
  {
    if ( m_vertices.size() < 2 )
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
  }

  sigc::signal<void, unsigned>& Bezierline::signal_vertex()
  {
    return m_signal_vertex;
  }

  sigc::signal<void>& Bezierline::signal_vertices()
  {
    return m_signal_vertices;
  }

  sigc::signal<void> Bezierline::signal_start_marker()
  {
    return m_signal_start_marker;
  }

  sigc::signal<void> Bezierline::signal_end_marker()
  {
    return m_signal_end_marker;
  }

  sigc::signal<void> Bezierline::signal_vertex_marker()
  {
    return m_signal_vertex_marker;
  }

  void Bezierline::on_vertex_changed ( int n )
  {
    this->shape_changed();
    m_signal_vertex.emit ( n );
    m_signal_vertices.emit();
  }

  void Bezierline::on_vertices_changed()
  {
    this->shape_changed();
    m_signal_vertices.emit();
  }

}
