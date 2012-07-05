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
#include "animatorframeintervalwidget.h"

namespace Papyrus
{
  namespace Gtk
  {

    AnimatorFrameIntervalWidget::AnimatorFrameIntervalWidget()
        : ::Gtk::HBox(), m_spinadjustment ( 33.0, 0.0, 10000.0 ), m_spinbutton ( m_spinadjustment )
    {
      m_label.set_text ( "Frame Interval (ms) " );

      this->pack_start ( m_label );
      this->pack_start ( m_spinbutton );

      m_spinbutton.signal_value_changed().connect ( sigc::mem_fun ( *this, &AnimatorFrameIntervalWidget::on_spinbutton_value_changed ) );

    }


    AnimatorFrameIntervalWidget::~AnimatorFrameIntervalWidget()
    {
    }

    ::Gtk::Label& AnimatorFrameIntervalWidget::label( )
    {
      return m_label;
    }

    ::Gtk::SpinButton& AnimatorFrameIntervalWidget::spinbutton( )
    {
      return m_spinbutton;
    }

    ::Gtk::Adjustment& AnimatorFrameIntervalWidget::spinadjustment( )
    {
      return m_spinadjustment;
    }

    void AnimatorFrameIntervalWidget::add ( Papyrus::Animator::pointer animator )
    {
      if ( animator ) m_animators.insert ( animator );
    }

    void AnimatorFrameIntervalWidget::remove ( Papyrus::Animator::pointer animator )
    {
      if ( animator ) m_animators.erase ( animator );
    }

    const AnimatorFrameIntervalWidget::Animators& AnimatorFrameIntervalWidget::animators( ) const
    {
      return m_animators;
    }

    void AnimatorFrameIntervalWidget::on_spinbutton_value_changed( )
    {
      int interval;
      Animators::iterator i;

      interval = m_spinbutton.get_value_as_int();

      // set the animators
      for ( i = m_animators.begin(); i != m_animators.end(); i++ )
        ( *i )->set_interval ( interval );

    }

  }

}
