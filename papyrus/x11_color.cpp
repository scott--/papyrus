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
#include "x11_color.h"

#include <papyrus/rgba.h>

namespace Papyrus
{

  void x11_colors_1( X11Colors& colors );
  void x11_colors_2( X11Colors& colors );
  void x11_colors_3( X11Colors& colors );
  void x11_colors_4( X11Colors& colors );

  X11Colors x11_colors( )
  {
    X11Colors colors;

    x11_colors_1( colors );
    x11_colors_2( colors );
    x11_colors_3( colors );
    x11_colors_4( colors );

    return colors;
  }

  RGBA x11_color( const Glib::ustring& name ) {
    static X11Colors colors = x11_colors();
    X11Colors::iterator i;

    if ( name == "none" ) return RGBA(0.0, 0.0, 0.0, 0.0);
    
    i = colors.find(name);
    if ( i != colors.end() )
      return i->second;
    else
      return RGBA();
  }

}
