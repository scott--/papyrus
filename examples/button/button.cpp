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
#include "button.h"

#include <cmath>

#define ANIMATE_ROTATE_STEP M_PI/60.0
#define ANIMATE_FRAME_RATE 20

Window::Window()
{

  set_title("Papyrus Button Example");

  m_vbox.set_border_width(12);

  m_slider.set_range(0, M_PI*2.0);
  m_slider.set_increments(0.05, 0.05);


  m_rect = Papyrus::Rectangle::create(); // Create the rectangle
  m_rect->set_xywh( 75, 75, 75, 75);
  m_rect->rotate(m_slider.get_value()); // set an initial rotation of the box to the value of the slider
  m_rect->set_fill( Cairo::SolidPattern::create_rgb(1.0, 0.0, 0.0) ); // set the box color to red

  m_animator = Papyrus::AffineAnimator::create();
  m_animator->add( m_rect );

  m_buttonimage.set_size_request(100, 100);
  m_buttonimage.canvas()->set_viewbox(Papyrus::Viewbox::create(-20, -20, 40, 40));
  m_buttonimage.canvas()->add(m_rect);

  m_button.add(m_buttonimage);
  m_vbox.pack_start(m_button);

  m_slider.set_draw_value(false);
  m_slider.signal_value_changed().connect(sigc::mem_fun(*this, &Window::slider_changed));
  m_vbox.pack_start(m_slider, Gtk::PACK_SHRINK);

  m_animate_button.set_label("Animate Rotation");
  m_animate_button.signal_toggled().connect(sigc::mem_fun(*this, &Window::animate_toggled));
  m_vbox.pack_start(m_animate_button, Gtk::PACK_SHRINK);

  add(m_vbox);
  m_vbox.show_all();
  show_all();
}

Window::~Window()
{
}

void
Window::slider_changed()
{
  // rotate the box to the value of the slider
  m_rect->rotate(m_slider.get_value());
}

void
Window::animate_step(int frames)
{
  double    newval = m_slider.get_value() + frames * ANIMATE_ROTATE_STEP;
  if (newval > M_PI*2.0)
    newval -= M_PI*2.0;
  m_slider.set_value(newval);
}

void
Window::animate_toggled()
{
  m_animator->set_frame_rate( ANIMATE_FRAME_RATE );
  m_animator->set_rotate( ANIMATE_ROTATE_STEP );
  if ( m_animate_button.get_active() )
    m_animator->start();
  else
    m_animator->stop();
}
