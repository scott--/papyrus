/* Gdk Pixbufs from a Papyrus Canvas
 *
 * It's easy ( a one line function call ) to render a Papyrus Canvas or any
 * other drawing that inherits from Papyrus::Renderable into a Gdk Pixbuf.
 * This example shows how.
 */

#include "gtkmm.h"

#include <papyrus/canvas.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/utility.h>

class Example_Pixbuf : public Gtk::Window
{
  public:
    Example_Pixbuf();
    virtual ~Example_Pixbuf();

  protected:
  //Member widgets:
    Gtk::Image m_GtkImage;
};

//Called by DemoWindow;
Gtk::Window* do_Pixbuf()
{
  return new Example_Pixbuf();
}

Example_Pixbuf::Example_Pixbuf()
{
  set_title("Pixbuf from Papyrus Canvas Example");
  set_border_width(10);

  Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();
  canvas->translate(100,100);
  Papyrus::Drawable::pointer drawable = Papyrus::example_group(true, false);
  canvas->add( Papyrus::example_group( true, false ) );

  Glib::RefPtr<Gdk::Pixbuf> pixbuf;
  // This is the real line of interest
  // Creating a Gdk::Pixbuf from a Papyrus::Canvas
  // But, any Papyrus::Renderable will work
//   pixbuf = Papyrus::Gtk::create_pixbuf(canvas, 200, 200);
  Cairo::RefPtr<Cairo::ImageSurface> is = Papyrus::imagesurface( drawable, 50, 50 );
  pixbuf = Papyrus::Gtk::cairo_image_to_pixbuf( is );

  m_GtkImage.set( pixbuf );
  this->add( m_GtkImage );
  this->modify_bg( Gtk::STATE_NORMAL, Gdk::Color("black") );
  this->show_all();
}

Example_Pixbuf::~Example_Pixbuf()
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
