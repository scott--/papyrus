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
#include "drawableset.h"

namespace Papyrus
{

  DrawableSet::DrawableSet(pointer to_copy)
  {
    if ( to_copy ) m_drawables = to_copy->m_drawables;
  }

  DrawableSet::~DrawableSet()
  {
    // This makes sure that the removed signal is emitted for each drawable when this container is destroyed
    this->clear();
  }

  void DrawableSet::clear()
  {
    Drawable::pointer p;
    iterator i;

    while ( m_drawables.size() > 0 )
    {
      i = m_drawables.begin();
      p = *i;
      m_drawables.erase(i);
      m_signal_drawable_removed.emit ( p );
    }

    m_signal_cleared.emit();
  }

  const DrawableSet::Drawables& DrawableSet::drawables()
  {
    return m_drawables;
  }

  void DrawableSet::set_drawables(pointer drawables)
  {
    if ( drawables ) this->set_drawables( *drawables );
  }

  void DrawableSet::set_drawables(const DrawableSet & drawables)
  {
    Drawables removed, added;
    iterator i;

    std::set_difference( m_drawables.begin(), m_drawables.end(),
                         drawables.m_drawables.begin(), drawables.m_drawables.end(),
                         std::inserter( removed, removed.begin() )
                       );

    std::set_difference( drawables.m_drawables.begin(), drawables.m_drawables.end(),
                         m_drawables.begin(), m_drawables.end(),
                         std::inserter( added, added.begin() )
                       );

    m_drawables = drawables.m_drawables;

    for ( i = removed.begin(); i != removed.end(); i++ )
      m_signal_drawable_removed.emit( *i );

    for ( i = added.begin(); i != added.end(); i++ )
      m_signal_drawable_added.emit( *i );
  }

  void DrawableSet::add( Drawable::pointer drawable )
  {
    if ( ! drawable ) return;

    if ( this->has( drawable ) ) return;

    m_drawables.insert ( drawable );
    m_signal_drawable_added.emit ( drawable );
  }

  void DrawableSet::remove ( Drawable::pointer drawable )
  {
    DrawableSet::iterator listpos;

    listpos = std::find ( m_drawables.begin(), m_drawables.end(), drawable );
    
    if ( listpos == m_drawables.end() ) return;

    m_drawables.erase ( listpos );
    m_signal_drawable_removed.emit ( drawable );
  }

  bool DrawableSet::has ( Drawable::pointer drawable ) const
  {
    return std::find( m_drawables.begin(), m_drawables.end(), drawable ) != m_drawables.end() ;
  }

  size_t DrawableSet::size( ) const
  {
    return m_drawables.size();
  }

  DrawableSet::iterator DrawableSet::begin( )
  {
    return m_drawables.begin();
  }

  DrawableSet::const_iterator DrawableSet::begin( ) const
  {
    return m_drawables.begin();
  }

  DrawableSet::iterator DrawableSet::end( )
  {
    return m_drawables.end();
  }

  DrawableSet::const_iterator DrawableSet::end( ) const
  {
    return m_drawables.end();
  }

  DrawableSet::reverse_iterator DrawableSet::rbegin( )
  {
    return m_drawables.rbegin();
  }

  DrawableSet::const_reverse_iterator DrawableSet::rbegin( ) const
  {
    return m_drawables.rbegin();
  }

  DrawableSet::reverse_iterator DrawableSet::rend( )
  {
    return m_drawables.rend();
  }

  DrawableSet::const_reverse_iterator DrawableSet::rend( ) const
  {
    return m_drawables.rend();
  }

  bool DrawableSet::empty( ) const
  {
    return m_drawables.empty();
  }

  Region DrawableSet::extents( )
  {
    Region extents;

    for ( iterator i = m_drawables.begin(); i != m_drawables.end(); i++ )
      extents.include( (*i)->global_extents() );

    return extents;
  }

  void DrawableSet::link(DrawableSet::pointer s)
  {
    std::map<DrawableSet::pointer,sigc::connection>::iterator conn_iter;

    // We need a valid pointer
    if ( not s ) return;

    // Check to see if we're already linked
    conn_iter = m_linked_added_conn_map.find( s );
    if ( conn_iter != m_linked_added_conn_map.end() ) return;

    m_linked_added_conn_map[s] = s->signal_drawable_added().connect( sigc::mem_fun( *this, &DrawableSet::on_linked_set_drawable_added ));
    m_linked_removed_conn_map[s] = s->signal_drawable_removed().connect( sigc::mem_fun( *this, &DrawableSet::on_linked_set_drawable_removed ));

    DrawableSet::const_iterator i;
    for ( i = s->begin(); i != s->end(); i++ ) this->add( *i );
  }

  void DrawableSet::unlink(DrawableSet::pointer s)
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

  void DrawableSet::on_linked_set_drawable_added(Drawable::pointer added)
  {
    this->add( added );
  }

  void DrawableSet::on_linked_set_drawable_removed(Drawable::pointer removed)
  {
    this->remove( removed );
  }

}



