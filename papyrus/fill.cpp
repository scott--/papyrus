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
#include "fill.h"

#include <sstream>
#include <iomanip>

#include "rgba.h"
#include "color.h"

namespace Papyrus
{

  Fill::Fill ( Paint::pointer paint, Cairo::FillRule rule ) :
      Renderable( Glib::ustring() ),
      m_paint ( paint ),
      m_fill_rule( rule )
  {
    if ( m_paint ) m_paint_changed_connection = m_paint->signal_changed().connect( sigc::mem_fun(*this, &Fill::on_paint_changed) );
  }

  Fill::pointer Fill::create(Paint::pointer paint, Cairo::FillRule rule)
  {
    return pointer( new Fill(paint, rule) );
  }

  Fill::pointer Fill::create(Cairo::RefPtr<Cairo::Pattern> pattern, Cairo::FillRule rule)
  {
    return pointer( new Fill(Color::create(pattern), rule) );
  }

  Fill::pointer Fill::create(const RGBA& rgba, Cairo::FillRule rule)
  {
    return pointer( new Fill(Color::create(rgba), rule) );
  }

  Fill::pointer Papyrus::Fill::create(const Glib::ustring & color, Cairo::FillRule rule)
  {
    if ( strcaseeq( color, "none" ) ) return pointer( new Fill( RGBA(0.0, 0.0, 0.0, 0.0), rule ) );
    return pointer( new Fill(RGBA(color), rule ) );
  }

  Fill::~Fill()
  { }

  Fill & Fill::operator = ( const Fill & other )
  {
    if ( m_paint_changed_connection ) m_paint_changed_connection.disconnect();
    m_paint = other.m_paint;
    if ( m_paint ) m_paint_changed_connection = m_paint->signal_changed().connect( sigc::mem_fun(*this, &Fill::on_paint_changed) );
    
    m_fill_rule = other.m_fill_rule;

    m_signal_paint_changed.emit();
    m_signal_fill_rule_changed.emit();
    m_signal_changed.emit();
    return *this;
  }

  bool Fill::operator== ( const Fill& other ) const
  {
    // TODO this is kind of hacked and needs to be improved
    return ( m_paint == other.m_paint &&
             m_fill_rule == other.m_fill_rule );
  }

  bool Fill::operator!= ( const Fill& other ) const
  {
    return ! this->operator== ( other );
  }

  Paint::pointer Fill::paint()
  {
    return m_paint;
  }

  void Fill::set_paint ( Paint::pointer paint )
  {
    if ( m_paint_changed_connection ) m_paint_changed_connection.disconnect();
    m_paint = paint;
    if ( m_paint ) m_paint_changed_connection = m_paint->signal_changed().connect( sigc::mem_fun(*this, &Fill::on_paint_changed) );

    m_signal_paint_changed.emit();
    m_signal_changed.emit();
  }

  Cairo::FillRule Fill::fill_rule()
  {
    return m_fill_rule;
  }

  void Fill::set_fill_rule( Cairo::FillRule rule )
  {
    m_fill_rule = rule;
    m_signal_fill_rule_changed.emit();
    m_signal_changed.emit();
  }

  void Fill::render ( Context& cairo ) const
  {
    if ( m_paint ) {
      bool old_fill_flag = cairo.set_flag( RENDER_HINT_FILL );
      m_paint->render(cairo);
      cairo.set_flag( RENDER_HINT_FILL, old_fill_flag );
    }
    cairo->set_fill_rule( m_fill_rule );
  }

  Glib::ustring Fill::svg(unsigned depth)
  {
    std::ostringstream s;

    if ( ! m_paint )
      return Glib::ustring();

    s << " fill=\"";

    // TODO fix this
//     if ( m_paint and m_paint->cairo_pattern() ) switch( m_paint->cairo_pattern()->get_type() )
//     {
//       case Cairo::PATTERN_TYPE_SOLID:
//         {
//           Cairo::RefPtr<Cairo::SolidPattern> p;
//           double r, g, b, a;
//           p = Cairo::RefPtr<Cairo::SolidPattern>::cast_dynamic(m_paint->cairo_pattern());
//           // HACK to get around cairomm 1.2 which doesn't have all the solid pattern methods wrapped
// //           p->get_rgba( r, g, b, a );
//           #if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 4, 0)
//             cairo_pattern_get_rgba( p->cobj(), &r, &g, &b, &a );
//             s << "#" << std::hex << std::setfill('0') << std::setw(2) << (unsigned)(255*r)
//               << std::setw(2) << (unsigned)(255*g)
//               << std::setw(2) << (unsigned)(255*b);
//           #endif
//         }
//         break;
//       case Cairo::PATTERN_TYPE_SURFACE:
//       case Cairo::PATTERN_TYPE_LINEAR:
//       case Cairo::PATTERN_TYPE_RADIAL:
//         break;
//     }

    s << "\"";
    return s.str();
  }

  sigc::signal<void> Fill::signal_paint_changed()
  {
    return m_signal_paint_changed;
  }

  sigc::signal<void> Fill::signal_fill_rule_changed()
  {
    return m_signal_fill_rule_changed;
  }

  void Fill::on_paint_changed()
  {
    m_signal_paint_changed.emit();
    m_signal_changed.emit();
  }

}

