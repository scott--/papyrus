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
#ifndef DRAWABLEMATRIXTESTS_H
#define DRAWABLEMATRIXTESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class DrawableMatrixTests : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( DrawableMatrixTests );

    CPPUNIT_TEST( drawable_matrix_remove_multiple_copies_single_matrix_multiple_levels );
    CPPUNIT_TEST( drawable_matrix_remove_multiple_copies_single_matrix_single_level );
    
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void drawable_matrix_remove_multiple_copies_single_matrix_multiple_levels();
    
    void drawable_matrix_remove_multiple_copies_single_matrix_single_level();
    
};

#endif
