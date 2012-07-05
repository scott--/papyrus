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
#ifndef PAPYRUSLINEARGRADIENT_H
#define PAPYRUSLINEARGRADIENT_H

#include <papyrus/primitives.h>
#include <papyrus/gradient.h>

namespace Papyrus
{

  /**
   * Linear gradients
   * 
   * This is similar to the cairo linear gradient class. However,
   * several items have been added to support SVG style gradients.
   * 
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class LinearGradient : public Gradient
  {
    public:
      struct Point: public Papyrus::Point {
        Point( double x=0.0, double y=0.0, Quantity q=ABSOLUTE ): Papyrus::Point(x,y), quantity_x(q), quantity_y(q) { }
        Point( double x, double y, Quantity qx, Quantity qy ): Papyrus::Point(x,y), quantity_x(qx), quantity_y(qy) { }
        Point( const Papyrus::Point& p, Quantity q=ABSOLUTE ): Papyrus::Point(p), quantity_x(q), quantity_y(q) { }
        Point( const Papyrus::Point& p, Quantity qx, Quantity qy ): Papyrus::Point(p), quantity_x(qx), quantity_y(qy) { }
        Point( const Point& p ): Papyrus::Point(p), quantity_x(p.quantity_x), quantity_y(p.quantity_y) { }

        bool has_percent() { return quantity_x == PERCENT or quantity_y == PERCENT; }

        Quantity quantity_x, quantity_y;

      };

      struct Vector: public LineSegment<Point> {
        Vector ( double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0, Quantity q=ABSOLUTE ): p0(x1,y1,q), p1(x2,y2,q) { }
        Vector ( const Papyrus::Point& point0, const Papyrus::Point& point1, Quantity q=ABSOLUTE ): p0(point0,q), p1(point1,q) { }
        Vector ( const Point& point0, const Point& point1 ): p0(point0), p1(point1) { }
        Vector ( const Vector& v ): p0(v.p0), p1(v.p1) { }
        
        Point p0, p1;

        bool has_percent() { return p0.has_percent() or p1.has_percent(); }

        void invalidate() { p0.invalidate(); p1.invalidate(); }

        operator bool() { return ( p0 and p1 ); }

        Point& operator [](int i) { if ( i <= 0 ) return p0; else return p1; }
        const Point& operator [](int i) const { if ( i <= 0 ) return p0; else return p1; }
     };
      

    protected:
      LinearGradient(const Vector& v);
      
    public:
      PAPYRUS_RENDERABLE(LinearGradient);

      static pointer create( double x0, double y0, double x1, double y1, Quantity q=ABSOLUTE );
      static pointer create( const Papyrus::Point& p0, const Papyrus::Point& p1, Quantity q=ABSOLUTE );
      static pointer create( const Point& p0, const Point& p1 );
      static pointer create( const Vector& v );
      
      virtual ~LinearGradient();

      const Vector& vector() const;

      void set_vector( const Vector& v );
      
      virtual void render ( Context& cairo ) const;
    
    protected:
      Vector m_vector;
  };

}

#endif
