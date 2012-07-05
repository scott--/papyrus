/***************************************************************************
 *   Copyright (C) 2007 by Rick L. Vinyard, Jr.                            *
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
#include "path.h"

namespace Papyrus
{

  Path::Path ( const Glib::ustring& id, const char* path, Fill::pointer fill, Stroke::pointer stroke ):
      Shape ( id, fill, stroke )
  {
    if ( path != NULL )
      m_elements = path_data_parser(path);
  }

  Path::Path( const AttributeValueMap& avmap )
  {
    this->set( avmap );
  }

  Path::pointer Path::create ( const char* path, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Path ( Glib::ustring(), path, fill, stroke ) );
  }

  Path::pointer Path::create ( const Glib::ustring& path, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Path ( Glib::ustring(), path.c_str(), fill, stroke ) );
  }

  Path::pointer Path::create ( const Glib::ustring& id, const char* path, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Path ( id, path, fill, stroke ) );
  }

  Path::pointer Path::create ( const Glib::ustring& id, const Glib::ustring& path, Fill::pointer fill, Stroke::pointer stroke )
  {
    PAPYRUS_CREATE ( Path ( id, path.c_str(), fill, stroke ) );
  }

  Path::pointer Path::create( const AttributeValueMap& avmap )
  {
    PAPYRUS_CREATE( Path( avmap ) );
  }

  Path::~Path()
  {}

  void Path::draw_shape ( Context& cairo ) const
  {
    Elements::const_iterator iter;
    PathElement::pointer previous;
    for ( iter = m_elements.begin(); iter != m_elements.end(); iter++ )
    {
      ( *iter )->render ( cairo, previous );
      previous = *iter;
    }
  }

  Path::iterator Path::begin()
  {
    return m_elements.begin();
  }

  Path::iterator Path::end()
  {
    return m_elements.end();
  }

  Path::const_iterator Path::begin() const
  {
    return m_elements.begin();
  }

  Path::const_iterator Path::end() const
  {
    return m_elements.end();
  }

  Path::reverse_iterator Path::rbegin()
  {
    return m_elements.rbegin();
  }

  Path::reverse_iterator Path::rend()
  {
    return m_elements.rend();
  }

  Path::const_reverse_iterator Path::rbegin() const
  {
    return m_elements.rbegin();
  }

  Path::const_reverse_iterator Path::rend() const
  {
    return m_elements.rend();
  }

  Path::size_type Path::size() const
  {
    return m_elements.size();
  }

  Path::size_type Path::max_size() const
  {
    return m_elements.max_size();
  }

  bool Path::empty() const
  {
    return m_elements.empty();
  }

  Path::reference Path::front()
  {
    return m_elements.front();
  }

  Path::const_reference Path::front() const
  {
    return m_elements.front();
  }

  Path::reference Path::back()
  {
    return m_elements.back();
  }

  Path::const_reference Path::back() const
  {
    return m_elements.back();
  }

  void Path::push_front ( PathElement::pointer element )
  {
    if ( ! element ) return;
    m_elements.push_front ( element );
    this->shape_changed();
  }

  void Path::push_front ( PathElementType type, double x, double y, double x1, double y1, double x2, double y2 )
  {
    this->push_front ( PathElement::create ( type, x, y, x1, y1, x2, y2 ) );
  }

  void Path::push_back ( PathElement::pointer element )
  {
    if ( ! element ) return;
    m_elements.push_back ( element );
    this->shape_changed();
  }

  void Path::push_back ( PathElementType type, double x, double y, double x1, double y1, double x2, double y2 )
  {
    this->push_back ( PathElement::create ( type, x, y, x1, y1, x2, y2 ) );
  }

  void Path::pop_front()
  {
    m_elements.pop_front();
    this->shape_changed();
  }

  void Path::pop_back()
  {
    m_elements.pop_back();
    this->shape_changed();
  }

  Path::iterator Path::insert ( iterator pos, PathElement::pointer element )
  {
    if ( ! element ) return m_elements.end();
    iterator retval = m_elements.insert ( pos, element );
    this->shape_changed();
    return retval;
  }

  Path::iterator Path::insert ( iterator pos, PathElementType type, double x, double y, double x1, double y1, double x2, double y2 )
  {
    return this->insert ( pos, PathElement::create ( type, x, y, x1, y1, x2, y2 ) );
  }

// Path::iterator Path::insert(iterator pos, size_type n, PathElement::pointer element)
// {
  // TODO this needs to clone the elements n times
//   iterator retval = m_elements.insert(pos, n, element);
//  this->invalidate_extents();
//   this->redraw();
//   return retval;
// }

  Path::iterator Path::erase ( iterator pos )
  {
    iterator retval = m_elements.erase ( pos );
    this->shape_changed();
    return retval;
  }

  Path::iterator Path::erase ( iterator first, iterator last )
  {
    iterator retval = m_elements.erase ( first, last );
    this->shape_changed();
    return retval;
  }

  void Path::set(const char * path)
  {
    m_elements = path_data_parser(path);
    this->shape_changed();
  }

  void Path::set(const Glib::ustring & path)
  {
    m_elements = path_data_parser(path.c_str());
    this->shape_changed();
  }

  void Path::set( const AttributeValueMap& avmap )
  {
    Shape::set( avmap );
    
    AttributeValueMap::const_iterator i;
    for ( i = avmap.begin(); i != avmap.end(); i++ )
    {
      if      ( strcaseeq( i->first, "d" ) )       m_elements = path_data_parser( i->second.c_str() );
      // TODO pathLength
    }
    this->shape_changed();
  }

  void Path::clear()
  {
    m_elements.clear();
    this->shape_changed();
  }

  void Path::remove ( PathElement::pointer element )
  {
    m_elements.remove ( element );
    this->shape_changed();
  }

  void Path::reverse()
  {
    m_elements.reverse();
    this->shape_changed();
  }


  Glib::ustring Path::svg(unsigned depth)
  {
    Glib::ustring s;
    iterator i;

    s += svg_spacing(depth) + "<path " + svg_id();

    s += svg_transform();

    s += svg_fill();
    
    if ( ! m_elements.empty() )
      s += " d=\"\n";
    
    for ( i = m_elements.begin(); i != m_elements.end(); i++ )
      s += (*i)->svg(depth+1);

    if ( ! m_elements.empty() )
      s += svg_spacing(depth+1) + "\"\n";

    s += svg_spacing(depth) + " />\n";
    
    return s;
  }

}

