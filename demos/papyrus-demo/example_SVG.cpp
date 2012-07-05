/* SVG
 *
 */

#include <gtkmm.h>
#include <iostream>
#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_SVG: public Gtk::Window
{
  public:
    Example_SVG();
    virtual ~Example_SVG();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::SVG::pointer m_SVG;

    Gtk::VBox m_vbox;
    Gtk::FileChooserButton m_file_button;

    void on_file_changed();
};

//Called by DemoWindow;
Gtk::Window* do_SVG()
{
  return new Example_SVG();
}

Example_SVG::Example_SVG()
{
  set_title("SVG Example");
  set_border_width(10);

  m_Viewport.canvas()->set_size( 500, 400 );

  m_vbox.pack_start( m_Viewport );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  m_vbox.pack_start( m_file_button );

  m_file_button.set_filename( "cairo_logo_dung.svg" );
  m_file_button.signal_selection_changed().connect( sigc::mem_fun( *this, &Example_SVG::on_file_changed ) );

  this->add( m_vbox );

  m_Viewport.canvas()->clear();
  m_Viewport.canvas()->set_background( Papyrus::RGBA("white") );

  m_SVG = Papyrus::example_svg( );
  m_Viewport.canvas()->add( m_SVG );

  show_all();
}

Example_SVG::~Example_SVG()
{
}

void Example_SVG::on_file_changed()
{
  std::cout << "New filename: " << m_file_button.get_filename() << std::endl;
  if ( m_file_button.get_filename().size() > 0 )
  {
    Papyrus::SVG::pointer new_svg = Papyrus::SVG::create( m_file_button.get_filename() );
    if ( new_svg ) std::cout << m_file_button.get_filename() << " loaded successfully" << std::endl;
    else std::cout << m_file_button.get_filename() << " loaded unsuccessfully" << std::endl;
    m_Viewport.canvas()->remove( m_SVG );
    m_SVG = new_svg;
    m_Viewport.canvas()->add( m_SVG );
    std::cout << m_SVG->svg() << std::endl;
  }
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
