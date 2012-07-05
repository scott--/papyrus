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
#ifndef PAPYRUSGTKLINEWIDTHCOMBOBOX_H
#define PAPYRUSGTKLINEWIDTHCOMBOBOX_H

#include <gtkmm.h>

#include <papyrus-gtkmm/enums.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
     * A drop-down combobox that can be loaded with a range of line widths that can grow
     * linearly or exponentially.
     *
     * \image html screenshot_linewidthcombobox_collapsed.png "LineWidthComboBox collapsed"
     *
     * \image html screenshot_linewidthcombobox_expanded.png "LineWidthComboBox expanded"
     *
     * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
     */
    class LineWidthComboBox : public ::Gtk::ComboBox
    {
      public:
        LineWidthComboBox ( int active = 0, double start=1.0, double stop=6.0, INCREMENT increment=INCREMENT_LINEAR, double factor=1.0 );

        ~LineWidthComboBox();

        double width();
        double start();
        double stop();
        void start_stop ( double& start, double& stop );

        void set_start ( double start );
        void set_stop ( double stop );
        void set_start_stop ( double start, double stop );

        double factor();
        void set_factor ( double factor );

        INCREMENT increment_type();
        void set_increment_type ( INCREMENT increment );

      protected:

      class ModelColumns: public ::Gtk::TreeModelColumnRecord
        {
          public:
            ModelColumns()
            {
              add ( picture );
            }

            ::Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > picture;
        };

        Glib::RefPtr< ::Gtk::ListStore> m_store;
        std::vector<Glib::RefPtr<Gdk::Pixbuf> > m_pixbufs;
        ModelColumns m_columns;

        double m_start, m_stop, m_factor;
        INCREMENT m_increment;

        void load_pixbufs();


    };

  }

}

#endif
