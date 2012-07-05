/* Zoomer
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/scrolledviewport.h>

class Example_Zoomer : public Gtk::Window
{
  public:
    Example_Zoomer();
    virtual ~Example_Zoomer();

  protected:
  //Member widgets:
    Papyrus::Gtk::ScrolledViewport m_ScrolledViewport;
    Papyrus::Zoomer::pointer m_Zoomer;
};

//Called by DemoWindow;
Gtk::Window* do_Zoomer()
{
  return new Example_Zoomer();
}

Example_Zoomer::Example_Zoomer()
{
  Gtk::HBox* hbox;
  Gtk::VBox* vbox;

  set_title("Zoomer Example");

  Papyrus::Gtk::Viewport& viewport = m_ScrolledViewport.viewport();

  m_Zoomer = Papyrus::Zoomer::create( );
  viewport.add_controller( m_Zoomer );

  viewport.set_size_request( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Group::pointer g = Papyrus::example_group( );

  viewport.canvas()->add( g );
  m_Zoomer->add( g );

  vbox = Gtk::manage( new Gtk::VBox() );
  vbox->pack_start( m_ScrolledViewport );

  this->add( *vbox );

  show_all();
}

Example_Zoomer::~Example_Zoomer()
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
