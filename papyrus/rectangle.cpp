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
#include "rectangle.h"

#include <cmath>
#include <sstream>

namespace Papyrus
{

  Rectangle::Rectangle ( const Glib::ustring& id, double x, double y, double w, double h, Fill::pointer fill, Stroke::pointer stroke ) :
      Shape ( id, fill, stroke ),
      m_width ( w ),
      m_height ( h ),
      m_corner_radius( NAN )
  {
    this->set_x(x);
    this->set_y(y);
  }

  Rectangle::Rectangle( const AttributeValueMap& avmap ):
      m_width( 0.0 ),
      m_height( 0.0 ),
      m_corner_radius( NAN )
  {
    this->set( avmap );
  }

  Rectangle::pointer Rectangle::create ( double x, double y, double w, double h, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Rectangle ( Glib::ustring(), x, y, w, h, fill, stroke ) );
  }

  Rectangle::pointer Rectangle::create ( double w, double h, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Rectangle ( Glib::ustring(), 0.0, 0.0, w, h, fill, stroke ) );
  }

  Rectangle::pointer Rectangle::create ( const Glib::ustring& id,
                                         double x,
                                         double y,
                                         double w,
                                         double h,
                                         Fill::pointer fill,
                                         Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Rectangle ( id, x, y, w, h, fill, stroke ) );
  }

  Rectangle::pointer Rectangle::create ( const Glib::ustring& id, double w, double h, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Rectangle ( id, 0.0, 0.0, w, h, fill, stroke ) );
  }

  Rectangle::pointer Rectangle::create( const AttributeValueMap& avmap )
  {
    PAPYRUS_CREATE( Rectangle( avmap ) );
  }

  Rectangle::~Rectangle()
  {}

  void Rectangle::set( const AttributeValueMap& avmap )
  {
    Shape::set( avmap );
    
    AttributeValueMap::const_iterator i;
    for ( i = avmap.begin(); i != avmap.end(); i++ )
    {
      if ( strcaseeq( i->first, "width" ) )   this->set_width( atof( i->second.c_str() ) );
      else if ( strcaseeq( i->first, "height" ) )  this->set_height( atof( i->second.c_str() ) );
    }
  }

  double Rectangle::width()
  {
    return m_width;
  }

  double Rectangle::height()
  {
    return m_height;
  }

  void Rectangle::xywh ( double& x, double& y, double& w, double& h )
  {
    x = Drawable::x();
    y = Drawable::y();
    w = m_width;
    h = m_height;
  }

  void Rectangle::set_width ( double w )
  {
    m_width = w;
    this->freeze();
    set_centroid_x( m_width / 2.0 );
    this->shape_changed();
    this->thaw();
    m_signal_size.emit();
  }

  void Rectangle::set_height ( double h )
  {
    m_height = h;
    this->freeze();
    set_centroid_y( m_height / 2.0 );
    this->shape_changed();
    this->thaw();
    m_signal_size.emit();
  }

  void Rectangle::set_xywh ( double x, double y, double w, double h )
  {
    this->freeze();
    set_x( x );
    set_y( y );
    m_width = w;
    m_height = h;
    set_centroid( m_width / 2.0, m_height / 2.0 );
    this->shape_changed();
    this->thaw();
    m_signal_size.emit();
  }

  void Rectangle::set_xywh ( const Region& r )
  {
    double x, y, w, h;
    r.xywh( x, y, w, h );
    this->set_xywh(x, y, w, h);
  }

  double Rectangle::corner_radius()
  {
    return m_corner_radius;
  }

  void Rectangle::set_corner_radius(double r)
  {
    if ( r < 0.0 ) r = NAN;
    else m_corner_radius = r;
    this->shape_changed();
  }

  void Rectangle::unset_corner_radius()
  {
    m_corner_radius = NAN;
    this->shape_changed();
  }

  void Rectangle::draw_shape ( Context& cairo ) const
  {
    if ( not isnan(m_corner_radius) )
    {
      double r = m_corner_radius;
      if ( (r > m_width / 2.0 ) || ( r > m_height / 2.0 ) )
            r = std::min( m_width/2.0, m_height/2.0 );
      cairo->move_to( r, 0.0 );
      cairo->line_to( m_width - r, 0.0 );
      cairo->arc( m_width - r, r, r, -M_PI_2, 0.0 );
      cairo->line_to( m_width, m_height - r );
      cairo->arc( m_width - r, m_height - r, r, 0.0, M_PI_2 );
      cairo->line_to( r, m_height );
      cairo->arc( r, m_height - r, r, M_PI_2, M_PI );
      cairo->line_to( 0.0, r );
      cairo->arc( r, r, r, -M_PI, -M_PI_2 );
      cairo->close_path(); 
    }
    else
    {
      cairo->rectangle ( 0.0, 0.0, m_width, m_height );
    }
    
  }

  Glib::ustring Rectangle::svg(unsigned depth)
  {
    std::ostringstream s;

    s << svg_spacing(depth) << "<rect " << svg_id();

    s << svg_transform() << svg_fill();
    
    s << " x=\"" << x() << "\" y=\"" << y() << "\" width=\"" << m_width << "\" height=\"" << m_height << "\" />\n";
    
    return s.str();
  }

  sigc::signal<void> Rectangle::signal_size()
  {
    return m_signal_size;
  }

  Region Rectangle::calculate_extents(const Matrix & m, ExtentsPerformance ep) const
  {
    if ( ep == EXTENTS_QUICK )
    {
      double top    = 0.0,
             right  = m_width,
             bottom = m_height,
             left   = 0.0,
             x, y;

      if ( m_stroke )
      {
        double width = m_stroke->width();
        top -= width;
        right += width;
        bottom += width;
        left -= width;
      }

      Region result;

      x = left; y = top;
      m.transform_point( x, y );
      result.include( x, y );
      
      x = right; y = top;
      m.transform_point( x, y );
      result.include( x, y );
      
      x = left; y = bottom;
      m.transform_point( x, y );
      result.include( x, y );
      
      x = right; y = bottom;
      m.transform_point( x, y );
      result.include( x, y );

      return result;
    }
    else
      return Shape::calculate_extents(m, ep);
  }
  
}

