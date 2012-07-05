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
#include "zoomer.h"

#include <iostream>

namespace Papyrus
{

  Zoomer::Zoomer( const Glib::ustring& id, DrawableSet::pointer drawables, double zoom_step ):
      AffineController( id, drawables ),
      m_zoom_step(1.0 + zoom_step),
      m_zoom_in_buttons( Event::BUTTON_4 | Event::BUTTON_11 ),
      m_zoom_out_buttons( Event::BUTTON_5 | Event::BUTTON_12 )
  {
  }

  Zoomer::pointer Zoomer::create( double zoom_step )
  {
    PAPYRUS_CREATE( Zoomer( Glib::ustring(), DrawableSet::pointer(), zoom_step ) );
  }

  Zoomer::pointer Zoomer::create( const Glib::ustring& id, DrawableSet::pointer drawables, double zoom_step )
  {
    PAPYRUS_CREATE( Zoomer( id, drawables, zoom_step ) );
  }

  Zoomer::pointer Zoomer::create( const Glib::ustring& id, double zoom_step )
  {
    PAPYRUS_CREATE( Zoomer( id, DrawableSet::pointer(), zoom_step ) );
  }

  Zoomer::pointer Zoomer::create( DrawableSet::pointer drawables, double zoom_step )
  {
    PAPYRUS_CREATE( Zoomer( Glib::ustring(), drawables, zoom_step ) );
  }

  Zoomer::~Zoomer()
  {}

  void Zoomer::zoom_in()
  {
    if ( m_zoom_step <= 0 ) return;
    this->scale( m_zoom_step );
  }

  void Zoomer::zoom_out()
  {
    if ( m_zoom_step <= 0 ) return;
    this->scale( 1.0 / m_zoom_step );
  }

  double Zoomer::zoom_step()
  {
    return m_zoom_step - 1.0;
  }

  void Zoomer::set_zoom_step(double zs)
  {
    m_zoom_step = 1.0 + zs;
  }

  unsigned Zoomer::zoom_in_buttons()
  {
    return m_zoom_in_buttons;
  }

  unsigned Zoomer::zoom_out_buttons()
  {
    return m_zoom_out_buttons;
  }

  void Zoomer::set_zoom_in_buttons(unsigned b)
  {
    m_zoom_in_buttons = b;
  }

  void Zoomer::set_zoom_out_buttons(unsigned b)
  {
    m_zoom_out_buttons = b;
  }

  void Zoomer::set_zoom_buttons(unsigned in, unsigned out)
  {
    m_zoom_in_buttons = in;
    m_zoom_out_buttons = out;
  }

  void Zoomer::set_zoom_buttons(unsigned set)
  {
    m_zoom_in_buttons = Event::BUTTON_NONE;
    m_zoom_out_buttons = Event::BUTTON_NONE;

    this->add_zoom_buttons( set );
  }

  void Zoomer::add_zoom_buttons(unsigned in, unsigned out)
  {
    m_zoom_in_buttons = m_zoom_in_buttons | in;
    m_zoom_out_buttons = m_zoom_out_buttons | out;
  }

  void Zoomer::add_zoom_buttons(unsigned set)
  {
    if ( set & Event::BUTTONS_1_3 ) this->add_zoom_buttons(Event::BUTTON_1, Event::BUTTON_3);
    if ( set & Event::BUTTONS_4_5 ) this->add_zoom_buttons(Event::BUTTON_4, Event::BUTTON_5);
    if ( set & Event::BUTTONS_6_7 ) this->add_zoom_buttons(Event::BUTTON_6, Event::BUTTON_7);
    if ( set & Event::BUTTONS_8_9 ) this->add_zoom_buttons(Event::BUTTON_8, Event::BUTTON_9);
    if ( set & Event::BUTTONS_11_12 ) this->add_zoom_buttons(Event::BUTTON_11, Event::BUTTON_12);
    if ( set & Event::BUTTONS_1_3_INV ) this->add_zoom_buttons(Event::BUTTON_3, Event::BUTTON_1);
    if ( set & Event::BUTTONS_4_5_INV ) this->add_zoom_buttons(Event::BUTTON_5, Event::BUTTON_4);
    if ( set & Event::BUTTONS_6_7_INV ) this->add_zoom_buttons(Event::BUTTON_7, Event::BUTTON_6);
    if ( set & Event::BUTTONS_8_9_INV ) this->add_zoom_buttons(Event::BUTTON_9, Event::BUTTON_8);
    if ( set & Event::BUTTONS_11_12_INV ) this->add_zoom_buttons(Event::BUTTON_12, Event::BUTTON_11);
  }

