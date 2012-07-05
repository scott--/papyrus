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
#include "region.h"

#include <algorithm>
#include <assert.h>

namespace Papyrus
{

  Region::Region ( double x, double y, double w, double h ) :
      m_x ( x ),
      m_y ( y ),
      m_w ( w ),
      m_h ( h ),
      m_suppress_change_signal(false) {}

  Region::~Region() {}

  double Region::x() const
  {
    return m_x;
  }
  double Region::y() const
  {
    return m_y;
  }
  double Region::width() const
  {
    return m_w;
  }
  double Region::height() const
  {
    return m_h;
  }

  void Region::xywh ( double& x, double& y, double& w, double& h ) const
  {
    x = m_x;
    y = m_y;
    w = m_w;
    h = m_h;
  }

  void Region::set_x ( double x )
  {
    m_x = x;
    m_signal_changed.emit();
  }

  void Region::set_y ( double y )
  {
    m_y = y;
    m_signal_changed.emit();
  }

  void Region::set_width ( double width )
  {
    m_w = width;
    m_signal_changed.emit();
  }

  void Region::set_height ( double height )
  {
    m_h = height;
    m_signal_changed.emit();
  }

  void Region::set_xywh ( double x, double y, double w, double h )
  {
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
    m_signal_changed.emit();
  }

  void Region::invalidate()
  {
    m_x = m_y = m_w = m_h = NAN;
    m_signal_changed.emit();
  }

  Region& Region::operator= ( const Region& other )
  {
    if ( *this == other )
      return *this;
    m_x = other.m_x;
    m_y = other.m_y;
    m_w = other.m_w;
    m_h = other.m_h;
    m_signal_changed.emit();
    return *this;
  }

  bool Region::operator== ( const Region& other ) const
  {
    return ( m_x == other.m_x and m_y == other.m_y and m_w == other.m_w and m_h == other.m_h );
  }

  bool Region::operator!= ( const Region& other ) const
  {
    return ! ( *this == other );
  }

  bool Region::operator< ( const Region& other ) const
  {
    if ( not *this ) return false;
    if ( not other ) return false;
    
    return (
               m_x < other.m_x and
               m_y < other.m_y and
               m_w > other.m_w and
               m_h > other.m_h
           );
  }

  bool Region::operator<= ( const Region& other ) const
  {
    if ( not *this ) return false;
    if ( not other ) return false;
    
    return (
               m_x <= other.m_x and
               m_y <= other.m_y and
               m_w >= other.m_w and
               m_h >= other.m_h
           );
  }

  bool Region::operator> ( const Region& other ) const
  {
    if ( not *this ) return false;
    if ( not other ) return false;
    
    return ( not *this <= other );
  }

  bool Region::operator>= ( const Region& other ) const
  {
    if ( not *this ) return false;
    if ( not other ) return false;
    
    return ( not *this < other );
  }

  Region::operator bool() const
  {
    if ( isnan ( m_x ) or isnan ( m_y ) or isnan ( m_w ) or isnan ( m_h ) ) return false;
    return true;
  }

  bool Region::include ( const Region& other )
  {
    bool changed, changed_left, changed_right, changed_top, changed_bottom;
    
    m_suppress_change_signal = true;

    changed_left = this->include_x(other.left());
    changed_right = this->include_x(other.right());
    changed_top = this->include_y(other.top());
    changed_bottom = this->include_y(other.bottom());

    m_suppress_change_signal = false;

    changed = changed_left or changed_right or changed_top or changed_bottom;

    if ( changed ) m_signal_changed.emit();

    return changed;
  }

  bool Region::include ( double x, double y )
  {
    bool changed, changed_x, changed_y;
    
    m_suppress_change_signal = true;

    changed_x = this->include_x(x);
    changed_y = this->include_y(y);

    m_suppress_change_signal = false;

    changed = changed_x or changed_y;
    
    if ( changed ) m_signal_changed.emit();

    return changed;
  }

  bool Region::include_x ( double x )
  {
    bool changed = false;

    // If x is NAN then we can't do anything
    if ( isnan(x) ) return false;

    // If m_x is invalid then we now have a valid x and a width of 0
    if ( isnan(m_x) )
    {
      m_x = x;
      m_w = 0.0;
      changed = true;
    }
    // But, if we got here we already have a valid x
    else
    {
      // If width wasn't already set, let's set it to zero
      if ( isnan(m_w) ) m_w = 0.0;

      // Now, determine where the included x is in relation to the old left and right
      if ( x < m_x )
      {
        m_w = m_x + m_w - x;
        m_x = x;
        changed = true;
      }
      else if ( x > m_x + m_w )
      {
        m_w = x - m_x;
        changed = true;
      }
      // else the x was already included
    }
    
    if ( changed and not m_suppress_change_signal ) m_signal_changed.emit();

    return changed;
  }

  bool Region::include_y ( double y )
  {
    bool changed = false;

    // If y is NAN then we can't do anything
    if ( isnan(y) ) return false;

    // If m_y is invalid then we now have a valid y and a height of 0
    if ( isnan(m_y) )
    {
      m_y = y;
      m_h = 0.0;
      changed = true;
    }
    // But, if we got here we already have a valid y
    else
    {
      // If height wasn't already set, let's set it to zero
      if ( isnan(m_h) ) m_h = 0.0;

      // Now, determine where the included y is in relation to the old top and bottom
      if ( y < m_y )
      {
        m_h = m_y + m_h - y;
        m_y = y;
        changed = true;
      }
      else if ( y > m_y + m_h )
      {
        m_h = y - m_y;
        changed = true;
      }
      // else the y was already included
    }
    
    if ( changed and not m_suppress_change_signal ) m_signal_changed.emit();

    return changed;
  }

