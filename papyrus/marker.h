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
#ifndef PAPYRUSMARKER_H
#define PAPYRUSMARKER_H

#include <papyrus/shape.h>

namespace Papyrus
{

  /**
   * Draws an marker head or tail (not the body of the marker) with the tip
   * or tail centered at (x,y).
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Marker : public Shape
  {
    public:
      typedef enum Style {
          FIRST_STYLE,
          NONE=FIRST_STYLE,
          LINES,
          TRIANGLE,
          DIAMOND,
          HALF_DIAMOND,
          HALF_HEAD_UPPER,
          HALF_HEAD_LOWER,
          SLASHED_CROSS,
          ELLIPSE,
          DOT,
          DOUBLE_TRIANGLE,
          DOT_AND_TRIANGLE,
          BOX,
          CROW_FOOT,
          CROSS,
          ONE_OR_MANY,
          ZERO_OR_MANY,
          ONE_OR_ZERO,
          ONE_EXACTLY,
          CONCAVE,
          ROUND,
          OPEN_ROUND,
          BACKSLASH,
          LAST_STYLE=BACKSLASH
    } Style;

    static const char* style_strings[];

      typedef enum Facing {
          LEFT,
          RIGHT
    } Facing;

    protected:

      /** Default constructor */
      Marker ( const Glib::ustring& id,
               Style style,
               double width,
               double height,
               Facing facing,
               Fill::pointer fill,
               Stroke::pointer stroke );

    public:
      PAPYRUS_DRAWABLE(Marker);

      /** Creates an marker with the specified style. */
      static pointer create ( Style style=NONE,
                              double width = 20.0,
                              double height = 20.0,
                              Facing facing = RIGHT,
                              Fill::pointer fill=Fill::pointer(),
                              Stroke::pointer stroke = Stroke::pointer() );

      /** Creates an marker with the specified style. */
      static pointer create ( const Glib::ustring& id,
                              Style style=NONE,
                              double width = 20.0,
                              double height = 20.0,
                              Facing facing = RIGHT,
                              Fill::pointer fill=Fill::pointer(),
                              Stroke::pointer stroke = Stroke::pointer() );

      /** Destructor */
      virtual ~Marker();

      /** @return marker style */
      Style style() const;

      /** set marker style */
      void set_style ( Style style );

      /** @return drawing width of marker */
      double width() const;

      /** set drawing width of marker */
      void set_width ( double width );

      /** @return drawing height of marker */
      double height() const;

      /** set drawing height of marker */
      void set_height ( double height );

      /** get the drawing width and height of the marker */
      void width_height ( double& width, double& height ) const;

      /** set the drawing width and height of the marker */
      void set_width_height ( double width, double height );

      /**
       * @return the facing direction.
       * Changing the facing direction is more than a simple 180' rotation.
       * It effects a mirror of the marker about the marker's local y-axis.
       */
      Facing facing() const;

      /** set the facing direction */
      void set_facing ( Facing facing );

      /** Draws on the provided context */
      virtual void draw_shape ( Context& cairo ) const;

    protected:
      Style m_style;

      double m_width;

      double m_height;

      Facing m_facing;

  };

}

#endif
