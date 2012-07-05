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
#include "gradient.h"

namespace Papyrus
{

  Gradient::Gradient(): 
      Paint(),
      m_units(GRADIENT_UNITS_NONE),
      m_spread(GRADIENT_SPREAD_NONE)
  {
    m_transform.signal_changed().connect( sigc::mem_fun( *this, &Gradient::on_transform_changed ) );
  }


  Gradient::~Gradient()
  {
  }

  GradientUnits Gradient::units() const
  {
    if ( m_units == GRADIENT_UNITS_NONE && m_parent ) return m_parent->units();
    return m_units;
  }

  void Gradient::set_units(GradientUnits gu)
  {
    m_units = gu;
    m_signal_changed.emit();
  }

  GradientSpread Gradient::spread() const
  {
    if ( m_spread == GRADIENT_SPREAD_NONE && m_parent ) return m_parent->spread();
    return m_spread;
  }

  void Gradient::set_spread(GradientSpread s)
  {
    m_spread = s;
    m_signal_changed.emit();
  }

  const Matrix & Gradient::transform() const
  {
    return m_transform;
  }

  Matrix & Gradient::transform()
  {
    return m_transform;
  }

  void Gradient::set_transform(const Matrix & m)
  {
    m_transform = m;
    // changed signal of this gradient is emitted through on_transform_changed() triggered by assignment
  }

  Gradient::pointer Gradient::parent()
  {
    return m_parent;
  }

  void Gradient::set_parent(Gradient::pointer p)
  {
    m_parent_changed_connection.disconnect();
    m_parent = p;
    if ( m_parent )
      m_parent_changed_connection = m_parent->signal_changed().connect( sigc::mem_fun(*this, &Gradient::on_parent_changed) );
    m_signal_changed.emit();
  }
  
  Gradient::Stop::Stop() :
      m_offset_set ( false ), m_color_set ( false ), m_alpha_set ( false ),
      m_offset ( 0.0 ),
      m_color ( 0.0, 0.0, 0.0 ),
      m_alpha ( 1.0 )
  {
  }

  Gradient::Stop::Stop ( const RGBA & rgba, double offset ) :
      m_offset_set ( true ), m_color_set ( true ), m_alpha_set ( false ),
      m_offset ( offset ),
      m_color ( rgba ),
      m_alpha ( 1.0 )
  {
  }

  Gradient::Stop::Stop ( const RGBA & rgba, double offset, double alpha ) :
      m_offset_set ( true ), m_color_set ( true ), m_alpha_set ( true ),
      m_offset ( offset ),
      m_color ( rgba ),
      m_alpha ( alpha )
  {
  }

  Gradient::Stop::Stop ( const Glib::ustring & id ) :
      Object ( id ),
      m_offset_set ( false ), m_color_set ( false ), m_alpha_set ( false ),
      m_offset ( 0.0 ),
      m_color ( 0.0, 0.0, 0.0 ),
      m_alpha ( 1.0 )
  {
  }

  Gradient::Stop::Stop ( const Glib::ustring & id, const RGBA & rgba, double offset ) :
      Object ( id ),
      m_offset_set ( true ), m_color_set ( true ), m_alpha_set ( false ),
      m_offset ( offset ),
      m_color ( rgba ),
      m_alpha ( 1.0 )
  {
  }

  Gradient::Stop::Stop ( const Glib::ustring & id, const RGBA & rgba, double offset, double alpha ) :
      Object ( id ),
      m_offset_set ( true ), m_color_set ( true ), m_alpha_set ( true ),
      m_offset ( offset ),
      m_color ( rgba ),
      m_alpha ( alpha )
  {
  }

  Gradient::Stop::~Stop()
  {
  }

  double Gradient::Stop::offset() const
  {
    return m_offset;
  }

  void Gradient::Stop::set_offset ( double off )
  {
    if ( off < 0.0 )
    {
      m_offset = 0.0;
      m_offset_set = false;
      return;
    }

    m_offset = std::min ( off, 1.0 );
    m_offset_set = true;
  }

  const RGBA & Gradient::Stop::color() const
  {
    return m_color;
  }

  RGBA & Gradient::Stop::color()
  {
    return m_color;
  }

  void Gradient::Stop::set_color ( const RGBA & rgba )
  {
    m_color = rgba;
    m_color_set = true;
  }

  void Gradient::Stop::unset_color()
  {
    m_color = RGBA ( 0.0, 0.0, 0.0 );
    m_color_set = false;
  }

  double Gradient::Stop::red() const
  {
    return m_color.red;
  }

  double Gradient::Stop::green() const
  {
    return m_color.green;
  }

  double Gradient::Stop::blue() const
  {
    return m_color.blue;
  }

  double Gradient::Stop::alpha() const
  {
    if ( m_alpha_set ) return m_alpha;
    return m_color.alpha;
  }

  void Gradient::Stop::set_alpha ( double opa )
  {
    if ( opa < 0.0 )
    {
      m_alpha = 1.0;
      m_alpha_set = false;
      return;
    }

    m_alpha = std::min ( opa, 1.0 );
    m_alpha_set = true;
  }

  const Gradient::Stops& Gradient::stops() const
  {
    if ( m_stops.size() == 0 and m_parent ) return m_parent->stops();
    return m_stops;
  }

  void Gradient::insert(Stops::iterator pos, const Stop & s)
  {
    m_stops.insert(pos, s);
    m_signal_changed.emit();
  }

  void Gradient::push_back(const Stop & s)
  {
    m_stops.push_back(s);
    m_signal_changed.emit();
  }

  void Gradient::push_front(const Stop & s)
  {
    m_stops.insert(m_stops.begin(), s);
    m_signal_changed.emit();
  }

  void Gradient::clear_stops()
  {
    m_stops.clear();
    m_signal_changed.emit();
  }

  void Gradient::remove(Stops::iterator pos)
  {
    m_stops.erase(pos);
    m_signal_changed.emit();
  }

  void Gradient::on_parent_changed()
  {
    m_signal_changed.emit();
  }
  
  void Gradient::on_transform_changed()
  {
    m_signal_changed.emit();
  }

}

