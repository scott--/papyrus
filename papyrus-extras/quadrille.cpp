/***************************************************************************
 *   Copyright (C) 2004,2009 by Rick L. Vinyard, Jr.                       *
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
#include "quadrille.h"

#include <cmath>

#include <papyrus/group.h>

#define m_FILL(__column,__row) m_fill[__row*m_columns+__column]
#define m_FILL_CHANGED_CONNECTION(__column,__row) m_fill_changed_connection[__row*m_columns+__column]

namespace Papyrus
{

  Quadrille::Quadrille ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length ):
      Tiling(id, rows, columns, side_length)
  {
    this->set_centroid( m_rows * m_side_length / 2.0, 
                        m_columns * m_side_length / 2.0 );
  }

  Quadrille::pointer Quadrille::create ( unsigned rows, unsigned columns, double side_length )
  {
    PAPYRUS_CREATE( Quadrille(std::string(), rows, columns, side_length) );
  }

  Quadrille::pointer Quadrille::create ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length )
  {
    PAPYRUS_CREATE( Quadrille(id, rows, columns, side_length) );
  }

  Quadrille::~ Quadrille()
  {
  }

  void Quadrille::draw ( Context& cairo ) const
  {
    Fill::pointer default_fill;
    Stroke::pointer stroke;

    default_fill = m_default_fill;
    if ( (not default_fill) and m_parent ) default_fill = m_parent->fill();

    stroke = m_stroke;
    if ( (not m_stroke) and m_parent ) stroke = m_parent->stroke();
    
    for ( unsigned c=0; c < m_columns; c++ )
    {
      for ( unsigned r=0; r < m_rows; r++ )
      {        
        if ( m_FILL(c,r) != NULL )
        {
          cairo->rectangle(c * m_side_length, r * m_side_length, m_side_length, m_side_length);
          (*m_FILL(c,r))->render(cairo);
          cairo.fill();
        }
        else if ( default_fill )
        {
          cairo->rectangle(c * m_side_length, r * m_side_length, m_side_length, m_side_length);
          default_fill->render ( cairo );
          cairo.fill();
        }

      }
    }
    
    for ( unsigned c=0; c < m_columns; c++ )
    {
      for ( unsigned r=0; r < m_rows; r++ )
      {
        cairo->rectangle(c * m_side_length, r * m_side_length, m_side_length, m_side_length);
      
        if ( stroke )
        {
          stroke->render ( cairo );
          cairo.stroke();
        }
      }
    }
  }

  void Quadrille::update_centroid_x()
  {
    this->set_centroid_x( m_rows * m_side_length / 2.0 );
  }

  void Quadrille::update_centroid_y()
  {
    this->set_centroid_y( m_columns * m_side_length / 2.0 );
  }

  void Quadrille::update_centroid()
  {
    this->set_centroid( m_rows * m_side_length / 2.0, 
                        m_columns * m_side_length / 2.0 );
  }

}

