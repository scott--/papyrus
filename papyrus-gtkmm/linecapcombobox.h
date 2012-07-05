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
#ifndef PAPYRUSGTKLINECAPCOMBOBOX_H
#define PAPYRUSGTKLINECAPCOMBOBOX_H

#include <gtkmm.h>

namespace Papyrus
{
  namespace Gtk
  {

    extern const char* line_cap_string[];

    /**
     * A drop-down combobox that is loaded with graphical examples of all line join
     * styles available in Cairo.
     *
     * \image html screenshot_linecapcombobox_collapsed.png "LineCapComboBox collapsed"
     *
     * \image html screenshot_linecapcombobox_expanded.png "LineCapComboBox expanded"
     *
     * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
     */
    class LineCapComboBox : public ::Gtk::ComboBox
    {
      public:
        LineCapComboBox ( int active = 0 );

        ~LineCapComboBox();

      protected:

      class ModelColumns: public ::Gtk::TreeModelColumnRecord
        {
          public:
            ModelColumns()
            {
              add ( picture );
              add ( name );
            }

            ::Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > picture;
            ::Gtk::TreeModelColumn<Glib::ustring> name;
        };

        Glib::RefPtr< ::Gtk::ListStore> m_store;
        ModelColumns m_columns;
        static std::vector<Glib::RefPtr<Gdk::Pixbuf> > m_pixbuf;

        void create_pixbufs();

    };

  }

}

#endif
