/* This example demonstrates the Selector controller.
 *
 * The selector controller captures events and builds a selection.
 *
 * DrawableContainerInterface is an ancestor of Selector. Therefore an owning
 * Papyrus::Group object may be set as well as a drawing Papyrus::Group object.
 *
 */

#include "gtkmm.h"

#include <iostream>
#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Selector : public Gtk::Window
{
  public:
    Example_Selector();
    virtual ~Example_Selector();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Selector::pointer m_Selector;
    Papyrus::Boxed::pointer m_boxed;

    void on_selected( Papyrus::Drawable::pointer selected );

    void on_deselected( Papyrus::Drawable::pointer deselected );

};

//Called by DemoWindow;
Gtk::Window* do_Selector()
{
  return new Example_Selector();
}

Example_Selector::Example_Selector()
{
  set_title("Selector Example");
  set_border_width(10);

  m_boxed = Papyrus::Boxed::create( );
  m_boxed->box()->set_fill( Cairo::SolidPattern::create_rgba(1.0, 0.85, 1.0, 0.9) );
  m_boxed->box()->set_stroke( Cairo::SolidPattern::create_rgba(1.0, 0.0, 1.0, 0.9) );

  // Create the selector
  m_Selector = Papyrus::Selector::create(m_Viewport.canvas());

  // Connect the Papyrus::Boxed group to the selector
  // Anything added to the selector will be added to the box and the box will be the drawing owner only
  m_boxed->link( m_Selector );

  // Example connecting to the added/removed signals of the selector
  m_Selector->signal_drawable_added().connect( sigc::mem_fun( *this, &Example_Selector::on_selected ) );
  m_Selector->signal_drawable_removed().connect( sigc::mem_fun( *this, &Example_Selector::on_deselected ) );

  // Place the selector under the control of the viewport so it will receive events
  m_Viewport.add_controller( m_Selector );

  m_Viewport.canvas()->set_size( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Rectangle::pointer rectangle = Papyrus::example_rectangle( );
  Papyrus::Circle::pointer circle = Papyrus::example_circle( );
  Papyrus::Arc::pointer arc = Papyrus::example_arc( );

  // Add the shapes to the group
  m_Viewport.canvas()->add( rectangle );
  m_Viewport.canvas()->add( circle );
  m_Viewport.canvas()->add( arc );
  m_Viewport.canvas()->add( m_boxed, Papyrus::Boxed::DEFAULT_LEVEL );

  // Translate the shapes so they don't necessarily overlap
  rectangle->set_xywh(0, -60, 50, 30);
  circle->translate(40, 20);
  circle->set_radius(25);
  arc->translate(0, 20);

  this->add( m_Viewport );

  show_all();
}

Example_Selector::~Example_Selector()
{
}

void Example_Selector::on_selected( Papyrus::Drawable::pointer selected )
{
  std::cout << "on_selected callback: added a drawable of type " << selected->class_name() << std::endl;
}

void Example_Selector::on_deselected( Papyrus::Drawable::pointer deselected )
{
  std::cout << "on_deselected callback: removed a drawable of type " << deselected->class_name() << std::endl;
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
