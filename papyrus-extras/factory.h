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
#ifndef PAPYRUS_FACTORY_H
#define PAPYRUS_FACTORY_H

#include <papyrus-extras.h>

namespace Papyrus {

typedef enum DRAWABLE {
  DRAWABLE_START=0,
  ARC=0,
  ANNULUS,
  BEZIERLINE,
  BEZIERGON,
  BOXED,
  CIRCLE,
  DELTILLE,
  FACE,
  GRID,
  GROUP,
  HANDLEBOX,
  HEXTILLE,
  HILBERT,
  IMAGE,
  KOCHCURVE,
  KOCHSNOWFLAKE,
  PATH,
  POLYGON,
  POLYLINE,
  QUADRILLE,
  RECTANGLE,
  REFERENCE,
  REGULARPOLYGON,
  SIERPINSKI,
  SVG,
  TEXT,
  DRAWABLE_END,
} DRAWABLE;

extern const char* DrawableStrings[];

Drawable::pointer example_factory( unsigned int d, bool fill=true, bool stroke=false );

Arc::pointer        example_arc(bool fill=true, bool stroke=false);
Annulus::pointer    example_annulus(bool fill=true, bool stroke=false);
Bezierline::pointer example_bezierline(bool fill=false, bool stroke=false);
Beziergon::pointer  example_beziergon(bool fill=false, bool stroke=false);
Boxed::pointer      example_boxed(bool fill=false, bool stroke=true);
Circle::pointer     example_circle(bool fill=true, bool stroke=false);
Group::pointer      example_group(bool fill=true, bool stroke=false);
Group::pointer      example_reference(bool fill=true, bool stroke=false);
Handlebox::pointer  example_handlebox(bool fill=true, bool stroke=false);
Image::pointer      example_image(bool, bool);
Rectangle::pointer  example_rectangle(bool fill=true, bool stroke=false);
SVG::pointer        example_svg(bool f=false, bool s=false);

Group::pointer  example_line_join( Cairo::LineJoin line_join );
Group::pointer  example_line_cap( Cairo::LineCap line_cap );
Polyline::pointer  example_marker( Papyrus::Marker::Style style, Papyrus::Marker::Facing facing, bool fill=false, bool stroke = true);

}

#endif
