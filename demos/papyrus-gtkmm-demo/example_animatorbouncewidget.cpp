/* Animator Bounce Widget
 *
 * Controls the bounce limits and direction of a group of animators.
 */

#include "gtkmm.h"

#include <papyrus/affineanimator.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/animatorbouncewidget.h>
#include <papyrus-gtkmm/viewport.h>

#include <gtkmm.h>

class Example_AnimatorBounceWidget : public Gtk::Window
{
  public:
    Example_AnimatorBounceWidget();
    virtual ~Example_AnimatorBounceWidget();

  protected:
  //Member widgets:
    Papyrus::Gtk::AnimatorBounceWidget m_AnimatorBounceWidget;
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
Gtk::Window* do_AnimatorBounceWidget()
{
  return new Example_AnimatorBounceWidget();
}

Example_AnimatorBounceWidget::Example_AnimatorBounceWidget()
{

  m_shape = Papyrus::example_group( true, true );
  m_Viewport.canvas()->add( m_shape );
  m_Viewport.set_size_request( 300, 300 );

  m_AffineAnimator = Papyrus::AffineAnimator::create();
  m_AffineAnimator->add( m_shape );
  m_AnimatorBounceWidget.add( m_AffineAnimator );
  m_AnimatorBounceWidget.spinbutton().set_value( 40 );

  set_title("Animator Bounce Widget");
  set_border_width(10);

  m_vbox.pack_start( m_AnimatorBounceWidget );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  m_vbox.pack_start( m_check );
  m_vbox.pack_start( m_reset );
  m_vbox.pack_start( m_Viewport );

  m_check.set_label( "Start Animation");
  m_check.signal_toggled().connect( sigc::mem_fun( *this, &Example_AnimatorBounceWidget::on_start_stop ) );

  m_reset.set_label( "Reset" );
  m_reset.signal_clicked().connect( sigc::mem_fun( *this, &Example_AnimatorBounceWidget::on_reset ) );

  m_AffineAnimator->set_frame_rate( 20 );
  m_AffineAnimator->set_rotate( M_PI/50 );
  m_AffineAnimator->set_translate( 2.0, -2.0 );
  m_AffineAnimator->set_scale( 0.95, 0.95 );

  this->add( m_vbox );

  show_all();
}

Example_AnimatorBounceWidget::~Example_AnimatorBounceWidget()
{
}

void Example_AnimatorBounceWidget::on_start_stop()
{
  if ( m_check.get_active() )
    m_AffineAnimator->start();
  else
    m_AffineAnimator->stop();
}

void Example_AnimatorBounceWidget::on_reset()
{
  m_shape->reset_position();
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
