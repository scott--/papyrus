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
#include "linecapcombobox.h"

#include <papyrus/polyline.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/utility.h>

namespace Papyrus
{
  namespace Gtk
  {

    const char* line_cap_string[] =
    {
      "Butt",
      "Round",
      "Square",
    };

    std::vector<Glib::RefPtr<Gdk::Pixbuf> > LineCapComboBox::m_pixbuf;

    LineCapComboBox::LineCapComboBox ( int active )
        : ::Gtk::ComboBox( )
    {

      create_pixbufs();

      m_store = ::Gtk::ListStore::create ( m_columns );
      ::Gtk::TreeModel::Row row;

      for ( unsigned int i = Cairo::LINE_JOIN_MITER; i <= Cairo::LINE_JOIN_BEVEL; i++ )
      {
        row = * ( m_store->append() );
        row[ m_columns.picture ] = m_pixbuf[ i ];
        row[ m_columns.name ] = line_cap_string[ i ];
      }

      set_model ( m_store );

      pack_start ( m_columns.picture );
      pack_start ( m_columns.name );

      set_active ( active );
    }


    LineCapComboBox::~LineCapComboBox() {}

    void LineCapComboBox::create_pixbufs()
    {
      if ( m_pixbuf.size() != 0 )
        return;

      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();

      canvas->translate ( 30, 20 );

      for ( unsigned int i = Cairo::LINE_CAP_BUTT; i <= Cairo::LINE_CAP_SQUARE; i++ )
      {
        canvas->add ( Papyrus::example_line_cap ( static_cast<Cairo::LineCap> ( i ) ) );
        pixbuf = create_pixbuf ( canvas, 60, 40 );
        m_pixbuf.push_back ( pixbuf );
        canvas->clear();
      }

    }

  }

}
