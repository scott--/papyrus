/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
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
#include "utility.h"

#include <cstring>
#include <cstdlib>

namespace Papyrus
{
  namespace Gtk
  {

    void deallocate_pixbuf_memory ( const guint8* data )
    {
      free ( const_cast<guint8*> ( data ) );
    }

    Glib::RefPtr<Gdk::Pixbuf> create_pixbuf ( Papyrus::Renderable::pointer renderable, int width, int height )
    {
      unsigned char* data = ( unsigned char* ) calloc ( width*height, 4 );

      Cairo::RefPtr<Cairo::ImageSurface> imagesurface = Cairo::ImageSurface::create ( data, Cairo::FORMAT_ARGB32, width, height, width*4 );

      Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create ( imagesurface );
      renderable->render ( context );

      unsigned char temp;
      for ( int i = 0; i < width*height*4; i += 4 )
      {
        temp = data[i];
        data[i] = data[i+2];
        data[i+2] = temp;
      }

      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data ( data, Gdk::COLORSPACE_RGB, true, 8, width, height, width*4, sigc::ptr_fun ( deallocate_pixbuf_memory ) );

      return pixbuf;
    }

    Glib::RefPtr<Gdk::Pixbuf> cairo_image_to_pixbuf( const Cairo::RefPtr<Cairo::ImageSurface> imgsurf )
    {
      if ( not imgsurf or imgsurf->get_format() != Cairo::FORMAT_ARGB32 ) return Glib::RefPtr<Gdk::Pixbuf>();

      int height = imgsurf->get_height();
      int width = imgsurf->get_width();

      unsigned char* data = (unsigned char*) calloc( width*height, 4 );

      const unsigned char* imgdata = imgsurf->get_data();

      memcpy( data, imgdata, width*height*4 );
      
      unsigned char temp;
      for ( int i = 0; i < width*height*4; i += 4 )
      {
        temp = data[i];
        data[i] = data[i+2];
        data[i+2] = temp;
      }

      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data ( data, Gdk::COLORSPACE_RGB, true, 8, width, height, width*4, sigc::ptr_fun ( deallocate_pixbuf_memory ) );

      return pixbuf;
    }



  }

}
