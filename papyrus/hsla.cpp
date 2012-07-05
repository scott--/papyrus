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
#include "hsla.h"

#include <stdexcept>
#include <cassert>

#include "rgba.h"
#include "color_utility.h"

namespace Papyrus
  {

  HSLA::HSLA(double h, double s, double l, double a):
      hue(h),
      saturation(s),
      lightness(l),
      alpha(a)
  { }

  HSLA::HSLA(const RGBA& rgb)
  {
    *this = rgb;
  }

  double HSLA::operator[](unsigned index)
  {
    switch (index)
      {
      case 0:
        return hue;
      case 1:
        return saturation;
      case 2:
        return lightness;
      case 3:
        return alpha;
      default:
        throw std::out_of_range("Papyrus::HSLA Only indexes 0-3 are valid.");
      }
  }

  HSLA& HSLA::operator=(const RGBA& rgb)
  {
    rgb_to_hsl(rgb.red, rgb.green, rgb.blue, hue, saturation, lightness);
    this->alpha = rgb.alpha;
    return *this;
  }

  HSLA::operator RGBA()
  {
    RGBA rgb;
    hsl_to_rgb(hue, saturation, lightness, rgb.red, rgb.green, rgb.blue);
    rgb.alpha = this->alpha;
    return rgb;
  }

  // From: Computer Graphics: Principles and Practice
  void rgb_to_hsl(double r, double g, double b,
                  double& h, double& s, double& l)
  {
    double max;
    double min;

    assert( r >= 0.0 && r <= 1.0);
    assert( g >= 0.0 && g <= 1.0);
    assert( b >= 0.0 && b <= 1.0);

    get_min_max(min, max, r, g, b);

    l = (max+min)/2.0;
    if (max == min)
      {
        s = 0;
        h = 0; // h is undefined
      }
    else
      {
        double delta = max - min;
        s = (l <= 0.5)?(delta/(max+min)):(delta/(2.0-(max+min)));
        if (r==max)
          h = (g-b)/delta;
        else if (g==max)
          h = 2.0 + (b-r)/delta;
        else if (b==max)
          h = 4.0+(r-g)/delta;
        h *= 60.0;
        if (h < 0.0)
          h += 360.0;
      }
  }

  // From: Computer Graphics: Principles and Practice
  double hsl_value(double m1, double m2, double hue)
  {
    if (hue > 360.0)
      hue -= 360.0;
    else if (hue < 0.0)
      hue += 360.0;
    if (hue < 60.0)
      return m1 + (m2-m1)*hue/60.0;
    else if (hue < 180.0)
      return m2;
    else if (hue < 240.0)
      return m1 + (m2-m1)*(240.0-hue)/60.0;
    else
      return m1;
  }

  // From: Computer Graphics: Principles and Practice
  void hsl_to_rgb(double h, double s, double l,
                  double& r, double& g, double& b)
  {
    double m1, m2;

    assert( h >= 0.0 && h <= 360.0);
    assert( s >= 0.0 && s <= 1.0);
    assert( l >= 0.0 && l <= 1.0);

    m2 = (l <= 0.5)?(l*(l+s)):(l+s-l*s);
    m1 = 2.0 * l - m2;
    if (s == 0.0)
      {
        if (h == 0)
          r = g = b = l;
      }
    else
      {
        r = hsl_value(m1, m2, h+120.0);
        g = hsl_value(m1, m2, h);
        b = hsl_value(m1, m2, h-120.0);
      }
  }

}
