
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
#ifndef _DEMOS_H
#define _DEMOS_H

#include "demowindow.h"

typedef sigc::slot<Gtk::Window*> type_slotDo;

struct Demo
{
  const char* title;
  const char* filename;
  //GDoDemoFunc func;
  type_slotDo slot; //The method to call.
  Demo* children;
};

Gtk::Window* do_drawables();
Gtk::Window* do_markers();
Gtk::Window* do_operators();
Gtk::Window* do_Viewbox();
Gtk::Window* do_AffineAnimator();
Gtk::Window* do_Flasher();
Gtk::Window* do_FreehandSketcher();
Gtk::Window* do_Selector();
Gtk::Window* do_AffineController();
Gtk::Window* do_Translator();
Gtk::Window* do_Rotator();
Gtk::Window* do_Scaler();
Gtk::Window* do_Zoomer();
Gtk::Window* do_Handlebox_Scaler();
Gtk::Window* do_Boxed();
Gtk::Window* do_SVG();
Gtk::Window* do_freeze_thaw();
Gtk::Window* do_LinearGradient();
Gtk::Window* do_RadialGradient();

Demo gradients[] = {
  { "Linear Gradient", "example_LinearGradient.cpp",  sigc::ptr_fun(&do_LinearGradient), 0 },
  { "Radial Gradient", "example_RadialGradient.cpp",  sigc::ptr_fun(&do_RadialGradient), 0 },
  { 0, 0, type_slotDo(), 0 }
};

Demo controllers[] = {
  { "Freehand Sketcher", "example_freehandsketcher.cpp",  sigc::ptr_fun(&do_FreehandSketcher), 0 },
  { "Selector", "example_selector.cpp",  sigc::ptr_fun(&do_Selector), 0 },
  { "Affine Controller", "example_affine_controller.cpp", sigc::ptr_fun(&do_AffineController), 0 },
  { "Translator", "example_translator.cpp",  sigc::ptr_fun(&do_Translator), 0 },
  { "Rotator", "example_rotator.cpp",  sigc::ptr_fun(&do_Rotator), 0 },
  { "Scaler", "example_scaler.cpp",  sigc::ptr_fun(&do_Scaler), 0 },
  { "Zoomer", "example_zoomer.cpp",  sigc::ptr_fun(&do_Zoomer), 0 },
    
//  { "Handlebox Scaler", "example_handlebox_scaler.cpp",  sigc::ptr_fun(&do_Handlebox_Scaler), 0 },
  { 0, 0, type_slotDo(), 0 }
};

Demo testgtk_demos[] =
{
  { "Drawables",       "example_drawables.cpp",      sigc::ptr_fun(&do_drawables),      0           },
  { "Freezing/Thawing","example_freeze_thaw.cpp",    sigc::ptr_fun(&do_freeze_thaw),    0           },
  { "Boxed",           "example_boxed.cpp",          sigc::ptr_fun(&do_Boxed),          0           },
  { "Line Markers",    "example_markers.cpp",        sigc::ptr_fun(&do_markers),        0           },
  { "Operators",       "example_operators.cpp",      sigc::ptr_fun(&do_operators),      0           },
  { "Affine Animator", "example_affineanimator.cpp", sigc::ptr_fun(&do_AffineAnimator), 0           },
  { "Flasher",         "example_flasher.cpp",        sigc::ptr_fun(&do_Flasher),        0           },
  { "View Boxes",      "example_viewbox.cpp",        sigc::ptr_fun(&do_Viewbox),        0           },
  { "SVG",             "example_svg.cpp",            sigc::ptr_fun(&do_SVG),            0           },
  { "Controllers",     "",                           type_slotDo(),                     controllers },
  { "Gradients",       "",                           type_slotDo(),                     gradients   },
  { 0,                 0,                            type_slotDo(),                     0           }
};

#endif //_DEMOS_H
