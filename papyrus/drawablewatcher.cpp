/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
#include "drawablewatcher.h"

namespace Papyrus
{

  DrawableWatcher::DrawableWatcher ( )
  {
  }

  DrawableWatcher::~DrawableWatcher()
  {
  }

  bool DrawableWatcher::watch ( Drawable::pointer item )
  {
    // We must have a valid pointer
    if ( ! item ) return false;

    // if we're already watching, we're done
    if ( m_watched.find(item) != m_watched.end() ) return true;

    // Connect to the changed signal
    m_watched_changed_connections[ item ] =
        item->signal_changed().connect ( sigc::bind ( sigc::mem_fun ( *this, &DrawableWatcher::on_watched_changed_proxy ), item ) );

    // Connect to the destroyed signal
    m_watched_destroyed_connections[ item ] =
        item->signal_changed().connect ( sigc::bind ( sigc::mem_fun ( *this, &DrawableWatcher::on_watched_destroyed ), item ) );

    // Add this object to the list of watched items
    m_watched.insert( item );

    // Notify anyone connected to the watch_added signal
    m_signal_watch_added.emit ( item );

    return true;
  }

  bool DrawableWatcher::remove_watch ( Drawable::pointer item )
  {
    Watched::iterator witer;
    Connections::iterator citer;

    // We must have a valid pointer
    if ( not item ) return false;

    // Are we watching this item?
    witer = m_watched.find(item);

    // If we're not watching the item we can't remove it
    if ( witer == m_watched.end() ) return false;

    // But, if we are watching it, let's remove it from the set
    m_watched.erase(witer);

    // Let's find out if we have a changed signal connection
    citer = m_watched_changed_connections.find ( item );
    if ( citer != m_watched_changed_connections.end() )
    {
      // if we do, let's disconnect and remove the connection
      citer->second.disconnect();
      m_watched_changed_connections.erase( citer );
    }

    // Let's find out if we have a destroyed signal connection
    citer = m_watched_destroyed_connections.find ( item );
    if ( citer != m_watched_destroyed_connections.end() )
    {
      // if we do, let's disconnect and remove the connection
      citer->second.disconnect();
      m_watched_destroyed_connections.erase( citer );
    }

    // Time to let everyone know it's removed
    m_signal_watch_removed.emit( item );

    return true;
  }

  void DrawableWatcher::remove_all_watches()
  {
    Watched::iterator witer;

    m_watched_changed_connections.clear();

    m_watched_destroyed_connections.clear();

    for ( witer = m_watched.begin(); witer != m_watched.end(); witer++ )
      m_signal_watch_removed.emit( witer->lock() );

    m_watched.clear();
  }
  
  const DrawableWatcher::Watched& DrawableWatcher::watched() const
  {
    return m_watched;
  }

  bool DrawableWatcher::is_watched ( Drawable::pointer item )
  {
    return ( m_watched.find(item) != m_watched.end() );
  }

  void DrawableWatcher::link(DrawableSet::pointer s)
  {
    std::map<DrawableSet::pointer,sigc::connection>::iterator conn_iter;

    // We need a valid pointer
    if ( not s ) return;

    // Check to see if we're already linked
    conn_iter = m_linked_added_conn_map.find( s );
    if ( conn_iter != m_linked_added_conn_map.end() ) return;

    m_linked_added_conn_map[s] = s->signal_drawable_added().connect( sigc::mem_fun( *this, &DrawableWatcher::on_linked_set_drawable_added ));
    m_linked_removed_conn_map[s] = s->signal_drawable_removed().connect( sigc::mem_fun( *this, &DrawableWatcher::on_linked_set_drawable_removed ));

    DrawableSet::const_iterator i;
    for ( i = s->begin(); i != s->end(); i++ ) this->watch( *i );
  }

  void DrawableWatcher::unlink(DrawableSet::pointer s)
  {
    std::map<DrawableSet::pointer,sigc::connection>::iterator i;

    i = m_linked_added_conn_map.find( s );
    if ( i != m_linked_added_conn_map.end() )
    {
      i->second.disconnect();
      m_linked_added_conn_map.erase(i);
    }
  
    i = m_linked_removed_conn_map.find( s );
    if ( i != m_linked_removed_conn_map.end() )
    {
      i->second.disconnect();
      m_linked_removed_conn_map.erase(i);
    }
  }

  sigc::signal<void, Drawable::pointer>& DrawableWatcher::signal_watch_added()
  {
    return m_signal_watch_added;
  }

  sigc::signal<void, Drawable::pointer>& DrawableWatcher::signal_watch_removed()
  {
    return m_signal_watch_removed;
  }

  sigc::signal< void, Drawable::pointer > & DrawableWatcher::signal_watched_changed()
  {
    return m_signal_watched_changed;
  }

  void DrawableWatcher::on_watched_changed ( Drawable::pointer watched )
  {
  }

  void DrawableWatcher::on_watched_changed_proxy(Drawable::weak_pointer watched)
  {
    this->on_watched_changed( watched.lock() );
    m_signal_watched_changed.emit( watched.lock() );
  }

  void DrawableWatcher::on_watched_destroyed(Drawable::weak_pointer watched)
  {
    this->remove_watch( watched.lock() );
  }

  void DrawableWatcher::on_linked_set_drawable_added(Drawable::pointer added)
  {
    this->watch( added );
  }

  void DrawableWatcher::on_linked_set_drawable_removed(Drawable::pointer removed)
  {
    this->remove_watch( removed );
  }

}

