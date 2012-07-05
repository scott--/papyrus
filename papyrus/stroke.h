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
#ifndef PAPYRUSSTROKE_H
#define PAPYRUSSTROKE_H

#include <cmath>
#include <papyrus/renderable.h>
#include <papyrus/drawable.h>
#include <papyrus/paint.h>

namespace Papyrus
{

  class RGBA;

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Stroke : public Renderable
  {
    protected:

      Stroke ( double width,
               Cairo::LineCap cap,
               Cairo::LineJoin join
             );

      Stroke ( Paint::pointer paint,
               double width,
               Cairo::LineCap cap,
               Cairo::LineJoin join
             );

    public:
      PAPYRUS_RENDERABLE(Stroke);

      static pointer create ( Paint::pointer paint = Paint::pointer(),
                              double width = 1.0,
                              Cairo::LineCap cap = Cairo::LINE_CAP_BUTT,
                              Cairo::LineJoin join = Cairo::LINE_JOIN_MITER
                            );

      static pointer create ( double width,
                              Cairo::LineCap cap = Cairo::LINE_CAP_BUTT,
                              Cairo::LineJoin join = Cairo::LINE_JOIN_MITER
                            );

      static pointer create ( Cairo::RefPtr<Cairo::Pattern> pattern,
                              double width = 1.0,
                              Cairo::LineCap cap = Cairo::LINE_CAP_BUTT,
                              Cairo::LineJoin join = Cairo::LINE_JOIN_MITER
                            );

      static pointer create ( const RGBA& rgba,
                              double width = 1.0,
                              Cairo::LineCap cap = Cairo::LINE_CAP_BUTT,
                              Cairo::LineJoin join = Cairo::LINE_JOIN_MITER
                            );

      static pointer create ( const Glib::ustring& color,
                              double width = 1.0,
                              Cairo::LineCap cap = Cairo::LINE_CAP_BUTT,
                              Cairo::LineJoin join = Cairo::LINE_JOIN_MITER
                            );

      virtual ~Stroke();

      Stroke& operator= ( const Stroke& other );

      bool operator== ( const Stroke& other ) const;

      bool operator!= ( const Stroke& other ) const;

      const std::valarray< double >& dash_array();

      double dash_offset();

      void set_dash ( const std::valarray< double > dashes = std::valarray<double>(), double offset = 0.0 );

      Cairo::LineCap cap();

      void set_cap ( Cairo::LineCap cap = Cairo::LINE_CAP_BUTT );

      /** Sets the cap according to the string value. Values are case independent and are the same as SVG: \e butt , \e round or \e square . */
      void set_cap( const Glib::ustring& c );

      Cairo::LineJoin join();

      void set_join ( Cairo::LineJoin join = Cairo::LINE_JOIN_MITER );

      /** Sets the join according to the string value. Values are case independent and are the same as SVG: \e miter , \e round or \e bevel . */
      void set_join( const Glib::ustring& c );

      double width();

      void set_width ( double width = 1.0 );

      double miter_limit();

      void set_miter_limit ( double limit = INFINITY );

      Paint::pointer paint();

      void set_paint ( Paint::pointer paint = Paint::pointer() );

      virtual void render ( Context& cairo ) const;

      sigc::signal<void> signal_paint_changed();
      sigc::signal<void> signal_width_changed();
      sigc::signal<void> signal_cap_changed();
      sigc::signal<void> signal_join_changed();
      sigc::signal<void> signal_miter_limit_changed();
      sigc::signal<void> signal_dash_changed();

    protected:
      Paint::pointer m_paint;
      double m_width;
      Cairo::LineCap m_cap;
      Cairo::LineJoin m_join;
      double m_miter_limit;
      std::valarray<double> m_dash_array;
      double m_dash_offset;

      sigc::signal<void> m_signal_paint_changed;
      sigc::signal<void> m_signal_width_changed;
      sigc::signal<void> m_signal_cap_changed;
      sigc::signal<void> m_signal_join_changed;
      sigc::signal<void> m_signal_miter_limit_changed;
      sigc::signal<void> m_signal_dash_changed;

      sigc::connection m_paint_changed_connection;
      void on_paint_changed();

  };

}

#endif
