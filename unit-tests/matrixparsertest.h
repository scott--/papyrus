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
#ifndef MATRIXPARSERTEST_H
#define MATRIXPARSERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class MatrixParserTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( MatrixParserTest );

    CPPUNIT_TEST( matrix_parser_matrix );
    CPPUNIT_TEST( matrix_parser_translate_x );
    CPPUNIT_TEST( matrix_parser_translate_x_y );
    CPPUNIT_TEST( matrix_parser_scale_uniform );
    CPPUNIT_TEST( matrix_parser_scale_x_y );
    CPPUNIT_TEST( matrix_parser_rotate );
    CPPUNIT_TEST( matrix_parser_rotate_cx_cy );
    CPPUNIT_TEST( matrix_parser_skewx );
    CPPUNIT_TEST( matrix_parser_skewy );
    CPPUNIT_TEST( matrix_parser_matrix_translate );
    CPPUNIT_TEST( matrix_parser_matrix_translate_scale );

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void matrix_parser_matrix();
    void matrix_parser_translate_x();
    void matrix_parser_translate_x_y();
    void matrix_parser_scale_uniform();
    void matrix_parser_scale_x_y();
    void matrix_parser_rotate();
    void matrix_parser_rotate_cx_cy();
    void matrix_parser_skewx();
    void matrix_parser_skewy();
    void matrix_parser_matrix_translate();
    void matrix_parser_matrix_translate_scale();
};

#endif
