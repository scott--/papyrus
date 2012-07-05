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
#include "utility.h"

#include <cmath>

namespace Papyrus {

  double rad2units(double value, DegRad units)
  {
    if ( units == DEGREES ) value *= 180.0 / M_PI;
    return value;
  }

  double units2rad(double value, DegRad units)
  {
    if ( units == DEGREES ) value *= M_PI / 180.0;
    return value;
  }

  bool strcaseeq(const Glib::ustring & str1, const Glib::ustring & str2)
  {
    return str1.casefold() == str2.casefold();
  }

  int strcasecmp(const Glib::ustring & str1, const Glib::ustring & str2)
  {
    if ( str1.casefold() < str2.casefold() ) return -1;
    if ( str1.casefold() == str2.casefold() ) return 0;
    return 1;
  }
  
  // HACK normally a bad hack, but we have the destruct signal to eliminate the normal problem
  bool wp_lt_compare::operator()(const PapyrusWeakPointer< Drawable >& wp1, 
                                 const PapyrusWeakPointer< Drawable >& wp2)
  {
    PapyrusPointer<Drawable> p1, p2;
    p1 = wp1.lock();
    p2 = wp2.lock();
    return p1 < p2;
  }




}



