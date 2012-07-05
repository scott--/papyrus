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
#ifndef PAPYRUSTEXT_H
#define PAPYRUSTEXT_H

#include <string>

#include <papyrus/shape.h>

/**
 * \page guide_text Text
 *
 * Text is specified by a size and a string (for now, not all cairo's text
 * handling features are exposed, such as setting the font).
 *
 * A text object is drawn such that the shape's (x,y) coordinate defines the
 * lower-left corner of the text area.
 *
 * The following contains an example that will add a text string to a canvas.
 *
 * The blue lines represent the x and y axes, and show through since an alpha value
 * of 0.9 is used.
 *
 * \image html text.png "Text drawn by example code below"
 *
 * \dontinclude shapes.cpp
 * \skip add_text
 * \until }
 *
 */


namespace Papyrus
{

  /**
   * A text object is drawn such that the shape's (x,y) coordinate defines the
   * lower-left corner of the text area.
   *
   * \image html text.png "Text"
   *
   * @author Rick L Vinyard Jr
   */
  class Text : public Shape
  {
    protected:
      Text (
          const Glib::ustring& id,
          const Glib::ustring& text,
          double size,
          const Glib::ustring& family,
          Cairo::FontSlant slant,
          Cairo::FontWeight weight,
          Fill::pointer fill,
          Stroke::pointer stroke
      );

    public:
      PAPYRUS_DRAWABLE(Text);

      static Text::pointer create ( const Glib::ustring& text = Glib::ustring(),
                                    double size = 12.0,
                                    const Glib::ustring& family = Glib::ustring(),
                                    Cairo::FontSlant slant = Cairo::FONT_SLANT_NORMAL,
                                    Cairo::FontWeight weight = Cairo::FONT_WEIGHT_NORMAL,
                                    Fill::pointer fill=Fill::pointer(),
                                    Stroke::pointer stroke=Stroke::pointer()
                                  );

      static Text::pointer create ( const Glib::ustring& id,
                                    const Glib::ustring& text = Glib::ustring(),
                                    double size = 12.0,
                                    const Glib::ustring& family = Glib::ustring(),
                                    Cairo::FontSlant slant = Cairo::FONT_SLANT_NORMAL,
                                    Cairo::FontWeight weight = Cairo::FONT_WEIGHT_NORMAL,
                                    Fill::pointer fill=Fill::pointer(),
                                    Stroke::pointer stroke=Stroke::pointer()
                                  );

      virtual ~Text();

      const Glib::ustring& font_family();

      Cairo::FontSlant font_slant();

      Cairo::FontWeight font_weight();

      void set_font_face ( const Glib::ustring& family,
                           Cairo::FontSlant slant,
                           Cairo::FontWeight weight
                         );

      const Cairo::FontOptions& font_options();

      void set_font_options ( const Cairo::FontOptions& font_options );

      double size();

      void set_size ( double );

      Glib::ustring text() const;

      void set_text ( const Glib::ustring );

      virtual void draw_shape ( Context& cairo ) const;

      sigc::signal<void> signal_text();

      sigc::signal<void> signal_font();

    protected:
      Glib::ustring m_text;
      double m_size;
      Glib::ustring m_family;
      Cairo::FontSlant m_slant;
      Cairo::FontWeight m_weight;
      Cairo::FontOptions m_font_options;

      sigc::signal<void> m_signal_text;

      sigc::signal<void> m_signal_font;

  };

}

#endif
