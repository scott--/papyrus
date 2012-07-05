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

#include <papyrus-gtkmm/viewport.h>
#include <papyrus/rectangle.h>
#include <papyrus/image.h>
#include <papyrus/circle.h>
#include <papyrus/text.h>
#include <papyrus/polyline.h>
#include <papyrus/polygon.h>

class Simple : public Gtk::Window
{

public:
  Simple();
  virtual ~Simple();

protected:
  //Signal handlers:

  //Member widgets:
  Gtk::VBox m_vbox;
  Gtk::Frame m_frame;
  Gtk::HScale m_slider;
  Gtk::HScale m_zoom;
  Gtk::CheckButton m_animate;
  Papyrus::Gtk::Viewport m_viewport;
  Papyrus::Rectangle::pointer m_rect;
  Papyrus::Image::pointer m_png;
  Papyrus::Circle::pointer m_circle;
  Papyrus::Text::pointer m_text;
  Papyrus::Polyline::pointer m_lines;
  Papyrus::Polygon::pointer m_polygon;
  Papyrus::Drawable::pointer m_drawables[7];

  int m_rotate_object;

  int m_zoom_object;

  void slider_changed();
  void zoom_changed();
  bool animate_step();
  void animate_toggled();
  void on_sig_size_allocate(Gtk::Allocation&);

  void adjust_canvas(int width, int height);

  void draw_scene();

  void on_rotate_object_changed(int n);

  void on_zoom_object_changed(int n);

};
