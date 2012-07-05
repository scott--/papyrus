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
#ifndef PAPYRUSIMAGE_H
#define PAPYRUSIMAGE_H

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
   * The Image class is used to represent an image to be drawn into
   * the canvas.  It can be scaled and transformed just like any other
   * drawable.
   *
   * TODO add x & y parameter support
   * 
   * @author Rick L Vinyard Jr
   */
  class Image : public Drawable
  {
    protected:

      Image();

      Image ( const Glib::ustring& id, const Glib::ustring& filename );

      Image ( const Glib::ustring& id, unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba=false );

      Image ( const Glib::ustring& id, Cairo::Format format, int width, int height );

      /**
       * Constructor which sets the image to a cairo surface.
       *
       * @param img
       *     The Cairo image surface to be drawn into the canvas.
       */
      Image ( const Glib::ustring& id, Cairo::RefPtr<Cairo::ImageSurface> img );

    public:
      PAPYRUS_DRAWABLE(Image);

      static pointer create( );

      static pointer create ( const Glib::ustring& filename );

      static pointer create ( unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba=false );

      static pointer create ( Cairo::Format format, int width, int height );

      /**
       * The create class method is used to create a new instance from
       * a Cairo image surface.
       *
       * @param img
       *     The cairo image surface containing the image.
       * @returns
       *     smart pointer to the new instance
       */
      static pointer create ( Cairo::RefPtr<Cairo::ImageSurface> img );

      static pointer create ( const Glib::ustring& id, const Glib::ustring& filename );

      static pointer create ( const Glib::ustring& id, unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba=false );

      static pointer create ( const Glib::ustring& id, Cairo::Format format, int width, int height );

      static pointer create ( const Glib::ustring& id, Cairo::RefPtr<Cairo::ImageSurface> img );

      /** Destructor */
      virtual ~Image();

      Glib::ustring filename() const;

      void set_image ( const Glib::ustring& filename );

      void set_image ( unsigned char* data, Cairo::Format format, int width, int height, int stride, bool convert_rgba=false );

      void set_image ( Cairo::Format format, int width, int height );

      virtual bool inside ( double x, double y );

      /**
       * The set_image method is used to replace the image with the
       * image in a cairo image surface.
       *
       * @param img
       *     The cairo image surface containing the image.
       */
      void set_image ( Cairo::RefPtr<Cairo::ImageSurface> img );

      virtual void draw ( Context& cairo ) const;

      double width();

      double height();

      void width_height ( double& width, double& height );

    protected:
      Glib::ustring m_filename;
      double m_width, m_height;
      Cairo::RefPtr<Cairo::ImageSurface> m_image;

      void on_image_changed();

      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;
      
  };

}

#endif
