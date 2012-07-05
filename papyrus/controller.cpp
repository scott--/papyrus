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
#include "controller.h"

namespace Papyrus
{

  Controller::Controller(const Glib::ustring& id ) : Object(id), m_disabled ( false ) {}

  Controller::pointer Controller::create ( const Glib::ustring & id )
  {
    PAPYRUS_CREATE( Controller(id) );
  }

  Controller::~Controller() {}

  bool Controller::is_disabled()
  {
    return m_disabled;
  }

  bool Controller::disable ( bool value )
  {
    m_disabled = value;
    m_signal_disabled.emit ( m_disabled );
    return true;
  }

  bool Controller::enable ( bool value )
  {
    m_disabled = !value;
    m_signal_disabled.emit ( m_disabled );
    return true;
  }

  sigc::signal<void,bool> Controller::signal_disabled()
  {
    return m_signal_disabled;
  }

  bool Controller::handle_event(const Event::Event & event)
  {
    return this->handle(event);
  }

  bool Controller::handle ( const Event::Event& event )
  {
    if ( m_disabled )
      return false;

    switch ( event.type() )
    {
      case Event::BUTTON_PRESS:
        return this->on_button_press ( dynamic_cast<const Event::ButtonPress&> ( event ) );
      case Event::BUTTON_RELEASE:
        return this->on_button_release ( dynamic_cast<const Event::ButtonRelease&> ( event ) );
      case Event::BUTTON_DOUBLE_PRESS:
        return this->on_button_double_press ( dynamic_cast<const Event::ButtonDoublePress&> ( event ) );
      case Event::BUTTON_TRIPLE_PRESS:
        return this->on_button_triple_press ( dynamic_cast<const Event::ButtonTriplePress&> ( event ) );
      case Event::SCROLL:
        return this->on_scroll ( dynamic_cast<const Event::Scroll&> ( event ) );
      case Event::MOTION:
        return this->on_motion ( dynamic_cast<const Event::Motion&> ( event ) );
      case Event::KEY_PRESS:
        return this->on_key_press ( dynamic_cast<const Event::KeyPress&> ( event ) );
      case Event::KEY_RELEASE:
        return this->on_key_release ( dynamic_cast<const Event::KeyRelease&> ( event ) );
      default:
        return false;
    }
  }

  bool Controller::handle ( const Event::Button& event )
  {
    if ( m_disabled )
      return false;

    switch ( event.type() )
    {
      case Event::BUTTON_PRESS:
        return this->on_button_press ( dynamic_cast<const Event::ButtonPress&> ( event ) );
      case Event::BUTTON_RELEASE:
        return this->on_button_release ( dynamic_cast<const Event::ButtonRelease&> ( event ) );
      case Event::BUTTON_DOUBLE_PRESS:
        return this->on_button_double_press ( dynamic_cast<const Event::ButtonDoublePress&> ( event ) );
      case Event::BUTTON_TRIPLE_PRESS:
        return this->on_button_triple_press ( dynamic_cast<const Event::ButtonTriplePress&> ( event ) );
      default:
        return false;
    }
  }

  bool Controller::handle ( const Event::ButtonPress& event )
  {
    if ( m_disabled )
      return false;

    return this->on_button_press ( event );
  }

  bool Controller::handle ( const Event::ButtonDoublePress& event )
  {
    if ( m_disabled )
      return false;

    return this->on_button_double_press ( event );
  }

  bool Controller::handle ( const Event::ButtonTriplePress& event )
  {
    if ( m_disabled )
      return false;

    return this->on_button_triple_press ( event );
  }

  bool Controller::handle ( const Event::ButtonRelease& event )
  {
    if ( m_disabled )
      return false;

    return this->on_button_release ( event );
  }

  bool Controller::handle ( const Event::Key& event )
  {
    if ( m_disabled )
      return false;

    switch ( event.type() )
    {
      case Event::KEY_PRESS:
        return this->on_key_press ( dynamic_cast<const Event::KeyPress&> ( event ) );
      case Event::KEY_RELEASE:
        return this->on_key_release ( dynamic_cast<const Event::KeyRelease&> ( event ) );
      default:
        return false;
    }
  }

  bool Controller::handle ( const Event::KeyPress& event )
  {
    if ( m_disabled )
      return false;

    return this->on_key_press ( event );
  }

  bool Controller::handle ( const Event::KeyRelease& event )
  {
    if ( m_disabled )
      return false;

    return this->on_key_release ( event );
  }

  bool Controller::handle ( const Event::Motion& event )
  {
    if ( m_disabled )
      return false;

    return this->on_motion ( event );
  }

  bool Controller::handle ( const Event::Scroll& event )
  {
    if ( m_disabled )
      return false;

    return this->on_scroll ( event );
  }

  bool Controller::on_button_press ( const Event::ButtonPress& event )
  {
    return false;
  }

  bool Controller::on_button_double_press ( const Event::ButtonDoublePress& event )
  {
    return false;
  }

  bool Controller::on_button_triple_press ( const Event::ButtonTriplePress& event )
  {
    return false;
  }

  bool Controller::on_button_release ( const Event::ButtonRelease& event )
  {
    return false;
  }

  bool Controller::on_key_press ( const Event::KeyPress& event )
  {
    return false;
  }

  bool Controller::on_key_release ( const Event::KeyRelease& event )
  {
    return false;
  }

  bool Controller::on_motion ( const Event::Motion& event )
  {
    return false;
  }

  bool Controller::on_scroll ( const Event::Scroll& event )
  {
    return false;
  }

}


