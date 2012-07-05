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
#ifndef RECTANGLEEXTENTSTEST_H
#define RECTANGLEEXTENTSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class RectangleExtentsTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( RectangleExtentsTest );

    CPPUNIT_TEST( rectangle_raw_extents_x0_y0_scaled );
    CPPUNIT_TEST( rectangle_pre_viewbox_extents_x0_y0_scaled );
    CPPUNIT_TEST( rectangle_extents_x0_y0_scaled );
    
    CPPUNIT_TEST( rectangle_raw_extents_x0_y0_scaled_with_viewbox );
    CPPUNIT_TEST( rectangle_pre_viewbox_extents_x0_y0_scaled_with_viewbox );
    CPPUNIT_TEST( rectangle_extents_x0_y0_scaled_with_viewbox );

    CPPUNIT_TEST( rectangle_raw_extents_xneg10_yneg20_scaled );
    CPPUNIT_TEST( rectangle_pre_viewbox_extents_xneg10_yneg20_scaled );
    CPPUNIT_TEST( rectangle_extents_xneg10_yneg20_scaled );
    
    CPPUNIT_TEST( rectangle_raw_extents_xneg10_yneg20_scaled_with_viewbox );
    CPPUNIT_TEST( rectangle_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox );
    CPPUNIT_TEST( rectangle_extents_xneg10_yneg20_scaled_with_viewbox );

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void rectangle_raw_extents_x0_y0_scaled();
    void rectangle_pre_viewbox_extents_x0_y0_scaled();
    void rectangle_extents_x0_y0_scaled();
    
    void rectangle_raw_extents_x0_y0_scaled_with_viewbox();
    void rectangle_pre_viewbox_extents_x0_y0_scaled_with_viewbox();
    void rectangle_extents_x0_y0_scaled_with_viewbox();
    
    void rectangle_raw_extents_xneg10_yneg20_scaled();
    void rectangle_pre_viewbox_extents_xneg10_yneg20_scaled();
    void rectangle_extents_xneg10_yneg20_scaled();
    
    void rectangle_raw_extents_xneg10_yneg20_scaled_with_viewbox();
    void rectangle_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox();
    void rectangle_extents_xneg10_yneg20_scaled_with_viewbox();
    
};

#endif
