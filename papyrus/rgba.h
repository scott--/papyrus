/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
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
#ifndef PAPYRUSRGBA_H
#define PAPYRUSRGBA_H

#include <regex.h>
#include <string>

#include <cairomm/pattern.h>
#include <papyrus/fill.h>
#include <papyrus/stroke.h>
#include <papyrus/paint.h>

namespace Papyrus {

typedef enum COLOR_INDEXES {
  RED=0x00,
  GREEN=0x01,
  BLUE=0x02,
  HUE=0x00,
  SATURATION=0x01,
  BRIGHTNESS=0x02,
  LIGHTNESS=0x02,
  ALPHA=0x03
} COLOR_INDEXES;

/**
 * A structure storing an RGBA value.
 */
struct RGBA {

  RGBA(double r=0.0, double g=0.0, double b=0.0, double a=1.0);

  RGBA(const Glib::ustring& name, double a=1.0);

  double red, green, blue, alpha;

  double operator[](unsigned index);

  operator Cairo::RefPtr<Cairo::Pattern>() const;

  operator Fill::pointer() const;

  operator Stroke::pointer() const;

  operator Paint::pointer() const;

  private:
  // TODO make this threadsafe
  static regex_t regular_expression[4];
  static bool regex_initialized;

  static void initialize_regular_expressions();

};

}
#endif
