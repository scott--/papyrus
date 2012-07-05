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
#ifndef PAPYRUSPATH_H
#define PAPYRUSPATH_H

#include <list>
#include <map>
#include <papyrus/shape.h>
#include <papyrus/path_element.h>

namespace Papyrus
{

  /* Forward declaration for svg_transform_parser utility method */
  class Path;

  /** Utility method to parse a SVG transform string into a list of path data elements. */
  std::list<PathElement::pointer> path_data_parser( const char* src );

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Path : public Shape
  {
    protected:
      Path ( const Glib::ustring& id, const char* path, Fill::pointer fill, Stroke::pointer stroke );

      Path( const AttributeValueMap& avmap );

    public:
      PAPYRUS_DRAWABLE(Path);
      
      typedef std::list<PathElement::pointer> Elements;
      typedef Elements::iterator iterator;
      typedef Elements::const_iterator const_iterator;
      typedef Elements::reverse_iterator reverse_iterator;
      typedef Elements::const_reverse_iterator const_reverse_iterator;
      typedef Elements::size_type size_type;
      typedef Elements::reference reference;
      typedef Elements::const_reference const_reference;

      static pointer create ( const char* path=NULL, Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& path, Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& id, const char* path, Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create ( const Glib::ustring& id, const Glib::ustring& path, Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

      static pointer create( const AttributeValueMap& avmap );
      
      ~Path();

      virtual void draw_shape ( Context& cairo ) const;

      iterator begin();

      iterator end();

      const_iterator begin() const;

      const_iterator end() const;

      reverse_iterator rbegin();

      reverse_iterator rend();

      const_reverse_iterator rbegin() const;

      const_reverse_iterator rend() const;

      size_type size() const;

      size_type max_size() const;

      bool empty() const;

      reference front();

      const_reference front() const;

      reference back();

      const_reference back() const;

      void push_front ( PathElement::pointer element );

      void push_front ( PathElementType type, double x=0.0, double y=0.0, double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0 );

      void push_back ( PathElement::pointer element );

      void push_back ( PathElementType type, double x=0.0, double y=0.0, double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0 );

      void pop_front();

      void pop_back();

      iterator insert ( iterator pos, PathElement::pointer element );

      iterator insert ( iterator pos, PathElementType type, double x=0.0, double y=0.0, double x1=0.0, double y1=0.0, double x2=0.0, double y2=0.0 );

//       iterator insert( iterator pos, size_type n, PathElement::pointer element );

      iterator erase ( iterator pos );

      iterator erase ( iterator first, iterator last );

      /** Sets the path elements to the given SVG path string */
      void set( const char* path );

      /** Sets the path elements to the given SVG path string */
      void set( const Glib::ustring& path );

      virtual void set( const AttributeValueMap& avmap );

      void clear();

      void remove ( PathElement::pointer element );

      void reverse();

      virtual Glib::ustring svg(unsigned depth=0);

    protected:
      Elements m_elements;

  };

}

#endif
