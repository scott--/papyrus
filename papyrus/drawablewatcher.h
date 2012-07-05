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
#ifndef PAPYRUSDRAWABLEWATCHER_H
#define PAPYRUSDRAWABLEWATCHER_H

#include <set>
#include <papyrus/drawable.h>
#include <papyrus/drawableset.h>

namespace Papyrus
{

  /**
   * DrawableWatcher is similar to DrawableMultiContainer except that it does
   * not own the drawables it is watching.
   * 
   * DrawableWatcher, unlike DrawableMultiContainer, uses weak smart pointers
   * and thus does not take ownership of the items it is watching. Therefore,
   * unless the item is owned by a group or some container other than the
   * DrawableWatcher the drawable will be destroyed.
   *
   * DrawableWatcher observes the destroyed signal of the drawables it is
   * watching and removes them immediately upon destruction.
   *
   * Since the container stores weak pointers, as a side note on
   * weak vs. strong smart pointers; you can create a strong (owner)
   * pointer from a weak (non-owning) pointer through the lock() method.
   * 
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class DrawableWatcher
  {
    public:

      typedef PapyrusPointer<DrawableWatcher> pointer;

      typedef std::set<Drawable::weak_pointer, wp_lt_compare> Watched;

      DrawableWatcher ( );

      virtual ~DrawableWatcher();

      /**
       * Watches a particular drawable for changes
       */
      virtual bool watch ( Drawable::pointer item );

      /**
       * Stops watching a particular drawable for changes
       */
      virtual bool remove_watch ( Drawable::pointer item );

      /**
       * Stops watching all drawables previously watched
       */
      virtual void remove_all_watches();

      /** Returns the set of drawables being watched */
      const Watched& watched() const;

      /** True if the specified drawable is being watched */
      bool is_watched ( Drawable::pointer item );

      /**
       * Links this watcher to the drawable set causing the watcher to watch/remove watches
       * as items are added to / removed from the set.
       */
      virtual void link( DrawableSet::pointer s );

      /** Unlinks the watcher and the DrawableSet */
      virtual void unlink( DrawableSet::pointer s );
      
      /** Signal emitted when a drawable is watched */
      sigc::signal<void, Drawable::pointer>& signal_watch_added();

      /** Signal emitted when a drawable is no longer watched */
      sigc::signal<void, Drawable::pointer>& signal_watch_removed();

      /** Signal emitted when a watched drawable emits the changed signal */
      sigc::signal<void, Drawable::pointer>& signal_watched_changed();

    protected:

      /** The set of drawables being watched */
      Watched m_watched;

      /** Map from a drawable to a signal connection */
      typedef std::map<Drawable::weak_pointer, sigc::connection, wp_lt_compare> Connections;
      Connections m_watched_changed_connections;
      Connections m_watched_destroyed_connections;

      std::map< DrawableSet::pointer, sigc::connection > m_linked_added_conn_map;
      std::map< DrawableSet::pointer, sigc::connection > m_linked_removed_conn_map;
      
      sigc::signal<void, Drawable::pointer> m_signal_watch_added;
      sigc::signal<void, Drawable::pointer> m_signal_watch_removed;
      sigc::signal<void, Drawable::pointer> m_signal_watched_changed;

      /**
       * Virtual method called when a watched child is changed.
       *
       * When a watch is added, the watched item's changed signal is actually connected to the
       * private proxy method, which in turn calls the virtual method. This allows children
       * to implement their own behavior by reimplementing this method without worrying about
       * modifying the add() or remove() methods.
       */
      virtual void on_watched_changed ( Drawable::pointer watched );

    private:

      /**
       * When a child is watched, this is the method connected to the child's changed signal
       * which in turn calls on_watched_changed().
       */
      void on_watched_changed_proxy( Drawable::weak_pointer watched );

      /**
       * This method is connected to a child's destroyed signal causing automatic
       * removal of the child.
       */
      void on_watched_destroyed( Drawable::weak_pointer watched );

      void on_linked_set_drawable_added( Drawable::pointer added );

      void on_linked_set_drawable_removed( Drawable::pointer removed );
      
  };

}

#endif
