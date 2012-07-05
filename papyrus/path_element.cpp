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
#include "path_element.h"

#include <sstream>

namespace Papyrus
{

  PathElement::PathElement ( const Glib::ustring& id, PathElementType type, double x, double y, double x1, double y1, double x2, double y2 ) :
      Renderable ( id ),
      m_type ( type ),
      m_x ( x ),
      m_y ( y ),
      m_x1 ( x1 ),
      m_y1 ( y1 ),
      m_x2 ( x2 ),
      m_y2 ( y2 )
  {}

  PathElement::pointer PathElement::create ( PathElementType type, double x, double y, double x1, double y1, double x2, double y2 )
  {
    PAPYRUS_CREATE ( PathElement ( Glib::ustring(), type, x, y, x1, y1, x2, y2 ) );
  }

  PathElement::pointer PathElement::create ( const Glib::ustring& id, PathElementType type, double x, double y, double x1, double y1, double x2, double y2 )
  {
    PAPYRUS_CREATE ( PathElement ( id, type, x, y, x1, y1, x2, y2 ) );
  }

  PathElement::~ PathElement()
  {}

  PathElementType PathElement::type()
  {
    return m_type;
  }

  void PathElement::set_type ( PathElementType type )
  {
    m_type = type;
    m_signal_changed.emit();
  }

  double PathElement::x()
  {
    return m_x;
  }

  double PathElement::y()
  {
    return m_y;
  }

  void PathElement::set_x ( double x )
  {
    m_x = x;
    this->signal_changed();
  }

  void PathElement::set_y ( double y )
  {
    m_y = y;
    this->signal_changed();
  }

  void PathElement::set_xy ( double x, double y )
  {
    m_x = x;
    m_y = y;
    this->signal_changed();
  }

  double PathElement::x1()
  {
    return m_x1;
  }

  double PathElement::y1()
  {
    return m_y1;
  }

  void PathElement::set_x1 ( double x1 )
  {
    m_x1 = x1;
    this->signal_changed();
  }

  void PathElement::set_y1 ( double y1 )
  {
    m_y1 = y1;
    this->signal_changed();
  }

  void PathElement::set_x1y1 ( double x1, double y1 )
  {
    m_x1 = x1;
    m_y1 = y1;
    this->signal_changed();
  }

  double PathElement::x2()
  {
    return m_x2;
  }

  double PathElement::y2()
  {
    return m_y2;
  }

  void PathElement::set_x2 ( double x2 )
  {
    m_x2 = x2;
    this->signal_changed();
  }

  void PathElement::set_y2 ( double y2 )
  {
    m_y2 = y2;
    this->signal_changed();
  }

  void PathElement::set_x2y2 ( double x2, double y2 )
  {
    m_x2 = x2;
    m_y2 = y2;
    this->signal_changed();
  }

  void PathElement::set_xyx1y1x2y2 ( double x, double y, double x1, double y1, double x2, double y2 )
  {
    m_x = x;
    m_y = y;
    m_x1 = x1;
    m_y1 = y1;
    m_x2 = x2;
    m_y2 = y2;
    this->signal_changed();
  }

  void PathElement::render ( Context& cairo ) const
  {
    this->render(cairo, pointer());
  }

