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
#ifndef PAPYRUSQUADRILLE_H
#define PAPYRUSQUADRILLE_H

#include <papyrus-extras/tiling.h>

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Quadrille : public Tiling
  {
    protected:

      Quadrille ( const Glib::ustring& id, unsigned rows, unsigned columns, double side_length );

    public:
      PAPYRUS_DRAWABLE(Quadrille);

      static pointer create ( unsigned rows=0, unsigned columns=0, double side_length=1.0 );

      static pointer create ( const Glib::ustring& id, unsigned rows, unsigned columns, double side_length );

      virtual ~Quadrille();

      virtual void draw ( Context& cairo ) const;
      
    protected:
      
      virtual void update_centroid_x();
      
      virtual void update_centroid_y();
      
      virtual void update_centroid();


  };

}

#endif
