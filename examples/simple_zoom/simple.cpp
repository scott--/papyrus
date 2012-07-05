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
#include "simple.h"

#include <cmath>
#include <iostream>

#define ANIMATE_ROTATE_STEP M_PI/8.0
#define ANIMATE_FRAME_DELAY 40

#define ROTATE_MAX M_PI*2.0

#define MARGIN 20
#define INITIAL_SIZE 300

Simple::Simple():
    m_rotate_object(0),
    m_zoom_object(0)
{
  m_rect = Papyrus::Rectangle::create( );
  m_drawables[0] = m_rect;

  m_circle = Papyrus::Circle::create( );
  m_drawables[1] = m_circle;

  m_text = Papyrus::Text::create( );
  m_drawables[2] = m_text;

  m_lines = Papyrus::Polyline::create( );
  m_drawables[3] = m_lines;

  m_polygon = Papyrus::Polygon::create( );
  m_drawables[4] = m_polygon;

  m_png = Papyrus::Image::create( );
  m_drawables[5] = m_png;

  m_drawables[6] = m_viewport.canvas();

  set_title("Papyrus Group Transformation Demo");

  m_vbox.set_border_width(12);
  m_frame.set_shadow_type(Gtk::SHADOW_IN);

  m_slider.set_range(0, ROTATE_MAX);
  m_slider.set_increments(M_PI/8.0, M_PI/8.0);
  m_zoom.set_range(0.1, 4.0);
  m_zoom.set_increments(0.25, 0.25);
  m_zoom.set_value(1.0);

  m_viewport.set_size_request(INITIAL_SIZE, INITIAL_SIZE);

  adjust_canvas(INITIAL_SIZE, INITIAL_SIZE);

  // This is the method that demonstrates the Papyrus objects
  draw_scene();

  m_frame.add(m_viewport);
  m_vbox.pack_start(m_frame);

  m_slider.set_draw_value(false);
  m_slider.signal_value_changed().connect(sigc::mem_fun(*this, &Simple::slider_changed));
  m_vbox.pack_start(*Gtk::manage(new Gtk::Label("Rotate")), Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_slider, Gtk::PACK_SHRINK);

  m_animate.set_label("Animate Rotation");
  m_animate.signal_toggled().connect(sigc::mem_fun(*this, &Simple::animate_toggled));
  m_vbox.pack_start(*Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_animate, Gtk::PACK_SHRINK);

  m_zoom.signal_value_changed().connect(sigc::mem_fun(*this, &Simple::zoom_changed));
  m_vbox.pack_start(*Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK);
  m_vbox.pack_start(*Gtk::manage(new Gtk::Label("Zoom")), Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_zoom, Gtk::PACK_SHRINK);

  m_vbox.pack_start(*Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_SHRINK);
  Gtk::RadioButtonGroup button_group1, button_group2;
  Gtk::RadioButton* radio_button;
  Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox());
  m_vbox.pack_start(*hbox);
  Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox());
  hbox->pack_start(*vbox);
  vbox->pack_start(*Gtk::manage(new Gtk::Label("Rotation Object")));
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Rectangle"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 0));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Circle"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 1));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Text"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 2));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Lines"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 3));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Polygon"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 4));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Image"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 5));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group1, "Canvas"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_rotate_object_changed), 6));
  vbox->pack_start(*radio_button);

  vbox = Gtk::manage(new Gtk::VBox());
  hbox->pack_start(*vbox);
  vbox->pack_start(*Gtk::manage(new Gtk::Label("Zoom Object")));
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Rectangle"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 0));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Circle"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 1));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Text"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 2));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Lines"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 3));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Polygon"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 4));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Image"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 5));
  vbox->pack_start(*radio_button);
  radio_button = Gtk::manage(new Gtk::RadioButton(button_group2, "Canvas"));
  radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Simple::on_zoom_object_changed), 6));
  vbox->pack_start(*radio_button);

  signal_size_allocate().connect(sigc::mem_fun(*this, &Simple::on_sig_size_allocate));

  add(m_vbox);
  m_vbox.show_all();
  show();
}

Simple::~Simple()
{
}

