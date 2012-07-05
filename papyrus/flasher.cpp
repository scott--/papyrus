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
#include "flasher.h"

namespace Papyrus
{

  Flasher::Flasher ( const Glib::ustring&  id, unsigned int interval_ms ):
      Animator(id),
      m_last_state(false)
  {
    this->set_interval(interval_ms);
  }

  Flasher::pointer Flasher::create ( const Glib::ustring& id,
                                     unsigned int interval_ms )
  {
    return pointer ( new Flasher ( id, interval_ms ) );
  }

  Flasher::pointer Flasher::create (unsigned int interval_ms)
  {
    return pointer ( new Flasher ( Glib::ustring(), interval_ms ) );
  }

  Flasher::~Flasher()
  {}

  int Flasher::animate ( int n )
  {
    Drawables::iterator i;

    /*
       If n % 2 == 0 then we have no work to do since
       that would result in a sequence of operations that
       would return us to our original state
    */
    if ( n % 2 == 0 || m_drawables.size() == 0 )
      return 1;

    /* If we got here we need to change the state */
    for ( i = m_drawables.begin(); i != m_drawables.end(); i++ )
    {
      if (m_last_state)
        (*i)->show();
      else
        (*i)->hide();
    }

    m_last_state = !m_last_state;

    return n;
  }

  void Flasher::add ( Drawable::pointer d )
  {
    m_drawables.insert ( d );
  }

  void Flasher::remove ( Drawable::pointer d )
  {
    m_drawables.erase ( d );
  }

  const Flasher::Drawables& Flasher::drawables()
  {
    return m_drawables;
  }

}
