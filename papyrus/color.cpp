/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
#include "color.h"
#include "rgba.h"

namespace Papyrus
{

  Color::Color ( const Glib::ustring& id, Cairo::RefPtr<Cairo::Pattern> pattern ):
      Paint ( id ),
      m_pattern(pattern)
  {
  }

  Color::pointer Color::create()
  {
    return pointer( new Color( Glib::ustring(), Cairo::RefPtr<Cairo::Pattern>() ) );
  }

  Color::pointer Color::create(const Glib::ustring & color_string)
  {
    return pointer( new Color( Glib::ustring(), RGBA(color_string) ) );
  }

  Color::pointer Color::create(Cairo::RefPtr< Cairo::Pattern > p)
  {
    return pointer( new Color( Glib::ustring(), p ) );
  }

  Color::pointer Color::create(const Glib::ustring& id, const Glib::ustring & color_string)
  {
    return pointer( new Color( id, RGBA(color_string) ) );
  }

  Color::pointer Color::create(const Glib::ustring& id, Cairo::RefPtr< Cairo::Pattern > p)
  {
    return pointer( new Color( id, p ) );
  }

  Color::~Color()
  {
  }

  Cairo::RefPtr< Cairo::Pattern > Color::cairo_pattern() const
  {
    return m_pattern;
  }

  Color::operator Cairo::RefPtr < Cairo::Pattern >() const
  {
    return m_pattern;
  }

  Color& Color::operator=( Color::pointer other )
  {
    this->set(other);
    return *this;
  }
  
  Color & Color::operator =(Cairo::RefPtr< Cairo::Pattern > p)
  {
    this->set(p);
    return *this;
  }

  Color & Color::operator =(Cairo::RefPtr< Cairo::Context > c)
  {
    this->set(c);
    return *this;
  }

  Color & Color::operator =(const Color & other)
  {
    m_pattern = other.m_pattern;
    m_signal_changed.emit();
    return *this;
  }

  void Color::set( Color::pointer other )
  {
    if ( other )
      m_pattern = other->m_pattern;
    else
      m_pattern = Cairo::RefPtr<Cairo::Pattern>();
    m_signal_changed.emit();
  }
  
  void Color::set(Cairo::RefPtr< Cairo::Pattern > p)
  {
    m_pattern = p;
    m_signal_changed.emit();
  }

  void Color::set(Cairo::RefPtr< Cairo::Context > c)
  {
    if ( c ) m_pattern = c->get_source();
    else m_pattern = Cairo::RefPtr<Cairo::Pattern>();
    
    m_signal_changed.emit();
  }

  void Color::render ( Context& cairo ) const
  {
    if ( m_pattern ) cairo->set_source(m_pattern);
  }

}

