/* Freehand Sketcher
 *
 * The FreehandSketcher manipulator may be attached to a Sketchpad. It captures
 * mouse input when mouse button 1 (left) is pressed and completes drawing when
 * the button is released. The default action is to remove the temporary drawing
 * and notify of the new drawing via a signal.
 */

#include "gtkmm.h"

#include <papyrus.h>
#include <papyrus-gtkmm/viewport.h>

class Example_FreehandSketcher : public Gtk::Window
{
  public:
    Example_FreehandSketcher();
    virtual ~Example_FreehandSketcher();

  protected:
  //Member widgets:
    Gtk::VBox m_VBox;
    Gtk::Frame m_Frame[2];
    Papyrus::Gtk::Viewport m_Viewport[2];
    Papyrus::FreehandSketcher::pointer m_FreehandSketcher[2];
};

//Called by DemoWindow;
Gtk::Window* do_FreehandSketcher()
{
  return new Example_FreehandSketcher();
}

Example_FreehandSketcher::Example_FreehandSketcher()
{

  set_title("Sketcher Example");
  set_border_width(10);

  m_Frame[0].set_label("Line Sketcher");
  m_FreehandSketcher[0] = Papyrus::FreehandSketcher::create(); // default is line sketcher

  // Two things must happen:
  //  1: The Viewport's canvas must be set as the sketching area
  //  2: The sketcher must be added as the Viewport's controller
  m_FreehandSketcher[0]->add_sketchpad( m_Viewport[0].canvas() ); // draw on the viewport canvas
  
  m_FreehandSketcher[0]->set_stroke( Papyrus::Stroke::create(Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0), 4.0) );

  m_Viewport[0].add_controller( m_FreehandSketcher[0] );

  m_Viewport[0].set_size_request( 300, 200 );
  m_Frame[0].add( m_Viewport[0] );
  m_VBox.pack_start( m_Frame[0], Gtk::PACK_EXPAND_WIDGET, 10);

  m_Frame[1].set_label("Polygon Sketcher");
  m_FreehandSketcher[1] = Papyrus::FreehandSketcher::create(Papyrus::SKETCH_POLYGON);

  m_FreehandSketcher[1]->add_sketchpad( m_Viewport[1].canvas() );
  m_Viewport[1].add_controller( m_FreehandSketcher[1] );

  m_FreehandSketcher[1]->set_stroke( Papyrus::Stroke::create(Cairo::SolidPattern::create_rgb(0.0, 0.0, 0.0), 4.0) );

  m_FreehandSketcher[1]->set_fill( Papyrus::Fill::create(Cairo::SolidPattern::create_rgba( 0.0, 0.0, 1.0, 0.5 ) ));
  m_Viewport[1].set_size_request( 300, 200 );
  m_Frame[1].add( m_Viewport[1] );
  m_VBox.pack_start( m_Frame[1], Gtk::PACK_EXPAND_WIDGET, 10);

  this->add( m_VBox );

  show_all();
}

Example_FreehandSketcher::~Example_FreehandSketcher()
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
