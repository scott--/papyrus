/***************************************************************************
 *   Copyright (C) 2004,2010 by Rick L. Vinyard, Jr.                       *
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
#ifndef PAPYRUS_H
#define PAPYRUS_H

#include <papyrus/papyrus-config.h>
#include <papyrus/enums.h>
#include <papyrus/animator.h>
#include <papyrus/affineanimator.h>
#include <papyrus/annulus.h>
#include <papyrus/arc.h>
#include <papyrus/bezierline.h>
#include <papyrus/beziergon.h>
#include <papyrus/boxed.h>
#include <papyrus/canvas.h>
#include <papyrus/color.h>
#include <papyrus/color_scheme.h>
#include <papyrus/circle.h>
#include <papyrus/controller.h>
#include <papyrus/drawable.h>
#include <papyrus/drawablesinglecontainer.h>
#include <papyrus/fill.h>
#include <papyrus/flasher.h>
#include <papyrus/freehandsketcher.h>
#include <papyrus/gradient.h>
#include <papyrus/grid.h>
#include <papyrus/group.h>
#include <papyrus/handlebox.h>
#include <papyrus/hsba.h>
#include <papyrus/hsla.h>
#include <papyrus/image.h>
#include <papyrus/lineargradient.h>
#include <papyrus/marker.h>
#include <papyrus/object.h>
#include <papyrus/path.h>
#include <papyrus/path_element.h>
#include <papyrus/polygon.h>
#include <papyrus/polyline.h>
#include <papyrus/radialgradient.h>
#include <papyrus/rectangle.h>
#include <papyrus/reference.h>
#include <papyrus/region.h>
#include <papyrus/regularpolygon.h>
#include <papyrus/renderable.h>
#include <papyrus/rgba.h>
#include <papyrus/rotator.h>
#include <papyrus/scaler.h>
#include <papyrus/selector.h>
#include <papyrus/shape.h>
#include <papyrus/pointer.h>
#include <papyrus/stroke.h>
#include <papyrus/svg.h>
#include <papyrus/text.h>
#include <papyrus/translator.h>
#include <papyrus/utility.h>
#include <papyrus/utility2.h>
#include <papyrus/viewbox.h>
#include <papyrus/yuva.h>
#include <papyrus/zoomer.h>

#endif
