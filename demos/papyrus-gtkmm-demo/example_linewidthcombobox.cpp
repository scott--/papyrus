/* Line Width Combo Box
 *
 * Line width combo boxes provide the user with a means of selecting various
 * line width. Each entry shows a graphical representation of the
 * line width.
 */

#include "gtkmm.h"

#include <papyrus-gtkmm/linewidthcombobox.h>

class Example_LineWidthComboBox : public Gtk::Window
{
public:
  Example_LineWidthComboBox();
  virtual ~Example_LineWidthComboBox();

protected:
  //Member widgets:
  Papyrus::Gtk::LineWidthComboBox m_LineWidthComboBox[4];
  Gtk::Frame m_frame[4];
  Gtk::VBox m_vbox;
};

//Called by DemoWindow;
Gtk::Window* do_LineWidthComboBox()
{
  return new Example_LineWidthComboBox();
}

Example_LineWidthComboBox::Example_LineWidthComboBox()
{

  set_title("Line Width Combo Boxes");
  set_border_width(10);

  this->add( m_vbox );

  m_frame[0].set_label( "Linear, Factor=1.0: " );
  m_LineWidthComboBox[0].set_start_stop( 1.0, 16.0 );

  m_frame[1].set_label( "Linear, Factor=2.0: " );
  m_LineWidthComboBox[1].set_start_stop( 1.0, 16.0 );
  m_LineWidthComboBox[1].set_factor( 2.0 );

  m_frame[2].set_label( "Exponential, Factor=1.15: " );
  m_LineWidthComboBox[2].set_start_stop( 1.0, 16.0 );
  m_LineWidthComboBox[2].set_increment_type( Papyrus::Gtk::INCREMENT_EXPONENTIAL );
  m_LineWidthComboBox[2].set_factor( 1.15 );

  m_frame[3].set_label( "Exponential, Factor=1.50: " );
  m_LineWidthComboBox[3].set_start_stop( 1.0, 16.0 );
  m_LineWidthComboBox[3].set_increment_type( Papyrus::Gtk::INCREMENT_EXPONENTIAL );
  m_LineWidthComboBox[3].set_factor( 1.5 );

  for ( int i = 0; i <= 4; i++ ) {
    m_frame[i].add( m_LineWidthComboBox[i] );
    m_vbox.pack_start( m_frame[i], Gtk::PACK_EXPAND_WIDGET, 10);
  }

  m_vbox.set_border_width(10);

  show_all();
}

Example_LineWidthComboBox::~Example_LineWidthComboBox()
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
