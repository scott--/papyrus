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
#ifndef PAPYRUSGTKLINECAPBUTTONBOX_H
#define PAPYRUSGTKLINECAPBUTTONBOX_H

#include <cairomm/cairomm.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/image.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/tooltips.h>

#include <papyrus-gtkmm/enums.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class LineCapButtonBox : public ::Gtk::HButtonBox
    {
      public:
        LineCapButtonBox ( Cairo::LineCap selected=Cairo::LINE_CAP_BUTT, SIZE size=SIZE_MEDIUM );

        ~LineCapButtonBox();

        sigc::signal<void, Cairo::LineCap> signal_selected();

        Cairo::LineCap selected();
        void set_selected ( Cairo::LineCap selected );

        SIZE get_size();
        void set_size ( SIZE size );

      protected:
        SIZE m_size;
        Cairo::LineCap m_selected;

        ::Gtk::Tooltips m_tooltips;
        std::vector< ::Gtk::Image*> m_images;
        std::vector< ::Gtk::ToggleButton*> m_buttons;

        sigc::signal<void, Cairo::LineCap> m_signal_selected;

        void create_images ( SIZE size );

    };

  }

}

#endif
