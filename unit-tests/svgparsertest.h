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
#ifndef SVGPARSERTEST_H
#define SVGPARSERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class SVGParserTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( SVGParserTest );

    CPPUNIT_TEST( svg_parser_simple_from_memory );
    CPPUNIT_TEST( svg_parser_simple_standalone );
    CPPUNIT_TEST( svg_parser_simple_groups );
    CPPUNIT_TEST( svg_parser_simple_circle );
    CPPUNIT_TEST( svg_parser_simple_path_triangle );
    // TODO fix and enable test
//     CPPUNIT_TEST( svg_parser_simple_reference );
    CPPUNIT_TEST( svg_parser_simple_linear_gradient );

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void svg_parser_simple_from_memory();
    void svg_parser_simple_standalone();
    void svg_parser_simple_groups();
    void svg_parser_simple_circle();
    void svg_parser_simple_path_triangle();
    void svg_parser_simple_reference();
    void svg_parser_simple_linear_gradient();
};

#endif
