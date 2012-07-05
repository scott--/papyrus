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
#include "reference.h"

#include <papyrus/group.h>

namespace Papyrus
{

  Reference::Reference ( const Glib::ustring& id, Drawable::pointer ref ) :
      Drawable ( id ),
      m_referenced ( ref )
  {
    if ( m_referenced )
      m_connection_referenced_composed_matrix_invalidated =
        m_referenced->signal_composed_matrix_invalidated().connect(
          sigc::mem_fun(*this, &Reference::invalidate_composed_matrix) );  
  }

  Reference::pointer Reference::create ( Drawable::pointer ref )
  {
    PAPYRUS_CREATE ( Reference ( Glib::ustring(), ref ) );
  }

  Reference::pointer Reference::create ( const Glib::ustring& id, Drawable::pointer ref )
  {
    PAPYRUS_CREATE ( Reference ( id, ref ) );
  }

  Reference::~Reference()
  {}

  void Reference::draw ( Context& cairo ) const
  {
    if ( m_referenced ) m_referenced->draw( cairo );
  }

  Drawable::pointer Reference::referenced()
  {
    return m_referenced;
  }

  void Reference::set_referenced ( Drawable::pointer d )
  {
    // Disconnect from the previous invalidation signal
    if ( m_connection_referenced_composed_matrix_invalidated )
      m_connection_referenced_composed_matrix_invalidated.disconnect();
    
    // Set the shape and reconnect to the new signal (unless the drawable is invalid)
    m_referenced = d;
    if ( m_referenced )
      m_connection_referenced_composed_matrix_invalidated =
          m_referenced->signal_composed_matrix_invalidated().connect(
        sigc::mem_fun(*this, &Reference::invalidate_composed_matrix) );  
    
    // Either way, we need to redraw
    this->redraw();
  }
  
  void Reference::clear_referenced()
  {
    this->set_referenced(Drawable::pointer());
  }

  Matrix Reference::global_matrix() const
  {
    Matrix local_matrix;
    if ( m_referenced )
      local_matrix = this->composed_matrix() * m_referenced->composed_matrix();
    else
      local_matrix = this->composed_matrix();

    if ( m_parent )
      return m_parent->global_matrix() * local_matrix;
    else
      return local_matrix;
  }

  Glib::ustring Reference::svg(unsigned depth)
  {
    Glib::ustring s;

    s += svg_spacing(depth) + "<use " + svg_id();

    if ( m_referenced )
      s += "xlink:href=\"#" + m_referenced->id() + "\" ";

    s += svg_transform();

    s += " />\n";
    
    return s;
  }

  Matrix Reference::calculate_composed_matrix() const
  {
    Matrix m;
    
    m.set_identity();
    
    m.translate( x(), y() );
    if ( m_referenced ) 
      m.translate( m_referenced->x(), m_referenced->y() );
    
    m.scale( get_scale_x(), get_scale_y() );
    if ( m_referenced ) 
      m.scale( m_referenced->get_scale_x(), m_referenced->get_scale_y() );
    
    m.translate( centroid_x(), centroid_y() );
    if ( m_referenced)
      m.translate( m_referenced->centroid_x(), m_referenced->centroid_y() );
    
    m.rotate( get_rotation() );
    if ( m_referenced )
      m.rotate( m_referenced->get_rotation() );
    
    m.translate( - centroid_x(), - centroid_y() );
    if ( m_referenced )
      m.translate( - m_referenced->centroid_x(), - m_referenced->centroid_y() );
    
    m.skew( get_skew_x(), get_skew_y() );
    if ( m_referenced )
      m.skew( m_referenced->get_skew_x(), m_referenced->get_skew_y() );

    this->apply_external_matrices( m );
    m_referenced->apply_external_matrices( m );
    
    return m;
  }

  Region Reference::calculate_extents(const Matrix & m, ExtentsPerformance ep) const
  {
    if ( not m_referenced ) return Region();
    return m_referenced->calculate_extents(m,ep);
  }

}

