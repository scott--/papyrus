/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
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
#include <gtkmm.h>
#include <papyrus-gtkmm.h>

#define WINDOW_SIZE 200
#define X -75
#define Y -50
#define WIDTH 150
#define HEIGHT 100

int main (int argc, char *argv[])
{
  // Set up the gtkmm main loop by passing command line arguments
  Gtk::Main kit(argc, argv);

  Gtk::Window window;                       // The Gtkmm window
  Papyrus::Gtk::Viewport viewport;          // A papyrus viewport to put in the window
  Papyrus::Rectangle::pointer rectangle;    // A rectangle to draw in the viewport

  // Set up the viewport and the window
  window.set_title("Simple Papyrus Example"); // Set the title of the window
  viewport.set_size_request(WINDOW_SIZE, WINDOW_SIZE); // Set the viewport window size
  window.add(viewport);
  window.show_all();

  rectangle = Papyrus::Rectangle::create(X, Y, WIDTH, HEIGHT, Papyrus::RGBA("orchid3"), Papyrus::RGBA("yellow") ); // Create the rectangle

  viewport.canvas()->add(rectangle); // add the rectangle to the canvas

  Gtk::Main::run(window); //Shows the window and returns when it is closed.

  return 0;
}

