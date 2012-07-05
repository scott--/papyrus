/* Marker Combo Box
 *
 * Marker combo boxes provide the user with a means of selecting various
 * marker styles via a drop-down combo box. Each selection shows a graphical
 * representation of the marker.
 */

#include "gtkmm.h"

#include <papyrus-gtkmm/markercombobox.h>

class Example_MarkerComboBox : public Gtk::Window
{
  public:
    Example_MarkerComboBox();
    virtual ~Example_MarkerComboBox();

  protected:
  //Member widgets:
    Papyrus::Gtk::MarkerComboBox m_MarkerComboBox;
};

//Called by DemoWindow;
Gtk::Window* do_MarkerComboBox()
{
  return new Example_MarkerComboBox();
}

Example_MarkerComboBox::Example_MarkerComboBox()
{

  set_title("Marker Combo Box");
  set_border_width(10);

  this->add( m_MarkerComboBox );

  show_all();
}

Example_MarkerComboBox::~Example_MarkerComboBox()
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
