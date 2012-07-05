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
#ifndef PAPYRUSGTKMARKERCOMBOBOX_H
#define PAPYRUSGTKMARKERCOMBOBOX_H

#include <gtkmm.h>

#include <papyrus.h>

namespace Papyrus
{
  namespace Gtk
  {

    extern const char* marker_string[];

    /**
     * A drop-down combobox that is loaded with graphical examples of all marker styles
     * styles available in Papyrus.
     *
     * \image html screenshot_markercombobox_collapsed.png "MarkerComboBox collapsed"
     *
     * \image html screenshot_markercombobox_expanded.png "MarkerComboBox expanded"
     *
     * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
     */
    class MarkerComboBox : public ::Gtk::HBox
    {
      public:
        MarkerComboBox ( Papyrus::Marker::Facing facing=Papyrus::Marker::RIGHT, int active = 0 );

        ~MarkerComboBox();

        Papyrus::Marker::Facing facing();
        void set_facing ( Papyrus::Marker::Facing facing );

        Papyrus::Marker::Style style();
        void set_style ( Papyrus::Marker::Style style );

        Glib::SignalProxy0<void>  signal_changed ();

      protected:
        ::Gtk::ComboBox m_combobox;
        ::Gtk::ToggleButton m_left, m_right;
        ::Gtk::Tooltips m_tips;
        Papyrus::Marker::Facing m_facing;

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
        std::vector<Glib::RefPtr<Gdk::Pixbuf> > m_pixbuf;

        void load_pixbufs();

    };

  }

}

#endif
