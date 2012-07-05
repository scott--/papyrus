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
#include "groupextentstest.h"

#include "helper.h"

void GroupExtentsTest::setUp()
{ }

void GroupExtentsTest::tearDown()
{ }

Group::pointer setup_basic_group()
{
  Group::pointer group = Group::create();
  group->add( Rectangle::create( 40.0, 80.0, RGBA("red"), RGBA("black") ) );
  group->add( Rectangle::create( 100.0, 120.0, 10.0, 10.0, RGBA("green"), RGBA("blue") ) );
  return group;
}

Group::pointer setup_group_x0_y0()
{
  Group::pointer group = setup_basic_group();
  return group;
}

void GroupExtentsTest::group_raw_extents_x0_y0()
{
  Group::pointer group = setup_group_x0_y0();
  Region e = group->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void GroupExtentsTest::group_pre_viewbox_extents_x0_y0()
{
  Group::pointer group = setup_group_x0_y0();
  Region e = group->pre_viewbox_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void GroupExtentsTest::group_extents_x0_y0()
{
  Group::pointer group = setup_group_x0_y0();
  Region e = group->extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

Group::pointer setup_group_x0_y0_scaled()
{
  Group::pointer group = setup_basic_group();
  group->scale( 0.5, 0.5 );
  return group;
}

void GroupExtentsTest::group_raw_extents_x0_y0_scaled()
{
  Group::pointer group = setup_group_x0_y0_scaled();
  Region e = group->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void GroupExtentsTest::group_pre_viewbox_extents_x0_y0_scaled()
{
  Group::pointer group = setup_group_x0_y0_scaled();
  Region e = group->pre_viewbox_extents();
  cppunit_assert_region( e, -0.5, -0.5, 56.0, 66.0 );
}

void GroupExtentsTest::group_extents_x0_y0_scaled()
{
  Group::pointer group = setup_group_x0_y0_scaled();
  Region e = group->extents();
  cppunit_assert_region( e, -0.5, -0.5, 56.0, 66.0 );
}

Group::pointer setup_group_x0_y0_scaled_with_viewbox()
{
  Group::pointer group = setup_basic_group();
  group->scale( 0.5, 0.5 );
  group->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return group;
}

void GroupExtentsTest::group_raw_extents_x0_y0_scaled_with_viewbox()
{
  Group::pointer group = setup_group_x0_y0_scaled_with_viewbox();
  Region e = group->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void GroupExtentsTest::group_pre_viewbox_extents_x0_y0_scaled_with_viewbox()
{
  Group::pointer group = setup_group_x0_y0_scaled_with_viewbox();
  Region e = group->pre_viewbox_extents();
  cppunit_assert_region( e, -0.5, -0.5, 56.0, 66.0 );
}

void GroupExtentsTest::group_extents_x0_y0_scaled_with_viewbox()
{
  Group::pointer group = setup_group_x0_y0_scaled_with_viewbox();
  Region e = group->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

Group::pointer setup_group_xneg10_yneg20_scaled()
{
  Group::pointer group = setup_basic_group();
  group->scale( 0.5, 0.5 );
  group->translate( -10.0, -20.0 );
  return group;
}

void GroupExtentsTest::group_raw_extents_xneg10_yneg20_scaled()
{
  Group::pointer group = setup_group_xneg10_yneg20_scaled();
  Region e = group->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void GroupExtentsTest::group_pre_viewbox_extents_xneg10_yneg20_scaled()
{
  Group::pointer group = setup_group_xneg10_yneg20_scaled();
  Region e = group->pre_viewbox_extents();
  cppunit_assert_region( e, -10.5, -20.5, 56.0, 66.0 );
}

void GroupExtentsTest::group_extents_xneg10_yneg20_scaled()
{
  Group::pointer group = setup_group_xneg10_yneg20_scaled();
  Region e = group->extents();
  cppunit_assert_region( e, -10.5, -20.5, 56.0, 66.0 );
}

Group::pointer setup_group_xneg10_yneg20_scaled_with_viewbox()
{
  Group::pointer group = setup_basic_group();
  group->scale( 0.5, 0.5 );
  group->translate( -10.0, -20.0 );
  group->set_viewbox( Viewbox::create( 100.0, 110.0, 20.0, 10.0 ) );
  return group;
}

void GroupExtentsTest::group_raw_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Group::pointer group = setup_group_xneg10_yneg20_scaled_with_viewbox();
  Region e = group->raw_extents();
  cppunit_assert_region( e, -1.0, -1.0, 112.0, 132.0 );
}

void GroupExtentsTest::group_pre_viewbox_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Group::pointer group = setup_group_xneg10_yneg20_scaled_with_viewbox();
  Region e = group->pre_viewbox_extents();
  cppunit_assert_region( e, -10.5, -20.5, 56.0, 66.0 );
}

void GroupExtentsTest::group_extents_xneg10_yneg20_scaled_with_viewbox()
{
  Group::pointer group = setup_group_xneg10_yneg20_scaled_with_viewbox();
  Region e = group->extents();
  cppunit_assert_region( e, 100.0, 110.0, 20.0, 10.0 );
}

