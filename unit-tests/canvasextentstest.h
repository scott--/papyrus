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
#ifndef CANVASEXTENTSTEST_H
#define CANVASEXTENTSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class CanvasExtentsTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( CanvasExtentsTest );

    CPPUNIT_TEST( canvas_raw_extents_x0_y0 );
    CPPUNIT_TEST( canvas_pre_viewbox_extents_x0_y0 );
    CPPUNIT_TEST( canvas_extents_x0_y0 );
    
    CPPUNIT_TEST( canvas_raw_extents_x0_y0_scaled );
    CPPUNIT_TEST( canvas_pre_viewbox_extents_x0_y0_scaled );
    CPPUNIT_TEST( canvas_extents_x0_y0_scaled );

    CPPUNIT_TEST( canvas_raw_extents_x0_y0_scaled_with_viewbox );
    CPPUNIT_TEST( canvas_pre_viewbox_extents_x0_y0_scaled_with_viewbox );
    CPPUNIT_TEST( canvas_extents_x0_y0_scaled_with_viewbox );

    CPPUNIT_TEST( canvas_raw_extents_xneg10_yneg20_scaled );
    CPPUNIT_TEST( canvas_pre_viewbox_extents_xneg10_yneg20_scaled );
    CPPUNIT_TEST( canvas_extents_xneg10_yneg20_scaled );

    CPPUNIT_TEST( canvas_raw_extents_xneg10_yneg20_scaled_with_viewbox );
    CPPUNIT_TEST( canvas_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox );
    CPPUNIT_TEST( canvas_extents_xneg10_yneg20_scaled_with_viewbox );

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void canvas_raw_extents_x0_y0();
    void canvas_pre_viewbox_extents_x0_y0();
    void canvas_extents_x0_y0();
    
    void canvas_raw_extents_x0_y0_scaled();
    void canvas_pre_viewbox_extents_x0_y0_scaled();
    void canvas_extents_x0_y0_scaled();
    
    void canvas_raw_extents_x0_y0_scaled_with_viewbox();
    void canvas_pre_viewbox_extents_x0_y0_scaled_with_viewbox();
    void canvas_extents_x0_y0_scaled_with_viewbox();
    
    void canvas_raw_extents_xneg10_yneg20_scaled();
    void canvas_pre_viewbox_extents_xneg10_yneg20_scaled();
    void canvas_extents_xneg10_yneg20_scaled();
    
    void canvas_raw_extents_xneg10_yneg20_scaled_with_viewbox();
    void canvas_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox();
    void canvas_extents_xneg10_yneg20_scaled_with_viewbox();
    
};

#endif
