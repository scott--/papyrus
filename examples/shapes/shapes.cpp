/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
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
#include <string>
#include <iostream>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <papyrus-extras.h>
#include <math.h>

void make_image(Glib::ustring filename, void (shape_function)( Papyrus::Canvas::pointer ) );

void add_kochsnowflake( Papyrus::Canvas::pointer canvas ) {
  Papyrus::Drawable::pointer sf = Papyrus::example_factory( Papyrus::KOCHSNOWFLAKE, true, true );

  sf->translate( -75.0, -75.0-13.1 );
  sf->scale( 1.5, 1.5 );
  canvas->add( sf );
}

void add_bezierline( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_bezierline( true, true ) );
}

void add_beziergon( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_beziergon( true, true ) );
}

void add_group( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_group(true, true) );
}

void add_boxed( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_boxed(false, true) );
}

void add_rectangle( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_rectangle(true, true) );
}

void add_circle( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_circle(true, true) );
}

void add_arc( Papyrus::Canvas::pointer canvas ) {
  canvas->add( Papyrus::example_arc(true, true) );
}

void add_polyline_unfilled( Papyrus::Canvas::pointer canvas ) {
  // Create a polyline that will form a Z
  Papyrus::Polyline::pointer polyline = Papyrus::Polyline::create();

  // Add the polyline to the canvas
  canvas->add( polyline );

  // To color the lines of a polyline shape, set the stroke paint
  polyline->set_stroke( Papyrus::RGBA(1.0, 0.0, 1.0, 0.9) );
  
  // Set a line width
  polyline->stroke()->set_width(10);

  // Add the four points of the Z (upper left, upper right, lower left, lower right)
  polyline->add_vertex( -50, -50 );
  polyline->add_vertex(  50, -50 );
  polyline->add_vertex( -50,  50 );
  polyline->add_vertex(  50,  50 );

}

void add_polyline_filled( Papyrus::Canvas::pointer canvas ) {
  // Create a filled polyline that will form a U
  Papyrus::Polyline::pointer polyline = Papyrus::Polyline::create();

  // Add the polyline to the canvas
  canvas->add( polyline );

  // Set the fill color to red, with an alpha value of 0.9
  polyline->set_fill( Papyrus::RGBA(0.0, 1.0, 1.0, 0.9) );

  // To color the lines of a polyline shape, set the stroke paint
  polyline->set_stroke( Papyrus::RGBA(0.0, 0.0, 0.0, 0.9) );
  
  // Set a line width
  polyline->stroke()->set_width(10);

  // Add the four points of the U (upper left, lower left, lower right, upper right)
  polyline->add_vertex( -50, -50 );
  polyline->add_vertex( -50,  50 );
  polyline->add_vertex(  50,  50 );
  polyline->add_vertex(  50, -50 );

}

void add_polygon_star( Papyrus::Canvas::pointer canvas ) {
  // Create a filled polygon that will form a star
  Papyrus::Polygon::pointer polygon = Papyrus::Polygon::create();

  // Add the polygon to the canvas
  canvas->add( polygon );

  // Set the fill color to red, with an alpha value of 0.9
  polygon->set_fill( Papyrus::RGBA(0.0, 0.0, 1.0, 0.9) );

  // To color the lines of a polygon shape, set the stroke paint
  polygon->set_stroke( Papyrus::RGBA(1.0, 0.0, 0.0, 0.9) );
  
  // Set a line width
  polygon->stroke()->set_width(10);

  // Add the 10 points of the star
  for (double angle=-M_PI_2; angle < 1.5*M_PI; angle += M_PI/2.5) {
    polygon->add_vertex( cos(angle)*80, sin(angle)*80);
    polygon->add_vertex( cos(angle+M_PI/5.0)*40, sin(angle+M_PI/5.0)*40);
  }

}

void add_polygon_u( Papyrus::Canvas::pointer canvas ) {
  // Create a filled polygon that will form a U
  Papyrus::Polygon::pointer polygon = Papyrus::Polygon::create();

  // Add the polygon to the canvas
  canvas->add( polygon );

  // Set the fill color to red, with an alpha value of 0.9
  polygon->set_fill( Papyrus::RGBA(0.0, 1.0, 1.0, 0.9) );

  // To color the lines of a polygon shape, set the stroke paint
  polygon->set_stroke( Papyrus::RGBA(0.0, 0.0, 0.0, 0.9) );
  
  // Set a line width
  polygon->stroke()->set_width(10);

  // Add the four points of the U (upper left, lower left, lower right, upper right)
  polygon->add_vertex( -50, -50 );
  polygon->add_vertex( -50,  50 );
  polygon->add_vertex(  50,  50 );
  polygon->add_vertex(  50, -50 );
}

