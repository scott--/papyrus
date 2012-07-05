/* Scaler
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Scaler : public Gtk::Window
{
  public:
    Example_Scaler();
    virtual ~Example_Scaler();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Scaler::pointer m_Scaler;

    Gtk::ToggleButton m_side_buttons[4];

  void on_button_toggled( int which );
};

//Called by DemoWindow;
Gtk::Window* do_Scaler()
{
  return new Example_Scaler();
}

Example_Scaler::Example_Scaler()
{
  Gtk::HBox* hbox;
  Gtk::VBox* vbox;

  set_title("Scaler Example");

  m_Scaler = Papyrus::Scaler::create( );
  m_Viewport.add_controller( m_Scaler );

  m_Viewport.set_size_request( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Arc::pointer arc = Papyrus::example_arc( );

  arc->translate(50, 50);

  // Add the shapes to the group
  m_Viewport.canvas()->add( arc );

  m_Scaler->add( arc );

  vbox = Gtk::manage( new Gtk::VBox() );
  vbox->pack_start( m_Viewport );
  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

  Gtk::Table* table;

  table = Gtk::manage( new Gtk::Table() );
  m_side_buttons[0].set_label("Top");
  m_side_buttons[1].set_label("Right");
  m_side_buttons[2].set_label("Bottom");
  m_side_buttons[3].set_label("Left");
  table->attach( m_side_buttons[0], 1, 2, 0, 1 );
  table->attach( m_side_buttons[1], 2, 3, 1, 2 );
  table->attach( m_side_buttons[2], 1, 2, 2, 3 );
  table->attach( m_side_buttons[3], 0, 1, 1, 2 );
  for ( int i=0; i < 4; i++ )
  {
    m_side_buttons[i].set_active(true);
    m_side_buttons[i].signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Example_Scaler::on_button_toggled), i ) );
  }

  vbox->pack_start( *table );

  this->add( *vbox );

  show_all();
}

Example_Scaler::~Example_Scaler()
{
}

void Example_Scaler::on_button_toggled( int which )
{
  Papyrus::Side side;
  switch (which) {
    case 0:
      side = Papyrus::TOP;
      break;
    case 1:
      side = Papyrus::RIGHT;
      break;
    case 2:
      side = Papyrus::BOTTOM;
      break;
    case 3:
      side = Papyrus::LEFT;
      break;
  }

  if ( m_side_buttons[which].get_active() )
    m_Scaler->enable_sides( side );
  else
    m_Scaler->disable_sides( side );

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
