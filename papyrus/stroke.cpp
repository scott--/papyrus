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
#include "stroke.h"

#include "rgba.h"
#include "color.h"

namespace Papyrus
{

  Stroke::Stroke ( double width, Cairo::LineCap cap, Cairo::LineJoin join ) :
      Renderable ( Glib::ustring() ),
      m_width ( width ),
      m_cap ( cap ),
      m_join ( join ),
      m_miter_limit ( INFINITY ),
      m_dash_offset ( 0.0 )
  { }

  Stroke::Stroke ( Paint::pointer paint,
                   double width, Cairo::LineCap cap, Cairo::LineJoin join ) :
      Renderable ( Glib::ustring() ),
      m_paint ( paint ),
      m_width ( width ),
      m_cap ( cap ),
      m_join ( join ),
      m_miter_limit ( INFINITY ),
      m_dash_offset ( 0.0 )
  {
    if ( m_paint ) m_paint_changed_connection = m_paint->signal_changed().connect( sigc::mem_fun(*this, &Stroke::on_paint_changed) );
  }

  Stroke::pointer Stroke::create ( Paint::pointer paint, double width, Cairo::LineCap cap, Cairo::LineJoin join )
  {
    return pointer ( new Stroke ( paint, width, cap, join ) );
  }

  Stroke::pointer Stroke::create ( double width, Cairo::LineCap cap, Cairo::LineJoin join )
  {
    return pointer ( new Stroke ( width, cap, join ) );
  }

  Stroke::pointer Stroke::create ( Cairo::RefPtr<Cairo::Pattern> pattern, double width, Cairo::LineCap cap, Cairo::LineJoin join )
  {
    return pointer ( new Stroke ( Color::create(pattern), width, cap, join ) );
  }

  Stroke::pointer Stroke::create ( const RGBA& rgba, double width, Cairo::LineCap cap, Cairo::LineJoin join )
  {
    return pointer ( new Stroke ( Color::create(rgba), width, cap, join ) );
  }

  Stroke::pointer Stroke::create ( const Glib::ustring & color, double width, Cairo::LineCap cap, Cairo::LineJoin join )
  {
    if ( strcaseeq( color, "none" ) ) return pointer( new Stroke( RGBA(0.0, 0.0, 0.0, 0.0), 0.0, Cairo::LINE_CAP_BUTT, Cairo::LINE_JOIN_MITER ) );
    return pointer ( new Stroke ( RGBA ( color ), width, cap, join ) );
  }

  Stroke::~Stroke()
  { }

  Stroke & Stroke::operator = ( const Stroke & other )
  {
    if ( m_paint_changed_connection ) m_paint_changed_connection.disconnect();
    m_paint = other.m_paint;
    if ( m_paint ) m_paint_changed_connection = m_paint->signal_changed().connect( sigc::mem_fun(*this, &Stroke::on_paint_changed) );
    
    m_width = other.m_width;
    m_cap = other.m_cap;
    m_join = other.m_join;
    m_miter_limit = other.m_miter_limit;
    m_dash_array.resize(other.m_dash_array.size());
    m_dash_array = other.m_dash_array;
    m_dash_offset = other.m_dash_offset;

    m_signal_paint_changed.emit();
    m_signal_width_changed.emit();
    m_signal_cap_changed.emit();
    m_signal_join_changed.emit();
    m_signal_miter_limit_changed.emit();
    m_signal_dash_changed.emit();
    m_signal_changed.emit();
    
    return *this;
  }

  bool Stroke::operator== ( const Stroke& other ) const
  {
    // TODO this is kind of hacked and needs to be improved
    return ( m_paint == other.m_paint &&
             m_width == other.m_width &&
             m_cap == other.m_cap &&
             m_join == other.m_join &&
             m_miter_limit == other.m_miter_limit &&
             //              m_dash_array == other.m_dash_array &&
             m_dash_offset == other.m_dash_offset );
  }

  bool Stroke::operator!= ( const Stroke& other ) const
  {
    return ! this->operator== ( other );
  }

  const std::valarray< double >& Stroke::dash_array()
  {
    return m_dash_array;
  }

  double Stroke::dash_offset()
  {
    return m_dash_offset;
  }

