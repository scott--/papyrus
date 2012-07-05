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
#ifndef CIRCLEEXTENTSTEST_H
#define CIRCLEEXTENTSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class CircleExtentsTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( CircleExtentsTest );

    CPPUNIT_TEST( circle_raw_extents_x0_y0_uniformly_scaled );
    CPPUNIT_TEST( circle_pre_viewbox_extents_x0_y0_uniformly_scaled );
    CPPUNIT_TEST( circle_extents_x0_y0_uniformly_scaled );
    
    CPPUNIT_TEST( circle_raw_extents_x0_y0_nonuniformly_scaled );
    CPPUNIT_TEST( circle_pre_viewbox_extents_x0_y0_nonuniformly_scaled );
    CPPUNIT_TEST( circle_extents_x0_y0_nonuniformly_scaled );
    
    CPPUNIT_TEST( circle_raw_extents_x0_y0_uniformly_scaled_rotated );
    CPPUNIT_TEST( circle_pre_viewbox_extents_x0_y0_uniformly_scaled_rotated );
    CPPUNIT_TEST( circle_extents_x0_y0_uniformly_scaled_rotated );
    
    CPPUNIT_TEST( circle_raw_extents_x0_y0_uniformly_scaled_with_viewbox );
    CPPUNIT_TEST( circle_pre_viewbox_extents_x0_y0_uniformly_scaled_with_viewbox );
    CPPUNIT_TEST( circle_extents_x0_y0_uniformly_scaled_with_viewbox );

    CPPUNIT_TEST( circle_raw_extents_xneg10_yneg20_uniformly_scaled );
    CPPUNIT_TEST( circle_pre_viewbox_extents_xneg10_yneg20_uniformly_scaled );
    CPPUNIT_TEST( circle_extents_xneg10_yneg20_uniformly_scaled );

    CPPUNIT_TEST( circle_raw_extents_xneg10_yneg20_uniformly_scaled_with_viewbox );
    CPPUNIT_TEST( circle_pre_viewbox_extents_xneg10_yneg20_uniformly_scaled_with_viewbox );
    CPPUNIT_TEST( circle_extents_xneg10_yneg20_uniformly_scaled_with_viewbox );

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();

    void tearDown();

    void circle_raw_extents_x0_y0_uniformly_scaled();
    void circle_pre_viewbox_extents_x0_y0_uniformly_scaled();
    void circle_extents_x0_y0_uniformly_scaled();
    
    void circle_raw_extents_x0_y0_nonuniformly_scaled();
    void circle_pre_viewbox_extents_x0_y0_nonuniformly_scaled();
    void circle_extents_x0_y0_nonuniformly_scaled();
    
    void circle_raw_extents_x0_y0_uniformly_scaled_rotated();
    void circle_pre_viewbox_extents_x0_y0_uniformly_scaled_rotated();
    void circle_extents_x0_y0_uniformly_scaled_rotated();
    
    void circle_raw_extents_x0_y0_uniformly_scaled_with_viewbox();
    void circle_pre_viewbox_extents_x0_y0_uniformly_scaled_with_viewbox();
    void circle_extents_x0_y0_uniformly_scaled_with_viewbox();

    void circle_raw_extents_xneg10_yneg20_uniformly_scaled();
    void circle_pre_viewbox_extents_xneg10_yneg20_uniformly_scaled();
    void circle_extents_xneg10_yneg20_uniformly_scaled();

    void circle_raw_extents_xneg10_yneg20_uniformly_scaled_with_viewbox();
    void circle_pre_viewbox_extents_xneg10_yneg20_uniformly_scaled_with_viewbox();
    void circle_extents_xneg10_yneg20_uniformly_scaled_with_viewbox();
    
};

#endif
