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
#ifndef PAPYRUSSELECTOR_H
#define PAPYRUSSELECTOR_H

#include <papyrus/drawablecontroller.h>
#include <papyrus/group.h>

namespace Papyrus
{

  /**
   * The selector controller captures events and builds a selection.
   *
   * DrawableContainerInterface is an ancestor of Selector. Therefore an owning
   * Papyrus::Group object may be set as well as a drawing Papyrus::Group object.
   *
   * The containers of these groups are @b not synchronized to the selection.
   * However as items are selected and deselected they are respectively added to
   * and removed from each group.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   *
   * @todo This probably needs to be a vector rather than a set
   * 
   */
  class Selector : public DrawableController
  {
    protected:
      
      Selector( const Glib::ustring& id,
                DrawableSet::pointer drawables,
                Group::pointer select_from_group = Group::pointer(),
                SelectionMode mode = SELECT_PRESS,
                int selection_depth = 1 );

    public:

      typedef PapyrusPointer<Selector> pointer;

      static pointer create( Group::pointer select_from_group = Group::pointer(),
                             SelectionMode mode = SELECT_PRESS,
                             int selection_depth = 1 );

      static pointer create( const Glib::ustring& id,
                             DrawableSet::pointer selected,
                             Group::pointer select_from_group = Group::pointer(),
                             SelectionMode mode = SELECT_PRESS,
                             int selection_depth = 1 );

      static pointer create( const Glib::ustring& id,
                             Group::pointer select_from_group = Group::pointer(),
                             SelectionMode mode = SELECT_PRESS,
                             int selection_depth = 1 );

      static pointer create( DrawableSet::pointer selected,
                             Group::pointer select_from_group,
                             SelectionMode mode = SELECT_PRESS,
                             int selection_depth = 1 );

      virtual ~Selector();

      Group::pointer select_from_group();

      void set_select_from_group( Group::pointer select_from_group );

      void set_select_mode( unsigned mode );

      void enable_select_mode( unsigned mode );

      void disable_select_mode( unsigned mode );

      unsigned select_mode();

      int selection_depth();

      void set_selection_depth( int selection_depth );

      const Drawables& selection();

    protected:
      unsigned m_select_mode;
      int m_selection_depth;
      Group::pointer m_select_from_group;
      bool m_add_drawable_only;
      Drawable::pointer m_picked;
      double m_last_position[ 2 ];

      virtual bool on_button_press( const Event::ButtonPress& event );
      virtual bool on_button_release( const Event::ButtonRelease& event );
      virtual bool on_motion( const Event::Motion& event );

  };

}

#endif
