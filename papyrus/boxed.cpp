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
#include "boxed.h"
#include "rgba.h"

#include <limits.h>

namespace Papyrus
{

  const int Boxed::DEFAULT_LEVEL = INT_MIN;

  Boxed::Boxed ( const Glib::ustring& id, Fill::pointer fill, Stroke::pointer stroke ):
      Drawable(id),
      m_box_position(UNDER)
  {
    m_box = Rectangle::create();
    if ( fill ) m_box->set_fill( fill );
    if ( stroke ) m_box->set_stroke ( stroke );
    m_box->hide();
    m_signal_added.connect( sigc::mem_fun(*this, &Boxed::on_child_added) );
    m_signal_removed.connect( sigc::mem_fun(*this, &Boxed::on_child_removed) );
    m_signal_cleared.connect( sigc::mem_fun(*this, &Boxed::on_cleared) );

    m_signal_watch_added.connect( sigc::mem_fun(*this, &Boxed::on_watched_event) );
    m_signal_watch_removed.connect( sigc::mem_fun(*this, &Boxed::on_watched_event) );
    m_signal_watched_changed.connect( sigc::mem_fun(*this, &Boxed::on_watched_event) );
  }

  Boxed::pointer Boxed::create ( const Glib::ustring& id, Fill::pointer fill, Stroke::pointer stroke )
  {
    return Boxed::pointer ( new Boxed ( id, fill, stroke ) );
  }

  Boxed::~Boxed()
  {}

  void Boxed::draw( Context& cairo ) const
  {
    if ( m_box_position == UNDER and m_box->is_visible() ) m_box->render(cairo);
    if ( m_child ) m_child->render(cairo);
    if ( m_box_position == OVER and m_box->is_visible() ) m_box->render(cairo);
  }

  Rectangle::pointer Boxed::box( )
  {
    return m_box;
  }

  OverUnder Boxed::box_position() const
  {
    return m_box_position;
  }

  void Boxed::set_box_position(OverUnder ou)
  {
    if ( m_box_position == ou ) return;
    m_box_position = ou;
    this->redraw();
  }

  void Boxed::on_child_added(Drawable::pointer added)
  {
    this->invalidate_extents();
    this->redraw();
  }

  void Boxed::on_child_removed(Drawable::pointer removed)
  {
    this->invalidate_extents();
    this->redraw();
  }

  void Boxed::on_cleared()
  {
    this->invalidate_extents();
    this->redraw();
  }

  Region Boxed::calculate_extents(const Matrix& m, ExtentsPerformance ep) const
  {
    Region total_extents;
    Region local_extents;

    Matrix m2 = m * this->composed_matrix();

    if ( m_child )
    {
      total_extents = m_child->extents();
    }

    Watched::iterator witer;
    
    for ( witer = m_watched.begin(); witer != m_watched.end(); witer++ )
    {
      Region watched_extents = witer->lock()->global_extents();
      total_extents.include( watched_extents );
    }

    if ( total_extents )
    {
      // Since the box will also be subject to the composed matrix we need
      // to apply the inverse of the composed matrix so that the box consists
      // entirely of the real extents.
      Matrix m = this->composed_matrix();
//       m.invert();
//       total_extents.transform(m);
      m_box->show();
      m_box->set_xywh( total_extents );
      total_extents = m_box->extents();
    }
    else
    {
      m_box->hide();
    }
    
    return total_extents;
  }

  void Boxed::on_child_changed(Drawable::pointer)
  {
    this->invalidate_extents();
    this->redraw();
  }

  void Boxed::on_watched_event(Drawable::pointer watched)
  {
    this->invalidate_extents();
    this->redraw();
  }

}

