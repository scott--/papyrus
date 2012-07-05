/* HandleBox Scaler
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Handlebox_Scaler : public Gtk::Window
{
  public:
    Example_Handlebox_Scaler();
    virtual ~Example_Handlebox_Scaler();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Scaler::pointer m_Scaler;
    Papyrus::Handlebox::pointer m_boxed;

    Gtk::CheckButton m_translate_x_button, m_translate_y_button;
    Gtk::Adjustment m_grid_x_adj, m_grid_y_adj;
    Gtk::SpinButton m_grid_x, m_grid_y;

  void on_translate_x_toggled();
  void on_translate_y_toggled();
  void on_grid_x_changed();
  void on_grid_y_changed();
};

//Called by DemoWindow;
Gtk::Window* do_Handlebox_Scaler()
{
  return new Example_Handlebox_Scaler();
}

Example_Handlebox_Scaler::Example_Handlebox_Scaler():
  m_translate_x_button("Translate X"),
  m_translate_y_button("Translate Y"),
  m_grid_x_adj( 0.0, 0.0, 500.0, 10.0, 50.0 ),
  m_grid_y_adj( 0.0, 0.0, 500.0, 10.0, 50.0 ),
  m_grid_x( m_grid_x_adj ),
  m_grid_y( m_grid_y_adj )
{
  Gtk::HBox* hbox;
  Gtk::VBox* vbox;

  set_title("Handlebox Scaler Example");

  m_boxed = Papyrus::Handlebox::create( Papyrus::ALL_HANDLES );
  m_boxed->box()->set_fill( Cairo::SolidPattern::create_rgba(1.0, 0.85, 1.0, 0.9) );
  m_boxed->box()->set_stroke( Cairo::SolidPattern::create_rgba(1.0, 0.0, 1.0, 0.9) );

  m_Scaler = Papyrus::Scaler::create();
//   m_Scaler = Papyrus::Scaler::create( m_Viewport.canvas(), m_boxed );
//   m_Scaler->set_drawables(m_Viewport.canvas());
  m_Viewport.add_controller( m_Scaler );

  m_Viewport.set_size_request( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Rectangle::pointer rectangle = Papyrus::example_rectangle( );
  Papyrus::Circle::pointer circle = Papyrus::example_circle( );
  Papyrus::Arc::pointer arc = Papyrus::example_arc( );

  // Add the shapes to the group
  m_Viewport.canvas()->add( rectangle );
  m_Viewport.canvas()->add( circle );
  m_Viewport.canvas()->add( arc );
  m_Viewport.canvas()->add( m_boxed );

  // Translate the shapes so they don't necessarily overlap
  rectangle->set_xywh(0, -60, 50, 30);
  circle->translate(40, 20);
  circle->set_radius(25);
  arc->translate(0, 20);

  vbox = Gtk::manage( new Gtk::VBox() );
  vbox->pack_start( m_Viewport );
  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
//   vbox->pack_start( m_translate_x_button );
//   vbox->pack_start( m_translate_y_button );
//   m_translate_x_button.set_active(true);
//   m_translate_y_button.set_active(true);

//   hbox = Gtk::manage( new Gtk::HBox() );
//   hbox->pack_start( *Gtk::manage( new Gtk::Label("Grid X size") ) );
//   hbox->pack_start( m_grid_x );
//   vbox->pack_start( *hbox );

//   hbox = Gtk::manage( new Gtk::HBox() );
//   hbox->pack_start( *Gtk::manage( new Gtk::Label("Grid Y size") ) );
//   hbox->pack_start( m_grid_y );
//   vbox->pack_start( *hbox );

  this->add( *vbox );

  m_translate_x_button.signal_toggled().connect( sigc::mem_fun(*this, &Example_Handlebox_Scaler::on_translate_x_toggled) );
  m_translate_y_button.signal_toggled().connect( sigc::mem_fun(*this, &Example_Handlebox_Scaler::on_translate_y_toggled) );
  m_grid_x.signal_value_changed().connect( sigc::mem_fun(*this, &Example_Handlebox_Scaler::on_grid_x_changed) );
  m_grid_y.signal_value_changed().connect( sigc::mem_fun(*this, &Example_Handlebox_Scaler::on_grid_y_changed) );

  show_all();
}

Example_Handlebox_Scaler::~Example_Handlebox_Scaler()
{
}

void Example_Handlebox_Scaler::on_translate_x_toggled()
{
/*  if ( m_translate_x_button.get_active() )
    m_Scaler->enable_sides( Papyrus::TRANSLATE_X );
  else
    m_Scaler->disable_sides( Papyrus::TRANSLATE_X );*/
}

void Example_Handlebox_Scaler::on_translate_y_toggled()
{
/*  if ( m_translate_y_button.get_active() )
    m_Scaler->enable_sides( Papyrus::TRANSLATE_Y );
  else
    m_Scaler->disable_sides( Papyrus::TRANSLATE_Y );*/
}

void Example_Handlebox_Scaler::on_grid_x_changed()
{
//   m_Scaler->set_grid_x( m_grid_x.get_value() );
}

void Example_Handlebox_Scaler::on_grid_y_changed()
{
//   m_Scaler->set_grid_y( m_grid_y.get_value() );
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
