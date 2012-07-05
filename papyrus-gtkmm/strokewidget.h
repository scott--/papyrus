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
#ifndef PAPYRUSGTKSTROKEWIDGET_H
#define PAPYRUSGTKSTROKEWIDGET_H

#include <gtkmm/table.h>

#include <papyrus/stroke.h>
#include <papyrus/polyline.h>
#include <papyrus-gtkmm/linejoinbuttonbox.h>
#include <papyrus-gtkmm/linecapbuttonbox.h>
#include <papyrus-gtkmm/viewport.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class StrokeWidget : public ::Gtk::Table
    {
      public:
        StrokeWidget ( bool use_preview=true );

        ~StrokeWidget();

        Papyrus::Stroke::pointer stroke() const;

        bool use_preview();
        void set_use_preview ( bool use=true );

      protected:
        ::Gtk::Expander* m_expander;
        Papyrus::Gtk::Viewport* m_viewport;
        Papyrus::Polyline::pointer m_line;

        ::Gtk::ColorButton m_color_button;
        ::Gtk::Adjustment m_width_adjustment;
        ::Gtk::SpinButton m_width_entry;
        ::Gtk::Adjustment m_miter_limit_adjustment;
        ::Gtk::SpinButton m_miter_limit_entry;
        Papyrus::Gtk::LineJoinButtonBox m_line_join_buttonbox;
        Papyrus::Gtk::LineCapButtonBox m_line_cap_buttonbox;

        Papyrus::Stroke::pointer m_stroke;

        void on_color_changed();
        void on_width_changed();
        void on_line_join_changed ( Cairo::LineJoin );
        void on_line_cap_changed ( Cairo::LineCap );

    };

  }

}

#endif
