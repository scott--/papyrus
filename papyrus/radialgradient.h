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
#ifndef PAPYRUSRADIALGRADIENT_H
#define PAPYRUSRADIALGRADIENT_H

#include <papyrus/lineargradient.h>
#include <papyrus/primitives.h>

namespace Papyrus
{

  /**
   * Radial gradients
   * 
   * This is similar to the cairo radial gradient class. However,
   * several items have been added to support SVG style gradients.
   * 
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class RadialGradient : public Gradient
  {
    public:
      struct Circle: public LinearGradient::Point {
        Circle( double x=0.0, double y=0.0, double cr=0.0, Quantity q=ABSOLUTE ): LinearGradient::Point(x,y,q), r(cr), quantity_r(q) { }
        Circle( double x, double y, double cr, Quantity qx, Quantity qy, Quantity qr ): LinearGradient::Point(x,y,qx,qy), r(cr), quantity_r(qr) { }
        Circle( const Papyrus::Point& p, double cr, Quantity q=ABSOLUTE ): LinearGradient::Point(p,q), r(cr), quantity_r(q) { }
        Circle( const Papyrus::Point& p, double cr, Quantity qx, Quantity qy, Quantity qr ): LinearGradient::Point(p,qx,qy), r(cr), quantity_r(qr) { }
        Circle( const Circle& p ): LinearGradient::Point(p), r(p.r), quantity_r(p.quantity_r) { }

        bool has_percent()
        {
          return quantity_x == PERCENT or
              quantity_y == PERCENT or
              quantity_r == PERCENT;
        }

        virtual operator bool() { return ( not isnan(x) and not isnan(y) and not isnan(r) ); }

        double r;
        Quantity quantity_r;
      };

    protected:
      
      RadialGradient(const Circle& outer, const Circle& inner);

    public:
      PAPYRUS_RENDERABLE(RadialGradient);

      static pointer create( double ox, double oy, double orad, Quantity q=ABSOLUTE );
      
      static pointer create( const Circle& outer );
      
      static pointer create( const Circle& outer, const Circle& inner );
      
      virtual ~RadialGradient();

      const Circle& outer_circle() const;

      void set_outer_circle( const Circle& outer );
      
      const Circle& inner_circle() const;

      void set_inner_circle( const Circle& inner );
      
      void set_circles( const Circle& outer, const Circle& inner );
      
      virtual void render ( Context& cairo ) const;

    protected:
      Circle m_outer_circle, m_inner_circle;
  };

}

#endif
