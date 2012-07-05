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
#ifndef PAPYRUSOBJECT_H
#define PAPYRUSOBJECT_H

#include <map>
#include <stdint.h>
#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

#include <papyrus/pointer.h>
#include <papyrus/utility.h>

namespace Papyrus
{

  typedef std::map<Glib::ustring,Glib::ustring> AttributeValueMap;

  /**
   * Base object that provides a common concept of a string identifier and a signal
   * emitted when the object is changed.
   *
   * The meaning of 'changed' is dependent upon the interpretation of derived types.
   *
   * @author Rick L Vinyard Jr
   */
  class Object: public sigc::trackable
  {
    protected:
      Object ( const Glib::ustring& id=Glib::ustring() ) :m_id ( id ) { }

      Object ( const AttributeValueMap& avmap ) { this->set( avmap ); }

    public:
      virtual ~Object() { }

      const Glib::ustring& id() const
      {
        return m_id;
      }

      void set_id ( const Glib::ustring& i )
      {
        m_id = i;
        m_signal_id_changed.emit();
      }

      virtual void set( const AttributeValueMap& avmap )
      {
        AttributeValueMap::const_iterator i;

        i = this->find_attribute( avmap, "id" );

        if ( i != avmap.end() ) this->set_id( i->second );
      }

      sigc::signal<void>& signal_changed()
      {
        return m_signal_changed;
      }

      sigc::signal<void>& signal_id_changed()
      {
        return m_signal_id_changed;
      }

    protected:
      Glib::ustring m_id;

      /**
       * Finds an attribute in the Attribute-Value map using caseless comparisons.
       *
       * This is an O(n) operation, so looking up multiple attributes may be much slower than
       * just iterating through the map once.
       */
      AttributeValueMap::const_iterator find_attribute( const AttributeValueMap& avmap, const Glib::ustring& attribute )
      {
        AttributeValueMap::const_iterator i;
        for ( i = avmap.begin(); i != avmap.end(); i++ )
          if ( strcaseeq( i->first, attribute ) ) return i;
        return avmap.end();
      }

      sigc::signal<void> m_signal_changed;
      sigc::signal<void> m_signal_id_changed;
  };

}

#endif
