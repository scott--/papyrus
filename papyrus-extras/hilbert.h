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
#ifndef PAPYRUSHILBERT_H
#define PAPYRUSHILBERT_H

#include <papyrus/polyline.h>

namespace Papyrus
{

  /**
    @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
  */
  class Hilbert : public Polyline
  {
    protected:

      Hilbert ( const Glib::ustring& id, unsigned level, double size, Fill::pointer fill, Stroke::pointer stroke );

    public:
      PAPYRUS_DRAWABLE(Hilbert);

      static pointer create ( unsigned level=0, double size=0, Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& id, unsigned level=0, double size=0, Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

      virtual ~Hilbert();

      unsigned level();

      void set_level ( unsigned level );

      double size();

      void set_size ( double size );

    protected:
      unsigned m_level;
      double m_size;
      double m_lsize;

      void create_vertices();

      void hilbert_a ( unsigned level );

      void hilbert_b ( unsigned level );

      void hilbert_c ( unsigned level );

      void hilbert_d ( unsigned level );

  };

}

#endif
