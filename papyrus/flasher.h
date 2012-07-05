/***************************************************************************
 *   Copyright (C) 2004,2010 by Rick L. Vinyard, Jr.                       *
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
#ifndef PAPYRUSFLASHER_H
#define PAPYRUSFLASHER_H

#include <set>

#include <papyrus/animator.h>

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
    @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
  */
  class Flasher : public Animator
  {
    protected:
      Flasher ( const Glib::ustring& id,
                unsigned int interval_ms );

    public:
      /** Class level typedef to container for items to transform */
      typedef std::set<Drawable::pointer> Drawables;

      /** Class level smart pointer typedef */
      typedef PapyrusPointer<Flasher> pointer;

      static pointer create ( const Glib::ustring& id=Glib::ustring(),
                              unsigned int interval_ms=1000 );

      static pointer create ( unsigned int interval_ms );
      
      virtual ~Flasher();

      void add ( Drawable::pointer d );

      void remove ( Drawable::pointer d );

      const Drawables& drawables();

    protected:
      Drawables m_drawables;

      bool m_last_state;

      virtual int animate ( int n=1 );

  };

}

#endif
