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
#ifndef PAPYRUS_UTILITY_H
#define PAPYRUS_UTILITY_H

#include <papyrus/enums.h>
#include <glibmm/ustring.h>
#include <papyrus/pointer.h>

#define PAPYRUS_CLASS_NAME( StrName )             \
  static const Glib::ustring& name_string()       \
  {                                               \
    static const Glib::ustring cn(StrName);       \
    return cn;                                    \
  }                                               \
                                                  \
  virtual const Glib::ustring& class_name() const \
  {                                               \
    static const Glib::ustring cn(StrName);       \
    return cn;                                    \
  }

#define PAPYRUS_RENDERABLE( Name )                  \
  typedef PapyrusPointer<Name> pointer;             \
                                                    \
  typedef PapyrusPointer<const Name> const_pointer; \
                                                    \
  typedef PapyrusWeakPointer<Name> weak_pointer;    \
                                                    \
  using Renderable::render;                         \
                                                    \
  PAPYRUS_CLASS_NAME("Name")

#define PAPYRUS_CLONE_METHOD( Type )          \
  virtual Drawable::pointer clone() const {   \
    Type::pointer other = Type::create();     \
    *other = *this;                           \
    return other;                             \
  }
  
#define PAPYRUS_DRAWABLE(Name)                \
  PAPYRUS_RENDERABLE(Name)                    \
                                              \
  PAPYRUS_CLONE_METHOD(Name)

#define PAPYRUS_CREATE( BaseObjCall )     \
  pointer p = pointer( new BaseObjCall ); \
  p->m_self = p;                          \
  return p;

  namespace Papyrus {

  double rad2units(double value, DegRad units);

  double units2rad(double value, DegRad units);

  bool strcaseeq( const Glib::ustring& str1, const Glib::ustring& str2 );

  int strcasecmp( const Glib::ustring& str1, const Glib::ustring& str2 );
  
  class Drawable;
  
  struct wp_lt_compare {
    bool operator()( const PapyrusWeakPointer<Drawable>&, const PapyrusWeakPointer<Drawable>& );
  };
  
  }

#endif
