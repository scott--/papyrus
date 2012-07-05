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
#include "helper.h"

void make_image(Drawable::pointer p, const Glib::ustring & filename)
{
  if ( not p ) return;
  Region size = p->extents();

  if ( not size ) return;

  p->translate( - size.x(), - size.y() );

  if ( size.width() == 0 or size.height() == 0 ) return;

  Cairo::RefPtr<Cairo::ImageSurface> surface =
      Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, size.width(), size.height());

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

  p->render(cr);

  surface->write_to_png(filename);
}
