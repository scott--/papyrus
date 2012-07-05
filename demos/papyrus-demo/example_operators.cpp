/* Operators
 *
 */

#include <gtkmm.h>

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_operators : public Gtk::Window
{
  public:
    Example_operators();
    virtual ~Example_operators();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Drawable::pointer m_Drawable;
    Papyrus::Drawable::pointer m_Cubes[3];
    Papyrus::Group::pointer m_CubeGroup;

    void redraw_canvas();

    Gtk::VBox m_vbox;
    Gtk::ComboBoxText m_combobox;
};

//Called by DemoWindow;
Gtk::Window* do_operators()
{
  return new Example_operators();
}

Example_operators::Example_operators()
{
  set_title("composite operator Example");
  set_border_width(10);

  m_Viewport.canvas()->set_size( 500, 400 );

  m_vbox.pack_start( m_Viewport );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  m_vbox.pack_start( m_combobox );

  m_combobox.append_text("CLEAR");
  m_combobox.append_text("SOURCE");
  m_combobox.append_text("OVER");
  m_combobox.append_text("IN");
  m_combobox.append_text("OUT");
  m_combobox.append_text("ATOP");
  m_combobox.append_text("DEST");
  m_combobox.append_text("DEST OVER");
  m_combobox.append_text("DEST IN");
  m_combobox.append_text("DEST OUT");
  m_combobox.append_text("DEST ATOP");
  m_combobox.append_text("XOR");
  m_combobox.append_text("ADD");
  m_combobox.append_text("SATURATE");

  m_combobox.set_active(2);

  m_combobox.signal_changed().connect( sigc::mem_fun(*this, &Example_operators::redraw_canvas));

  this->add( m_vbox );

  m_Viewport.canvas()->clear();
  m_Viewport.canvas()->set_background( Papyrus::RGBA("white") );

  m_Drawable = Papyrus::example_factory( Papyrus::SVG );
  m_Viewport.canvas()->add( m_Drawable );

  m_Cubes[0] = Papyrus::Rectangle::create( -100, -100, 150, 150, Papyrus::RGBA(0.7,0.0,0.0,0.8) );
  m_Cubes[1] = Papyrus::Rectangle::create( -50, -50, 150, 150, Papyrus::RGBA(0.0,0.9,0.0,0.4) );
  m_Cubes[2] = Papyrus::Rectangle::create( 0, 0, 150, 150, Papyrus::RGBA(0.0,0.0,0.9,0.4) );

  m_CubeGroup = Papyrus::Group::create();

  for ( int i=0; i < 3; i++)
    m_CubeGroup->add( m_Cubes[i] );
    
  m_Viewport.canvas()->add( m_CubeGroup );

  show_all();
}

Example_operators::~Example_operators()
{
}

void Example_operators::redraw_canvas( )
{
  int which;
  Papyrus::Polyline::pointer line;

  which = m_combobox.get_active_row_number();

  if ( which < 0 )
    return;

  m_Cubes[1]->set_composite_operator((Cairo::Operator)which);
  m_Cubes[2]->set_composite_operator((Cairo::Operator)which);
  
//   m_CubeGroup->set_composite_operator((Cairo::Operator)which);

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
