/* Scrolled Viewport
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/scrolledviewport.h>

class Example_ScrolledViewport : public Gtk::Window
{
  public:
    Example_ScrolledViewport();
    virtual ~Example_ScrolledViewport();

  protected:
  //Member widgets:
    Papyrus::Gtk::ScrolledViewport m_ScrolledViewport;
    Papyrus::Zoomer::pointer m_Zoomer;

    void on_scroll_placement_changed( ::Gtk::CornerType corner );
};

//Called by DemoWindow;
Gtk::Window* do_ScrolledViewport()
{
  return new Example_ScrolledViewport();
}

Example_ScrolledViewport::Example_ScrolledViewport()
{
  Gtk::HBox* hbox;
  Gtk::VBox* vbox;

  set_title("ScrolledViewport Example");

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
  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

  Gtk::RadioButton* rb;
  Gtk::VBox* vbox2;
  Gtk::Frame* frame;
  Gtk::Label* label;

  label = Gtk::manage( new Gtk::Label("Use the mouse wheel to zoom in and out.\n\nThe scrollbars are set to automatic in this example so you will need to zoom in before they show up.") );
  label->set_use_markup();
  label->set_line_wrap();
  vbox->pack_start(*label, Gtk::PACK_SHRINK, 10);
  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

  vbox2 = Gtk::manage( new Gtk::VBox() );
  frame = Gtk::manage( new Gtk::Frame("Viewport Scroll Placement") );
  frame->add(*vbox2);
  vbox->pack_start(*frame, Gtk::PACK_SHRINK, 10);
  label = Gtk::manage( new Gtk::Label("<i>Placement refers to the corner where the viewport will be placed</i>") );
  label->set_use_markup();
  label->set_line_wrap();
  vbox2->pack_start(*label, Gtk::PACK_SHRINK);
  Gtk::RadioButtonGroup scroll_placement_group;
  rb = Gtk::manage( new Gtk::RadioButton( scroll_placement_group, "Top Left" ) );
  rb->signal_toggled().connect( sigc::bind(sigc::mem_fun(*this, &Example_ScrolledViewport::on_scroll_placement_changed), Gtk::CORNER_TOP_LEFT) );
  vbox2->pack_start( *rb );
  rb = Gtk::manage( new Gtk::RadioButton( scroll_placement_group, "Bottom Left" ) );
  rb->signal_toggled().connect( sigc::bind(sigc::mem_fun(*this, &Example_ScrolledViewport::on_scroll_placement_changed), Gtk::CORNER_BOTTOM_LEFT) );
  vbox2->pack_start( *rb );
  rb = Gtk::manage( new Gtk::RadioButton( scroll_placement_group, "Top Right" ) );
  rb->signal_toggled().connect( sigc::bind(sigc::mem_fun(*this, &Example_ScrolledViewport::on_scroll_placement_changed), Gtk::CORNER_TOP_RIGHT) );
  vbox2->pack_start( *rb );
  rb = Gtk::manage( new Gtk::RadioButton( scroll_placement_group, "Bottom Right" ) );
  rb->signal_toggled().connect( sigc::bind(sigc::mem_fun(*this, &Example_ScrolledViewport::on_scroll_placement_changed), Gtk::CORNER_BOTTOM_RIGHT) );
  vbox2->pack_start( *rb );
  
  this->add( *vbox );

  show_all();
}

Example_ScrolledViewport::~Example_ScrolledViewport()
{
}

void Example_ScrolledViewport::on_scroll_placement_changed( ::Gtk::CornerType corner )
{
  m_ScrolledViewport.set_placement( corner );
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
