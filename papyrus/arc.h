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
#ifndef PAPYRUSARC_H
#define PAPYRUSARC_H

#include <cmath>

#include <papyrus/shape.h>

/**
 * \page guide_arc Arcs
 * An arc is drawn centered on the (x,y) coordinate with a specified radius
 * and start/stop angles.
 *
 * The following contains an example that will add a yellow arc with a black
 * border to a canvas. The blue lines represent the
 * x and y axes, and show through since an alpha value of 0.9 is used.
 *
 * \image html arc.png "Arc drawn by example code below"
 *
 * \dontinclude factory.cpp
 * \skip example_arc
 * \until }
 *
 */

namespace Papyrus
{

  /**
   * An arc is drawn centered on the (x,y) coordinate with a specified radius
   * and start/stop angles.
   *
   * \image html arc.png "Arc"
   *
   * @author Rick L Vinyard Jr
   */
  class Arc : public Shape
  {
    protected:

      Arc ( const Glib::ustring& id,
            double radius,
            double angle_start,
            double angle_end,
            Fill::pointer fill = Fill::pointer(),
            Stroke::pointer stroke = Stroke::pointer()
          );

    public:
      PAPYRUS_DRAWABLE(Arc);

      /** Creates an arc with the specified start angle, stop angle and radius. */
      static pointer create ( double radius = 1.0,
                              double angle_start = 0.0,
                              double angle_end = M_PI / 2.0,
                              Fill::pointer fill = Fill::pointer(),
                              Stroke::pointer stroke = Stroke::pointer()
                            );

      /** Creates an arc with the specified start angle, stop angle and radius. */
      static pointer create ( const Glib::ustring& id,
                              double radius = 1.0,
                              double angle_start = 0.0,
                              double angle_end = M_PI / 2.0,
                              Fill::pointer fill = Fill::pointer(),
                              Stroke::pointer stroke = Stroke::pointer()
                            );

      /** Destructor */
      virtual ~Arc();

      /** Returns the radius of this arc */
      double radius() const;

      /** Sets the radius to r */
      void set_radius ( double r );

      /** Sets the start angle of the arc. */
      double start_angle() const;

      /** Sets the end angle of the arc. */
      double end_angle() const;

      /** Set both start and stop angles in a single method. */
      void set_angles ( double start, double end );

      /** Draws on the provided context */
      virtual void draw_shape ( Context& cairo ) const;

      /** Signal emitted when the radius is changed */
      sigc::signal<void> signal_radius();

      /** Signal emitted when the start or end angle is changed */
      sigc::signal<void> signal_angle();

    protected:

      /** The radius of the arc */
      double m_radius;

      double m_angle_start;

      double m_angle_end;

      /** Signal emitted when the radius is changed */
      sigc::signal<void> m_signal_radius;

      /** Signal emitted when the start or end angle is changed */
      sigc::signal<void> m_signal_angle;

  };

}

#endif
