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
#ifndef PAPYRUSDRAWABLESINGLECONTAINER_H
#define PAPYRUSDRAWABLESINGLECONTAINER_H

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
   * This is an interface for an object that contains a single drawable.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class DrawableSingleContainer
  {
    public:

      DrawableSingleContainer();

      virtual ~DrawableSingleContainer();

      virtual Drawable::pointer child();

      virtual void add( Drawable::pointer new_child = Drawable::pointer() );
      
      virtual void clear();

      virtual bool has ( Drawable::pointer drawable ) const;

      virtual size_t size() const;

      virtual bool empty() const;

      sigc::signal<void, Drawable::pointer> signal_added();

      sigc::signal<void, Drawable::pointer> signal_removed();

      sigc::signal<void> signal_cleared();

    protected:
      Drawable::pointer m_child;

      sigc::signal<void, Drawable::pointer> m_signal_added;

      sigc::signal<void, Drawable::pointer> m_signal_removed;

      sigc::signal<void> m_signal_cleared;

      sigc::connection m_child_changed_conn;

      virtual void on_child_changed(Drawable::pointer);

    private:

      void on_child_changed_proxy(Drawable::weak_pointer);

  };

}

#endif
