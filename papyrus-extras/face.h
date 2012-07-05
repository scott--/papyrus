/***************************************************************************
 *   Copyright (C) 2004,2009 by Rick L. Vinyard, Jr.                       *
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
#ifndef PAPYRUSFACE_H
#define PAPYRUSFACE_H

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
   * Why is there a Face primitive in this library? For testing of course; like the
   * teapot in OpenGL.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Face : public Drawable
  {
    public:
      typedef enum TYPE {
          SMILEY,
    } TYPE;

    protected:

      Face ( const Glib::ustring& id, double size=20.0, TYPE type = SMILEY );

    public:
      PAPYRUS_DRAWABLE(Face);

      static pointer create ( double size=20.0, TYPE type = SMILEY );

      static pointer create ( const Glib::ustring& id, double size=20.0, TYPE type = SMILEY );

      virtual ~Face();

      virtual void draw ( Context& cairo ) const;

      TYPE type();
      void set_type ( TYPE type );

      double size();
      void set_size ( double size );

      void set_size_type ( double size, TYPE type );

    protected:
      TYPE m_type;
      double m_size;

  };

}

#endif
