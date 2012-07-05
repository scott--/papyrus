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
#ifndef PAPYRUSHSBA_H
#define PAPYRUSHSBA_H

#include <cairomm/pattern.h>

namespace Papyrus {

class RGBA;

  /**
   * A structure containing a HSBA value.
   */

struct HSBA {
  HSBA(double h=0.0, double s=0.0, double b=0.0, double a=1.0);

  HSBA(const RGBA& rgb);

  double hue, saturation, brightness, alpha;

  double operator[](unsigned index);

  HSBA& operator=(const RGBA& rgb);

  operator RGBA() const;

  operator Cairo::RefPtr<Cairo::Pattern>();

  };

  void rgb_to_hsb(double rgb_r, double rgb_g, double rgb_b,
                  double& hsb_h, double& hsb_s, double& hsb_b);

  void hsb_to_rgb(double hsb_h, double hsb_s, double hsb_b,
                  double& rgb_r, double& rgb_g, double& rgb_b);


}

#endif
