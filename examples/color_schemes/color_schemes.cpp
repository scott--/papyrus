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
#include <algorithm>

#include <glibmm/ustring.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <papyrus.h>

using namespace Papyrus;

void draw_scheme(Colors scheme,
                 const Glib::ustring& name,
                 const Glib::ustring& title,
                 const Glib::ustring& footer );

int main()
{
  draw_scheme( primary_colors( ), "color_scheme_primary_colors", "Primary", "" );
  draw_scheme( secondary_colors( ), "color_scheme_secondary_colors", "Secondary", "" );
  draw_scheme( primary_secondary_colors( ), "color_scheme_primary_secondary_colors", "Primary + Secondary", "" );
  draw_scheme( tertiary_colors( ), "color_scheme_tertiary_colors", "Tertiary Colors", "" );
  draw_scheme( rgb_color_wheel( 12 ), "color_scheme_rgb_color_wheel_12", "RGB Color Wheel", "Bands = 12" );
  draw_scheme( complements( RGBA("turquoise4") ), "color_scheme_complements", "Complements", "" );
  draw_scheme( complements( shades( RGBA("turquoise4") ) ), "color_scheme_shades_complements", "Shaded and Complemented", "A scheme based on a color scheme" );
  draw_scheme( split_complements( RGBA("turquoise4") ), "color_scheme_split_complements", "Split Complements", "" );
  draw_scheme( triads( RGBA("turquoise4") ), "color_scheme_triads", "Triads", "" );
  draw_scheme( tetrads( RGBA("turquoise4") ), "color_scheme_tetrads", "Tetrads", "" );
  draw_scheme( analogous( RGBA("turquoise4"), 6 ), "color_scheme_analogous", "Analogous Colors", "" );
  draw_scheme( tints( RGBA("turquoise4") ), "color_scheme_tints", "Tints", "" );
  draw_scheme( tints( split_complements( HSBA(210, 1.0, 1.0) ) ), "color_scheme_tinted_split_complements", "Tinted Split Complements", "" );
  draw_scheme( shades( RGBA("turquoise4") ), "color_scheme_shades", "Shades", "" );
  draw_scheme( tones( RGBA("turquoise4") ), "color_scheme_tones", "Tones", "" );
  draw_scheme( monochromatic( RGBA("turquoise4"), 5, -0.25 ), "color_scheme_monochromatic", "Monochromatic", "" );
  return 0;
}

void draw_scheme(Colors scheme,
                 const Glib::ustring& name,
                 const Glib::ustring& title,
                 const Glib::ustring& footer )
{
  RGBA color;

  Cairo::RefPtr<Cairo::ImageSurface> surface =
    Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, std::max(scheme.size()*80+10UL,360UL), 200);

  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

  Canvas::pointer canvas = Canvas::create();
  Rectangle::pointer rectangle;
  Text::pointer title_text, footer_text;

  canvas->set_background( RGBA(1, 1, 1) );

  title_text = Text::create( title,
                                      40,
                                      "times",
                                      Cairo::FONT_SLANT_NORMAL,
                                      Cairo::FONT_WEIGHT_BOLD );
  title_text->set_fill( RGBA( 0, 0, 0 ) );
  title_text->translate( 10, 35 );
  canvas->add( title_text );

  footer_text = Text::create( footer,
                                       25,
                                       "sans",
                                       Cairo::FONT_SLANT_ITALIC,
                                       Cairo::FONT_WEIGHT_BOLD );
  footer_text->set_fill( RGBA( 0, 0, 0 ) );
  footer_text->translate( 10, 185 );
  canvas->add( footer_text );

  for (unsigned i = 0; i < scheme.size(); i++)
    {
      color = scheme[i];
      rectangle = Rectangle::create( 70.0, 110.0 );
      rectangle->translate( i*80+10, 50.0 );
      rectangle->set_fill( static_cast<RGBA>(scheme[i]) );
      canvas->add( rectangle );
    }

  Glib::ustring filename = name + Glib::ustring(".png");
  canvas->render( cr );
  surface->write_to_png(filename);
  std::cout << "Wrote color scheme " << name << " to file " << filename << std::endl;
}
