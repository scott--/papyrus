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
#include "pick_simple.h"
#include <iostream>

using namespace Papyrus;

Simple::Simple()
{
  set_title("Papyrus Object Picking Demo");

  // Set up the scene that can be picked from
  Rectangle::pointer rect;
  Circle::pointer circle;
  RegularPolygon::pointer regularpolygon;
  Group::pointer group;

  // We'll have a group container with a rectangle, circle and octagon inside
  rect = Rectangle::create( "rectangle", 40, 80, RGBA("red") );
  circle = Circle::create( "circle", 60, RGBA("green") );
  regularpolygon = RegularPolygon::create( "octagon", 8, 40, RegularPolygon::ZERO_APOTHEM, RGBA("blue"));
  group = Group::create("group");
  
  group->add( rect );
  group->add( circle );
  group->add( regularpolygon );
  
  // Let's move things around a bit
  group->set_xy(20, 20);
  rect->translate(-50, -50);
  rect->rotate(45, DEGREES);

  // Add the group to the canvas
  m_viewport.canvas()->add( group );

  // Connect our callback to the papyrus event signal
  m_viewport.signal_papyrus_event().connect( sigc::mem_fun(*this, &Simple::on_papyrus_event));
  
  add(m_viewport);
  show_all();
}

Simple::~Simple()
{
}

bool Simple::on_papyrus_event( const Event::Event& event )
{
  // In this example we'll just look for button press events
  if ( event.type() == Event::BUTTON_PRESS )
  {
    // Downcast to the specific event type
    // This is dangerous if you don't check the event type first or have
    // this in a try/catch block
    const Event::ButtonPress& bpevent = dynamic_cast<const Event::ButtonPress&>(event);
    
    // Output where the raw button press event was at
    std::cout << "Button press at " << bpevent.x << ", " << bpevent.y << std::endl;
    
    // Select up to a 5 deep vector of the drawables at the button press
    // The vector is in descending order with the first element the topmost object
    Selection selection = m_viewport.canvas()->select(bpevent.x, bpevent.y, 5);

    // Output the selection
    std::cout << "Selected (" << selection.size() << ") ";
    for ( int i=0; i < selection.size(); i++ )
      std::cout << "\t" << selection[i]->id();
    std::cout << std::endl << std::endl;
  }

  // Returning true stops event propagation
  return true;
}
