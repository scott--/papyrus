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
#include "hextille.h"

#include <cmath>

#include <papyrus/group.h>

#define m_FILL(__column,__row) m_fill[__row*m_columns+__column]
#define m_FILL_CHANGED_CONNECTION(__column,__row) m_fill_changed_connection[__row*m_columns+__column]

namespace Papyrus
{

  Hextille::Hextille ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length ):
      Tiling(id, rows, columns, side_length)
  {
    this->set_centroid( m_rows * m_side_length / 2.0, 
                        m_columns * m_side_length / 2.0 );
  }

  Hextille::pointer Hextille::create ( unsigned rows, unsigned columns, double side_length )
  {
    PAPYRUS_CREATE( Hextille(std::string(), rows, columns, side_length) );
  }

  Hextille::pointer Hextille::create ( const Glib::ustring & id, unsigned rows, unsigned columns, double side_length )
  {
    PAPYRUS_CREATE( Hextille(id, rows, columns, side_length) );
  }

  Hextille::~ Hextille()
  {
  }

  void draw_path( Context& cairo,
                  unsigned col,
                  unsigned row,
                  double side,
                  double sidex2,
                  double sidex3,
                  double side_half,
                  double height,
                  double height_half)
  {
    double base_x, base_y;
    if ( col % 2 == 0 )
    {
      base_x = col/2 * sidex3 + side_half;
      base_y = row * height;
    }
    else
    {
      base_x = col/2 * sidex3 + sidex2;
      base_y = row * height + height_half;
    }
    cairo->move_to( base_x, base_y );
    cairo->rel_line_to( side, 0.0 );
    cairo->rel_line_to( side_half, height_half );
    cairo->rel_line_to( - side_half, height_half );
    cairo->rel_line_to( - side, 0.0 );
    cairo->rel_line_to( - side_half, - height_half );
    cairo->rel_line_to( side_half, - height_half );
    cairo->close_path();
  }
  
  
  void Hextille::draw ( Context& cairo ) const
  {
    Fill::pointer default_fill;
    Stroke::pointer stroke;

    default_fill = m_default_fill;
    if ( (not default_fill) and m_parent ) default_fill = m_parent->fill();

    stroke = m_stroke;
    if ( (not m_stroke) and m_parent ) stroke = m_parent->stroke();
    
    double side, sidex2, sidex3, side_half;
    double height, height_half;

    side = m_side_length;
    sidex2 = side * 2.0;
    sidex3 = side * 3.0;
    side_half = side / 2.0;
    height = tan(M_PI/3.0) * side;
    height_half = height / 2.0;
     
    for ( unsigned c=0; c < m_columns; c++ )
    {
      for ( unsigned r=0; r < m_rows; r++ )
      {        
        if ( m_FILL(c,r) != NULL )
        {
          draw_path( cairo, c, r, side, sidex2, sidex3, side_half, height, height_half);
          (*m_FILL(c,r))->render(cairo);
          cairo.fill();
        }
        else if ( default_fill )
        {
          draw_path( cairo, c, r, side, sidex2, sidex3, side_half, height, height_half);
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
          draw_path( cairo, c, r, side, sidex2, sidex3, side_half, height, height_half);
          cairo.stroke();
        }
      }
    }
  }

  void Hextille::update_centroid_x()
  {
    this->set_centroid_x( m_rows * m_side_length / 2.0 );
  }

  void Hextille::update_centroid_y()
  {
    this->set_centroid_y( m_columns * m_side_length / 2.0 );
  }

  void Hextille::update_centroid()
  {
    this->set_centroid( m_rows * m_side_length / 2.0, 
                        m_columns * m_side_length / 2.0 );
  }

}

