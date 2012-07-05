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
#include "drawablecontroller.h"

#include <algorithm>

namespace Papyrus
{

  DrawableController::DrawableController( const Glib::ustring& id, DrawableSet::pointer drawables ):
      Controller(id),
      DrawableSet( drawables )
  {
    m_signal_drawable_added.connect( sigc::mem_fun( *this, &DrawableController::on_drawable_added_proxy ) );
    m_signal_drawable_removed.connect( sigc::mem_fun( *this, &DrawableController::on_drawable_removed_proxy ) );
    m_signal_cleared.connect( sigc::mem_fun( *this, &DrawableController::on_drawables_cleared_proxy ) );
  }

  DrawableController::pointer DrawableController::create( const Glib::ustring& id, DrawableSet::pointer drawables )
  {
    PAPYRUS_CREATE( DrawableController(id, drawables) );
  }

  DrawableController::pointer DrawableController::create( DrawableSet::pointer drawables )
  {
    PAPYRUS_CREATE( DrawableController(Glib::ustring(), drawables) );
  }

  DrawableController::~DrawableController()
  {
  }

  void DrawableController::on_drawable_added( Drawable::pointer d )
  {
  }

  void DrawableController::on_drawable_removed( Drawable::pointer d )
  {
  }

  void DrawableController::on_drawables_cleared( )
  {
  }

  void DrawableController::on_drawable_added_proxy( Drawable::pointer d )
  {
    this->on_drawable_added( d );
  }

  void DrawableController::on_drawable_removed_proxy( Drawable::pointer d )
  {
    this->on_drawable_removed( d );
  }

  void DrawableController::on_drawables_cleared_proxy( )
  {
    this->on_drawables_cleared();
  }

}

