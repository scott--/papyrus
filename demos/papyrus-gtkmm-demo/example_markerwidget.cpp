/* Marker Widget
 *
 * Marker widgets provide the user with a means of selecting various attributes
 * of markers including the fill color, outline color, width, height, line
 * width, line cap, and line join.
 *
 * In addition to setting the attributes, a preview widget is also available.
 */

#include "gtkmm.h"

#include <papyrus-gtkmm/markerwidget.h>

class Example_MarkerWidget : public Gtk::Window
{
  public:
    Example_MarkerWidget();
    virtual ~Example_MarkerWidget();

  protected:
  //Member widgets:
    Papyrus::Gtk::MarkerWidget m_MarkerWidget;
};

//Called by DemoWindow;
Gtk::Window* do_MarkerWidget()
{
  return new Example_MarkerWidget();
}

Example_MarkerWidget::Example_MarkerWidget()
{

  set_title("Marker Widget");
  set_border_width(10);

  this->add( m_MarkerWidget );

  show_all();
}

Example_MarkerWidget::~Example_MarkerWidget()
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