  bool Region::is_inside ( double x, double y ) const
  {
    return (
               x >= m_x        and
               x <= m_x + m_w  and
               y >= m_y        and
               y <= m_y + m_h
           );
  }

  bool Region::is_interior ( double x, double y ) const
  {
    return (
               x > m_x        and
               x < m_x + m_w  and
               y > m_y        and
               y < m_y + m_h
           );
  }

  bool Region::is_boundary ( double x, double y ) const
  {
    return (
               x == m_x        or
               x == m_x + m_w  or
               y == m_y        or
               y == m_y + m_h
           );
  }

  bool Region::overlaps(const Region & other) const
  {
    return (
            m_x >= other.m_x                    or
            m_x <= other.m_x + other.m_w        or
            m_x + m_w >= other.m_x              or
            m_x + m_w <= other.m_x + other.m_w  or
            m_y >= other.m_y                    or
            m_y <= other.m_y + other.m_h        or
            m_y + m_h >= other.m_y              or
            m_y + m_h <= other.m_y + other.m_h
           );
  }
  
  void Region::transform ( const Matrix& matrix )
  {
    if ( ! *this ) return;

    double x[4] = {m_x, m_x,     m_x+m_w, m_x+m_w};
    double y[4] = {m_y, m_y+m_h, m_y,     m_y+m_h};
    double xmin, xmax, ymin, ymax;

    for ( int i=0; i < 4; i++ )
      matrix.transform_point ( x[i], y[i] );

    xmin = xmax = x[0];
    ymin = ymax = y[0];

    for ( int i=1; i < 4; i++ )
    {
      xmin = std::min ( xmin, x[i] );
      xmax = std::max ( xmax, x[i] );
      ymin = std::min ( ymin, y[i] );
      ymax = std::max ( ymax, y[i] );
    }

    m_x = xmin;
    m_y = ymin;
    m_w = xmax - xmin;
    m_h = ymax - ymin;

    m_signal_changed.emit();
  }

  double Region::left( ) const
  {
    return m_x;
  }

  double Region::right( ) const
  {
    return m_x + m_w;
  }

  double Region::top( ) const
  {
    return m_y;
  }

  double Region::bottom( ) const
  {
    return m_y + m_h;
  }

  void Region::lrtb ( double & l, double & r, double & t, double & b ) const
  {
    l = m_x;
    r = m_x + m_w;
    t = m_y;
    b = m_y + m_h;
  }

  void Region::set_lrtb(double l, double r, double t, double b)
  {
    this->set_xywh(l, t, r-l, b-t);
  }

  void Region::center ( double & x, double & y ) const
  {
    x = m_x + m_w / 2.0;
    y = m_y + m_h / 2.0;
  }

  bool Region::include_point ( double x, double y )
  {
    bool changed = false;

    if ( isnan ( x ) )
    {
      if ( isnan ( y ) ) return false;

      // x = nan, y != nan

      if ( isnan ( m_y ) ) // if m_y is nan then we'll just run with the y value for m_y
      {
        // These are pretty obvious from the if statements, but we'll just recap
        // in assert statements rather than comments
        assert( isnan(x) );
        assert( ! isnan(y) );
        assert( isnan(m_y) );
        m_y = y;
        changed = true;
      }
      else if ( y < m_y ) // but, if m_y != nan then we need to find out if y is less
      {
        // now we need to find out whether m_h needs to be expanded or calculated
        if ( isnan( m_h ) ) 
          m_h = m_y - y; // if m_h = nan then we need to calculate m_h
        else
          m_h += m_y - y; // but if m_h != nan then we need to expand it
          
        m_y = y; // we also need to set the lower bound to y
        changed = true;
      }
      else if ( isnan ( m_h ) )
      {
        // if 
      }
      else if ( y > m_y + m_h )
      {
        m_h = y - m_y;
        changed = true;
      }
      /* else y is contained between m_y and m_y + m_h */

      return changed;
    }

    if ( isnan ( y ) )
    {
      if ( isnan ( m_x ) )
      {
        m_x = x;
        changed = true;
      }
      else if ( x < m_x )
      {
        m_w += m_x - x;
        m_x = x;
        changed = true;
      }
      else if ( ! isnan ( m_w ) and x > m_x + m_w )
      {
        m_w = x - m_x;
        changed = true;
      }
      /* else x is contained between m_x and m_x + m_w */

      return changed;
    }

    if ( isnan ( m_x ) or isnan ( m_y ) )
    {
      m_x = x;
      m_y = y;
      changed = true;
    }
    else
    {
      if ( isnan ( m_w ) )
      {
        if ( x < m_x )
        {
          m_w = m_x - x;
          m_x = x;
          changed = true;
        }
        else /* x >= m_x */
        {
          m_w = x - m_x;
          changed = true;
        }
      }
      else /* m_w != nan */
      {
        if ( x < m_x )
        {
          m_w += m_x - x;
          m_x = x;
          changed = true;
        }
        else if ( x > m_x + m_w )
        {
          m_w = x - m_x;
          changed = true;
        }
        /* else x is contained between m_x and m_x + m_w */
      }

      if ( isnan ( m_h ) )
      {
        if ( y < m_y )
        {
          m_h = m_y - y;
          m_y = y;
          changed = true;
        }
        else /* y >= m_y */
        {
          m_h = y - m_y;
          changed = true;
        }
      }
      else /* m_h != nan */
      {
        if ( y < m_y )
        {
          m_h += m_y - y;
          m_y = y;
          changed = true;
        }
        else if ( y > m_y + m_h )
        {
          m_h = y - m_y;
          changed = true;
        }
        /* else y is contained between m_y and m_y + m_h */
      }
    }

    return changed;
  }

  sigc::signal< void >& Region::signal_changed()
  {
    return m_signal_changed;
  }

}


