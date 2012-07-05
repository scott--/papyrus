
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


Gtk::Window* do_AnimatorBounceWidget();
Gtk::Window* do_AnimatorFrameIntervalWidget();
Gtk::Window* do_AnimatorFrameRateWidget();
Gtk::Window* do_LineCapButtonBox();
Gtk::Window* do_LineJoinButtonBox();
Gtk::Window* do_LineCapComboBox();
Gtk::Window* do_LineJoinComboBox();
Gtk::Window* do_LineWidthComboBox();
Gtk::Window* do_MarkerComboBox();
Gtk::Window* do_MarkerWidget();
Gtk::Window* do_StrokeWidget();
Gtk::Window* do_Pixbuf();
Gtk::Window* do_Viewport();
Gtk::Window* do_ScrolledViewport();
Gtk::Window* do_Selector();
Gtk::Window* do_DrawableTreeView();
Gtk::Window* do_LinearGradient();

Demo comboboxes[] = {
  { "Line Cap Combo Box", "example_linecapcombobox.cpp",  sigc::ptr_fun(&do_LineCapComboBox), 0 },
  { "Line Join Combo Box", "example_linejoincombobox.cpp",  sigc::ptr_fun(&do_LineJoinComboBox), 0 },
  { "Line Width Combo Boxes", "example_linewidthcombobox.cpp",  sigc::ptr_fun(&do_LineWidthComboBox), 0 },
  { "Marker Combo Box", "example_markercombobox.cpp",  sigc::ptr_fun(&do_MarkerComboBox), 0 },
  { 0, 0, type_slotDo(), 0 }
};

Demo animator[] = {
  { "Bounce Widget", "example_animatorbouncewidget.cpp",  sigc::ptr_fun(&do_AnimatorBounceWidget), 0 },
  { "Frame Interval Widget", "example_animatorframeintervalwidget.cpp",  sigc::ptr_fun(&do_AnimatorFrameIntervalWidget), 0 },
  { "Frame Rate Widget", "example_animatorframeratewidget.cpp",  sigc::ptr_fun(&do_AnimatorFrameRateWidget), 0 },
  { 0, 0, type_slotDo(), 0 }
};

Demo viewports[] = {
  { "Basic Viewport", "example_viewport.cpp",  sigc::ptr_fun(&do_Viewport), 0 },
  { "Scrolled Viewport", "example_scrolledviewport.cpp",  sigc::ptr_fun(&do_ScrolledViewport), 0 },
  { 0, 0, type_slotDo(), 0 }
};

Demo gradients[] = {
  { "Linear Gradient", "example_lineargradient.cpp", sigc::ptr_fun(&do_LinearGradient), 0 },
  { 0, 0, type_slotDo(), 0 }
};


Demo testgtk_demos[] =
{
	{ "Viewports", "", type_slotDo(), viewports },
  { "Gdk Pixbufs", "example_pixbuf.cpp",  sigc::ptr_fun(&do_Pixbuf), 0 },
  { "Line Cap Button Boxes", "example_linecapbuttonbox.cpp",  sigc::ptr_fun(&do_LineCapButtonBox), 0 },
  { "Line Join Button Boxes", "example_linejoinbuttonbox.cpp",  sigc::ptr_fun(&do_LineJoinButtonBox), 0 },
  { "Marker Widget", "example_markerwidget.cpp",  sigc::ptr_fun(&do_MarkerWidget), 0 },
  { "Line Style Widget", "example_strokewidget.cpp",  sigc::ptr_fun(&do_StrokeWidget), 0 },
  { "Drawable Tree View", "example_drawabletreeview.cpp",  sigc::ptr_fun(&do_DrawableTreeView), 0 },
  { "Combo Boxes", "", type_slotDo(), comboboxes },
  { "Animator Widgets", "", type_slotDo(), animator },
  { "Gradients", "", type_slotDo(), gradients },
  { 0, 0, type_slotDo(), 0 }
};

#endif //_DEMOS_H
