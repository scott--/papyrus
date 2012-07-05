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
#include "deltille.h"

#include <cmath>

#include <papyrus/group.h>

#define m_FILL(__column,__row) m_fill[__row*m_columns+__column]
#define m_FILL_CHANGED_CONNECTION(__column,__row) m_fill_changed_connection[__row*m_columns+__column]

namespace Papyrus
{

  Deltille::Deltille ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length ):
      Tiling(id, rows, columns, side_length)
  {
    this->set_centroid( (m_rows / 2.0 + 0.5) * m_side_length / 2.0, 
                         m_columns * m_side_length * M_SQRT1_2 / 2.0 );
  }

  Deltille::pointer Deltille::create ( unsigned rows, unsigned columns, double side_length )
  {
    PAPYRUS_CREATE( Deltille(std::string(), rows, columns, side_length) );
  }

  Deltille::pointer Deltille::create ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length )
  {
    PAPYRUS_CREATE( Deltille(id, rows, columns, side_length) );
  }

  Deltille::~ Deltille()
  {
  }
  
  void Deltille::draw_path( Context& cairo, unsigned col, unsigned row, double side, double half_side, double height ) const
  {
    double base_x, base_y;
    if ( col % 2 == 0 )
    {
      if ( row % 2 == 0 ) 
        base_x = col/2 * side;
      else 
        base_x = col/2 * side + half_side;
      base_y = row * height;
      cairo->move_to( base_x, base_y + height );
      cairo->rel_line_to( half_side, -height );
      cairo->rel_line_to( half_side, height );
      cairo->rel_line_to( -side, 0.0 );
      cairo->close_path();
    }
    else
    {
      if ( row % 2 == 1 ) 
        base_x = col/2 * side;
      else
        base_x = col/2 * side + half_side;
      base_y = row * height;
      cairo->move_to( base_x, base_y );
      cairo->line_to( base_x+side, base_y );
      cairo->line_to( base_x+half_side, base_y + height );
      cairo->line_to( base_x, base_y );
      cairo->close_path();
    }
  }

  void Deltille::draw ( Context& cairo ) const
  {
    Fill::pointer default_fill;
    Stroke::pointer stroke;

    default_fill = m_default_fill;
    if ( (not default_fill) and m_parent ) default_fill = m_parent->fill();

    stroke = m_stroke;
    if ( (not m_stroke) and m_parent ) stroke = m_parent->stroke();
    
    double height = m_side_length * M_SQRT1_2;
    double half_side = m_side_length / 2.0;
    
    for ( unsigned c=0; c < m_columns; c++ )
    {
      for ( unsigned r=0; r < m_rows; r++ )
      {        
        if ( m_FILL(c,r) != NULL )
        {
          draw_path( cairo, c, r, m_side_length, half_side, height );
          (*m_FILL(c,r))->render(cairo);
          cairo.fill();
        }
        else if ( default_fill )
        {
          draw_path( cairo, c, r, m_side_length, half_side, height );
          default_fill->render ( cairo );
          cairo.fill();
        }

      }
    }
    
    if ( stroke )
    {
      stroke->render ( cairo );
      for ( unsigned c=0; c < m_columns; c++ )
      {
        for ( unsigned r=0; r < m_rows; r++ )
        {
          draw_path( cairo, c, r, m_side_length, half_side, height );
          cairo.stroke();
        }
      }
    }
  }

  void Deltille::update_centroid_x()
  {
    this->set_centroid_x( (m_rows / 2.0 + 0.5) * m_side_length / 2.0 );
  }

  void Deltille::update_centroid_y()
  {
    this->set_centroid_y( m_columns * m_side_length * M_SQRT1_2 / 2.0 );
  }

  void Deltille::update_centroid()
  {
    this->set_centroid( (m_rows / 2.0 + 0.5) * m_side_length / 2.0, 
                         m_columns * m_side_length * M_SQRT1_2 / 2.0 );
  }

}

