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
#include "rectangleextentstest.h"

#include "helper.h"

void RectangleExtentsTest::setUp()
{ }

void RectangleExtentsTest::tearDown()
{ }

Rectangle::pointer setup_rectangle_x0_y0_scaled()
{
  Rectangle::pointer rect = Rectangle::create( 40.0, 80.0, RGBA("red"), RGBA("black") );
  rect->scale( 0.5, 0.5 );
  return rect;
}

void RectangleExtentsTest::rectangle_raw_extents_x0_y0_scaled()
{
  Rectangle::pointer rect = setup_rectangle_x0_y0_scaled();
  Region e = rect->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 42.0, 82.0 );
}

void RectangleExtentsTest::rectangle_pre_viewbox_extents_x0_y0_scaled()
{
  Rectangle::pointer rect = setup_rectangle_x0_y0_scaled();
  Region e = rect->pre_viewbox_extents();
  cppunit_assert_region( e, -0.5, -0.5, 21.0, 41.0 );
}

void RectangleExtentsTest::rectangle_extents_x0_y0_scaled()
{
  Rectangle::pointer rect = setup_rectangle_x0_y0_scaled();
  Region e = rect->extents();
  cppunit_assert_region( e, -0.5, -0.5, 21.0, 41.0 );
}

Rectangle::pointer setup_rectangle_x0_y0_scaled_with_viewbox()
{
  Rectangle::pointer rect = Rectangle::create( 40.0, 80.0, RGBA("red"), RGBA("black") );
  rect->scale( 0.5, 0.5 );
  rect->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return rect;
}

void RectangleExtentsTest::rectangle_raw_extents_x0_y0_scaled_with_viewbox()
{
  Rectangle::pointer rect = setup_rectangle_x0_y0_scaled_with_viewbox();
  Region e = rect->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 42.0, 82.0 );
}

void RectangleExtentsTest::rectangle_pre_viewbox_extents_x0_y0_scaled_with_viewbox()
{
  Rectangle::pointer rect = setup_rectangle_x0_y0_scaled_with_viewbox();
  Region e = rect->pre_viewbox_extents();
  cppunit_assert_region( e, -0.5, -0.5, 21.0, 41.0 );
}

void RectangleExtentsTest::rectangle_extents_x0_y0_scaled_with_viewbox()
{
  Rectangle::pointer rect = setup_rectangle_x0_y0_scaled_with_viewbox();
  Region e = rect->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

Rectangle::pointer setup_rectangle_xneg10_yneg20_scaled()
{
  Rectangle::pointer rect = Rectangle::create( -10.0, -20.0, 40.0, 80.0, RGBA("red"), RGBA("black") );
  rect->scale( 0.5, 0.5 );
  return rect;
}

void RectangleExtentsTest::rectangle_raw_extents_xneg10_yneg20_scaled()
{
  Rectangle::pointer rect = setup_rectangle_xneg10_yneg20_scaled();
  Region e = rect->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 42.0, 82.0 );
}

void RectangleExtentsTest::rectangle_pre_viewbox_extents_xneg10_yneg20_scaled()
{
  Rectangle::pointer rect = setup_rectangle_xneg10_yneg20_scaled();
  Region e = rect->pre_viewbox_extents();
  cppunit_assert_region( e, -10.5, -20.5, 21.0, 41.0 );
}

void RectangleExtentsTest::rectangle_extents_xneg10_yneg20_scaled()
{
  Rectangle::pointer rect = setup_rectangle_xneg10_yneg20_scaled();
  Region e = rect->extents();
  cppunit_assert_region( e, -10.5, -20.5, 21.0, 41.0 );
}

Rectangle::pointer setup_rectangle_xneg10_yneg20_scaled_with_viewbox()
{
  Rectangle::pointer rect = Rectangle::create( -10.0, -20.0, 40.0, 80.0, RGBA("red"), RGBA("black") );
  rect->scale( 0.5, 0.5 );
  rect->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return rect;
}

void RectangleExtentsTest::rectangle_raw_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Rectangle::pointer rect = setup_rectangle_xneg10_yneg20_scaled_with_viewbox();
  Region e = rect->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 42.0, 82.0 );
}

void RectangleExtentsTest::rectangle_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Rectangle::pointer rect = setup_rectangle_xneg10_yneg20_scaled_with_viewbox();
  Region e = rect->pre_viewbox_extents();
  cppunit_assert_region( e, -10.5, -20.5, 21.0, 41.0 );
}

void RectangleExtentsTest::rectangle_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Rectangle::pointer rect = setup_rectangle_xneg10_yneg20_scaled_with_viewbox();
  Region e = rect->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

