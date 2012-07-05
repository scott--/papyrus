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
#include "matrixparsertest.h"

#include "helper.h"

void MatrixParserTest::setUp()
{ }

void MatrixParserTest::tearDown()
{ }

void MatrixParserTest::matrix_parser_matrix()
{
  Matrix m;
  CPPUNIT_ASSERT( m.set("matrix(1.1 2.2 3.3 4.4 5.5 6.6)") );
  Cairo::Matrix cm = m;
  
  CPPUNIT_ASSERT_EQUAL( 1.1, cm.xx );
  CPPUNIT_ASSERT_EQUAL( 2.2, cm.yx );
  CPPUNIT_ASSERT_EQUAL( 3.3, cm.xy );
  CPPUNIT_ASSERT_EQUAL( 4.4, cm.yy );
  CPPUNIT_ASSERT_EQUAL( 5.5, cm.x0 );
  CPPUNIT_ASSERT_EQUAL( 6.6, cm.y0 );
}

void MatrixParserTest::matrix_parser_translate_x()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("translate( 5.2 )") );
  m2.translate( 5.2, 0.0 );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_translate_x_y()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("translate( 5.2, 20.7 )") );
  m2.translate( 5.2, 20.7 );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_scale_uniform()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("scale( 20.7 )") );
  m2.scale( 20.7 );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_scale_x_y()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("scale( 5.2, 20.7 )") );
  m2.scale( 5.2, 20.7 );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_rotate()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("rotate( 30 )") );
  m2.rotate( 30, DEGREES );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_rotate_cx_cy()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("rotate( 35, 20 40 )") );
  m2.rotate( 35, 20, 40, DEGREES );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_skewx()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("skewX( 30 )") );
  m2.skew_x( 30, DEGREES );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_skewy()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("skewY( -20 )") );
  m2.skew_y( -20, DEGREES );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_matrix_translate()
{
  Matrix m1, m2;
  CPPUNIT_ASSERT( m1.set("  matrix( 123.456 .34, 33 34.5 82.7, 78.2 ) , translate( 5.2 )   ") );
  m2 = Matrix( 123.456, 0.34, 33.0, 34.5, 82.7, 78.2 );
  m2.translate( 5.2, 0.0 );
  CPPUNIT_ASSERT( m1 == m2 );
}

void MatrixParserTest::matrix_parser_matrix_translate_scale()
{
  Matrix m1, m2;
  m1.set("  matrix( 123.456 .34, 33 34.5 82.7, 78.2 ) , translate( 5.2 )  scale( 5.3, 6.7) ");
  m2 = Matrix( 123.456, 0.34, 33.0, 34.5, 82.7, 78.2 );
  m2.translate( 5.2, 0.0 );
  m2.scale( 5.3, 6.7 );
  CPPUNIT_ASSERT( m1 == m2 );
}
