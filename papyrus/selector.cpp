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
#include "selector.h"

#include <algorithm>

namespace Papyrus
{

  Selector::Selector ( const Glib::ustring& id,
                       DrawableSet::pointer selected,
                       Group::pointer select_from_group,
                       SelectionMode mode,
                       int selection_depth
                     ) :
      DrawableController( id, DrawableSet::pointer() ),
      m_select_mode ( mode ),
      m_selection_depth ( selection_depth ),
      m_select_from_group ( select_from_group ),
      m_add_drawable_only ( true )
  {
    if ( selected and select_from_group )
    {
      for ( iterator i = selected->begin(); i != selected->end(); i++ )
      {
        if ( select_from_group->has( *i ) ) this->add( *i );
      }
    }
  }

  Selector::pointer Selector::create ( Group::pointer select_from_group, SelectionMode mode, int selection_depth )
  {
    PAPYRUS_CREATE( Selector ( Glib::ustring(), DrawableSet::pointer(), select_from_group, mode, selection_depth ) );
  }

  Selector::pointer Selector::create ( const Glib::ustring& id, DrawableSet::pointer selected, Group::pointer select_from_group, SelectionMode mode, int selection_depth )
  {
    PAPYRUS_CREATE( Selector ( id, selected, select_from_group, mode, selection_depth ) );
  }

  Selector::pointer Selector::create ( const Glib::ustring& id, Group::pointer select_from_group, SelectionMode mode, int selection_depth )
  {
    PAPYRUS_CREATE( Selector ( id, DrawableSet::pointer(), select_from_group, mode, selection_depth ) );
  }

  Selector::pointer Selector::create ( DrawableSet::pointer selected, Group::pointer select_from_group, SelectionMode mode, int selection_depth )
  {
    PAPYRUS_CREATE( Selector ( Glib::ustring(), selected, select_from_group, mode, selection_depth ) );
  }

  Selector::~Selector()
  {}

  Group::pointer Selector::select_from_group()
  {
    return m_select_from_group;
  }

  void Selector::set_select_from_group ( Group::pointer select_from_group )
  {
    this->clear();

    m_select_from_group = select_from_group;
  }

  void Selector::set_select_mode ( unsigned mode )
  {
    m_select_mode = mode;
  }

  void Selector::enable_select_mode ( unsigned mode )
  {
    m_select_mode |= mode;
  }

  void Selector::disable_select_mode ( unsigned mode )
  {
    m_select_mode &= ~mode;
  }

  unsigned Selector::select_mode( )
  {
    return m_select_mode;
  }

  int Selector::selection_depth()
  {
    return m_selection_depth;
  }

  void Selector::set_selection_depth ( int selection_depth )
  {
    m_selection_depth = selection_depth;
  }

  const Selector::Drawables& Selector::selection()
  {
    return m_drawables;
  }

  bool Selector::on_button_press ( const Event::ButtonPress& event )
  {
    std::vector<Drawable::pointer> results;
    std::vector<Drawable::pointer>::iterator i;

    if ( ! m_select_from_group )
      return false;

    if ( m_select_mode & SELECT_PRESS )
    {

      results = m_select_from_group->select ( event.x, event.y, m_selection_depth );

      if ( results.size() > 0 )
      {

        // if the CTRL key is pressed, or the selection size is 0, let's add everything to the selection
        if ( event.state & Event::CONTROL_MASK || this->size() == 0 )
        {
          for ( i = results.begin(); i != results.end(); i++ )
            this->add ( *i );
        }
        else
        {
          // otherwise we have hit a situation where the control key is not pressed and we already
          // have some items selected
          // let's check and see if anything is already in the selection group
          bool existing = false;
          for ( i = results.begin(); i != results.end() && !existing; i++ )
            if ( this->has ( *i ) )
              existing = true;

          // if we have a new selection, let's clear the old selection and start a new one,
          // otherwise we'll leave the current selection alone
          if ( !existing )
          {
            this->clear();
            for ( i = results.begin(); i != results.end(); i++ )
              this->add ( *i );
          }
        }

        m_last_position[ 0 ] = event.x;
        m_last_position[ 1 ] = event.y;

        return true;
      }
      else
      {
        // let's clear it if a blank area was selected and the CTRL key wasn't pressed
        if ( ! ( event.state & Event::CONTROL_MASK ) )
          this->clear();
      }
    }

    return false;
  }

  bool Selector::on_motion ( const Event::Motion& event )
  {
    //       double dx, dy;
    //       dx = event->x;
    //         if (!m_line)
    //             return false;
    //
    //         if (sqrt(pow(m_last_position[0] - event->x, 2) + pow(m_last_position[1] - event->y, 2)) < m_movement_threshhold)
    //             return false;
    //
    //         m_line->add_vertex(event->x, event->y);
    //         m_last_position[0] = event->x;
    //         m_last_position[1] = event->y;

    return false;
  }


  bool Selector::on_button_release ( const Event::ButtonRelease& event )
  {
    //         if (! (m_canvas && m_line) )
    //             return false;
    //
    //         m_canvas->remove
    //         (m_line);
    //         m_signal_complete(m_line);
    //         m_line.reset();

    return false;
  }

}
