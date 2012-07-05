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
#include <papyrus/affineanimator.h>

class Window : public Gtk::Window
{

public:
  Window();
  virtual ~Window();

protected:
  //Signal handlers:

  //Member widgets:
  Gtk::VBox m_vbox;
  Gtk::HScale m_slider;
  Gtk::HScale m_zoom;
  Gtk::CheckButton m_animate_button;
  Gtk::Button m_button;

  Papyrus::AffineAnimator::pointer m_animator;
  Papyrus::Rectangle::pointer m_rect;
  Papyrus::Gtk::Viewport m_buttonimage;

  void slider_changed();
  void animate_step(int);
  void animate_toggled();
};
