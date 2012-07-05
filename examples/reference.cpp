/***************************************************************************
 *   This example was initially created by Julius Ziegler and slightly     *
 *   modified by Rick Vinyard.                                             *
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
#include <gtkmm.h>
#include <papyrus-gtkmm.h>

#include <iostream>

int main( int argc, char** argv )
{
  Gtk::Main gtk_kit( argc, argv );
  Gtk::Window window;

  Papyrus::Gtk::Viewport viewport;
  window.add( viewport );

  window.show_all();

  Papyrus::Group::pointer rect_group = Papyrus::Group::create();
  Papyrus::Rectangle::pointer rect = Papyrus::Rectangle::create( 0, 0, 
      40, 5, Papyrus::RGBA( 0, 0, 1, .5 ) );

  rect_group->add( rect );
  rect_group->set_xy( -50, 30 );
  rect_group->set_rotation( 0.25*M_PI );

  viewport.canvas()->add( rect_group );

  Papyrus::Reference::pointer reference = Papyrus::Reference::create( 
      rect_group );

  reference->set_xy( 50, 0 );
  reference->rotate( 0.25*M_PI );

  viewport.canvas()->add( reference );
  
  Papyrus::Region region;
  double x,y,w,h;
  region = rect_group->global_extents();
  region.xywh(x,y,w,h);
  std::cout << "rect_group: " << x << ", " << y << ", " << w << ", " << h << std::endl;
  region = reference->global_extents();
  region.xywh(x,y,w,h);
  std::cout << "reference: " << x << ", " << y << ", " << w << ", " << h << std::endl;

  Gtk::Main::run( window );
}
