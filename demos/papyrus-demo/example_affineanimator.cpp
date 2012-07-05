/* Affine Animators
 *
 * An affine animator is capable of animating a Papyrus::Drawable
 * or a set of Papyrus::Drawables by applying periodic or controlled
 * affine transformations such as translation, scaling, rotation and/or
 * skewing.
 *
 * The drawables animated do not necessarily need to be contained by
 * the same group, or even be in the same canvas.
 *
 * In addition to specifying what is to be animated, the animation
 * interval or frame rate may also be specified.
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_AffineAnimator : public Gtk::Window
{
  public:
    Example_AffineAnimator();
    virtual ~Example_AffineAnimator();

  protected:
  //Member widgets:
    Papyrus::AffineAnimator::pointer m_AffineAnimator;
    Papyrus::Bezierline::pointer m_BezierLine;
    Papyrus::Arc::pointer m_Arc;
    Papyrus::Group::pointer m_Group;
    Papyrus::Gtk::Viewport m_Viewport;
    Gtk::VBox m_vbox;
    Gtk::CheckButton m_animate_bezierline, m_animate_arc, m_animate_group;

    void on_animate_bezierline_toggled();
    void on_animate_arc_toggled();
    void on_animate_group_toggled();
};

//Called by DemoWindow;
Gtk::Window* do_AffineAnimator()
{
  return new Example_AffineAnimator();
}

Example_AffineAnimator::Example_AffineAnimator()
{

  set_title("Affine Animator Example");
  set_border_width(10);

  m_AffineAnimator = Papyrus::AffineAnimator::create();

  m_BezierLine = Papyrus::example_bezierline( false, true );
  m_Arc = Papyrus::example_arc( true, false );
  m_Group = Papyrus::example_group( true, true );

	m_Viewport.set_size_request(600, 600);

  m_Viewport.canvas()->add( m_Arc );
  m_Viewport.canvas()->add( m_Group );
  m_Viewport.canvas()->add( m_BezierLine );

  m_vbox.pack_start( m_Viewport );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

  m_animate_bezierline.set_label( "Animate Bezierline" );
  m_animate_arc.set_label( "Animate Arc" );
  m_animate_group.set_label( "Animate Group" );
  m_animate_bezierline.signal_toggled().connect( sigc::mem_fun(*this, &Example_AffineAnimator::on_animate_bezierline_toggled) );
  m_animate_arc.signal_toggled().connect( sigc::mem_fun(*this, &Example_AffineAnimator::on_animate_arc_toggled) );
  m_animate_group.signal_toggled().connect( sigc::mem_fun(*this, &Example_AffineAnimator::on_animate_group_toggled) );
  m_vbox.pack_start( m_animate_bezierline );
  m_vbox.pack_start( m_animate_arc );
  m_vbox.pack_start( m_animate_group );

  m_AffineAnimator->set_frame_rate( 25 );
  m_AffineAnimator->set_rotate( M_PI/50 );
  m_AffineAnimator->set_bounce_frames( 60 );
  m_AffineAnimator->start();

  this->add( m_vbox );

  show_all();
}

Example_AffineAnimator::~Example_AffineAnimator()
{
}

void Example_AffineAnimator::on_animate_bezierline_toggled()
{
  if ( m_animate_bezierline.get_active() )
    m_AffineAnimator->add( m_BezierLine );
  else
    m_AffineAnimator->remove( m_BezierLine );
}

void Example_AffineAnimator::on_animate_arc_toggled()
{
  if ( m_animate_arc.get_active() )
    m_AffineAnimator->add( m_Arc );
  else
    m_AffineAnimator->remove( m_Arc );
}

void Example_AffineAnimator::on_animate_group_toggled()
{
  if ( m_animate_group.get_active() )
    m_AffineAnimator->add( m_Group );
  else
    m_AffineAnimator->remove( m_Group );
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
