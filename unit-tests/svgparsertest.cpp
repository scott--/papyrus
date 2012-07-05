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
#include "svgparsertest.h"

#include "helper.h"

#define svg_simple_contained_rect                         \
"                                                         \
<svg width=\"4cm\" height=\"8cm\" version=\"1.1\">        \
  <ellipse cx=\"2cm\" cy=\"4cm\" rx=\"2cm\" ry=\"1cm\" /> \
</svg>"

#define svg_simple_standalone                                                     \
"<?xml version=\"1.0\" standalone=\"no\"?>                                        \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"                                  \
          \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">                   \
<svg width=\"5cm\" height=\"4cm\" version=\"1.1\"                                 \
     xmlns=\"http://www.w3.org/2000/svg\">                                        \
  <desc>Four separate rectangles                                                  \
  </desc>                                                                         \
  <rect id=\"rect1\" x=\"0.5cm\" y=\"0.5cm\" width=\"2cm\" height=\"1cm\"/>       \
  <rect id=\"rect2\" x=\"0.5cm\" y=\"2cm\" width=\"1cm\" height=\"1.5cm\"/>       \
  <rect id=\"rect3\" x=\"3cm\" y=\"0.5cm\" width=\"1.5cm\" height=\"2cm\"/>       \
  <rect id=\"rect4\" x=\"3.5cm\" y=\"3cm\" width=\"1cm\" height=\"0.5cm\"/>       \
  <!-- Show outline of canvas using 'rect' element -->                            \
  <rect id=\"border\" x=\".01cm\" y=\".01cm\" width=\"4.98cm\" height=\"3.98cm\"  \
        fill=\"none\" stroke=\"blue\" stroke-width=\".02cm\" />                   \
</svg>"

void SVGParserTest::setUp()
{ }

void SVGParserTest::tearDown()
{ }

void SVGParserTest::svg_parser_simple_from_memory()
{
  SVG::pointer svg = SVG::create( svg_simple_contained_rect, SVG::MEMORY );

  svg->scale( 20.0, 20.0 );
  make_image( svg, "simple_from_memory.png" );
//   Matrix m;
//   CPPUNIT_ASSERT( m.set("matrix(1.1 2.2 3.3 4.4 5.5 6.6)") );
//   Cairo::Matrix cm = m;
//   
//   CPPUNIT_ASSERT_EQUAL( 1.1, cm.xx );
//   CPPUNIT_ASSERT_EQUAL( 2.2, cm.yx );
//   CPPUNIT_ASSERT_EQUAL( 3.3, cm.xy );
//   CPPUNIT_ASSERT_EQUAL( 4.4, cm.yy );
//   CPPUNIT_ASSERT_EQUAL( 5.5, cm.x0 );
//   CPPUNIT_ASSERT_EQUAL( 6.6, cm.y0 );
}

void SVGParserTest::svg_parser_simple_standalone()
{
  Rectangle::pointer rect;
  double x, y, w, h;

  SVG::pointer svg = SVG::create( svg_simple_standalone, SVG::MEMORY );

  CPPUNIT_ASSERT( 5 == svg->size() );
  CPPUNIT_ASSERT( 5 == svg->layer(0).size() );

  rect = svg->child<Rectangle>( "rect1" );
  CPPUNIT_ASSERT( rect );
  rect->xywh( x, y, w, h );
  CPPUNIT_ASSERT_EQUAL( 0.5, x );
  CPPUNIT_ASSERT_EQUAL( 0.5, y );
  CPPUNIT_ASSERT_EQUAL( 2.0, w );
  CPPUNIT_ASSERT_EQUAL( 1.0, h );

  rect = svg->child<Rectangle>( "rect2" );
  CPPUNIT_ASSERT( rect );
  rect->xywh( x, y, w, h );
  CPPUNIT_ASSERT_EQUAL( 0.5, x );
  CPPUNIT_ASSERT_EQUAL( 2.0, y );
  CPPUNIT_ASSERT_EQUAL( 1.0, w );
  CPPUNIT_ASSERT_EQUAL( 1.5, h );

  rect = svg->child<Rectangle>( "rect3" );
  CPPUNIT_ASSERT( rect );
  rect->xywh( x, y, w, h );
  CPPUNIT_ASSERT_EQUAL( 3.0, x );
  CPPUNIT_ASSERT_EQUAL( 0.5, y );
  CPPUNIT_ASSERT_EQUAL( 1.5, w );
  CPPUNIT_ASSERT_EQUAL( 2.0, h );

  rect = svg->child<Rectangle>( "rect4" );
  CPPUNIT_ASSERT( rect );
  rect->xywh( x, y, w, h );
  CPPUNIT_ASSERT_EQUAL( 3.5, x );
  CPPUNIT_ASSERT_EQUAL( 3.0, y );
  CPPUNIT_ASSERT_EQUAL( 1.0, w );
  CPPUNIT_ASSERT_EQUAL( 0.5, h );

  rect = svg->child<Rectangle>( "border" );
  CPPUNIT_ASSERT( rect );
  rect->xywh( x, y, w, h );
//   <rect id=\"border\" x=\".01cm\" y=\".01cm\" width=\"4.98cm\" height=\"3.98cm\"
//         fill=\"none\" stroke=\"blue\" stroke-width=\".02cm\" />                   
  CPPUNIT_ASSERT_EQUAL( 0.01, x );
  CPPUNIT_ASSERT_EQUAL( 0.01, y );
  CPPUNIT_ASSERT_EQUAL( 4.98, w );
  CPPUNIT_ASSERT_EQUAL( 3.98, h );

  svg->scale( 20.0, 20.0 );
  make_image( svg, "simple_standalone.png" );
}

