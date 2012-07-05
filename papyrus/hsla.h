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
#ifndef PAPYRUSHSLA_H
#define PAPYRUSHSLA_H

namespace Papyrus
  {

  struct RGBA;

  /**
   * A structure containing a HSLA value.
   */
  struct HSLA
    {
      HSLA(double h=0.0, double s=0.0, double l=0.0, double a=0.0);

      HSLA(const RGBA& rgb);

      double hue, saturation, lightness, alpha;

      double operator[](unsigned index);

      HSLA& operator=(const RGBA& rgb);

      operator RGBA();

    };

    /**
     * Convert RGB color to HSL
     * Given r,g,b, each in [0,1], returns h in [0,360]; s and l in [0,1].
     */
    void rgb_to_hsl(double rgb_r, double rgb_g, double rgb_b,
                  double& h, double& s, double& l);

    /**
     * Convert HSLA color to RGB
     * Given h in [0,360]; s and l in [0,1], returns r,g,b each in [0,1].
     */
    void hsl_to_rgb(double hsl_h, double hsl_s, double hsl_l,
                    double& rgb_r, double& rgb_g, double& rgb_b);

}

#endif
