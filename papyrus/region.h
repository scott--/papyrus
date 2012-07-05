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
#ifndef PAPYRUSREGION_H
#define PAPYRUSREGION_H

#include <cairomm/cairomm.h>

#include <papyrus/object.h>
#include <papyrus/matrix.h>

namespace Papyrus
{

  /**
   * This class defines a region with left and right sides and width and height.
   *
   * A region is invalid if @b any aspect (l,r,w,h) evaluates to NAN.
   *
   * @author Rick L Vinyard Jr
   */
  class Region: public sigc::trackable
  {
    public:

      Region ( double x=NAN, double y=NAN, double w=NAN, double h=NAN );

      virtual ~Region();

      double x() const;
      double y() const;
      double width() const;
      double height() const;

      void xywh ( double& x, double& y, double& w, double& h ) const;

      double left() const;
      double right() const;
      double top() const;
      double bottom() const;
      void lrtb ( double& l, double& r, double& t, double& b ) const;
      void set_lrtb( double l, double r, double t, double b );

      void center ( double& x, double& y ) const;


      void set_x ( double x );
      void set_y ( double y );
      void set_width ( double w );
      void set_height ( double h );
      void set_xywh ( double x, double y, double w, double h );

      /** Sets all parameters to NAN */
      void invalidate();

      /**
       * Expands this region to include region other.
       * 
       * @return true if inclusion of region other caused a change in this region, false otherwise
       * @param other At a minimum must have valid (x,y) coordinates
       *
       * 
       */
      bool include ( const Region& other );

      /**
       * Expands this region to include the point (x,y)
       * @return true if inclusion of the point(x,y) caused a changed in this region, false otherwise
       * @return false if both parameters x and y are NAN.
       */
      bool include ( double x, double y );

      /**
       * Expands this region to include x between m_x and m_x + m_w
       * @return true if the inclusion caused a change in this region, or false if no change occurred or x is NAN
       */
      bool include_x ( double x );

      /**
       * Expands this region to include y between m_y and m_y + m_h
       * @return true if the inclusion caused a change in this region, or false if no change occurred or y is NAN
       */
      bool include_y ( double y );

      void left_bottom ( double& l, double& b ) const;
      void right_top ( double& r, double& t ) const;

      Region& operator= ( const Region& other );

      /** true if the regions are identical */
      bool operator== ( const Region& other ) const;

      bool operator!= ( const Region& other ) const;

      /** true if this region is completely contained within the other region */
      bool operator< ( const Region& other ) const;

      bool operator<= ( const Region& other ) const;

      /** true of this region is completely outside the other region */
      bool operator> ( const Region& other ) const;

      bool operator>= ( const Region& other ) const;

      operator bool() const;

      /** true if (x,y) is an interior point of or on the boundary of this region */
      bool is_inside ( double x, double y ) const ;

      /** true if (x,y) is an interior point of this region */
      bool is_interior ( double x, double y ) const ;

      /** true if (x,y) is a boundary point of this region */
      bool is_boundary ( double x, double y ) const ;

      /** true if any part of this region overlaps the other region */
      bool overlaps( const Region& other ) const;

      void transform ( const Matrix& matrix );

      sigc::signal<void>& signal_changed();

    protected:
      double m_x, m_y, m_w, m_h;
      bool m_suppress_change_signal;
      sigc::signal<void> m_signal_changed;

      bool include_point(double x, double y);

      
  };

}

#endif