#define svg_simple_groups                                               \
"<?xml version=\"1.0\" standalone=\"no\"?>                              \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"                        \
  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">                 \
<svg width=\"5cm\" height=\"5cm\" version=\"1.1\"                       \
     xmlns=\"http://www.w3.org/2000/svg\">                              \
  <desc>Two groups, each of two rectangles                              \
  </desc>                                                               \
  <g id=\"group1\" fill=\"red\" >                                       \
    <rect id=\"r1\" x=\"1cm\" y=\"1cm\" width=\"1cm\" height=\"1cm\" /> \
    <rect id=\"r2\" x=\"3cm\" y=\"1cm\" width=\"1cm\" height=\"1cm\" /> \
  </g>                                                                  \
  <g id=\"group2\" fill=\"blue\" >                                      \
    <rect id=\"r3\" x=\"1cm\" y=\"3cm\" width=\"1cm\" height=\"1cm\" /> \
    <rect id=\"r4\" x=\"3cm\" y=\"3cm\" width=\"1cm\" height=\"1cm\" /> \
  </g>                                                                  \
  <!-- Show outline of canvas using 'rect' element -->                  \
  <rect x=\".01cm\" y=\".01cm\" width=\"4.98cm\" height=\"4.98cm\"      \
        fill=\"none\" stroke=\"blue\" stroke-width=\".02cm\" />         \
</svg>"

void SVGParserTest::svg_parser_simple_groups()
{
  Group::pointer g;
  Rectangle::pointer r;

  SVG::pointer svg = SVG::create( svg_simple_groups, SVG::MEMORY );

  CPPUNIT_ASSERT( 3 == svg->size() );
  CPPUNIT_ASSERT( 3 == svg->layer(0).size() );

  g = svg->child<Group>("group1");
  CPPUNIT_ASSERT( g );
  CPPUNIT_ASSERT( 2 == g->size() );
  CPPUNIT_ASSERT( 2 == g->layer(0).size() );
  r = g->child<Rectangle>("r1");
  CPPUNIT_ASSERT(r);
  r = g->child<Rectangle>("r2");
  CPPUNIT_ASSERT(r);

  g = svg->child<Group>("group2");
  CPPUNIT_ASSERT( g );
  CPPUNIT_ASSERT( 2 == g->size() );
  CPPUNIT_ASSERT( 2 == g->layer(0).size() );
  r = g->child<Rectangle>("r3");
  CPPUNIT_ASSERT(r);
  r = g->child<Rectangle>("r4");
  CPPUNIT_ASSERT(r);

  svg->scale( 20.0, 20.0 );
  make_image( svg, "simple_groups.png" );
}

