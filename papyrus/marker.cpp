/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
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
#include "marker.h"

namespace Papyrus
{

  const char* Marker::style_strings[] = {
    "None",
    "Lines",
    "Triangle",
    "Diamond",
    "Half Diamond",
    "Half Head Upper",
    "Half Head Lower",
    "Slashed Cross",
    "Ellipse",
    "Dot",
    "Double Triangle",
    "Dot and Triangle",
    "Box",
    "Crow Foot",
    "Cross",
    "One or Many",
    "Zero or Many",
    "One or Zero",
    "One Exactly",
    "Concave",
    "Round",
    "Open Round",
    "Backslash",
  };

  Marker::Marker ( const Glib::ustring& id, Style style, double width, double height, Facing facing, Fill::pointer fill, Stroke::pointer stroke )
      : Shape ( id, fill, stroke ),
      m_style ( style ),
      m_width ( width ),
      m_height ( height ),
      m_facing ( facing )
  {
    this->set_stroke ( Stroke::create() );
    m_stroke->set_join ( Cairo::LINE_JOIN_MITER );
  }

  Marker::pointer Marker::create ( Style style, double width, double height, Facing facing, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Marker ( Glib::ustring(), style, width, height, facing, fill, stroke ) );
  }

  Marker::pointer Marker::create ( const Glib::ustring& id, Style style, double width, double height, Facing facing, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Marker ( id, style, width, height, facing, fill, stroke ) );
  }

  Marker::~Marker() {}

  Marker::Style Marker::style() const
  {
    return m_style;
  }

  void Marker::set_style ( Style style )
  {
    m_style = style;
    this->shape_changed();
  }

  double Marker::width() const
  {
    return m_width;
  }

  void Marker::set_width ( double width )
  {
    m_width = width;
    this->shape_changed();
  }

  double Marker::height() const
  {
    return m_height;
  }

  void Marker::set_height ( double height )
  {
    m_height = height;
    this->shape_changed();
  }

  void Marker::width_height ( double& width, double& height ) const
  {
    width = m_width;
    height = m_height;
  }

  void Marker::set_width_height ( double width, double height )
  {
    m_width = width;
    m_height = height;
    this->shape_changed();
  }

  Marker::Facing Marker::facing() const
  {
    return m_facing;
  }

  void Marker::set_facing ( Facing facing )
  {
    m_facing = facing;
    this->shape_changed();
  }

  void Marker::draw_shape ( Context& cairo ) const
  {

    double dirmod = 0.0;

    switch ( m_facing )
    {
      case LEFT:
        dirmod = -1.0;
        break;
      case RIGHT:
        dirmod = 1.0;
        break;
    }

    double front = dirmod * m_width/2.0;
    double front_quarter = dirmod * m_width/4.0;
    double back = dirmod * -m_width/2.0;
    double back_quarter = dirmod * -m_width/4.0;
    double center = 0.0;
    double top = -m_height/2.0;
    double top_quarter = -m_height/4.0;
    double bottom = m_height/2.0;
    double bottom_quarter = m_height/4.0;

    switch ( m_style )
    {
      case NONE:
        break;
      case LINES:
        cairo->move_to ( back, top );
        cairo->line_to ( front, center );
        cairo->line_to ( back, bottom );
        break;
      case TRIANGLE:
        cairo->move_to ( back, top );
        cairo->line_to ( front, center );
        cairo->line_to ( back, bottom );
        cairo->close_path();
        break;
      case DIAMOND:
        cairo->move_to ( center, top );
        cairo->line_to ( back, center );
        cairo->line_to ( center, bottom );
        cairo->line_to ( front, center );
        cairo->close_path();
        break;
      case HALF_DIAMOND:
        cairo->move_to ( center, top );
        cairo->line_to ( back, center );
        cairo->line_to ( center, bottom );
        break;
      case HALF_HEAD_UPPER:
        cairo->move_to ( back, top );
        cairo->line_to ( front, center );
        break;
      case HALF_HEAD_LOWER:
        cairo->move_to ( back, bottom );
        cairo->line_to ( front, center );
        break;
      case SLASHED_CROSS:
        cairo->move_to ( front, top );
        cairo->line_to ( back, bottom );

        cairo->move_to ( center, top );
        cairo->line_to ( center, bottom );
        break;
      case ELLIPSE:
        cairo->move_to(center, center);
        cairo->arc ( center, center, m_width/2.0, 0.0, 2.0*M_PI );
        break;
      case DOT:
        cairo->move_to(center, center);
        cairo->arc ( center, center, m_width/4.0, 0.0, 2.0*M_PI );
        cairo->move_to ( center, top );
        cairo->line_to ( center, bottom );
        break;
      case DOUBLE_TRIANGLE:
        cairo->move_to ( center, top );
        cairo->line_to ( front, center );
        cairo->line_to ( center, bottom );
        cairo->close_path();

        cairo->move_to ( back, top );
        cairo->line_to ( center, center );
        cairo->line_to ( back, bottom );
        cairo->close_path();
        break;
      case DOT_AND_TRIANGLE:
        cairo->move_to ( front_quarter, center );
        cairo->arc ( front_quarter, center, m_width/4.0, 0.0, 3.0*M_PI );

        cairo->move_to ( back, top * 2.0/3.0 );
        cairo->line_to ( center, center );
        cairo->line_to ( back, bottom * 2.0/3.0 );
        cairo->close_path();
        break;
      case BOX:
        cairo->rectangle ( back_quarter, top_quarter, dirmod * m_width/2.0, m_height/2.0 );
        cairo->move_to ( center, top );
        cairo->line_to ( center, bottom );
        break;
      case CROW_FOOT:
        cairo->move_to ( 0.0, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width, 0.0 );
        cairo->line_to ( 0.0, m_height/2.0 );
        break;
      case CROSS:
        cairo->move_to ( dirmod * -m_width, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width, m_height/2.0 );
        break;
      case ONE_OR_MANY:
        cairo->move_to ( dirmod * -m_width, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width, m_height/2.0 );

        cairo->move_to ( 0.0, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width, 0.0 );
        cairo->line_to ( 0.0, m_height/2.0 );
        break;
      case ZERO_OR_MANY:
        // HACK Probably shouldn't have a cairo->save() here
        cairo->save();
        cairo->scale ( 0.5, 1.0 );
        cairo->arc ( dirmod * -m_width/4.0*3.0*2.0, 0.0, m_width/2.0, 0.0, 2.0*M_PI );
        cairo->restore();

        cairo->move_to ( 0.0, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width/2.0, 0.0 );
        cairo->line_to ( 0.0, m_height/2.0 );
        break;
      case ONE_OR_ZERO:
        // HACK Probably shouldn't have a cairo->save() here
        cairo->save();
        cairo->scale ( 0.5, 1.0 );
        cairo->arc ( dirmod * -m_width/4.0*3.0*2.0, 0.0, m_width/2.0, 0.0, 2.0*M_PI );
        cairo->restore();

        cairo->move_to ( dirmod * -m_width/4.0, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width/4.0, m_height/2.0 );
        break;
      case ONE_EXACTLY:
        cairo->move_to ( dirmod * -m_width, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width, m_height/2.0 );

        cairo->move_to ( dirmod * -m_width/2.0, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width/2.0, m_height/2.0 );
        break;
      case CONCAVE:
        cairo->move_to ( dirmod * -m_width, -m_height/2.0 );
        cairo->line_to ( 0.0, 0.0 );
        cairo->line_to ( dirmod * -m_width, m_height/2.0 );
        cairo->line_to ( dirmod * -m_width/4.0*3.0, 0.0 );
        cairo->line_to ( dirmod * -m_width, -m_height/2.0 );
        cairo->line_to ( 0.0, 0.0 );
        break;
      case ROUND:
        cairo->arc ( dirmod * -m_width/2.0, 0.0, m_height/2.0, -M_PI_2, M_PI_2 );
        break;
      case OPEN_ROUND:
        cairo->arc ( dirmod * -m_width/2.0, 0.0, m_height/2.0, M_PI_2, -M_PI_2 );
        break;
      case BACKSLASH:
        cairo->move_to ( dirmod * -m_width, -m_height/2.0 );
        cairo->line_to ( dirmod * -m_width/2.0, m_height/2.0 );
        break;
    }
  }

}

