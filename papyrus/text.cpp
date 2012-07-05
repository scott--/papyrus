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
#include "text.h"

namespace Papyrus
{

  Text::Text ( const Glib::ustring& id,
               const Glib::ustring& text,
               double size,
               const Glib::ustring& family,
               Cairo::FontSlant slant,
               Cairo::FontWeight weight,
               Fill::pointer fill,
               Stroke::pointer stroke
             ) :
      Shape ( id, fill, stroke ),
      m_text ( text ),
      m_size ( size ),
      m_family ( family ),
      m_slant ( slant ),
      m_weight ( weight ) {}

  Text::pointer Text::create ( const Glib::ustring& text,
                               double size,
                               const Glib::ustring& family,
                               Cairo::FontSlant slant,
                               Cairo::FontWeight weight,
                               Fill::pointer fill,
                               Stroke::pointer stroke
                             )
  {
    PAPYRUS_CREATE ( Text ( Glib::ustring(), text, size, family, slant, weight, fill, stroke ) );
  }

  Text::pointer Text::create ( const Glib::ustring& id,
                               const Glib::ustring& text,
                               double size,
                               const Glib::ustring& family,
                               Cairo::FontSlant slant,
                               Cairo::FontWeight weight,
                               Fill::pointer fill,
                               Stroke::pointer stroke
                             )
  {
    PAPYRUS_CREATE ( Text ( id, text, size, family, slant, weight, fill, stroke ) );
  }

  Text::~Text() {}

  const Glib::ustring& Text::font_family()
  {
    return m_family;
  }

  Cairo::FontSlant Text::font_slant()
  {
    return m_slant;
  }

  Cairo::FontWeight Text::font_weight()
  {
    return m_weight;
  }

  void Text::set_font_face ( const Glib::ustring& family,
                             Cairo::FontSlant slant,
                             Cairo::FontWeight weight
                           )
  {
    m_family = family;
    m_slant = slant;
    m_weight = weight;
    this->shape_changed();
    m_signal_font.emit();
  }

  const Cairo::FontOptions& Text::font_options()
  {
    return m_font_options;
  }

  void Text::set_font_options ( const Cairo::FontOptions& font_options )
  {
    m_font_options = font_options;
    this->shape_changed();
    m_signal_font.emit();
  }

  double Text::size()
  {
    return m_size;
  }

  void Text::set_size ( double size )
  {
    m_size = size;
    this->shape_changed();
    m_signal_font.emit();
  }

  Glib::ustring Text::text() const
  {
    return m_text;
  }

  void Text::set_text ( const Glib::ustring text )
  {
    m_text = text;
    this->shape_changed();
    m_signal_text.emit();
  }

  void Text::draw_shape ( Context& cairo ) const
  {
    cairo->move_to(0.0, 0.0);
    if ( m_family.size() > 0 )
      cairo->select_font_face ( m_family, m_slant, m_weight );
    cairo->set_font_options ( m_font_options );
    cairo->set_font_size ( m_size );

    cairo->text_path ( m_text );
  }

  sigc::signal<void> Text::signal_text()
  {
    return m_signal_text;
  }

  sigc::signal<void> Text::signal_font()
  {
    return m_signal_font;
  }

}
