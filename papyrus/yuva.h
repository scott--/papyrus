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
#ifndef PAPYRUSYUVA_H
#define PAPYRUSYUVA_H

namespace Papyrus {

class RGBA;

  /**
   * A structure containing a YUV value.
   */

struct YUVA {
  YUVA(double yuv_y=0.0, double yuv_u=0.0, double yuv_v=0.0, double yuv_a=1.0);

  YUVA(const RGBA& rgb);

  double y, u, v, alpha;

  double operator[](unsigned index);

  YUVA& operator=(const RGBA& rgb);

  operator RGBA();


  };

  void rgb_to_yuv(double rgb_r, double rgb_g, double rgb_b,
                  double& yuv_y, double& yuv_u, double& yuv_v);

  void yuv_to_rgb(double yuv_y, double yuv_u, double yuv_v,
                  double& rgb_r, double& rgb_g, double& rgb_b);


}

#endif
