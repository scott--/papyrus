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
#ifndef HELPER_H
#define HELPER_H

#include <papyrus.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Papyrus;

inline void cppunit_assert_region( Region& r, double x, double y, double w, double h )
{
  CPPUNIT_ASSERT_DOUBLES_EQUAL( x, r.x(), 1.0e-13 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( y, r.y(), 1.0e-13 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( w, r.width(), 1.0e-13 );
  CPPUNIT_ASSERT_DOUBLES_EQUAL( h, r.height(), 1.0e-13 );
}

void make_image( Drawable::pointer p, const Glib::ustring& filename );

#endif

