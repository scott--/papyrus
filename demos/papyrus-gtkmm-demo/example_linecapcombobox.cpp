/* Line Cap Combo Box
 *
 * Line cap combo boxes provide the user with a means of selecting various
 * line cap styles via a drop-down combo box. Each selection shows a graphical
 * representation of the line cap.
 */

#include "gtkmm.h"

#include <papyrus-gtkmm/linecapcombobox.h>

class Example_LineCapComboBox : public Gtk::Window
{
  public:
    Example_LineCapComboBox();
    virtual ~Example_LineCapComboBox();

  protected:
  //Member widgets:
    Papyrus::Gtk::LineCapComboBox m_LineCapComboBox;
};

//Called by DemoWindow;
Gtk::Window* do_LineCapComboBox()
{
  return new Example_LineCapComboBox();
}

Example_LineCapComboBox::Example_LineCapComboBox()
{

  set_title("Line Cap Combo Boxes");
  set_border_width(10);

  this->add( m_LineCapComboBox );

  show_all();
}

Example_LineCapComboBox::~Example_LineCapComboBox()
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
