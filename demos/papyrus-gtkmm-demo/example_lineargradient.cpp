/* Linar Gradients
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/gradientstopwidget.h>

class Example_LinearGradient : public Gtk::Window
{
  public:
    Example_LinearGradient();
    virtual ~Example_LinearGradient();

  protected:
  //Member widgets:
    Papyrus::Gtk::GradientStopWidget m_stopwidget;
};

//Called by DemoWindow;
Gtk::Window* do_LinearGradient()
{
  return new Example_LinearGradient();
}

Example_LinearGradient::Example_LinearGradient():
    m_stopwidget(4)
{

  set_title("Linear Gradient Example");
  set_border_width(10);

  this->add( m_stopwidget );

  show_all();
}

Example_LinearGradient::~Example_LinearGradient()
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