#define SIMPLE_CIRCLE \
"<?xml version=\"1.0\" standalone=\"no\"?>                                      \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"                                \
    \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">                       \
<svg width=\"12cm\" height=\"4cm\" viewBox=\"0 0 1200 400\"                     \
    xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">                       \
  <desc>Example circle01 - circle filled with red and stroked with blue</desc>  \
  <!-- Show outline of canvas using 'rect' element -->                          \
  <rect x=\"1\" y=\"1\" width=\"1198\" height=\"398\"                           \
    fill=\"none\" stroke=\"blue\" stroke-width=\"2\"/>                          \
  <circle id=\"circle\" cx=\"600\" cy=\"200\" r=\"100\"                         \
    fill=\"red\" stroke=\"blue\" stroke-width=\"10\"  />                        \
</svg>"
    
void SVGParserTest::svg_parser_simple_circle()
{
  Circle::pointer circle;

  SVG::pointer svg = SVG::create( SIMPLE_CIRCLE, SVG::MEMORY );

  CPPUNIT_ASSERT( 2 == svg->size() );
  CPPUNIT_ASSERT( 2 == svg->layer(0).size() );

  circle = svg->child<Circle>( "circle" );
  CPPUNIT_ASSERT( circle );
  CPPUNIT_ASSERT_EQUAL( 600.0, circle->x() );
  CPPUNIT_ASSERT_EQUAL( 200.0, circle->y() );
  CPPUNIT_ASSERT_EQUAL( 100.0, circle->radius() );

  make_image( svg, "simple_circle.png" );
}

#define SIMPLE_PATH_TRIANGLE                                     \
"<?xml version=\"1.0\" standalone=\"no\"?>                       \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"                 \
  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">          \
<svg width=\"4cm\" height=\"4cm\" viewBox=\"0 0 400 400\"        \
     xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">       \
  <title>Example triangle01- simple example of a 'path'</title>  \
  <desc>A path that draws a triangle</desc>                      \
  <rect x=\"1\" y=\"1\" width=\"398\" height=\"398\"             \
    fill=\"none\" stroke=\"blue\" />                             \
  <path id=\"path\" d=\"M 100 100 L 300 100 L 200 300 z\"        \
    fill=\"red\" stroke=\"blue\" stroke-width=\"3\" />           \
</svg>"

void SVGParserTest::svg_parser_simple_path_triangle()
{
  Path::pointer path;

  SVG::pointer svg = SVG::create( SIMPLE_PATH_TRIANGLE, SVG::MEMORY );

  CPPUNIT_ASSERT( 2 == svg->size() );
  CPPUNIT_ASSERT( 2 == svg->layer(0).size() );

  path = svg->child<Path>( "path" );
  CPPUNIT_ASSERT( path );
  CPPUNIT_ASSERT_EQUAL( (size_t)4, path->size() );

  Path::iterator i = path->begin();
  CPPUNIT_ASSERT_EQUAL( PATH_MOVETO, (*i)->type() );
  CPPUNIT_ASSERT_EQUAL( 100.0, (*i)->x() );
  CPPUNIT_ASSERT_EQUAL( 100.0, (*i)->y() );

  i++;
  CPPUNIT_ASSERT_EQUAL( PATH_LINETO, (*i)->type() );
  CPPUNIT_ASSERT_EQUAL( 300.0, (*i)->x() );
  CPPUNIT_ASSERT_EQUAL( 100.0, (*i)->y() );
  
  i++;
  CPPUNIT_ASSERT_EQUAL( PATH_LINETO, (*i)->type() );
  CPPUNIT_ASSERT_EQUAL( 200.0, (*i)->x() );
  CPPUNIT_ASSERT_EQUAL( 300.0, (*i)->y() );
  
  i++;
  CPPUNIT_ASSERT_EQUAL( PATH_CLOSE, (*i)->type() );

  make_image( svg, "simple_path_triangle.png" );
}

#define SIMPLE_REFERENCE                                                               \
"<?xml version=\"1.0\" standalone=\"no\"?>                                             \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"                                       \
    \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">                              \
<svg width=\"10cm\" height=\"3cm\" viewBox=\"0 0 100 30\" version=\"1.1\"              \
    xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\"> \
  <desc>Example Use01 - Simple case of 'use' on a 'rect'</desc>                        \
  <defs>                                                                               \
    <rect id=\"MyRect\" width=\"60\" height=\"10\" fill=\"red\" stroke=\"gold\"/>      \
  </defs>                                                                              \
  <rect x=\".1\" y=\".1\" width=\"99.8\" height=\"29.8\"                               \
    fill=\"none\" stroke=\"blue\" stroke-width=\".2\" />                               \
  <use id=\"ref\" x=\"20\" y=\"10\" xlink:href=\"#MyRect\" />                          \
</svg>"
    
