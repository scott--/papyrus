/* Animator Frame Rate Widget
 *
 * Controls the frame rate of a group of animators.
 */

#include "gtkmm.h"

#include <papyrus/affineanimator.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/animatorframeratewidget.h>
#include <papyrus-gtkmm/viewport.h>

#include <gtkmm.h>

class Example_AnimatorFrameRateWidget : public Gtk::Window
{
  public:
    Example_AnimatorFrameRateWidget();
    virtual ~Example_AnimatorFrameRateWidget();

  protected:
  //Member widgets:
    Papyrus::Gtk::AnimatorFrameRateWidget m_AnimatorFrameRateWidget;
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::AffineAnimator::pointer m_AffineAnimator;
    Papyrus::Group::pointer m_shape;

    Gtk::VBox m_vbox;
    Gtk::CheckButton m_check;
    Gtk::Button m_reset;

    void on_start_stop();

    void on_reset();
};

//Called by DemoWindow;
Gtk::Window* do_AnimatorFrameRateWidget()
{
  return new Example_AnimatorFrameRateWidget();
}

Example_AnimatorFrameRateWidget::Example_AnimatorFrameRateWidget()
{

  m_shape = Papyrus::example_group( true, true );
  m_Viewport.canvas()->add( m_shape );
  m_Viewport.set_size_request( 300, 300 );

  m_AffineAnimator = Papyrus::AffineAnimator::create();
  m_AffineAnimator->add( m_shape );
  m_AnimatorFrameRateWidget.add( m_AffineAnimator );

  set_title("Animator Frame Rate Widget");
  set_border_width(10);

  m_vbox.pack_start( m_AnimatorFrameRateWidget );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  m_vbox.pack_start( m_check );
  m_vbox.pack_start( m_reset );
  m_vbox.pack_start( m_Viewport );

  m_check.set_label( "Start Animation");
  m_check.signal_toggled().connect( sigc::mem_fun( *this, &Example_AnimatorFrameRateWidget::on_start_stop ) );

  m_reset.set_label( "Reset" );
  m_reset.signal_clicked().connect( sigc::mem_fun( *this, &Example_AnimatorFrameRateWidget::on_reset ) );

  m_AffineAnimator->set_frame_rate( 20 );
  m_AffineAnimator->set_rotate( M_PI/50 );
  m_AffineAnimator->set_translate( 2.0, -2.0 );
  m_AffineAnimator->set_bounce_frames( 40 );

  this->add( m_vbox );

  show_all();
}

Example_AnimatorFrameRateWidget::~Example_AnimatorFrameRateWidget()
{
}

void Example_AnimatorFrameRateWidget::on_start_stop()
{
  if ( m_check.get_active() )
    m_AffineAnimator->start();
  else
    m_AffineAnimator->stop();
}

void Example_AnimatorFrameRateWidget::on_reset()
{
  // TODO fix
//   m_shape->set_rotate( 0.0 );
//   m_shape->set_translate( 0.0, 0.0 );
}

/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
