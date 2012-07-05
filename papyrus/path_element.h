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
#ifndef PAPYRUSPATH_ELEMENTS_H
#define PAPYRUSPATH_ELEMENTS_H

#include <papyrus/enums.h>
#include <papyrus/renderable.h>

namespace Papyrus
{
  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class PathElement : public Renderable
  {
    protected:
      PathElement ( const Glib::ustring& id, PathElementType type, double x, double y, double x1, double y1, double x2, double y2 );

    public:
      PAPYRUS_RENDERABLE(PathElement);

      static pointer create ( PathElementType type, double x=0.0, double y=0.0, double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0 );

      static pointer create ( const Glib::ustring& id, PathElementType type, double x=0.0, double y=0.0, double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0 );

      ~PathElement();

      PathElementType type();

      void set_type ( PathElementType type );

      double x();

      double y();

      void set_x ( double x );

      void set_y ( double y );

      void set_xy ( double x, double y );

      double x1();

      double y1();

      void set_x1 ( double x1 );

      void set_y1 ( double y1 );

      void set_x1y1 ( double x1, double y1 );

      double x2();

      double y2();

      void set_x2 ( double x2 );

      void set_y2 ( double y2 );

      void set_x2y2 ( double x2, double y2 );

      void set_xyx1y1x2y2 ( double x, double y, double x1, double y1, double x2, double y2 );

      virtual void render ( Context& cairo ) const;

      virtual void render ( Context& cairo, pointer previous ) const;

      virtual Glib::ustring svg(unsigned depth=0);

    protected:
      PathElementType m_type;
      weak_pointer m_self;
      double m_x, m_y;
      mutable double m_x1, m_y1, m_x2, m_y2;
//       pointer m_previous;
  };

}

#endif