void Simple::draw_scene( )
{
  // set the box color to red
  m_rect->set_fill( Cairo::SolidPattern::create_rgba( 1.0, 0.0, 0.0, 0.8 ) );

  m_circle->set_fill( Cairo::SolidPattern::create_rgb( 0.0, 0.0, 1.0 ) );
  m_circle->set_stroke( Cairo::SolidPattern::create_rgb( 0.0, 1.0, 0.0 ) );

  m_text->set_text("Text");
  m_text->set_size(40);
  m_text->set_fill( Cairo::SolidPattern::create_rgb( 1.0, 1.0, 0.0 ) );

  m_png->set_image("new_mexico_desert_spring_sm.png");

  m_lines->add_vertex(0, 0);
  m_lines->add_vertex(40, 0);
  m_lines->add_vertex(0, 40);
  m_lines->add_vertex(40, 40);
  m_lines->set_fill( Cairo::SolidPattern::create_rgb( 0.0, 1.0, 1.0 ) );
  m_lines->set_stroke( Cairo::SolidPattern::create_rgb( 1.0, 0.0, 0.0 ) );

  m_polygon->add_vertex(0, 0);
  m_polygon->add_vertex(40, 0);
  m_polygon->add_vertex(0, 40);
  m_polygon->add_vertex(40, 40);
  m_polygon->set_xy(50,50);
  m_polygon->set_fill( Cairo::SolidPattern::create_rgb( 1.0, 0.0, 1.0 ) );
  m_polygon->set_stroke( Cairo::SolidPattern::create_rgb( 0.0, 1.0, 0.0 ) );

  // add the box to the canvas
  m_viewport.canvas()->add(m_text);
  m_viewport.canvas()->add(m_lines);
  m_viewport.canvas()->add(m_rect);
  m_viewport.canvas()->add(m_circle);
  m_viewport.canvas()->add(m_polygon);
  m_viewport.canvas()->add(m_png);
}

void Simple::slider_changed()
{
  double rotation = m_slider.get_value();

  if ( m_rotate_object >= 0 && m_rotate_object < 7)
    m_drawables[m_rotate_object]->set_rotation(rotation);
}

void Simple::zoom_changed()
{
  double s = m_zoom.get_value();
  
  if ( m_zoom_object >= 0 && m_zoom_object < 7)
    m_drawables[m_zoom_object]->set_scale(s);
}


bool
Simple::animate_step ()
{
  double    newval = m_slider.get_value() + ANIMATE_ROTATE_STEP;
  if (newval > ROTATE_MAX)
    newval -= ROTATE_MAX;
  m_slider.set_value(newval);
  return true;
}

void
Simple::animate_toggled()
{
  static sigc::connection timer;
  bool  active = m_animate.get_active();
  if (active && !timer.connected())
      timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Simple::animate_step), ANIMATE_FRAME_DELAY);
  else if (!active && timer.connected())
      timer.disconnect();
}

void Simple::on_sig_size_allocate(Gtk::Allocation& a) {
  adjust_canvas(m_viewport.get_width(), m_viewport.get_height());
}

void Simple::adjust_canvas(int width, int height) {
  int box_size = (width + height) / 6;

  // adjust the box size
  m_rect->set_xywh(-box_size, -box_size, box_size, box_size);

  m_circle->set_radius(box_size/2);
  m_circle->set_xy(-box_size/2, 0);
}

void Simple::on_rotate_object_changed(int n)
{
  static bool changing = false;

  if (changing) return;
  if ( n == m_rotate_object ) return;

  m_rotate_object = 10;
  changing = true;
  m_slider.set_value(m_drawables[n]->get_rotation());
  m_rotate_object = n;
  changing = false;
}

void Simple::on_zoom_object_changed(int n)
{
  static bool changing = false;
  double sx, sy;
  
  if (changing) return;
  if ( n == m_zoom_object ) return;

  m_zoom_object = 10;
  changing = true;

  m_drawables[n]->get_scale(sx, sy);
  m_zoom.set_value(sx);
  m_zoom_object = n;
  changing = false;
}

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  Simple win;
  Gtk::Main::run(win); //Shows the window and returns when it is closed.

  return 0;
}

