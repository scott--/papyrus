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
#include "yuva.h"

#include <stdexcept>
#include <cassert>
#include <cmath>

#include "rgba.h"
#include "color_utility.h"

namespace Papyrus
  {

  YUVA::YUVA(double yuv_y, double yuv_u, double yuv_v, double yuv_a):
      y(yuv_y),
      u(yuv_u),
      v(yuv_v),
      alpha(yuv_a)
  { }

  YUVA::YUVA(const RGBA& rgb)
  {
    *this = rgb;
  }

  double YUVA::operator[](unsigned index)
  {
    switch (index)
      {
      case 0:
        return this->y;
      case 1:
        return this->u;
      case 2:
        return this->v;
      case 3:
        return this->alpha;
      default:
        throw std::out_of_range("Papyrus::YUVA Only indexes 0-3 are valid.");
      }
  }

  YUVA& YUVA::operator=(const RGBA& rgb)
  {
    rgb_to_yuv(rgb.red, rgb.green, rgb.blue, y, u, v);
    this->alpha = rgb.alpha;
    return *this;
  }

  YUVA::operator RGBA()
  {
    RGBA rgb;
    yuv_to_rgb(y, u, v, rgb.red, rgb.green, rgb.blue);
    rgb.alpha = this->alpha;
    return rgb;
  }

  void rgb_to_yuv(double r, double g, double b,
                  double& y, double& u, double& v)
  {
    y = (0.257 * r)  + (0.504 * g) + (0.098 * b) + 16;

    v = (0.439 * r)  - (0.368 * g) - (0.071 * b) + 128;

    u = -(0.148 * r) - (0.291 * g) + (0.439 * b) + 128;
  }

  void yuv_to_rgb(double y, double u, double v,
                  double& r, double& g, double& b)
  {
    b = 1.164*(y - 16)                   + 2.018*(u - 128);

    g = 1.164*(y - 16) - 0.813*(v - 128) - 0.391*(u - 128);

    r = 1.164*(y - 16) + 1.596*(v - 128);
  }


}
