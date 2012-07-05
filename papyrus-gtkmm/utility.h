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
#ifndef PAPYRUSGTKUTILITY_H
#define PAPYRUSGTKUTILITY_H

#include <gtkmm.h>
#include <papyrus/renderable.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
     * \page guide_pixbuf Gdk::Pixbuf from Papyrus::Canvas
     *
     * Glib::RefPtr<Gdk::Pixbuf> create_pixbuf(Papyrus::Renderable::pointer, int width, int height)
     *
     * Given a Papyrus::Renderable and size as width, height this method will create a Gdk::Pixbuf.
     * This method will not resize the Papyrus::Renderable to fit on the Gdk::Pixbuf. It will simply
     * render directly into the Gdk::Pixbuf.
     *
     * Although the PapyrusGtk::CanvasArea is capable of displaying a Papyrus::Canvas, this utility
     * method is provided for those cases where a Gdk::Pixbuf is needed instead. As an example, one such
     * class present in Gtkmm is Gtk::CellRendererPixbuf.
     *
     * The following contains an example that will add a Papyrus::Group to a Papyrus::Canvas, render
     * the Papyrus::Canvas into a Gdk::Pixbuf, and display the Gdk::Pixbuf inside a Gtk::Image widget.
     *
     * \image html screenshot_pixbuf_from_canvas.png "Screenshot created with code below; Gtk::Image containing Gdk::Pixbuf created with PapyrusGtk::create_pixbuf()"
     *
     * \dontinclude pixbuf.cpp
     * \skip PixbufWindow
     * \until }
     *
     */
    Glib::RefPtr<Gdk::Pixbuf> create_pixbuf ( Papyrus::Renderable::pointer, int width, int height );

    Glib::RefPtr<Gdk::Pixbuf> cairo_image_to_pixbuf( const Cairo::RefPtr<Cairo::ImageSurface> );

  }

}

#endif
