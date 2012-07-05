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
#ifndef PAPYRUSRECTANGLE_H
#define PAPYRUSRECTANGLE_H

#include <papyrus/shape.h>

/**
 * \page guide_rectangle Rectangles
 * A rectangle is drawn with the (x,y) coordinate as the upper left corner, and with a
 * specified width and height.
 *
 * Rotation of a rectangle occurs about a centroid which is defined as the center of the
 * rectangle, or more formally as (x+w/2, y+h/2).
 *
 * The following contains an example that will add a rectangle with a border to a canvas.
 * The blue lines represent the x and y axes, and show through since an alpha value of
 * 0.9 is used.
 *
 * \image html rectangle.png "Rectangle drawn by example code below"
 *
 * \dontinclude factory.cpp
 * \skip example_rectangle
 * \until }
 *
 */

namespace Papyrus
{

  /**
   * A rectangle centered on the x,y coordinate.
   *
   * \image html rectangle.png "Rectangle"
   *
   * @author Rick L Vinyard Jr
   */
  class Rectangle : public Shape
  {
    protected:

      Rectangle ( const Glib::ustring& id,
                  double x,
                  double y,
                  double w,
                  double h,
                  Fill::pointer fill,
                  Stroke::pointer stroke
                );

      Rectangle( const AttributeValueMap& avmap );

    public:
      PAPYRUS_DRAWABLE(Rectangle);

      static Rectangle::pointer create ( double x,
                                         double y,
                                         double w,
                                         double h,
                                         Fill::pointer fill = Fill::pointer(),
                                         Stroke::pointer stroke=Stroke::pointer() );

      /** Creates a rectangle of a specified width and height */
      static Rectangle::pointer create ( double w=0.0,
                                         double h=0.0,
                                         Fill::pointer fill = Fill::pointer(),
                                         Stroke::pointer stroke=Stroke::pointer() );

      static Rectangle::pointer create ( const Glib::ustring& id,
                                         double x,
                                         double y,
                                         double w,
                                         double h,
                                         Fill::pointer fill = Fill::pointer(),
                                         Stroke::pointer stroke=Stroke::pointer() );

      static Rectangle::pointer create ( const Glib::ustring& id,
                                         double w,
                                         double h,
                                         Fill::pointer fill = Fill::pointer(),
                                         Stroke::pointer stroke=Stroke::pointer() );

      static Rectangle::pointer create( const AttributeValueMap& avmap );

      virtual ~Rectangle();

      virtual void set( const AttributeValueMap& avmap );

      /** Returns the width of the rectangle */
      double width();

      /** Returns the height of the rectangle */
      double height();

      /** Fills parameters w and h with the width and height of the rectangle */
      void xywh ( double& x, double& y, double& w, double& h );

      /** Sets the width of the rectangle to w */
      void set_width ( double w );

      /** Sets the height of the rectangle to h */
      void set_height ( double h );

      /**
       * Sets the center of the rectangle to (x,y) and also sets the width
       * and height of the rectangle.
       */
      void set_xywh ( double x, double y, double w, double h );

      void set_xywh ( const Region& r );

      /** If not NAN will draw a rectangle with rounded corners. */
      double corner_radius();
      
      /** Draws a rounded rectangle using the provided radius */
      void set_corner_radius( double r );

      /**
       * Unsets the corner radius
       * 
       * The corner radius can be unset either by:
       * # Use \c unset_corner_radius() to explicitly unset
       * # Set the corner radius to \c NAN or a negative number
       */
      void unset_corner_radius();

      /** Draws on the provided context */
      virtual void draw_shape ( Context& cairo ) const;

      virtual Glib::ustring svg(unsigned depth=0);

      /** signal emitted when the size of the rectangle is changed */
      sigc::signal<void> signal_size();

    protected:

      double m_width, m_height;

      double m_corner_radius;

      sigc::signal<void> m_signal_size;

      /** Reimplments the extent calculation to optimize quick extents without rendering to the sidebuffer */
      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

  };

}

#endif
