/* $Id: textwidget.h,v 1.1 2006/06/10 05:01:13 rvinyard Exp $ */

/* textwidget.h
 *
 * Copyright (C) 2001-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _TEXTWIDGET_H
#define _TEXTWIDGET_H

#include "gtkmm/scrolledwindow.h"
#include "gtkmm/textview.h"


class TextWidget : public Gtk::ScrolledWindow
{
public:
  TextWidget(bool is_source);
  virtual ~TextWidget();

  Glib::RefPtr<Gtk::TextBuffer> get_buffer();
  void wipe();
  void fontify();

protected:

  //Signal handlers:

  //Child widgets:
  Gtk::TextView m_TextView;
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

};

#endif //_TEXTWIDGET_H
