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
#include "drawablesinglecontainer.h"

namespace Papyrus
{

  DrawableSingleContainer::DrawableSingleContainer()
  {
  }

  DrawableSingleContainer::~DrawableSingleContainer() { }

  Drawable::pointer DrawableSingleContainer::child()
  {
    return m_child;
  }

  void DrawableSingleContainer::add ( Drawable::pointer new_child )
  {
    if ( m_child )
    {
      m_signal_removed.emit ( m_child );
      m_child_changed_conn.disconnect();
    }

    m_child = new_child;

    if ( m_child )
    {
      m_child_changed_conn = m_child->signal_changed().connect ( sigc::bind( sigc::mem_fun ( *this, &DrawableSingleContainer::on_child_changed_proxy ), new_child ) );
      m_signal_added.emit ( m_child );
    }
  }

  void DrawableSingleContainer::clear()
  {
    if ( m_child )
    {
      m_signal_removed.emit ( m_child );
      m_child_changed_conn.disconnect();
      m_signal_cleared.emit();
    }
  }

  bool DrawableSingleContainer::has ( Drawable::pointer drawable ) const
  {
    return m_child == drawable;
  }

  size_t DrawableSingleContainer::size() const
  {
    if ( m_child ) return 1;
    else return 0;
  }

  bool DrawableSingleContainer::empty() const
  {
    return ( not m_child );
  }

  sigc::signal<void, Drawable::pointer> DrawableSingleContainer::signal_added()
  {
    return m_signal_added;
  }

  sigc::signal<void, Drawable::pointer> DrawableSingleContainer::signal_removed()
  {
    return m_signal_removed;
  }

  sigc::signal<void> DrawableSingleContainer::signal_cleared()
  {
    return m_signal_cleared;
  }

  void DrawableSingleContainer::on_child_changed(Drawable::pointer changed)
  {
  }

  void DrawableSingleContainer::on_child_changed_proxy(Drawable::weak_pointer weak_changed)
  {
    Drawable::pointer changed = weak_changed.lock();
    this->on_child_changed(changed);
  }

}

