/* Line Join Combo Box
 *
 * Line join combo boxes provide the user with a means of selecting various
 * line join styles via a drop-down combo box. Each selection shows a graphical
 * representation of the line join.
 */

#include "gtkmm.h"

#include <papyrus-gtkmm/linejoincombobox.h>

class Example_LineJoinComboBox : public Gtk::Window
{
  public:
    Example_LineJoinComboBox();
    virtual ~Example_LineJoinComboBox();

  protected:
  //Member widgets:
    Papyrus::Gtk::LineJoinComboBox m_LineJoinComboBox;
};

//Called by DemoWindow;
Gtk::Window* do_LineJoinComboBox()
{
  return new Example_LineJoinComboBox();
}

Example_LineJoinComboBox::Example_LineJoinComboBox()
{

  set_title("Line Join Combo Boxes");
  set_border_width(10);

  this->add( m_LineJoinComboBox );

  show_all();
}

Example_LineJoinComboBox::~Example_LineJoinComboBox()
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
