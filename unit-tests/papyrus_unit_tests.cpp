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
#include <iostream>

#include <cppunit/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextOutputter.h>

#include "rectangleextentstest.h"
#include "circleextentstest.h"
#include "groupextentstest.h"
#include "canvasextentstest.h"
#include "matrixparsertest.h"
#include "svgparsertest.h"
#include "drawablematrixtests.h"

CPPUNIT_TEST_SUITE_REGISTRATION( RectangleExtentsTest );
CPPUNIT_TEST_SUITE_REGISTRATION( CircleExtentsTest );
CPPUNIT_TEST_SUITE_REGISTRATION( GroupExtentsTest );
CPPUNIT_TEST_SUITE_REGISTRATION( CanvasExtentsTest );
CPPUNIT_TEST_SUITE_REGISTRATION( MatrixParserTest );
CPPUNIT_TEST_SUITE_REGISTRATION( SVGParserTest );
CPPUNIT_TEST_SUITE_REGISTRATION( DrawableMatrixTests );

int main() {
  // Create the event manager and test controller
  CppUnit::TestResult controller;

  // Add a listener that collects test result
  CppUnit::TestResultCollector result;
  controller.addListener( &result );

  // Add a listener that print dots as test run.
  CppUnit::BriefTestProgressListener progress;
  controller.addListener( &progress );

  // Add the top suite to the test runner
  CppUnit::TestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  CppUnit::TextOutputter output(&result, std::cout);
  std::cout << std::endl
      << "==================================================" << std::endl
      << "Papyrus Library Unit Tests: " << std::endl;
  output.printHeader();
  output.printStatistics();
  output.printFailures();

  return result.wasSuccessful() ? 0 : 1;
}

