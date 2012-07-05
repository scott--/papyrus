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
#include "circleextentstest.h"

#include "helper.h"

void CircleExtentsTest::setUp()
{ }

void CircleExtentsTest::tearDown()
{ }

Circle::pointer setup_circle_x0_y0_uniformly_scaled()
{
  Circle::pointer circle = Circle::create( 40.0, RGBA("red"), RGBA("black") );
  circle->scale( 0.5, 0.5 );
  return circle;
}

void CircleExtentsTest::circle_raw_extents_x0_y0_uniformly_scaled()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled();
  Region e = circle->raw_extents();
  cppunit_assert_region( e, -41.0, -41.0, 82.0, 82.0 );
}

void CircleExtentsTest::circle_pre_viewbox_extents_x0_y0_uniformly_scaled()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled();
  Region e = circle->pre_viewbox_extents();
  cppunit_assert_region( e, -20.5, -20.5, 41.0, 41.0 );
}

void CircleExtentsTest::circle_extents_x0_y0_uniformly_scaled()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled();
  Region e = circle->extents();
  cppunit_assert_region( e, -20.5, -20.5, 41.0, 41.0 );
}

Circle::pointer setup_circle_x0_y0_nonuniformly_scaled()
{
  Circle::pointer circle = Circle::create( 40.0, RGBA("red"), RGBA("black") );
  circle->scale( 0.75, 0.5 );
  return circle;
}

void CircleExtentsTest::circle_raw_extents_x0_y0_nonuniformly_scaled()
{
  Circle::pointer circle = setup_circle_x0_y0_nonuniformly_scaled();
  Region e = circle->raw_extents();
  cppunit_assert_region( e, -41.0, -41.0, 82.0, 82.0 );
}

void CircleExtentsTest::circle_pre_viewbox_extents_x0_y0_nonuniformly_scaled()
{
  Circle::pointer circle = setup_circle_x0_y0_nonuniformly_scaled();
  Region e = circle->pre_viewbox_extents();
  cppunit_assert_region( e, -30.75, -20.5, 61.5, 41.0 );
}

void CircleExtentsTest::circle_extents_x0_y0_nonuniformly_scaled()
{
  Circle::pointer circle = setup_circle_x0_y0_nonuniformly_scaled();
  Region e = circle->extents();
  cppunit_assert_region( e, -30.75, -20.5, 61.5, 41.0 );
}

Circle::pointer setup_circle_x0_y0_uniformly_scaled_rotated()
{
  Circle::pointer circle = Circle::create( 40.0, RGBA("red"), RGBA("black") );
  circle->rotate( M_PI/4.0 );
  circle->scale( 0.5, 0.5 );
  return circle;
}

void CircleExtentsTest::circle_raw_extents_x0_y0_uniformly_scaled_rotated()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled_rotated();
  Region e = circle->raw_extents();
  cppunit_assert_region( e, -41.0, -41.0, 82.0, 82.0 );
}

void CircleExtentsTest::circle_pre_viewbox_extents_x0_y0_uniformly_scaled_rotated()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled_rotated();
  Region e = circle->pre_viewbox_extents();
  cppunit_assert_region( e, -20.5, -20.5, 41.0, 41.0 );
}

void CircleExtentsTest::circle_extents_x0_y0_uniformly_scaled_rotated()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled_rotated();
  Region e = circle->extents();
  cppunit_assert_region( e, -20.5, -20.5, 41.0, 41.0 );
}

Circle::pointer setup_circle_x0_y0_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = Circle::create( 40.0, RGBA("red"), RGBA("black") );
  circle->scale( 0.5, 0.5 );
  circle->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return circle;
}

void CircleExtentsTest::circle_raw_extents_x0_y0_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled_with_viewbox();
  Region e = circle->raw_extents();
  cppunit_assert_region( e, -41.0, -41.0, 82.0, 82.0 );
}

void CircleExtentsTest::circle_pre_viewbox_extents_x0_y0_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled_with_viewbox();
  Region e = circle->pre_viewbox_extents();
  cppunit_assert_region( e, -20.5, -20.5, 41.0, 41.0 );
}

void CircleExtentsTest::circle_extents_x0_y0_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = setup_circle_x0_y0_uniformly_scaled_with_viewbox();
  Region e = circle->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

Circle::pointer setup_circle_xneg10_yneg20_uniformly_scaled()
{
  Circle::pointer circle = Circle::create( 40.0, RGBA("red"), RGBA("black") );
  circle->translate( -10.0, -20.0 );
  circle->scale( 0.5, 0.5 );
  return circle;
}

void CircleExtentsTest::circle_raw_extents_xneg10_yneg20_uniformly_scaled()
{
  Circle::pointer circle = setup_circle_xneg10_yneg20_uniformly_scaled();
  Region e = circle->raw_extents();
  cppunit_assert_region( e, -41.0, -41.0, 82.0, 82.0 );
}

void CircleExtentsTest::circle_pre_viewbox_extents_xneg10_yneg20_uniformly_scaled()
{
  Circle::pointer circle = setup_circle_xneg10_yneg20_uniformly_scaled();
  Region e = circle->pre_viewbox_extents();
  cppunit_assert_region( e, -30.5, -40.5, 41.0, 41.0 );
}

void CircleExtentsTest::circle_extents_xneg10_yneg20_uniformly_scaled()
{
  Circle::pointer circle = setup_circle_xneg10_yneg20_uniformly_scaled();
  Region e = circle->extents();
  cppunit_assert_region( e, -30.5, -40.5, 41.0, 41.0 );
}

Circle::pointer setup_circle_xneg10_yneg20_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = Circle::create( 40.0, RGBA("red"), RGBA("black") );
  circle->translate( -10.0, -20.0 );
  circle->scale( 0.5, 0.5 );
  circle->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return circle;
}

void CircleExtentsTest::circle_raw_extents_xneg10_yneg20_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = setup_circle_xneg10_yneg20_uniformly_scaled_with_viewbox();
  Region e = circle->raw_extents();
  cppunit_assert_region( e, -41.0, -41.0, 82.0, 82.0 );
}

void CircleExtentsTest::circle_pre_viewbox_extents_xneg10_yneg20_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = setup_circle_xneg10_yneg20_uniformly_scaled_with_viewbox();
  Region e = circle->pre_viewbox_extents();
  cppunit_assert_region( e, -30.5, -40.5, 41.0, 41.0 );
}

void CircleExtentsTest::circle_extents_xneg10_yneg20_uniformly_scaled_with_viewbox()
{
  Circle::pointer circle = setup_circle_xneg10_yneg20_uniformly_scaled_with_viewbox();
  Region e = circle->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

