/* Flasher
 *
 * A flasher inherits from Animator and simply alternates between showing and
 * hiding the associated drawables with each frame.
 *
 * To control the rate of flash, adjust the interval of the animator.
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

class Example_Flasher : public Gtk::Window
{
  public:
    Example_Flasher();
    virtual ~Example_Flasher();

  protected:
  //Member widgets:
    Papyrus::Flasher::pointer m_Flasher;
    Papyrus::Bezierline::pointer m_BezierLine;
    Papyrus::Arc::pointer m_Arc;
    Papyrus::Group::pointer m_Group;
    Papyrus::Gtk::Viewport m_Viewport;
    Gtk::VBox m_vbox;
    Gtk::CheckButton m_flash_bezierline, m_flash_arc, m_flash_group;

    void on_flash_bezierline_toggled();
    void on_flash_arc_toggled();
    void on_flash_group_toggled();
};

//Called by DemoWindow;
Gtk::Window* do_Flasher()
{
  return new Example_Flasher();
}

Example_Flasher::Example_Flasher()
{

  set_title("Flasher Example");
  set_border_width(10);

  m_Flasher = Papyrus::Flasher::create();

  m_BezierLine = Papyrus::example_bezierline( false, true );
  m_Arc = Papyrus::example_arc( true, false );
  m_Group = Papyrus::example_group( true, true );

	m_Viewport.set_size_request(600, 600);

  m_Viewport.canvas()->add( m_Arc );
  m_Viewport.canvas()->add( m_Group );
  m_Viewport.canvas()->add( m_BezierLine );

  m_vbox.pack_start( m_Viewport );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

  m_flash_bezierline.set_label( "Flash Bezierline" );
  m_flash_arc.set_label( "Flash Arc" );
  m_flash_group.set_label( "Flash Group" );
  m_flash_bezierline.signal_toggled().connect( sigc::mem_fun(*this, &Example_Flasher::on_flash_bezierline_toggled) );
  m_flash_arc.signal_toggled().connect( sigc::mem_fun(*this, &Example_Flasher::on_flash_arc_toggled) );
  m_flash_group.signal_toggled().connect( sigc::mem_fun(*this, &Example_Flasher::on_flash_group_toggled) );
  m_vbox.pack_start( m_flash_bezierline );
  m_vbox.pack_start( m_flash_arc );
  m_vbox.pack_start( m_flash_group );

  m_Flasher->start();

  this->add( m_vbox );

  show_all();
}

Example_Flasher::~Example_Flasher()
{
}

void Example_Flasher::on_flash_bezierline_toggled()
{
  if ( m_flash_bezierline.get_active() )
    m_Flasher->add( m_BezierLine );
  else
    m_Flasher->remove( m_BezierLine );
}

void Example_Flasher::on_flash_arc_toggled()
{
  if ( m_flash_arc.get_active() )
    m_Flasher->add( m_Arc );
  else
    m_Flasher->remove( m_Arc );
}

void Example_Flasher::on_flash_group_toggled()
{
  if ( m_flash_group.get_active() )
    m_Flasher->add( m_Group );
  else
    m_Flasher->remove( m_Group );
}

/***************************************************************************
 *   Copyright (C) 2009,2010 by Rick L. Vinyard, Jr.                       *
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
