/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   Copyright (C) 2007 Peter Miller                                       *
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
#include "image.h"

#include <byteswap.h>

#include <endian.h>

namespace Papyrus
{

  Image::Image() :
      Drawable(Glib::ustring()),
      m_width ( 0.0 ),
      m_height ( 0.0 ) {}

  Image::Image ( const Glib::ustring& id, const Glib::ustring& filename )  :
      Drawable ( id ),
      m_width ( 0.0 ),
      m_height ( 0.0 )
  {
    this->set_image ( filename );
  }

  Image::Image ( const Glib::ustring& id, unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba ) :
      Drawable ( id )
  {
    this->set_image ( data, format, width, height, stride, convert_rgba );
  }

  Image::Image ( const Glib::ustring& id, Cairo::Format format, int width, int height ) :
      Drawable ( id )
  {
    this->set_image ( format, width, height );
  }

  Image::Image ( const Glib::ustring& id, Cairo::RefPtr<Cairo::ImageSurface> img ) :
      Drawable ( id )
  {
    this->set_image ( img );
  }

  Image::pointer Image::create( )
  {
    PAPYRUS_CREATE ( Image( ) );
  }

  Image::pointer Image::create ( const Glib::ustring& filename )
  {
    PAPYRUS_CREATE ( Image ( Glib::ustring(), filename ) );
  }

  Image::pointer Image::create ( unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba )
  {
    PAPYRUS_CREATE ( Image ( Glib::ustring(), data, format, width, height, stride, convert_rgba ) );
  }

  Image::pointer Image::create ( Cairo::Format format, int width, int height )
  {
    PAPYRUS_CREATE ( Image ( Glib::ustring(), format, width, height ) );
  }

  Image::pointer Image::create ( Cairo::RefPtr<Cairo::ImageSurface> img )
  {
    PAPYRUS_CREATE ( Image ( Glib::ustring(), img ) );
  }

  Image::pointer Image::create ( const Glib::ustring& id, const Glib::ustring& filename )
  {
    PAPYRUS_CREATE ( Image ( id, filename ) );
  }

  Image::pointer Image::create ( const Glib::ustring& id, unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba )
  {
    PAPYRUS_CREATE ( Image ( id, data, format, width, height, stride, convert_rgba ) );
  }

  Image::pointer Image::create ( const Glib::ustring& id, Cairo::Format format, int width, int height )
  {
    PAPYRUS_CREATE ( Image ( id, format, width, height ) );
  }

  Image::pointer Image::create ( const Glib::ustring& id, Cairo::RefPtr<Cairo::ImageSurface> img )
  {
    PAPYRUS_CREATE ( Image ( id, img ) );
  }

  Image::~Image() {}

  bool Image::inside(double x, double y)
  {
    return this->extents().is_inside(x, y);
  }

  void Image::draw ( Context& cairo ) const
  {
    if ( m_image )
    {
      cairo->set_source ( m_image, 0, 0 );
      cairo.paint();
    }
  }

  Glib::ustring Image::filename( ) const
  {
    return m_filename;
  }

  void Image::set_image ( const Glib::ustring & filename )
  {
    m_filename = filename;
    m_image.clear();
    if ( m_filename.size() > 0 )
      m_image = Cairo::ImageSurface::create_from_png ( m_filename );
    this->on_image_changed();
  }

  void Image::set_image ( unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba )
  {
    uint32_t* data32;
    uint32_t alpha;
    m_filename.clear();
    m_image.clear();

    if ( convert_rgba )
    {
      data32 = ( uint32_t* ) ( data );
      for ( int i = 0; i < width*height; i++ )
      {
#ifdef __LITTLE_ENDIAN
        data32[i] = bswap_32 ( data32[i] );
#endif
        alpha = data32[i] << 24;
        data32[i] >>= 8;
        data32[i] |= alpha;
      }
    }

    m_image = Cairo::ImageSurface::create ( data, format, width, height, stride );
    this->on_image_changed();
  }

  void Image::set_image ( Cairo::Format format, int width, int height )
  {
    m_filename.clear();
    m_image.clear();
    m_image = Cairo::ImageSurface::create ( format, width, height );
    this->on_image_changed();
  }

  void Image::set_image ( Cairo::RefPtr<Cairo::ImageSurface> img )
  {
    m_filename.clear();
    m_image = img;
    this->on_image_changed();
  }

  double Image::width()
  {
    return m_width;
  }

  double Image::height()
  {
    return m_height;
  }

  void Image::width_height ( double& width, double& height )
  {
    width = m_width;
    height = m_height;
  }

  void Image::on_image_changed()
  {
    this->freeze();
    
    this->invalidate_extents();

    if ( ! m_image )
    {
      m_width = 0.0;
      m_height = 0.0;
      this->set_centroid( 0.0, 0.0 );
    }
    else
    {
      m_width = m_image->get_width( );
      m_height = m_image->get_height( );
      this->set_centroid( m_width / 2.0, m_height / 2.0 );
    }

    this->thaw(true /*force redraw on thaw */);
  }

  Region Image::calculate_extents(const Matrix& m, ExtentsPerformance ep) const
  {
    Region e(0.0, 0.0, m_width, m_height);
    e.transform(m);
    return e;
  }
  
}


