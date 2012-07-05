/* Viewports
 *
 * A Viewport widget displays a Papyrus Canvas, and is roughly similar in concept to a
 * Gtk DrawingArea or a Gnome Canvas object. The Viewport inherits from Gtk::EventBox
 * so it is capable of capturing user input.
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Viewport : public Gtk::Window
{
  public:
    Example_Viewport();
    virtual ~Example_Viewport();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
};

//Called by DemoWindow;
Gtk::Window* do_Viewport()
{
  return new Example_Viewport();
}

Example_Viewport::Example_Viewport()
{

  set_title("Viewport Example");
  set_border_width(10);

	m_Viewport.set_size_request(200, 200);
	m_Viewport.canvas()->add( Papyrus::example_group( true, true ) );

  this->add( m_Viewport );

  show_all();
}

Example_Viewport::~Example_Viewport()
{
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
