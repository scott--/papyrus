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
#include "linejoincombobox.h"

#include <papyrus/polyline.h>
#include <papyrus/canvas.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/utility.h>

namespace Papyrus
{
  namespace Gtk
  {

    const char* line_join_string[] =
    {
      "Miter",
      "Round",
      "Bevel",
    };

    std::vector<Glib::RefPtr<Gdk::Pixbuf> > LineJoinComboBox::m_pixbuf;

    LineJoinComboBox::LineJoinComboBox ( int active )
        : ::Gtk::ComboBox( )
    {

      create_pixbufs();

      m_store = ::Gtk::ListStore::create ( m_columns );
      ::Gtk::TreeModel::Row row;

      for ( unsigned int i = Cairo::LINE_JOIN_MITER; i <= Cairo::LINE_JOIN_BEVEL; i++ )
      {
        row = * ( m_store->append() );
        row[ m_columns.picture ] = m_pixbuf[ i ];
        row[ m_columns.name ] = line_join_string[ i ];
      }

      set_model ( m_store );

      pack_start ( m_columns.picture );
      pack_start ( m_columns.name );

      set_active ( active );
    }

    LineJoinComboBox::~LineJoinComboBox() {}

    void LineJoinComboBox::create_pixbufs()
    {
      if ( m_pixbuf.size() != 0 )
        return;

      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();

      canvas->translate ( 30, 30 );

      for ( unsigned int i = Cairo::LINE_JOIN_MITER; i <= Cairo::LINE_JOIN_BEVEL; i++ )
      {
        canvas->add ( Papyrus::example_line_join ( static_cast<Cairo::LineJoin> ( i ) ) );
        pixbuf = create_pixbuf ( canvas, 60, 55 );
        m_pixbuf.push_back ( pixbuf );
        canvas->clear();
      }

    }


  }

}
