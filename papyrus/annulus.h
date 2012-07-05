/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
#ifndef PAPYRUSANNULUS_H
#define PAPYRUSANNULUS_H

#include <papyrus/shape.h>

namespace Papyrus
{

  /**
   * An annulus (donut/flat torus) is drawn centered on the x,y coordinate with
   * a specified inner and outer radii. The arcs of the annulus default to a
   * full circle but can be set to any start/end point.
   *
   * @author Rick L Vinyard Jr
   */
  class Annulus : public Shape
  {
    protected:

      Annulus ( const Glib::ustring& id,
            double outer_radius,
            double inner_radius,
            double angle_start,
            double angle_end,
            Fill::pointer fill = Fill::pointer(),
                Stroke::pointer stroke = Stroke::pointer()
          );

    public:
      PAPYRUS_DRAWABLE(Annulus);

      /** Creates an annulus with the specified start angle, stop angle and radii. */
      static pointer create ( double outer_radius = 1.0,
                              double inner_radius = 1.0,
                              double angle_start = 0.0,
                              double angle_end = 2.0 * M_PI,
                              Fill::pointer fill = Fill::pointer(),
                                  Stroke::pointer stroke = Stroke::pointer()
                            );

      /** Creates an a with the specified start angle, stop angle and radius. */
      static pointer create ( const Glib::ustring& id,
                              double outer_radius = 1.0,
                              double inner_radius = 0.5,
                              double angle_start = 0.0,
                              double angle_end = 2.0 * M_PI,
                              Fill::pointer fill = Fill::pointer(),
                                  Stroke::pointer stroke = Stroke::pointer()
                            );

      /** Destructor */
      virtual ~Annulus();

      /** Returns the outer radius of this annulus */
      double outer_radius() const;

      /** Sets the outer radius to r */
      void set_outer_radius ( double r );

      /** Returns the inner radius of this annulus */
      double inner_radius() const;

      /** Sets the inner radius to r */
      void set_inner_radius ( double r );

      /** Sets the outer and inner radii */
      void set_radii( double outer, double inner );

      /** Sets the start angle of the annulus. */
      double start_angle() const;

      /** Sets the end angle of the annulus. */
      double end_angle() const;

      /** Set both start and stop angles in a single method. */
      void set_angles ( double start, double end );

      /** Draws on the provided context */
      virtual void draw_shape ( Context& cairo ) const;

      /** Signal emitted when the outer radius is changed */
      sigc::signal<void> signal_outer_radius();

      /** Signal emitted when the inner radius is changed */
      sigc::signal<void> signal_inner_radius();

      /** Signal emitted when the start or end angle is changed */
      sigc::signal<void> signal_angle();

    protected:

      /** The outer radius of the annulus */
      double m_outer_radius;

      /** The inner radius of the annulus */
      double m_inner_radius;

      double m_angle_start;

      double m_angle_end;

      /** Signal emitted when the outer radius is changed */
      sigc::signal<void> m_signal_outer_radius;

      /** Signal emitted when the inner radius is changed */
      sigc::signal<void> m_signal_inner_radius;

      /** Signal emitted when the start or end angle is changed */
      sigc::signal<void> m_signal_angle;

  };

}

#endif
