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
#include "canvasextentstest.h"

#include "helper.h"

void CanvasExtentsTest::setUp()
{ }

void CanvasExtentsTest::tearDown()
{ }

Canvas::pointer setup_basic_canvas()
{
  Canvas::pointer canvas = Canvas::create();
  canvas->add( Rectangle::create( 40.0, 80.0, RGBA("red"), RGBA("black") ) );
  canvas->add( Rectangle::create( 100.0, 120.0, 10.0, 10.0, RGBA("green"), RGBA("blue") ) );
  canvas->set_scroll_anchor( SCROLL_ANCHOR_CENTER );
  return canvas;
}

Canvas::pointer setup_canvas_x0_y0()
{
  Canvas::pointer canvas = setup_basic_canvas();
  return canvas;
}

void CanvasExtentsTest::canvas_raw_extents_x0_y0()
{
  Canvas::pointer canvas = setup_canvas_x0_y0();
  Region e = canvas->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void CanvasExtentsTest::canvas_pre_viewbox_extents_x0_y0()
{
  Canvas::pointer canvas = setup_canvas_x0_y0();
  Region e = canvas->pre_viewbox_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void CanvasExtentsTest::canvas_extents_x0_y0()
{
  Canvas::pointer canvas = setup_canvas_x0_y0();
  Region e = canvas->extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

Canvas::pointer setup_canvas_x0_y0_scaled()
{
  Canvas::pointer canvas = setup_basic_canvas();
  canvas->scale( 0.5, 0.5 );
  return canvas;
}

void CanvasExtentsTest::canvas_raw_extents_x0_y0_scaled()
{
  Canvas::pointer canvas = setup_canvas_x0_y0_scaled();
  Region e = canvas->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void CanvasExtentsTest::canvas_pre_viewbox_extents_x0_y0_scaled()
{
  Canvas::pointer canvas = setup_canvas_x0_y0_scaled();
  Region e = canvas->pre_viewbox_extents();
  cppunit_assert_region( e, -0.5, -0.5, 56.0, 66.0 );
}

void CanvasExtentsTest::canvas_extents_x0_y0_scaled()
{
  Canvas::pointer canvas = setup_canvas_x0_y0_scaled();
  Region e = canvas->extents();
  cppunit_assert_region( e, -0.5, -0.5, 56.0, 66.0 );
}

Canvas::pointer setup_canvas_x0_y0_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_basic_canvas();
  canvas->scale( 0.5, 0.5 );
  canvas->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return canvas;
}

void CanvasExtentsTest::canvas_raw_extents_x0_y0_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_canvas_x0_y0_scaled_with_viewbox();
  Region e = canvas->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void CanvasExtentsTest::canvas_pre_viewbox_extents_x0_y0_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_canvas_x0_y0_scaled_with_viewbox();
  Region e = canvas->pre_viewbox_extents();
  cppunit_assert_region( e, -0.5, -0.5, 56.0, 66.0 );
}

void CanvasExtentsTest::canvas_extents_x0_y0_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_canvas_x0_y0_scaled_with_viewbox();
  Region e = canvas->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

Canvas::pointer setup_canvas_xneg10_yneg20_scaled()
{
  Canvas::pointer canvas = setup_basic_canvas();
  canvas->scale( 0.5, 0.5 );
  canvas->translate( -10.0, -20.0 );
  return canvas;
}

void CanvasExtentsTest::canvas_raw_extents_xneg10_yneg20_scaled()
{
  Canvas::pointer canvas = setup_canvas_xneg10_yneg20_scaled();
  Region e = canvas->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void CanvasExtentsTest::canvas_pre_viewbox_extents_xneg10_yneg20_scaled()
{
  Canvas::pointer canvas = setup_canvas_xneg10_yneg20_scaled();
  Region e = canvas->pre_viewbox_extents();
  cppunit_assert_region( e, -10.5, -20.5, 56.0, 66.0 );
}

void CanvasExtentsTest::canvas_extents_xneg10_yneg20_scaled()
{
  Canvas::pointer canvas = setup_canvas_xneg10_yneg20_scaled();
  Region e = canvas->extents();
  cppunit_assert_region( e, -10.5, -20.5, 56.0, 66.0 );
}

Canvas::pointer setup_canvas_xneg10_yneg20_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_basic_canvas();
  canvas->scale( 0.5, 0.5 );
  canvas->translate( -10.0, -20.0 );
  canvas->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return canvas;
}

void CanvasExtentsTest::canvas_raw_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_canvas_xneg10_yneg20_scaled_with_viewbox();
  Region e = canvas->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void CanvasExtentsTest::canvas_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_canvas_xneg10_yneg20_scaled_with_viewbox();
  Region e = canvas->pre_viewbox_extents();
  cppunit_assert_region( e, -10.5, -20.5, 56.0, 66.0 );
}

void CanvasExtentsTest::canvas_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Canvas::pointer canvas = setup_canvas_xneg10_yneg20_scaled_with_viewbox();
  Region e = canvas->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