  void Zoomer::perform_button_action(Event::ButtonID b)
  {
    switch ( b )
    {
      case Event::BUTTON_1:
        if ( m_zoom_in_buttons & Event::BUTTON_1 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_1 ) this->zoom_out();
        break;
      case Event::BUTTON_2:
        if ( m_zoom_in_buttons & Event::BUTTON_2 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_2 ) this->zoom_out();
        break;
      case Event::BUTTON_3:
        if ( m_zoom_in_buttons & Event::BUTTON_3 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_3 ) this->zoom_out();
        break;
      case Event::BUTTON_4:
        if ( m_zoom_in_buttons & Event::BUTTON_4 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_4 ) this->zoom_out();
        break;
      case Event::BUTTON_5:
        if ( m_zoom_in_buttons & Event::BUTTON_5 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_5 ) this->zoom_out();
        break;
      case Event::BUTTON_6:
        if ( m_zoom_in_buttons & Event::BUTTON_6 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_6 ) this->zoom_out();
        break;
      case Event::BUTTON_7:
        if ( m_zoom_in_buttons & Event::BUTTON_7 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_7 ) this->zoom_out();
        break;
      case Event::BUTTON_8:
        if ( m_zoom_in_buttons & Event::BUTTON_8 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_8 ) this->zoom_out();
        break;
      case Event::BUTTON_9:
        if ( m_zoom_in_buttons & Event::BUTTON_9 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_9 ) this->zoom_out();
        break;
      case Event::BUTTON_10:
        if ( m_zoom_in_buttons & Event::BUTTON_10 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_10 ) this->zoom_out();
        break;
      case Event::BUTTON_11:
        if ( m_zoom_in_buttons & Event::BUTTON_11 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_11 ) this->zoom_out();
        break;
      case Event::BUTTON_12:
        if ( m_zoom_in_buttons & Event::BUTTON_12 ) this->zoom_in();
        else if ( m_zoom_out_buttons & Event::BUTTON_12 ) this->zoom_out();
        break;
      default:
        break;
    }
  }

  bool Zoomer::on_button_press( const Event::ButtonPress& event )
  {
    switch ( event.button )
    {
      case 1: this->perform_button_action(Event::BUTTON_1); break;
      case 2: this->perform_button_action(Event::BUTTON_2); break;
      case 3: this->perform_button_action(Event::BUTTON_3); break;
      case 4: this->perform_button_action(Event::BUTTON_4); break;
      case 5: this->perform_button_action(Event::BUTTON_5); break;
      case 6: this->perform_button_action(Event::BUTTON_6); break;
      case 7: this->perform_button_action(Event::BUTTON_7); break;
      case 8: this->perform_button_action(Event::BUTTON_8); break;
      case 9: this->perform_button_action(Event::BUTTON_9); break;
      case 10: this->perform_button_action(Event::BUTTON_10); break;
      case 11: this->perform_button_action(Event::BUTTON_11); break;
      case 12: this->perform_button_action(Event::BUTTON_12); break;
      default: break;
    }
    
    return true;
  }

  bool Zoomer::on_scroll(const Event::Scroll & event)
  {
    switch ( event.direction )
    {
      case Event::SCROLL_UP:    this->perform_button_action(Event::BUTTON_4); break;
      case Event::SCROLL_DOWN:  this->perform_button_action(Event::BUTTON_5); break;
      case Event::SCROLL_LEFT:  this->perform_button_action(Event::BUTTON_6); break;
      case Event::SCROLL_RIGHT: this->perform_button_action(Event::BUTTON_7); break;
      default: break;
    }

    return true;
  }

}

