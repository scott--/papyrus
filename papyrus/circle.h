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
#ifndef PAPYRUSCIRCLE_H
#define PAPYRUSCIRCLE_H

#include <papyrus/shape.h>

/**
 * \page guide_circle Circles
 * A circle is drawn centered on the x,y coordinate with a specified radius.
 *
 * The following contains an example that will add a green circle with a black
 * border to a canvas. The blue lines represent the
 * x and y axes, and show through since an alpha value of 0.9 is used.
 *
 * \image html circle.png "Circle drawn by example code below"
 *
 * \dontinclude factory.cpp
 * \skip example_circle
 * \until }
 *
 */

namespace Papyrus
{

  /**
   * A circle is drawn centered on the x,y coordinate with a specified radius.
   *
   * The circle class is a very thin interface for a 360' arc, and doesn't actually extend
   * the arc in any meaningful way, but is provided for convenience and notation.
   *
   * \image html circle.png "Circle"
   *
   * @author Rick L Vinyard Jr
   */
  class Circle : public Shape
  {
    protected:

      Circle ( const Glib::ustring& id, double radius, Fill::pointer fill, Stroke::pointer stroke );

      Circle( const AttributeValueMap& avmap );

    public:
      PAPYRUS_DRAWABLE(Circle);

      /** Creates a circle with the specified radius */
      static Circle::pointer create ( double radius = 1.0,
                                      Fill::pointer fill = Fill::pointer(),
                                      Stroke::pointer stroke = Stroke::pointer()
                                    );

      /** Creates a circle with the specified radius */
      static Circle::pointer create ( const Glib::ustring& id,
                                      double radius = 1.0,
                                      Fill::pointer fill = Fill::pointer(),
                                      Stroke::pointer stroke = Stroke::pointer()
                                    );

      static Circle::pointer create( const AttributeValueMap& avmap );

      virtual ~Circle();

      virtual void set( const AttributeValueMap& avmap );

      /** Returns the radius of this arc */
      double radius() const;

      /** Sets the radius to r */
      void set_radius ( double r );

      /** Signal emitted when the radius is changed */
      sigc::signal<void> signal_radius();

      /** Draws on the provided context */
      virtual void draw_shape( Context& cairo ) const;

      virtual Glib::ustring svg ( unsigned depth=0 );

    protected:
      
      /** The radius of the arc */
      double m_radius;

      /** Signal emitted when the radius is changed */
      sigc::signal<void> m_signal_radius;

      /** Reimplments the extent calculation to optimize quick extents without rendering to the sidebuffer */
      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

  };

}

#endif