  void Stroke::set_dash ( const std::valarray< double > dashes, double offset )
  {
    m_dash_array.resize( dashes.size() );
    m_dash_array = dashes;
    m_dash_offset = offset;
    m_signal_dash_changed.emit();
    m_signal_changed.emit();
  }

  Cairo::LineCap Stroke::cap()
  {
    return m_cap;
  }

  void Stroke::set_cap ( Cairo::LineCap cap )
  {
    m_cap = cap;
    m_signal_cap_changed.emit();
    m_signal_changed.emit();
  }

  void Stroke::set_cap(const Glib::ustring & c)
  {
    if ( c.lowercase() == "butt" ) this->set_cap( Cairo::LINE_CAP_BUTT );
    else if ( c.lowercase() == "round" ) this->set_cap( Cairo::LINE_CAP_ROUND );
    else if ( c.lowercase() == "square" ) this->set_cap( Cairo::LINE_CAP_SQUARE );
  }

  Cairo::LineJoin Stroke::join()
  {
    return m_join;
  }

  void Stroke::set_join ( Cairo::LineJoin join )
  {
    m_join = join;
    m_signal_join_changed.emit();
    m_signal_changed.emit();
  }

  void Stroke::set_join(const Glib::ustring & c)
  {
    if ( c.lowercase() == "miter" ) this->set_join( Cairo::LINE_JOIN_MITER );
    else if ( c.lowercase() == "round" ) this->set_join( Cairo::LINE_JOIN_ROUND );
    else if ( c.lowercase() == "bevel" ) this->set_join( Cairo::LINE_JOIN_BEVEL );
  }

  double Stroke::width()
  {
    return m_width;
  }

  void Stroke::set_width ( double width )
  {
    m_width = width;
    m_signal_width_changed.emit();
    m_signal_changed.emit();
  }

  double Stroke::miter_limit()
  {
    return m_miter_limit;
  }

  void Stroke::set_miter_limit ( double limit )
  {
    m_miter_limit = limit;
    m_signal_miter_limit_changed.emit();
    m_signal_changed.emit();
  }

  Paint::pointer Stroke::paint()
  {
    return m_paint;
  }

  void Stroke::set_paint ( Paint::pointer paint )
  {
    if ( m_paint_changed_connection ) m_paint_changed_connection.disconnect();
    m_paint = paint;
    if ( m_paint ) m_paint_changed_connection = m_paint->signal_changed().connect( sigc::mem_fun(*this, &Stroke::on_paint_changed) );

    m_signal_paint_changed.emit();
    m_signal_changed.emit();
  }

  void Stroke::render ( Context& cairo ) const
  {
    if ( m_paint ) {
      bool old_stroke_flag = cairo.set_flag( RENDER_HINT_STROKE );
      m_paint->render(cairo);
      cairo.set_flag( RENDER_HINT_STROKE, old_stroke_flag );
    }
    cairo->set_line_width ( m_width );
    cairo->set_line_cap ( m_cap );
    cairo->set_line_join ( m_join );
    if ( m_join == Cairo::LINE_JOIN_MITER ) cairo->set_miter_limit ( m_miter_limit );

    // HACK because cairomm doesn't have a method that takes a const parameter
    std::valarray<double> dash_array = m_dash_array;
    if ( m_dash_array.size() > 0 ) cairo->set_dash ( dash_array, m_dash_offset );
  }

  sigc::signal<void> Stroke::signal_paint_changed()
  {
    return m_signal_paint_changed;
  }

  sigc::signal<void> Stroke::signal_width_changed()
  {
    return m_signal_width_changed;
  }

  sigc::signal<void> Stroke::signal_cap_changed()
  {
    return m_signal_cap_changed;
  }

  sigc::signal<void> Stroke::signal_join_changed()
  {
    return m_signal_join_changed;
  }

  sigc::signal<void> Stroke::signal_miter_limit_changed()
  {
    return m_signal_miter_limit_changed;
  }

  sigc::signal<void> Stroke::signal_dash_changed()
  {
    return m_signal_dash_changed;
  }

  void Stroke::on_paint_changed()
  {
    m_signal_paint_changed.emit();
    m_signal_changed.emit();
  }

}

