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
#include "rgba.h"
#include "color.h"
#include "color_utility.h"
#include "x11_color.h"

#include <stdexcept>

namespace Papyrus
  {

  regex_t RGBA::regular_expression[4];

  bool RGBA::regex_initialized = false;

  RGBA::RGBA(double r, double g, double b, double a):
      red(r),
      green(g),
      blue(b),
      alpha(a)
  { }

  RGBA::RGBA(const Glib::ustring& name, double a)
  {
    int matched;
    int i;
    unsigned int r, g, b;
    regmatch_t match[4];
    Glib::ustring srgb[3];
    Glib::ustring srgb_final;
    
    if ( ! regex_initialized )
      this->initialize_regular_expressions();

    matched = -1;

    for ( i=0; i < 4; i++ )
    {
      if ( regexec(regular_expression+i, name.c_str(), 4, match, 0) == 0 )
      {
        matched = i;
        break;
      }
    }

    if ( matched != -1 )
    {
      for (i=0; i < 3; i++)
      {
        srgb[i] = Glib::ustring( name.c_str()+match[i+1].rm_so, match[i+1].rm_eo-match[i+1].rm_so );
        if ( matched == 1 )
          srgb[i] += srgb[i][0];
        srgb_final += srgb[i] + " ";
      }
    }

    switch (matched)
    {
      case -1:
        *this = x11_color( name );
        break;
      case 0:
      case 1:
        sscanf( srgb_final.c_str(), "%x%x%x", &r, &g, &b );
        red = r / 255.0;
        green = g / 255.0;
        blue = b / 255.0;
        break;
      case 2:
        sscanf( srgb_final.c_str(), "%u%u%u", &r, &g, &b );
        red = r / 255.0;
        green = g / 255.0;
        blue = b / 255.0;
        break;
      case 3:
        sscanf( srgb_final.c_str(), "%u%u%u", &r, &g, &b );
        red = r / 100.0;
        green = g / 100.0;
        blue = b / 100.0;
        break;
      default:
        throw;
    }
    
    this->alpha = a;
  }

  double RGBA::operator[](unsigned index)
  {
    switch (index)
      {
      case 0:
        return red;
      case 1:
        return green;
      case 2:
        return blue;
      case 3:
        return alpha;
      default:
        throw std::out_of_range("Papyrus::RGB Only indexes 0-3 are valid.");
      }
  }

  RGBA::operator Cairo::RefPtr<Cairo::Pattern>() const
  {
    return Cairo::SolidPattern::create_rgba(this->red,
                                            this->green,
                                            this->blue,
                                            this->alpha );
  }

  RGBA::operator Fill::pointer() const
  {
    Cairo::RefPtr<Cairo::Pattern> pattern = Cairo::SolidPattern::create_rgba(this->red, this->green, this->blue, this->alpha);
    return Fill::create( pattern );
  }

  RGBA::operator Stroke::pointer() const
  {
    Cairo::RefPtr<Cairo::Pattern> pattern = Cairo::SolidPattern::create_rgba(this->red, this->green, this->blue, this->alpha);
    return Stroke::create( pattern );
  }

  RGBA::operator Paint::pointer() const
  {
    Cairo::RefPtr<Cairo::Pattern> pattern = Cairo::SolidPattern::create_rgba(this->red, this->green, this->blue, this->alpha);
    return Color::create( pattern );
  }
  
  void RGBA::initialize_regular_expressions()
  {
    int result;
    const char* expression[] = {
      "#([[:xdigit:]][[:xdigit:]])([[:xdigit:]][[:xdigit:]])([[:xdigit:]][[:xdigit:]])",
      "#([[:xdigit:]])([[:xdigit:]])([[:xdigit:]])",
      "rgb[[:blank:]]*[(][[:blank:]]*([[:digit:]]{1,3})[[:blank:]]*,[[:blank:]]*([[:digit:]]{1,3})[[:blank:]]*,[[:blank:]]*([[:digit:]]{1,3})[[:blank:]]*[)]",
      "rgb[[:blank:]]*[(][[:blank:]]*([[:digit:]]{1,3})[[:blank:]]*%[[:blank:]]*,[[:blank:]]*([[:digit:]]{1,3})[[:blank:]]*%[[:blank:]]*,[[:blank:]]*([[:digit:]]{1,3})[[:blank:]]*%[[:blank:]]*[)]"
    };

    for ( int i=0; i < 4; i++ )
    {
      result = regcomp( regular_expression+i, expression[i], REG_EXTENDED|REG_ICASE );
      if ( result != 0 )
        throw;
    }
    
    regex_initialized = true;
  }

}

