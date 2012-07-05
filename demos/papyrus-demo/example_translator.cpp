/* Translator
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Translator : public Gtk::Window
{
  public:
    Example_Translator();
    virtual ~Example_Translator();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Translator::pointer m_Translator;

    Gtk::CheckButton m_translate_x_button, m_translate_y_button;
    Gtk::Adjustment m_grid_x_adj, m_grid_y_adj;
    Gtk::SpinButton m_grid_x, m_grid_y;

  void on_translate_x_toggled();
  void on_translate_y_toggled();
  void on_grid_x_changed();
  void on_grid_y_changed();
};

//Called by DemoWindow;
Gtk::Window* do_Translator()
{
  return new Example_Translator();
}

Example_Translator::Example_Translator():
  m_translate_x_button("Translate X"),
  m_translate_y_button("Translate Y"),
  m_grid_x_adj( 0.0, 0.0, 500.0, 10.0, 50.0 ),
  m_grid_y_adj( 0.0, 0.0, 500.0, 10.0, 50.0 ),
  m_grid_x( m_grid_x_adj ),
  m_grid_y( m_grid_y_adj )
{
  Gtk::HBox* hbox;
  Gtk::VBox* vbox;

  set_title("Translator Example");

  m_Translator = Papyrus::Translator::create( );
  m_Viewport.add_controller( m_Translator );

  m_Viewport.set_size_request( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Arc::pointer arc = Papyrus::example_arc( );

  // Add the shapes to the group
  m_Viewport.canvas()->add( arc );
  m_Translator->add( arc );

  vbox = Gtk::manage( new Gtk::VBox() );
  vbox->pack_start( m_Viewport );
  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  vbox->pack_start( m_translate_x_button );
  vbox->pack_start( m_translate_y_button );
  m_translate_x_button.set_active(true);
  m_translate_y_button.set_active(true);

  hbox = Gtk::manage( new Gtk::HBox() );
  hbox->pack_start( *Gtk::manage( new Gtk::Label("Grid X size") ) );
  hbox->pack_start( m_grid_x );
  vbox->pack_start( *hbox );

  hbox = Gtk::manage( new Gtk::HBox() );
  hbox->pack_start( *Gtk::manage( new Gtk::Label("Grid Y size") ) );
  hbox->pack_start( m_grid_y );
  vbox->pack_start( *hbox );

  this->add( *vbox );

  m_translate_x_button.signal_toggled().connect( sigc::mem_fun(*this, &Example_Translator::on_translate_x_toggled) );
  m_translate_y_button.signal_toggled().connect( sigc::mem_fun(*this, &Example_Translator::on_translate_y_toggled) );
  m_grid_x.signal_value_changed().connect( sigc::mem_fun(*this, &Example_Translator::on_grid_x_changed) );
  m_grid_y.signal_value_changed().connect( sigc::mem_fun(*this, &Example_Translator::on_grid_y_changed) );

  show_all();
}

Example_Translator::~Example_Translator()
{
}

void Example_Translator::on_translate_x_toggled()
{
  if ( m_translate_x_button.get_active() )
    m_Translator->enable_transforms( Papyrus::TRANSLATE_X );
  else
    m_Translator->disable_transforms( Papyrus::TRANSLATE_X );
}

void Example_Translator::on_translate_y_toggled()
{
  if ( m_translate_y_button.get_active() )
    m_Translator->enable_transforms( Papyrus::TRANSLATE_Y );
  else
    m_Translator->disable_transforms( Papyrus::TRANSLATE_Y );
}

void Example_Translator::on_grid_x_changed()
{
  m_Translator->set_grid_x( m_grid_x.get_value() );
}

void Example_Translator::on_grid_y_changed()
{
  m_Translator->set_grid_y( m_grid_y.get_value() );
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
