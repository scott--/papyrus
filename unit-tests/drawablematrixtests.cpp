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
#include "drawablematrixtests.h"

#include "helper.h"

void DrawableMatrixTests::setUp()
{ }

void DrawableMatrixTests::tearDown()
{ }

void DrawableMatrixTests::drawable_matrix_remove_multiple_copies_single_matrix_multiple_levels()
{
  Rectangle::pointer rect = Rectangle::create(-10, -10, 50,100, RGBA("red"), RGBA("black"));
  Matrix::pointer matrix = Matrix::create(20, 20, 1.5, 1.5);
  
  Drawable::MatrixConnMap::const_iterator conniter;
  const Drawable::MatrixConnMap& connmap = rect->matrix_connection_map();
  
  CPPUNIT_ASSERT( connmap.find(matrix) == connmap.end() );
  rect->add_matrix(matrix);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 1U, conniter->second.count );
  
  rect->add_matrix(matrix, 3);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 2U, conniter->second.count );
  
  rect->add_matrix(matrix, 5);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 3U, conniter->second.count );
  
  rect->add_matrix(matrix, -4);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 4U, conniter->second.count );
  
  rect->remove_matrix(matrix);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter == connmap.end() );
}

void DrawableMatrixTests::drawable_matrix_remove_multiple_copies_single_matrix_single_level()
{
  Rectangle::pointer rect = Rectangle::create(-10, -10, 50,100, RGBA("red"), RGBA("black"));
  Matrix::pointer matrix = Matrix::create(20, 20, 1.5, 1.5);
  
  Drawable::MatrixConnMap::const_iterator conniter;
  const Drawable::MatrixConnMap& connmap = rect->matrix_connection_map();
  
  CPPUNIT_ASSERT( connmap.find(matrix) == connmap.end() );
  rect->add_matrix(matrix);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 1U, conniter->second.count );
  
  rect->add_matrix(matrix, 3);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 2U, conniter->second.count );
  
  rect->add_matrix(matrix, 3);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 3U, conniter->second.count );
  
  rect->add_matrix(matrix, -4);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 4U, conniter->second.count );
  
  rect->remove_matrix(matrix, 3);
  conniter = connmap.find(matrix);
  CPPUNIT_ASSERT( conniter != connmap.end() );
  CPPUNIT_ASSERT_EQUAL( 2U, conniter->second.count );
}

