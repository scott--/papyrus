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
#ifndef PAPYRUSGTKSTROKEDIALOG_H
#define PAPYRUSGTKSTROKEDIALOG_H

#include <gtkmm.h>

#include <papyrus/stroke.h>
#include <papyrus-gtkmm/strokewidget.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class StrokeDialog : public ::Gtk::Dialog
    {
      public:
        StrokeDialog();

        ~StrokeDialog();

        const ::Gtk::Button* get_apply_button() const;
        ::Gtk::Button* get_apply_button();

        const ::Gtk::Button* get_cancel_button() const;
        ::Gtk::Button* get_cancel_button();

        const ::Gtk::Button* get_ok_button() const;
        ::Gtk::Button* get_ok_button();

        Papyrus::Stroke::pointer stroke() const;

      protected:
        ::Gtk::Button* m_apply_button;
        ::Gtk::Button* m_cancel_button;
        ::Gtk::Button* m_ok_button;

        StrokeWidget m_stroke_widget;

    };

  }

}

#endif
