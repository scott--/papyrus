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
#ifndef PAPYRUSGTKLINEJOINBUTTONBOX_H
#define PAPYRUSGTKLINEJOINBUTTONBOX_H

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
    class LineJoinButtonBox : public ::Gtk::HButtonBox
    {
      public:
        LineJoinButtonBox ( Cairo::LineJoin selected=Cairo::LINE_JOIN_MITER, SIZE size=SIZE_MEDIUM );

        ~LineJoinButtonBox();

        sigc::signal<void, Cairo::LineJoin> signal_selected();

        Cairo::LineJoin selected();
        void set_selected ( Cairo::LineJoin selected );

        SIZE get_size();
        void set_size ( SIZE size );

      protected:
        SIZE m_size;
        Cairo::LineJoin m_selected;

        ::Gtk::Tooltips m_tooltips;
        std::vector< ::Gtk::Image*> m_images;
        std::vector< ::Gtk::ToggleButton*> m_buttons;

        sigc::signal<void, Cairo::LineJoin> m_signal_selected;

        void create_images ( SIZE size );

    };

  }

}

#endif
