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
#include "animatorbouncewidget.h"

#include <gtkmm/separator.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>

namespace Papyrus
{
  namespace Gtk
  {

    AnimatorBounceWidget::AnimatorBounceWidget()
        : ::Gtk::HBox(), m_spinadjustment ( 0.0, -1000.0, 1000.0 ), m_spinbutton ( m_spinadjustment )
    {
      m_label.set_text ( "Bounce frames  " );

      this->pack_start ( m_label );
      this->pack_start ( m_spinbutton );
      this->pack_start ( *::Gtk::manage ( new ::Gtk::VSeparator() ) );

      m_spinbutton.signal_value_changed().connect ( sigc::mem_fun ( *this, &AnimatorBounceWidget::on_spinbutton_value_changed ) );

      m_direction[REVERSE].set_image ( *::Gtk::manage ( new ::Gtk::Image ( ::Gtk::Stock::GO_BACK, ::Gtk::ICON_SIZE_SMALL_TOOLBAR ) ) );
      m_direction[STOP].set_image ( *::Gtk::manage ( new ::Gtk::Image ( ::Gtk::Stock::NO, ::Gtk::ICON_SIZE_SMALL_TOOLBAR ) ) );
      m_direction[FORWARD].set_image ( *::Gtk::manage ( new ::Gtk::Image ( ::Gtk::Stock::GO_FORWARD, ::Gtk::ICON_SIZE_SMALL_TOOLBAR ) ) );
      m_direction[STOP].set_active ( true );
      for ( int i=0; i<3; i++ )
      {
        m_direction[i].signal_toggled().connect ( sigc::bind ( sigc::mem_fun ( *this, &AnimatorBounceWidget::on_direction_changed ), i ) );
        this->pack_start ( m_direction[i] );
      }

    }


    AnimatorBounceWidget::~AnimatorBounceWidget()
    {
    }

    ::Gtk::Label& AnimatorBounceWidget::label( )
    {
      return m_label;
    }

    ::Gtk::SpinButton& AnimatorBounceWidget::spinbutton( )
    {
      return m_spinbutton;
    }

    ::Gtk::Adjustment& AnimatorBounceWidget::spinadjustment( )
    {
      return m_spinadjustment;
    }

    void AnimatorBounceWidget::add ( Papyrus::Animator::pointer animator )
    {
      if ( animator ) m_animators.insert ( animator );
    }

    void AnimatorBounceWidget::remove ( Papyrus::Animator::pointer animator )
    {
      if ( animator ) m_animators.erase ( animator );
    }

    const AnimatorBounceWidget::Animators& AnimatorBounceWidget::animators( ) const
    {
      return m_animators;
    }

    void AnimatorBounceWidget::on_spinbutton_value_changed( )
    {
      int frames;
      Animators::iterator i;

      frames = m_spinbutton.get_value_as_int();

      // check for button consistency
      if ( frames < 0 )
        m_direction[REVERSE].set_active ( true );
      else if ( frames == 0 )
        m_direction[STOP].set_active ( true );
      else
        m_direction[FORWARD].set_active ( true );

      // set the animators
      for ( i = m_animators.begin(); i != m_animators.end(); i++ )
        ( *i )->set_bounce_frames ( frames );

    }

    void AnimatorBounceWidget::on_direction_changed ( int direction )
    {
      static bool locked=false;
      int frames;

      if ( locked )
        return;

      locked = true;

      frames = m_spinbutton.get_value_as_int();

      if ( frames == 0 )
        direction = STOP;

      switch ( direction )
      {
        case REVERSE:
          m_direction[STOP].set_active ( false );
          m_direction[FORWARD].set_active ( false );
          if ( frames > 0 )
            m_spinbutton.set_value ( -frames );
          break;
        case STOP:
          m_direction[REVERSE].set_active ( false );
          m_direction[FORWARD].set_active ( false );
          if ( frames != 0 )
            m_spinbutton.set_value ( 0 );
          break;
        case FORWARD:
          m_direction[REVERSE].set_active ( false );
          m_direction[STOP].set_active ( false );
          if ( frames < 0 )
            m_spinbutton.set_value ( -frames );
          break;
      }

      locked = false;
    }

  }

}
