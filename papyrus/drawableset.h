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
#ifndef PAPYRUSDRAWABLESET_H
#define PAPYRUSDRAWABLESET_H

#include <set>
#include <papyrus/drawablecontainer.h>

namespace Papyrus
{

  /**
   * Provides an implementation of a set that stores drawables and emits
   * signals when drawables are added, removed, changed, et. al.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class DrawableSet: public DrawableContainer
  {
    public:
      typedef PapyrusPointer<DrawableSet> pointer;
      
      typedef std::set<Drawable::pointer> Drawables;

      typedef Drawables::iterator iterator;
      typedef Drawables::reverse_iterator reverse_iterator;
      typedef Drawables::const_iterator const_iterator;
      typedef Drawables::const_reverse_iterator const_reverse_iterator;

      DrawableSet(pointer to_copy=pointer());

      virtual ~DrawableSet();

      const Drawables& drawables();

      virtual void set_drawables( pointer drawables );

      virtual void set_drawables( const DrawableSet& drawables );
      
      virtual void add( Drawable::pointer drawable );

      virtual void remove ( Drawable::pointer drawable );

      virtual void clear();

      virtual bool has ( Drawable::pointer drawable ) const;

      virtual size_t size() const;

      virtual iterator begin();

      virtual const_iterator begin() const;

      virtual iterator end();

      virtual const_iterator end() const;

      virtual reverse_iterator rbegin();

      virtual const_reverse_iterator rbegin() const;

      virtual reverse_iterator rend();

      virtual const_reverse_iterator rend() const;

      virtual bool empty() const;

      Region extents();

      /**
       * Links this set to the parameter set causing this set to add/remove
       * items as the other set adds/removes items.
       *
       * This is not a bi-directional link. The other set will not be modified
       * if items are added to this set.
       */
      virtual void link( DrawableSet::pointer s );

      /** Unlinks the other set from this set */
      virtual void unlink( DrawableSet::pointer s );
      
    protected:
      Drawables m_drawables;
      
      std::map< DrawableSet::pointer, sigc::connection > m_linked_added_conn_map;
      std::map< DrawableSet::pointer, sigc::connection > m_linked_removed_conn_map;

      void on_linked_set_drawable_added( Drawable::pointer added );

      void on_linked_set_drawable_removed( Drawable::pointer removed );
      
  };

}

#endif
