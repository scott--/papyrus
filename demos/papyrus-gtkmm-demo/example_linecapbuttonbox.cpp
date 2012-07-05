/* Line Cap Button Box
 *
 * Line cap button boxes provide the user with a means of selecting various
 * line cap styles. Each button shows a graphical representation of the
 * line cap.
 */

#include "gtkmm.h"

#include <papyrus-gtkmm/linecapbuttonbox.h>

class Example_LineCapButtonBox : public Gtk::Window
{
public:
  Example_LineCapButtonBox();
  virtual ~Example_LineCapButtonBox();

protected:
  //Member widgets:
  Papyrus::Gtk::LineCapButtonBox m_LineCapButtonBox[5];
  Gtk::Frame m_frame[5];
  Gtk::VBox m_vbox;
};

//Called by DemoWindow;
Gtk::Window* do_LineCapButtonBox()
{
  return new Example_LineCapButtonBox();
}

Example_LineCapButtonBox::Example_LineCapButtonBox()
{

  set_title("Line Cap Button Boxes");
  set_border_width(10);

  this->add( m_vbox );

  m_frame[0].set_label( "Extra Small: " );
  m_LineCapButtonBox[0].set_size( Papyrus::Gtk::SIZE_XSMALL );

  m_frame[1].set_label( "Small: " );
  m_LineCapButtonBox[1].set_size( Papyrus::Gtk::SIZE_SMALL );

  m_frame[2].set_label( "Medium: " );
  m_LineCapButtonBox[2].set_size( Papyrus::Gtk::SIZE_MEDIUM );

  m_frame[3].set_label( "Large: " );
  m_LineCapButtonBox[3].set_size( Papyrus::Gtk::SIZE_LARGE );

  m_frame[4].set_label( "Extra Large: " );
  m_LineCapButtonBox[4].set_size( Papyrus::Gtk::SIZE_XLARGE );

  for ( int i = 0; i <= 5; i++ ) {
    m_frame[i].add( m_LineCapButtonBox[i] );
    m_vbox.pack_start( m_frame[i], Gtk::PACK_EXPAND_WIDGET, 10);
  }

  m_vbox.set_border_width(10);

  show_all();
}

Example_LineCapButtonBox::~Example_LineCapButtonBox()
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