  void PathElement::render ( Context& cairo, pointer previous ) const
  {
    double current_x, current_y;

    switch ( m_type )
    {
      case PATH_UNDEFINED:
        break;
      case PATH_MOVETO:
        cairo->move_to ( m_x, m_y );
        break;
      case PATH_REL_MOVETO:
        cairo->begin_new_sub_path();
        cairo->translate ( m_x, m_y );
        break;
      case PATH_CLOSE:
        cairo->close_path();
        break;
      case PATH_LINETO:
        cairo->line_to ( m_x, m_y );
        break;
      case PATH_REL_LINETO:
        cairo->rel_line_to ( m_x, m_y );
        break;
      case PATH_HORIZONTAL_LINETO:
        cairo->get_current_point ( current_x, current_y );
        cairo->line_to ( m_x, current_y );
        break;
      case PATH_REL_HORIZONTAL_LINETO:
        cairo->rel_line_to ( m_x, 0.0 );
        break;
      case PATH_VERTICAL_LINETO:
        cairo->get_current_point ( current_x, current_y );
        cairo->line_to ( current_x, m_y );
        break;
      case PATH_REL_VERTICAL_LINETO:
        cairo->rel_line_to ( 0.0, m_y );
        break;
      case PATH_QUADRATIC_BEZIER_CURVETO:
        m_x2 = m_x1;
        m_y2 = m_y1;
        // fall through to next case and draw quadratic bezier curveto
      case PATH_CURVETO:
        cairo->curve_to ( m_x1, m_y1, m_x2, m_y2, m_x, m_y );
        break;
      case PATH_REL_QUADRATIC_BEZIER_CURVETO:
        m_x2 = m_x1;
        m_y2 = m_y1;
        // fall through to next case and draw quadratic bezier curveto
      case PATH_REL_CURVETO:
        cairo->rel_curve_to ( m_x1, m_y1, m_x2, m_y2, m_x, m_y );
        break;
      case PATH_SMOOTH_CURVETO:
      case PATH_REL_SMOOTH_CURVETO:
        // The first control point will be either the current point
        // or relative to the previous control point
        if ( previous &&
                (
                    previous->type() == PATH_CURVETO ||
                    previous->type() == PATH_REL_CURVETO ||
                    previous->type() == PATH_SMOOTH_CURVETO ||
                    previous->type() == PATH_REL_SMOOTH_CURVETO
                )
           )
        {
          // first control point becomes the reflection of the second
          // control previous point relative to the current point
          if ( m_type == PATH_SMOOTH_CURVETO )
          {
            cairo->get_current_point ( m_x1, m_y1 );
            m_x1 += previous->x() - previous->x2();
            m_y1 += previous->y() - previous->y2();
          }
          else
          {
            m_x1 = previous->x() - previous->x2();
            m_y1 = previous->y() - previous->y2();
          }
        }

        if ( m_type == PATH_SMOOTH_CURVETO )
          cairo->curve_to ( m_x1, m_y1, m_x2, m_y2, m_x, m_y );
        else // if ( m_type == PATH_REL_SMOOTH_CURVETO )
          cairo->rel_curve_to ( m_x1, m_y1, m_x2, m_y2, m_x, m_y );
        break;
      case PATH_SMOOTH_QUADRATIC_BEZIER_CURVETO:
      case PATH_REL_SMOOTH_QUADRATIC_BEZIER_CURVETO:
        // The first control point will be either the current point
        // or relative to the previous control point
        cairo->get_current_point ( m_x1, m_y1 );

        if ( previous &&
                (
                    previous->type() == PATH_QUADRATIC_BEZIER_CURVETO ||
                    previous->type() == PATH_REL_QUADRATIC_BEZIER_CURVETO ||
                    previous->type() == PATH_SMOOTH_QUADRATIC_BEZIER_CURVETO ||
                    previous->type() == PATH_REL_SMOOTH_QUADRATIC_BEZIER_CURVETO
                )
           )
        {
          m_x1 += m_x1 - previous->x2();
          m_y1 += m_y1 - previous->y2();
        }

        m_x2 = m_x1;
        m_y2 = m_y1;

        if ( m_type == PATH_SMOOTH_QUADRATIC_BEZIER_CURVETO )
          cairo->curve_to ( m_x1, m_y1, m_x2, m_y2, m_x, m_y );
        else // if m_type == PATH_REL_SMOOTH_QUADRATIC_BEZIER_CURVETO
          cairo->rel_curve_to ( m_x1, m_y1, m_x2, m_y2, m_x, m_y );
        break;
      case PATH_ELIPTICAL_ARC:
        break;
      case PATH_REL_ELIPTICAL_ARC:
        break;
    }
    return;
  }

  Glib::ustring PathElement::svg( unsigned depth )
  {
    std::ostringstream s;
    s << svg_spacing(depth);

    switch( m_type )
    {
      case PATH_UNDEFINED:
        return Glib::ustring();
        break;
      case PATH_MOVETO:
        s << " M " << m_x << ", " << m_y;
        break;
      case PATH_REL_MOVETO:
        s << " m " << m_x << ", " << m_y;
        break;
      case PATH_CLOSE:
        s << " Z";
        break;
      case PATH_LINETO:
        s << " L " << m_x << ", " << m_y;
        break;
      case PATH_REL_LINETO:
        s << " l " << m_x << ", " << m_y;
        break;
      case PATH_HORIZONTAL_LINETO:
        s << " H " << m_x;
        break;
      case PATH_REL_HORIZONTAL_LINETO:
        s << " h " << m_x;
        break;
      case PATH_VERTICAL_LINETO:
        s << " V " << m_y;
        break;
      case PATH_REL_VERTICAL_LINETO:
        s << " v " << m_y;
        break;
      case PATH_CURVETO:
        s << " C " << m_x1 << ", " << m_y1 << " " << m_x2 << ", " << m_y2 << " " << m_x << ", " << m_y;
        break;
      case PATH_REL_CURVETO:
        s << " c " << m_x1 << ", " << m_y1 << " " << m_x2 << ", " << m_y2 << " " << m_x << ", " << m_y;
        break;
      case PATH_SMOOTH_CURVETO:
        s << " S " << m_x2 << ", " << m_y2 << " " << m_x << ", " << m_y;
        break;
      case PATH_REL_SMOOTH_CURVETO:
        s << " s " << m_x2 << ", " << m_y2 << " " << m_x << ", " << m_y;
        break;
      case PATH_QUADRATIC_BEZIER_CURVETO:
        s << " Q " << m_x1 << ", " << m_y1 << " " << m_x << ", " << m_y;
        break;
      case PATH_REL_QUADRATIC_BEZIER_CURVETO:
        s << " q " << m_x1 << ", " << m_y1 << " " << m_x << ", " << m_y;
        break;
      case PATH_SMOOTH_QUADRATIC_BEZIER_CURVETO:
        s << " T " << m_x << ", " << m_y;
        break;
      case PATH_REL_SMOOTH_QUADRATIC_BEZIER_CURVETO:
        s << " t " << m_x << ", " << m_y;
        break;
      case PATH_ELIPTICAL_ARC:
        break;
      case PATH_REL_ELIPTICAL_ARC:
        break;
    }

    s << "\n";
    return s.str();
  }
  
}



