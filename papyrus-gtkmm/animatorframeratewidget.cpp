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
#include "animatorframeratewidget.h"

namespace Papyrus
{
  namespace Gtk
  {

    AnimatorFrameRateWidget::AnimatorFrameRateWidget()
        : ::Gtk::HBox(), m_spinadjustment ( 30.0, 0.0, 1000.0 ), m_spinbutton ( m_spinadjustment )
    {
      m_label.set_text ( "Frames/sec " );

      this->pack_start ( m_label );
      this->pack_start ( m_spinbutton );

      m_spinbutton.signal_value_changed().connect ( sigc::mem_fun ( *this, &AnimatorFrameRateWidget::on_spinbutton_value_changed ) );

    }


    AnimatorFrameRateWidget::~AnimatorFrameRateWidget()
    {
    }

    ::Gtk::Label& AnimatorFrameRateWidget::label( )
    {
      return m_label;
    }

    ::Gtk::SpinButton& AnimatorFrameRateWidget::spinbutton( )
    {
      return m_spinbutton;
    }

    ::Gtk::Adjustment& AnimatorFrameRateWidget::spinadjustment( )
    {
      return m_spinadjustment;
    }

    void AnimatorFrameRateWidget::add ( Papyrus::Animator::pointer animator )
    {
      if ( animator ) m_animators.insert( animator );
    }

    void AnimatorFrameRateWidget::remove ( Papyrus::Animator::pointer animator )
    {
      if ( animator ) m_animators.erase( animator );
    }

    const AnimatorFrameRateWidget::Animators& AnimatorFrameRateWidget::animators( ) const
    {
      return m_animators;
    }

    void AnimatorFrameRateWidget::on_spinbutton_value_changed( )
    {
      int rate;
      Animators::iterator i;

      rate = m_spinbutton.get_value_as_int();

      // set the animators
      for ( i = m_animators.begin(); i != m_animators.end(); i++ )
        ( *i )->set_frame_rate ( rate );

    }

  }

}