void add_regularpolygon_radius( Papyrus::Canvas::pointer canvas ) {
  // Create a filled hexagon (sides=6, radius=75)
  Papyrus::RegularPolygon::pointer hexagon = Papyrus::RegularPolygon::create(6, 75);

  // Add the hexagon to the canvas
  canvas->add( hexagon );

  // Set the fill color to red, with an alpha value of 0.9
  hexagon->set_fill( Papyrus::RGBA(1.0, 0.0, 1.0, 0.9) );

  // To color the lines of a hexagon shape, set the stroke paint
  hexagon->set_stroke( Papyrus::RGBA(0.0, 0.0, 0.0, 0.9) );
}

void add_regularpolygon_apothem( Papyrus::Canvas::pointer canvas ) {
  // Create a filled hexagon (sides=6, radius=75)
  Papyrus::RegularPolygon::pointer hexagon =
    Papyrus::RegularPolygon::create(6, 75, Papyrus::RegularPolygon::ZERO_APOTHEM);

  // Add the hexagon to the canvas
  canvas->add( hexagon );

  // Set the fill color to red, with an alpha value of 0.9
  hexagon->set_fill( Papyrus::RGBA(0.0, 1.0, 1.0, 0.9) );

  // To color the lines of a hexagon shape, set the stroke paint
  hexagon->set_stroke( Papyrus::RGBA(0.0, 0.0, 0.0, 0.9) );
}

void add_text( Papyrus::Canvas::pointer canvas ) {
  // Create a text object
  Papyrus::Text::pointer text = Papyrus::Text::create("Text", 40);

  // Add the text to the canvas
  canvas->add( text );

  // Set the fill color to red, with an alpha value of 0.9
  text->set_fill( Papyrus::RGBA(0.0, 1.0, 0.0, 0.9) );

  // To color the lines of a text shape, set the stroke paint
  text->set_stroke( Papyrus::RGBA(0.0, 0.0, 0.0, 0.9) );
}


int main(int argc, char** argv) {
  make_image("arc.png", add_arc);
  make_image("boxed.png", add_boxed);
  make_image("bezierline.png", add_bezierline);
  make_image("beziergon.png", add_beziergon);
  make_image("circle.png", add_circle);
  make_image("group.png", add_group);
  make_image("polyline.png", add_polyline_unfilled);
  make_image("polyline_filled.png", add_polyline_filled);
  make_image("polygon_star.png", add_polygon_star);
  make_image("polygon_u.png", add_polygon_u);
  make_image("rectangle.png", add_rectangle);
  make_image("regularpolygon_radius.png", add_regularpolygon_radius);
  make_image("regularpolygon_apothem.png", add_regularpolygon_apothem);
  make_image("text.png", add_text);
  make_image("kochsnowflake.png", add_kochsnowflake);
  return 0;
}

void make_image(Glib::ustring filename, void (shape_function)( Papyrus::Canvas::pointer ) ) {
  Cairo::RefPtr<Cairo::ImageSurface> surface =
      Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 200, 200);

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

  Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();
  canvas->translate( 100, 100 );
//   canvas->set_background( Cairo::SolidPattern::create_rgb(0.9, 0.9, 0.9) );
  Papyrus::Polyline::pointer line = Papyrus::Polyline::create();
  line->add_vertex(0, -100);
  line->add_vertex(0, 100);
  line->set_stroke( Cairo::SolidPattern::create_rgb(0.0, 0.0, 1.0) );
  line->stroke()->set_width(2);
  canvas->add( line );
  line = Papyrus::Polyline::create();
  line->add_vertex(-100, 0);
  line->add_vertex(100, 0);
  line->set_stroke( Cairo::SolidPattern::create_rgb(0.0, 0.0, 1.0) );
  line->stroke()->set_width(2);
  canvas->add( line );
  shape_function( canvas );

  canvas->render( cr );

  surface->write_to_png(filename);

  std::cout << "Wrote png file \"" << filename << "\"" << std::endl;

}
