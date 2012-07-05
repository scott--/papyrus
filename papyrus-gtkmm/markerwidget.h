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
#ifndef PAPYRUSGTKMARKERWIDGET_H
#define PAPYRUSGTKMARKERWIDGET_H

#include <gtkmm/table.h>
#include <papyrus-gtkmm/markercombobox.h>
#include <papyrus-gtkmm/strokewidget.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
     * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
     */
    class MarkerWidget : public ::Gtk::Table
    {
      public:
        MarkerWidget ( bool use_preview=true );

        ~MarkerWidget();

        Papyrus::Marker::pointer get_marker();

        bool use_preview();
        void set_use_preview ( bool use=true );

      protected:
        ::Gtk::Expander* m_expander;
        Papyrus::Gtk::Viewport* m_viewport;
        Papyrus::Polyline::pointer m_line;
        Papyrus::Marker::pointer m_marker;

        ::Gtk::ColorButton m_fill_color_button;
        ::Gtk::ColorButton m_stroke_color_button;
        ::Gtk::Adjustment m_marker_width_adjustment;
        ::Gtk::SpinButton m_marker_width_entry;
        ::Gtk::Adjustment m_marker_height_adjustment;
        ::Gtk::SpinButton m_marker_height_entry;
        ::Gtk::Adjustment m_line_width_adjustment;
        ::Gtk::SpinButton m_line_width_entry;
        Papyrus::Gtk::MarkerComboBox m_marker_combobox;
        Papyrus::Gtk::LineJoinButtonBox m_line_join_buttonbox;
        Papyrus::Gtk::LineCapButtonBox m_line_cap_buttonbox;

        void on_marker_style_changed();
        void on_fill_color_changed();
        void on_stroke_color_changed();
        void on_marker_width_changed();
        void on_marker_height_changed();
        void on_line_width_changed();
        void on_line_join_changed ( Cairo::LineJoin );
        void on_line_cap_changed ( Cairo::LineCap );

        void update_line_marker();
    };

  }

}

#endif
