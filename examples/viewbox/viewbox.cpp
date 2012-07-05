/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
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

void add_test(Papyrus::Canvas::pointer, Glib::ustring testname, int testnum, Papyrus::Viewbox::ALIGN align, Papyrus::Viewbox::MEET_OR_SLICE mos );

int main(int argc, char** argv) {

  Cairo::RefPtr<Cairo::ImageSurface> surface =
      Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 300, 20*160+190);

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

  Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();

  const char* mos_string[] = { "Meet", "Slice" };
  const char* align_string[] = {
   "None", "XMIN, YMIN", "XMID, YMIN", "XMAX, YMIN",
      "XMIN, YMID", "XMID, YMID", "XMAX, YMID",
      "XMIN, YMAX", "XMID, YMAX", "XMAX, YMAX"};

  Glib::ustring s1, s2, test_string;
  unsigned int testnum = 0;
  for (unsigned int i = Papyrus::Viewbox::MEET; i <= Papyrus::Viewbox::SLICE; i++) {
    s1 = mos_string[i];
    for (unsigned int j = Papyrus::Viewbox::ALIGN_NONE; j <= Papyrus::Viewbox::ALIGN_XMAX_YMAX; j++) {
    s2 = align_string[j];
      test_string = "Alignment: (" + s2 + ")  Type: " + s1;
      add_test(canvas, test_string, testnum+1, static_cast<Papyrus::Viewbox::ALIGN>(j), static_cast<Papyrus::Viewbox::MEET_OR_SLICE>(i) );
      testnum++;
    }
  }

  Papyrus::Text::pointer text = Papyrus::Text::create("Original Image", 20);
  text->set_fill( Cairo::SolidPattern::create_rgb( 0.0, 0.0, 0.0 ) );
  text->set_viewbox( Papyrus::Viewbox::create(10.0, 0.0, 280.0, 40.0) );
  canvas->add(text);

  Papyrus::Face::pointer face = Papyrus::Face::create(60.0);
  face->translate(150.0, 110.0);
  canvas->add(face);

  canvas->render( cr );

  surface->write_to_png("viewbox.png");

  std::cout << "Wrote \"viewbox.png\"" << std::endl;

  return 0;
}

void add_test(Papyrus::Canvas::pointer canvas, Glib::ustring testname, int testnum, Papyrus::Viewbox::ALIGN align, Papyrus::Viewbox::MEET_OR_SLICE mos ) {

std::cout << "Test: " << testnum << "   " << testname << std::endl;
  double y = 160.0 * (testnum-1)+ 190;
std::cout << "y: " << y << std::endl;
  Papyrus::Face::pointer face;
  Papyrus::Rectangle::pointer rectangle;

  Papyrus::Text::pointer text = Papyrus::Text::create(testname, 20);
  text->set_fill( Cairo::SolidPattern::create_rgb( 0.0, 0.0, 0.0 ) );
  text->set_viewbox( 10.0, y, 280.0, 40.0 );
  canvas->add(text);

  face = Papyrus::Face::create(60.0);
  face->set_viewbox( 10.0, y+50.0, 80.0, 40.0, align, mos );
  canvas->add(face);

  rectangle = Papyrus::Rectangle::create(80.0, 40.0);
  rectangle->translate(10.0, y+50.0);
  rectangle->set_stroke( Cairo::SolidPattern::create_rgba(0.0, 0.0, 1.0, 0.85) );
  canvas->add( rectangle );

  face = Papyrus::Face::create(60.0);
  face->set_viewbox( 110.0, y+50.0, 40.0, 80.0, align, mos );
  canvas->add(face);

  rectangle = Papyrus::Rectangle::create(40.0, 80.0);
  rectangle->translate(110.0, y+50.0);
  rectangle->set_stroke( Cairo::SolidPattern::create_rgba(0.0, 0.0, 1.0, 0.85) );
  canvas->add( rectangle );
}
