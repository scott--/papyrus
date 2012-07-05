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
#ifndef PAPYRUSDRAWABLECONTAINER_H
#define PAPYRUSDRAWABLECONTAINER_H

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
   * Provides a common base for all containers of drawables
   *
   * For now the only child of this class is DrawableSet. If that doesn't
   * change the signals will probably be moved into DrawableSet and this
   * class will go away.
   * 
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class DrawableContainer
  {
    public:
      DrawableContainer() { }

      virtual ~DrawableContainer() { }

      /** Use the same syntax as groups */
      virtual void add ( Drawable::pointer drawable ) = 0;

      virtual void remove ( Drawable::pointer drawable ) = 0;

      virtual void clear() = 0;

      virtual bool has ( Drawable::pointer drawable ) const = 0;

      virtual size_t size() const = 0;

      virtual bool empty() const = 0;

      sigc::signal<void, Drawable::pointer> signal_drawable_added() { return m_signal_drawable_added; }

      sigc::signal<void, Drawable::pointer> signal_drawable_removed() { return m_signal_drawable_removed; }

      sigc::signal<void> signal_cleared() { return m_signal_cleared; }

    protected:
      sigc::signal<void, Drawable::pointer> m_signal_drawable_added;

      sigc::signal<void, Drawable::pointer> m_signal_drawable_removed;

      sigc::signal<void> m_signal_cleared;

  };

}

#endif
