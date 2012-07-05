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
#include "linecapbuttonbox.h"

#include <papyrus/polyline.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/utility.h>

namespace Papyrus
{
  namespace Gtk
  {

    extern const char* line_cap_string[];

    LineCapButtonBox::LineCapButtonBox ( Cairo::LineCap selected, SIZE size )
        : ::Gtk::HButtonBox(), m_selected ( selected )
    {
      this->set_layout ( ::Gtk::BUTTONBOX_START );
      this->set_child_min_width ( 1 );
      this->set_child_min_height ( 1 );
      this->set_child_ipadding_x ( 0 );
      this->set_child_ipadding_y ( 0 );
      this->set_size ( size );
    }


    LineCapButtonBox::~LineCapButtonBox() {}

    sigc::signal< void, Cairo::LineCap > LineCapButtonBox::signal_selected( )
    {
      return m_signal_selected;
    }

    Cairo::LineCap LineCapButtonBox::selected( )
    {
      return m_selected;
    }

    void LineCapButtonBox::set_selected ( Cairo::LineCap selected )
    {
      static bool locked = false;
      if ( locked )
        return;
      locked = true;

      if ( selected > Cairo::LINE_CAP_SQUARE )
        selected = Cairo::LINE_CAP_BUTT;

      for ( unsigned int i = Cairo::LINE_CAP_BUTT; i <= Cairo::LINE_CAP_SQUARE; i++ )
      {
        if ( (Cairo::LineCap) i == selected )
          m_buttons[i]->set_active ( true );
        else
          m_buttons[i]->set_active ( false );
      }
      locked = false;
      m_selected = selected;
      m_signal_selected.emit ( selected );
    }

    void LineCapButtonBox::set_size ( SIZE size )
    {
      ::Gtk::ToggleButton* button;

      create_images ( size );

      while ( this->get_children().size() > 0 )
        this->remove ( ** ( this->get_children().begin() ) );

      m_buttons.clear();

      m_tooltips.enable();

      for ( unsigned int i = Cairo::LINE_CAP_BUTT; i <= Cairo::LINE_CAP_SQUARE; i++ )
      {
        button = ::Gtk::manage ( new ::Gtk::ToggleButton() );
        button->add ( * ( m_images[i] ) );
        m_tooltips.set_tip ( *button, line_cap_string[i] );
        button->signal_toggled().connect ( sigc::bind ( sigc::mem_fun ( *this, &LineCapButtonBox::set_selected ), ( Cairo::LineCap ) i ) );
        m_buttons.push_back ( button );
        this->pack_start ( *button, false, false );
      }

      this->set_selected ( m_selected );

      this->show_all();
    }

    void LineCapButtonBox::create_images ( SIZE size )
    {
      double scale;
      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      ::Gtk::Image* image;
      Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();

      m_images.clear();

      switch ( size )
      {
        case SIZE_XSMALL:
          scale = 0.4;
          break;
        case SIZE_SMALL:
          scale = 0.6;
          break;
        default:
        case SIZE_MEDIUM:
          scale = 0.8;
          break;
        case SIZE_LARGE:
          scale = 1.0;
          break;
        case SIZE_XLARGE:
          scale = 1.5;
          break;
      }

      canvas->scroll_to ( 25*scale, 10*scale );
      canvas->set_scale ( scale );

      for ( unsigned int i = Cairo::LINE_CAP_BUTT; i <= Cairo::LINE_CAP_SQUARE; i++ )
      {
        canvas->add ( Papyrus::example_line_cap ( static_cast<Cairo::LineCap> ( i ) ) );
        pixbuf = create_pixbuf ( canvas, ( int ) ( 50*scale ), ( int ) ( 20*scale ) );
        image = ::Gtk::manage ( new ::Gtk::Image ( pixbuf ) );
        m_images.push_back ( image );
        canvas->clear();
      }

    }

  }

}
