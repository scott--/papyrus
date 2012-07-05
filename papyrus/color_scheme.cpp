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
#include "color_scheme.h"

using namespace std;

#include <stdexcept>
#include <cassert>
#include <cmath>

namespace Papyrus
  {

  Colors primary_colors(double saturation, double brightness) {
    Colors colorset;
    for (unsigned i=0; i<3; i++)
      colorset.push_back( HSBA(i*120, saturation, brightness) );
    return colorset;
  }

  Colors secondary_colors(double saturation, double brightness) {
    Colors colorset;
    for (unsigned i=0; i<3; i++)
      colorset.push_back( HSBA(i*120+60, saturation, brightness) );
    return colorset;
  }

  Colors primary_secondary_colors(double saturation, double brightness) {
    Colors colorset;
    for (unsigned i=0; i<6; i++)
      colorset.push_back( HSBA(i*60, saturation, brightness) );
    return colorset;
  }

  Colors tertiary_colors(double saturation, double brightness) {
    Colors colorset;
    for (unsigned i=0; i<6; i++)
      colorset.push_back( HSBA(i*60+30, saturation, brightness) );
    return colorset;
  }

  Colors rgb_color_wheel(unsigned bands, double saturation, double brightness) {
    Colors colorset;
    for (unsigned i=0; i<bands; i++)
      colorset.push_back( HSBA(i*(360.0/bands), saturation, brightness) );
    return colorset;
  }

  Colors complements(const HSBA& color)
  {
    Colors scheme;
    scheme.push_back(color);
    scheme.push_back( hue_offset(color, 180.0) );
    return scheme;
  }

  Colors complements(const Colors& colors) {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = complements(*i);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors split_complements(const HSBA& color, double split)
  {
    Colors scheme;
    scheme.push_back(color);
    scheme.push_back( hue_offset(color, 180.0-split) );
    scheme.push_back( hue_offset(color, 180.0+split) );
    return scheme;
  }

  Colors split_complements(const Colors& colors, double split)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = split_complements(*i, split);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors triads(const HSBA& color)
  {
    Colors scheme;
    scheme.push_back(color);
    scheme.push_back( hue_offset(color, 120.0) );
    scheme.push_back( hue_offset(color, 240.0) );
    return scheme;
  }

  Colors triads(const Colors& colors)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = triads(*i);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors tetrads(const HSBA& color, double split)
  {
    Colors scheme;
    scheme.push_back(color);
    scheme.push_back( hue_offset(color, split) );
    scheme.push_back( hue_offset(color, 180.0) );
    scheme.push_back( hue_offset(color, 180.0+split) );
    return scheme;
  }

  Colors tetrads(const Colors& colors, double split)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = tetrads(*i, split);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors analogous(const HSBA& color, unsigned size, double offset)
  {
    Colors scheme;
    for (unsigned i = 0; i < size; i++)
      scheme.push_back( hue_offset(color, offset*i) );
    return scheme;
  }

  Colors analogous(const Colors& colors, unsigned size, double offset)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = analogous(*i, size, offset);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors tints(const HSBA& color,
                                  unsigned size,
                                  double offset,
                                  double start)
  {
    Colors scheme;
    double h=color.hue, b=color.brightness, sat=start;

    assert(start >= 0.0 && start <= 1.0);
    assert(offset > -1.0 && offset < 1.0);

    for (unsigned i=0; i < size; i++)
      {
        scheme.push_back( HSBA(h, sat, b) );
        sat += offset;
        if (sat < 0.0)
          sat += 1.0;
        else if (sat > 1.0)
          sat -= 1.0;
      }
    return scheme;
  }

  Colors tints(const Colors& colors,
               unsigned size,
               double offset,
               double start)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = tints(*i, size, offset, start);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors shades(const HSBA& color,
                                  unsigned size,
                                  double offset,
                                  double start)
  {
    Colors scheme;
    double h=color.hue, s=color.saturation, bright=start;

    assert(start >= 0.0 && start <= 1.0);
    assert(offset > -1.0 && offset < 1.0);

    for (unsigned i=0; i < size; i++)
      {
        scheme.push_back( HSBA(h, s, bright) );
        bright += offset;
        if (bright < 0.0)
          bright += 1.0;
        else if (bright > 1.0)
          bright -= 1.0;
      }
    return scheme;
  }

  Colors shades(const Colors& colors,
                unsigned size,
                double offset,
                double start)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = shades(*i, size, offset, start);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors tones(const HSBA& color,
                unsigned size,
                double offset,
                double start)
  {
    Colors scheme;
    double h=color.hue;

    assert(start >= 0.0 && start <= 1.0);
    assert(offset > -1.0 && offset < 1.0);

    for (unsigned i=0; i < size; i++)
    {
      scheme.push_back( HSBA(h, start, start) );
      start += offset;
      if (start < 0.0)
        start += 1.0;
      else if (start > 1.0)
        start -= 1.0;
    }
    return scheme;
  }

  Colors tones(const Colors& colors,
               unsigned size,
               double offset,
               double start)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = tones(*i, size, offset, start);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  Colors monochromatic(const HSBA& color,
                          unsigned size,
                          double offset,
                          double start)
  {
    Colors scheme;
    double h=color.hue, changed = start;

    assert(start >= 0.0 && start <= 1.0);
    assert(offset > -1.0 && offset < 1.0);

    if (size > 0)
      scheme.push_back( HSBA(h, start, start) );

    for (unsigned i=1; i < size; i++)
      {
        changed += offset;
        scheme.push_back( HSBA(h, changed, start) );
        if (i+1 < size)
          {
            scheme.push_back( HSBA(h, start, changed) );
            i++;
          }
        start = changed;
      }
    return scheme;
  }

  Colors monochromatic(const Colors& colors,
                       unsigned size,
                       double offset,
                       double start)
  {
    Colors colorset, temp_colors;
    for (Colors::const_iterator i = colors.begin(); i != colors.end(); i++) {
      temp_colors = monochromatic(*i, size, offset, start);
      colorset.insert( colorset.end(), temp_colors.begin(), temp_colors.end() );
    }
    return colorset;
  }

  HSBA complement(const HSBA& color)
  {
    return hue_offset(color, 180.0);

  }

  HSBA hue_offset(const HSBA& color, double o)
  {
    HSBA offset = color;
    offset.hue += o;
    if ( offset.hue >= 360.0 )
      offset.hue -= ( (int)offset.hue/360 ) * 360.0;
    else if (offset.hue < 0.0)
      offset.hue += ( (int)offset.hue/-360 + 1 ) * 360.0;
    return offset;
  }

}
