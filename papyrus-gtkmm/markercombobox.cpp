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
#include "markercombobox.h"

#include <papyrus-gtkmm/utility.h>
#include <papyrus-extras.h>

namespace Papyrus
{
  namespace Gtk
  {

    const char* marker_string[] =
    {
      "None",
      "Lines",
      "Triangle",
      "Diamond",
      "Half Diamond",
      "Half Head (Upper)",
      "Half Head (Lower)",
      "Slashed Cross",
      "Ellipse",
      "Dot",
      "Double Triangle",
      "Dot and Triangle",
      "Box",
      "Crow Foot",
      "Cross",
      "1 or Many",
      "0 or Many",
      "1 or 0",
      "1 Exactly",
      "Concave",
      "Round",
      "Open Round",
      "Backslash",
    };

    MarkerComboBox::MarkerComboBox ( Papyrus::Marker::Facing facing, int active )
        : m_facing ( Papyrus::Marker::RIGHT )
    {

      m_store = ::Gtk::ListStore::create ( m_columns );

      this->load_pixbufs();

      m_combobox.set_model ( m_store );

      m_combobox.pack_start ( m_columns.picture );
      m_combobox.pack_start ( m_columns.name );

      m_combobox.set_active ( active );

      m_left.set_image ( *::Gtk::manage ( new ::Gtk::Image ( ::Gtk::Stock::GO_BACK, ::Gtk::ICON_SIZE_SMALL_TOOLBAR ) ) );
      m_right.set_image ( *::Gtk::manage ( new ::Gtk::Image ( ::Gtk::Stock::GO_FORWARD, ::Gtk::ICON_SIZE_SMALL_TOOLBAR ) ) );

      m_tips.set_tip ( m_left, "Left facing markers" );
      m_tips.set_tip ( m_right, "Right facing markers" );

      m_right.set_active ( true );
      m_left.signal_toggled().connect ( sigc::bind ( sigc::mem_fun ( *this, &MarkerComboBox::set_facing ), Papyrus::Marker::LEFT ) );
      m_right.signal_toggled().connect ( sigc::bind ( sigc::mem_fun ( *this, &MarkerComboBox::set_facing ), Papyrus::Marker::RIGHT ) );

      this->pack_start ( m_combobox );
      this->pack_start ( *::Gtk::manage ( new ::Gtk::VSeparator() ) );
      this->pack_start ( m_left, ::Gtk::PACK_SHRINK );
      this->pack_start ( m_right, ::Gtk::PACK_SHRINK );
      this->set_homogeneous ( false );
    }

    MarkerComboBox::~MarkerComboBox()
    {
    }

    Papyrus::Marker::Facing MarkerComboBox::facing()
    {
      return m_facing;
    }

    void MarkerComboBox::set_facing ( Papyrus::Marker::Facing facing )
    {
      static bool change_lock = false;
      int active;

      if ( change_lock ) return;

      change_lock = true;

      if ( facing != this->facing() )
      {
        active = m_combobox.get_active_row_number();

        if ( facing == Papyrus::Marker::LEFT )
        {
          m_left.set_active ( true );
          m_right.set_active ( false );
        }
        else
        {
          m_left.set_active ( false );
          m_right.set_active ( true );
        }

        m_facing = facing;

        load_pixbufs();

        m_combobox.set_active ( active );
      }
      else if ( facing == Papyrus::Marker::LEFT )
      {
        m_left.set_active ( true );
        m_right.set_active ( false );
      }
      else
      {
        m_left.set_active ( false );
        m_right.set_active ( true );
      }

      change_lock = false;
    }

    Papyrus::Marker::Style MarkerComboBox::style()
    {
      return static_cast<Papyrus::Marker::Style> ( m_combobox.get_active_row_number() );
    }

    void MarkerComboBox::set_style ( Papyrus::Marker::Style style )
    {
      m_combobox.set_active ( style );
    }

    void MarkerComboBox::load_pixbufs()
    {
      ::Gtk::TreeModel::Row row;
      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();

      m_store->clear();
      m_pixbuf.clear();
      canvas->translate ( 30, 10 );

      for ( unsigned int i = Papyrus::Marker::NONE; i <= Papyrus::Marker::BACKSLASH; i++ )
      {
        canvas->add ( Papyrus::example_marker ( static_cast<Papyrus::Marker::Style> ( i ), this->facing() ) );
        pixbuf = create_pixbuf ( canvas, 50, 20 );
        m_pixbuf.push_back ( pixbuf );
        canvas->clear();

        row = * ( m_store->append() );
        row[ m_columns.picture ] = pixbuf;
        row[ m_columns.name ] = marker_string[ i ];
      }

    }

    Glib::SignalProxy0< void > MarkerComboBox::signal_changed( )
    {
      return m_combobox.signal_changed();
    }

  }

}
