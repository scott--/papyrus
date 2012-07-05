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
#include <papyrus/circle.h>
#include <papyrus/text.h>
#include <papyrus/polyline.h>
#include <papyrus/polygon.h>
#include <papyrus/regularpolygon.h>

class Simple : public Gtk::Window
{

public:
  Simple();
  virtual ~Simple();

protected:
  Papyrus::Gtk::Viewport m_viewport;
  
  bool on_papyrus_event( const Papyrus::Event::Event& event );

};