void SVGParserTest::svg_parser_simple_reference()
{
  Group::pointer g;
  Rectangle::pointer rect;
  
  SVG::pointer svg = SVG::create( SIMPLE_REFERENCE, SVG::MEMORY );

  CPPUNIT_ASSERT( 2 == svg->size() );
  CPPUNIT_ASSERT( 2 == svg->layer(0).size() );

  g = svg->child<Group>( "ref" );
  CPPUNIT_ASSERT( g );
  CPPUNIT_ASSERT( 1 == g->size() );
  CPPUNIT_ASSERT( 1 == g->layer(0).size() );
  CPPUNIT_ASSERT_EQUAL( 20.0, g->x() );
  CPPUNIT_ASSERT_EQUAL( 10.0, g->y() );

  rect = g->child<Rectangle>("MyRect");
  CPPUNIT_ASSERT_EQUAL( 0.0, rect->x() );
  CPPUNIT_ASSERT_EQUAL( 0.0, rect->y() );
  CPPUNIT_ASSERT_EQUAL( 60.0, rect->width() );
  CPPUNIT_ASSERT_EQUAL( 10.0, rect->height() );
  CPPUNIT_ASSERT_EQUAL( 1.0, rect->stroke()->width() );
  CPPUNIT_ASSERT(rect);

  make_image( svg, "simple_reference.png" );
}

#define SIMPLE_LINEAR_GRADIENT                                                      \
"<?xml version=\"1.0\" standalone=\"no\"?>                                          \
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"                                    \
  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">                             \
<svg width=\"8cm\" height=\"4cm\" viewBox=\"0 0 800 400\"                           \
     xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">                          \
  <desc>Example lingrad01 - fill a rectangle using a                                \
           linear gradient paint server</desc>                                      \
  <g id=\"group\">                                                                  \
    <defs>                                                                          \
      <linearGradient id=\"MyGradient\" x2=\"600\">                                 \
        <stop offset=\"5%\" stop-color=\"#F60\" />                                  \
        <stop offset=\"95%\" stop-color=\"#FF6\" />                                 \
      </linearGradient>                                                             \
    </defs>                                                                         \
    <!-- Outline the drawing area in blue -->                                       \
    <rect id=\"border\" fill=\"none\" stroke=\"blue\"                               \
          x=\"1\" y=\"1\" width=\"798\" height=\"398\"/>                            \
    <!-- The rectangle is filled using a linear gradient paint server -->           \
    <rect id=\"rect\" fill=\"url(#MyGradient)\" stroke=\"black\" stroke-width=\"5\" \
          x=\"100\" y=\"100\" width=\"600\" height=\"200\"/>                        \
  </g>                                                                              \
</svg>"

void SVGParserTest::svg_parser_simple_linear_gradient()
{
//   Group::pointer g;
//   Rectangle::pointer rect;
  
  SVG::pointer svg = SVG::create( SIMPLE_LINEAR_GRADIENT, SVG::MEMORY );

//   CPPUNIT_ASSERT( 2 == svg->size() );
//   CPPUNIT_ASSERT( 2 == svg->layer(0).size() );
// 
//   g = svg->child<Group>( "ref" );
//   CPPUNIT_ASSERT( g );
//   CPPUNIT_ASSERT( 1 == g->size() );
//   CPPUNIT_ASSERT( 1 == g->layer(0).size() );
//   CPPUNIT_ASSERT_EQUAL( 20.0, g->x() );
//   CPPUNIT_ASSERT_EQUAL( 10.0, g->y() );
// 
//   rect = g->child<Rectangle>("MyRect");
//   CPPUNIT_ASSERT_EQUAL( 0.0, rect->x() );
//   CPPUNIT_ASSERT_EQUAL( 0.0, rect->y() );
//   CPPUNIT_ASSERT_EQUAL( 60.0, rect->width() );
//   CPPUNIT_ASSERT_EQUAL( 10.0, rect->height() );
//   CPPUNIT_ASSERT_EQUAL( 1.0, rect->stroke()->width() );
//   CPPUNIT_ASSERT(rect);

  make_image( svg, "simple_linear_gradient.png" );
}

