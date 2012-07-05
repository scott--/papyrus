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
#ifndef PAPYRUSPRIMITIVES_H
#define PAPYRUSPRIMITIVES_H

#include <cmath>

namespace Papyrus
{
  /**
   * A very simple point primitive with x and y values as doubles.
   *
   * Provides for invalidation and boolean tests of invalidation using the
   * NAN constant.
   */
  struct Point {
    Point( double xval=0.0, double yval=0.0 ): x(xval), y(yval) { }
    Point( const Point& p ): x(p.x), y(p.y) { }

    double x;
    double y;

    void invalidate() { x = NAN; y = NAN; }

    virtual operator bool() { return ( not isnan(x) and not isnan(y) ); }
  };

  /**
   * A very simple line segment primitive template.
   *
   * This is templatized to allow the point primitive to vary.
   *
   * The point type must support an \c invalidate() method as well
   * as \c operator \c bool(). Anything derived from Point will
   * work.
   */
  template<typename PointType>
  struct LineSegment {
    LineSegment ( double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0 ): p0(x1,y1), p1(x2,y2) { }
    LineSegment ( const PointType& point0, const PointType& point1 ): p0(point0), p1(point1) { }
    LineSegment ( const LineSegment& l ): p0(l.p0), p1(l.p1) { }
    
    PointType p0, p1;

    void invalidate() { p0.invalidate(); p1.invalidate(); }

    operator bool() { return ( p0 and p1 ); }

    PointType& operator [](int i) { if ( i <= 0 ) return p0; else return p1; }
    const PointType& operator [](int i) const { if ( i <= 0 ) return p0; else return p1; }
  };
  
}

#endif
