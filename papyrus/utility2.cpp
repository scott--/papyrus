/***************************************************************************
 *   Copyright (C) 2007 by Rick L. Vinyard, Jr.                            *
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
#include "utility2.h"

namespace Papyrus {

  Cairo::RefPtr<Cairo::ImageSurface> imagesurface( Drawable::pointer drawable, int width, int height, bool fit )
  {
    Cairo::RefPtr<Cairo::ImageSurface> imagesurface = Cairo::ImageSurface::create ( Cairo::FORMAT_ARGB32, width, height );

    Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create ( imagesurface );

    Viewbox::pointer original_viewbox, render_viewbox;

    if ( fit )
    {
      original_viewbox = drawable->viewbox();
      render_viewbox = Viewbox::create( 0.0, 0.0, width, height, Viewbox::ALIGN_XMID_YMID, Viewbox::MEET );
      drawable->set_viewbox( render_viewbox );
    }
    
    drawable->render ( context );

    if ( fit ) drawable->set_viewbox( original_viewbox );

    return imagesurface;
  }

}

