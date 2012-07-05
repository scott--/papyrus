/* Rotator
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Rotator : public Gtk::Window
{
  public:
    Example_Rotator();
    virtual ~Example_Rotator();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Rotator::pointer m_Rotator;

    Gtk::Adjustment m_rotate_interval_adj;
    Gtk::SpinButton m_rotate_interval;

  void on_rotate_interval_changed();
};

//Called by DemoWindow;
Gtk::Window* do_Rotator()
{
  return new Example_Rotator();
}

Example_Rotator::Example_Rotator():
  m_rotate_interval_adj( 0.0, 0.0, 2.0 * M_PI, M_PI / 10.0, M_PI / 2.0 ),
  m_rotate_interval( m_rotate_interval_adj )
{
  Gtk::HBox* hbox;
  Gtk::VBox* vbox;

  set_title("Rotator Example");

  m_Rotator = Papyrus::Rotator::create( );
  m_Viewport.add_controller( m_Rotator );

  m_Viewport.set_size_request( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Arc::pointer arc = Papyrus::example_arc( );

  // Add the shapes to the group
  m_Viewport.canvas()->add( arc );

  m_Rotator->add( arc );

  vbox = Gtk::manage( new Gtk::VBox() );
  vbox->pack_start( m_Viewport );
  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

//   hbox = Gtk::manage( new Gtk::HBox() );
//   hbox->pack_start( *Gtk::manage( new Gtk::Label("Rotation Interval") ) );
//   hbox->pack_start( m_rotate_interval );
//   vbox->pack_start( *hbox );

  this->add( *vbox );

  m_rotate_interval.signal_value_changed().connect( sigc::mem_fun(*this, &Example_Rotator::on_rotate_interval_changed) );

  show_all();
}

Example_Rotator::~Example_Rotator()
{
}

void Example_Rotator::on_rotate_interval_changed()
{
//   m_Rotator->set_radian_interval( m_rotate_interval.get_value() );
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
