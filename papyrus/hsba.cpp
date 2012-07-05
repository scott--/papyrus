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
#include "hsba.h"

#include <stdexcept>
#include <cassert>
#include <cmath>

#include "rgba.h"
#include "color_utility.h"

namespace Papyrus
  {

  HSBA::HSBA(double h, double s, double b, double a):
      hue(h),
      saturation(s),
      brightness(b),
      alpha(a)
  { }

  HSBA::HSBA(const RGBA& rgb)
  {
    *this = rgb;
  }

  double HSBA::operator[](unsigned index)
  {
    switch (index)
      {
      case 0:
        return hue;
      case 1:
        return saturation;
      case 2:
        return brightness;
      case 3:
        return alpha;
      default:
        throw std::out_of_range("Papyrus::HSBA Only indexes 0-3 are valid.");
      }
  }

  HSBA& HSBA::operator=(const RGBA& rgb)
  {
    rgb_to_hsb(rgb.red, rgb.green, rgb.blue, hue, saturation, brightness);
    this->alpha = rgb.alpha;
    return *this;
  }

  HSBA::operator RGBA() const
  {
    RGBA rgb;
    hsb_to_rgb(hue, saturation, brightness, rgb.red, rgb.green, rgb.blue);
    rgb.alpha = this->alpha;
    return rgb;
  }

  HSBA::operator Cairo::RefPtr<Cairo::Pattern>()
  {
    return static_cast<RGBA>(*this);
  }


  // From: Computer Graphics: Principles and Practice
  void rgb_to_hsb(double r, double g, double b,
                  double& h, double& s, double& v)
  {
    double max;
    double min;

    get_min_max(min, max, r, g, b);

    v = max;

    s = (max != 0.0)?((max-min)/max):0.0;

    if (s == 0)
      h = 0;
    else
      {
        double delta = max - min;
        if (r == max)
          h = (g-b)/delta;
        else if (g == max)
          h = 2.0 + (b-r)/delta;
        else if (b == max)
          h = 4.0 + (r-g)/delta;
        h *= 60.0;
        if (h < 0.0)
          h += 360.0;
      }
  }

  // From: Computer Graphics: Principles and Practice
  void hsb_to_rgb(double h, double s, double v,
                  double& r, double& g, double& b)
  {
    if (s == 0.0)
      r = g = b = v;
    else
      {
        double f, p, q, t;
        int i;

        if (h == 360.0)
          h = 0.0;
        h /= 60.0;
        i = (int) floor(h);
        f = h - i;
        p = v * (1.0 - s);
        q = v * (1.0 - (s*f));
        t = v * (1.0 - (s*(1.0-f)));
        switch(i)
          {
          case 0:
            r = v;
            g = t;
            b = p;
            break;
          case 1:
            r = q;
            g = v;
            b = p;
            break;
          case 2:
            r = p;
            g = v;
            b = t;
            break;
          case 3:
            r = p;
            g = q;
            b = v;
            break;
          case 4:
            r = t;
            g = p;
            b = v;
            break;
          case 5:
            r = v;
            g = p;
            b = q;
            break;
          }
      }
  }


}
