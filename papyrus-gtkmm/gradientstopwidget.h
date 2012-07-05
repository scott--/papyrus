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
#ifndef PAPYRUS_GTKGRADIENTSTOPWIDGET_H
#define PAPYRUS_GTKGRADIENTSTOPWIDGET_H

#include <vector>

#include <gtkmm/table.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>

#include <papyrus/gradient.h>

namespace Papyrus
{

  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class GradientStopWidget : public ::Gtk::Table
    {
      public:
        GradientStopWidget ( unsigned num_stops=1,
                             bool show_header=false,
                             bool show_stop_num=false
                           );

        ~GradientStopWidget();

        unsigned num_stops();

        void set_num_stops ( unsigned num_stops );

        void show_header ( bool show=false );

        void show_stop_num ( bool show=false );

        sigc::signal<void> signal_stops_changed();

        Gradient::Stops stops();

      protected:

        unsigned m_num_stops;
        bool m_show_header;
        bool m_show_stop_num;

        sigc::signal<void> m_signal_stops_changed;

        std::vector< ::Gtk::Label* > m_headers;
        std::vector< ::Gtk::Label* > m_stop_nums;
        std::vector< ::Gtk::ColorButton* > m_colorbuttons;
        std::vector< ::Gtk::SpinButton* > m_offsets;
        std::vector< ::Gtk::SpinButton* > m_alphas;

        Gradient::Stops m_stops;

        void on_color_changed ( int which );

        void on_offset_changed ( int which );

        void on_alpha_changed ( int which );

    };

  }

}

#endif
