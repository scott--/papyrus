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
#ifndef PAPYRUSREGULARPOLYGON_H
#define PAPYRUSREGULARPOLYGON_H

#include <papyrus/polygon.h>

/**
 * \page guide_regularpolygon Regular Polygons
 *
 * A regular polygon is "a plane polygon which is both equilateral and equiangular." [1]
 *
 * A regular polygon is specified by a combination of the number of sides and
 * either of the radius (the distance from the center to a vertex), the apothem
 * (the perpendicular from the center to an edge), or the length of the edges.
 *
 * A regular polygon may also be specified as ZERO_RADIUS or ZERO_APOTHEM,
 * which will result in the radius or apothem respectively being draw at 0
 * radians.
 *
 * The following contains an example that will add a hexagon polygon to a canvas,
 * with the <b>radius</b> drawn at 0 radians.
 *
 * The blue lines represent the x and y axes, and show through since an alpha value
 * of 0.9 is used.
 *
 * \image html regularpolygon_radius.png "Regular polygon with six sides (hexagon) and radius at 0 radians drawn by example code below"
 *
 * \dontinclude shapes.cpp
 * \skip add_regularpolygon_radius
 * \until }
 *
 * The following contains an example that will add a hexagon polygon to a canvas,
 * with the <b>apothem</b> drawn at 0 radians.
 *
 * The blue lines represent the x and y axes, and show through since an alpha value
 * of 0.9 is used.
 *
 * \image html regularpolygon_apothem.png "Regular polygon with six sides (hexagon) and apothem at 0 radians drawn by example code below"
 *
 * \dontinclude shapes.cpp
 * \skip add_regularpolygon_apothem
 * \until }
 *
 * [1] 1913 Webster
 *
 */


namespace Papyrus
{

  /**
  @author Rick L Vinyard Jr
  */
  class RegularPolygon : public Polygon
  {
    public:
      typedef enum Style {ZERO_RADIUS, ZERO_APOTHEM} Style;

    protected:

      RegularPolygon ( const Glib::ustring& id,
                       unsigned int sides,
                       double radius,
                       Style style,
                       Fill::pointer fill,
                       Stroke::pointer stroke );

    public:
      PAPYRUS_DRAWABLE(RegularPolygon);

      static RegularPolygon::pointer create ( unsigned int sides=3,
                                              double radius=1.0,
                                              Style style=ZERO_RADIUS,
                                              Fill::pointer fill=Fill::pointer(),
                                              Stroke::pointer stroke = Stroke::pointer() );

      static RegularPolygon::pointer create ( const Glib::ustring& id,
                                              unsigned int sides=3,
                                              double radius=1.0,
                                              Style style=ZERO_RADIUS,
                                              Fill::pointer fill=Fill::pointer(),
                                              Stroke::pointer stroke = Stroke::pointer() );

      virtual ~RegularPolygon();

      unsigned int sides();

      void set_sides ( unsigned int s );

      double radius();
      void set_radius ( double r );
      void set_sides_radius ( unsigned int s, double r );

      double edge_length();
      void set_edge_length ( double e );
      void set_sides_edge_length ( unsigned int s, double e );

      double apothem_length();
      void set_apothem_length ( double a );
      void set_sides_apothem_length ( unsigned int s, double a );

      Style style();
      void set_style ( Style );

      /** signal emitted when the number of sides changes */
      sigc::signal<void> signal_sides();

      /** signal emitted when the radius, edge length, or apothem length changes */
      sigc::signal<void> signal_size();

      /** signal emitted when the style changes */
      sigc::signal<void> signal_style();

    protected:
      unsigned int m_sides;
      double m_radius;
      Style m_style;

      void create_vertices();

      sigc::signal<void> m_signal_sides;

      sigc::signal<void> m_signal_size;

      sigc::signal<void> m_signal_style;

  };

}

#endif
