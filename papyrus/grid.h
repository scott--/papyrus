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
#ifndef PAPYRUSGRID_H
#define PAPYRUSGRID_H

#include <papyrus/drawable.h>
#include <papyrus/stroke.h>
#include <papyrus/enums.h>

namespace Papyrus
{

  /**
        @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
  */
  class Grid : public Drawable
  {
    protected:

      Grid ( const Glib::ustring& id,
             double xmin=-infinity, double xmax=infinity,
             double ymin=-infinity, double ymax=infinity );

    public:
      PAPYRUS_DRAWABLE(Grid);

      static const double infinity;

      static pointer create ( double xmin=-infinity, double xmax=infinity,
                              double ymin=-infinity, double ymax=infinity );

      static pointer create ( const Glib::ustring& id,
                              double xmin=-infinity, double xmax=infinity,
                              double ymin=-infinity, double ymax=infinity );

      virtual ~Grid();

      double x_min();

      void set_x_min ( double min );

      double x_max();

      void set_x_max ( double max );

      void x_min_max ( double& min, double& max );

      void set_x_min_max ( double min, double max );

      double y_min();

      void set_y_min ( double min );

      double y_max();

      void set_y_max ( double max );

      void y_min_max ( double& min, double& max );

      void set_y_min_max ( double min, double max );

      void xy_min_max ( double& x_min, double& x_max, double& y_min, double& y_max );

      void set_xy_min_max ( double x_min, double x_max, double y_min, double y_max );

      void enable_axis ( unsigned which = X_AXIS | Y_AXIS );

      void disable_axis ( unsigned which = X_AXIS | Y_AXIS );

      Stroke::pointer x_axis_stroke() const;

      void set_x_axis_stroke ( Stroke::pointer stroke );

      Stroke::pointer y_axis_stroke() const;

      void set_y_axis_stroke ( Stroke::pointer stroke );

      void set_xy_axis_stroke ( Stroke::pointer stroke );

      void enable_border ( unsigned which = TOP | RIGHT | BOTTOM | LEFT );

      void disable_border ( unsigned which = TOP | RIGHT | BOTTOM | LEFT );

      void set_border_stroke ( Stroke::pointer stroke,
                               unsigned which = TOP | RIGHT | BOTTOM | LEFT );

      double x_interval();

      void set_x_interval ( double x_interval );

      Stroke::pointer x_interval_stroke();

      void set_x_interval_stroke ( Stroke::pointer );

      double y_interval();

      void set_y_interval ( double y_interval );

      Stroke::pointer y_interval_stroke();

      void set_y_interval_stroke ( Stroke::pointer );

      void xy_interval ( double& x_interval, double& y_interval );

      void set_xy_interval ( double interval );

      void set_xy_interval ( double x_interval, double y_interval );

      void xy_interval_stroke ( Stroke::pointer x_stroke, Stroke::pointer y_stroke );

      void set_xy_interval_stroke ( Stroke::pointer stroke );

      void set_xy_interval_stroke ( Stroke::pointer x_stroke, Stroke::pointer y_stroke );

      /** Draws on the provided context */
      virtual void draw ( Context& cairo ) const;

    protected:
      Stroke::pointer m_x_axis_stroke;
      Stroke::pointer m_y_axis_stroke;
      Stroke::pointer m_x_interval_stroke;
      Stroke::pointer m_y_interval_stroke;
      Stroke::pointer m_border_stroke[ 4 ];
      double m_x_min, m_x_max, m_y_min, m_y_max;
      double m_x_interval, m_y_interval;
      unsigned int m_enabled_axes, m_enabled_borders;

  };

}

#endif
