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
#ifndef PAPYRUSSCHEME_H
#define PAPYRUSSCHEME_H

#include <vector>

#include <papyrus/hsba.h>

namespace Papyrus
  {

  typedef std::vector<HSBA> Colors;

  Colors primary_colors(double saturation=1.0, double brightness=1.0);

  Colors secondary_colors(double saturation=1.0, double brightness=1.0);

  Colors primary_secondary_colors(double saturation=1.0, double brightness=1.0);

  Colors tertiary_colors(double saturation=1.0, double brightness=1.0);

  Colors rgb_color_wheel(unsigned bands=24, double saturation=1.0, double brightness=1.0);

  Colors complements(const HSBA& color);

  Colors complements(const Colors& colors);

  Colors split_complements(const HSBA& color, double split=24.0);

  Colors split_complements(const Colors& colors, double split=24.0);

  Colors triads(const HSBA& color);

  Colors triads(const Colors& colors);

  Colors tetrads(const HSBA& color, double offset=-60.0);

  Colors tetrads(const Colors& colors, double offset=-60.0);

  Colors analogous(const HSBA& color, unsigned size=3, double offset=-30.0);

  Colors analogous(const Colors& colors, unsigned size=3, double offset=-30.0);

  /** Adjusting the white level (saturation) */
  Colors tints(const HSBA& color,
                                  unsigned size=5,
                                  double offset=-0.2,
                                  double start=1.0
                                 );

  Colors tints(const Colors& colors,
               unsigned size=5,
               double offset=-0.2,
               double start=1.0
              );

  /** Adjusting the black level (brightness) */
  Colors shades(const HSBA& color,
                                  unsigned size=5,
                                  double offset=-0.2,
                                  double start=1.0
                                 );

  Colors shades(const Colors& colors,
                unsigned size=5,
                double offset=-0.2,
                double start=1.0
               );

  /** Adjusting the gray level (brightness and saturation) */
  Colors tones(const HSBA& color,
               unsigned size=5,
               double offset=-0.2,
               double start=1.0
              );

  Colors tones(const Colors& colors,
               unsigned size=5,
               double offset=-0.2,
               double start=1.0
              );

  /** Tints and shades */
  Colors monochromatic(const HSBA& color,
                          unsigned size=3,
                          double offset=-0.5,
                          double start=1.0
                         );

  Colors monochromatic(const Colors& colors,
                       unsigned size=3,
                       double offset=-0.5,
                       double start=1.0
                      );


  HSBA complement(const HSBA& color, double offset);

  HSBA hue_offset(const HSBA& color, double offset);


}

#endif
