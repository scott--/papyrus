/* Boxed
 *
 */

#include <gtkmm.h>

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Boxed : public Gtk::Window
{
  public:
    Example_Boxed();
    virtual ~Example_Boxed();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Boxed::pointer m_Boxed;
    Papyrus::Drawable::pointer m_Owned;
    Papyrus::Annulus::pointer m_Watched;

};

//Called by DemoWindow;
Gtk::Window* do_Boxed()
{
  return new Example_Boxed();
}

Example_Boxed::Example_Boxed()
{
  Papyrus::Canvas::pointer canvas;
  
  set_title("Boxed Example");
  set_border_width(10);

  canvas = m_Viewport.canvas();
  canvas->set_id( "Canvas" );
  
  canvas->set_size( 500, 400 );

  canvas->clear();
  canvas->set_background( Papyrus::RGBA("white") );

//   Papyrus::Group::pointer g = Papyrus::Group::create();

  m_Boxed = Papyrus::Boxed::create("Boxed", Papyrus::RGBA(0.0,0.0,1.0,0.4), Papyrus::RGBA(0.0,0.0,1.0,0.7) );

  m_Owned = Papyrus::example_factory( Papyrus::GROUP );
//   m_Owned = Papyrus::Rectangle::create( -100.0, -100.0, 40.0, 80.0, Papyrus::RGBA("red"), Papyrus::RGBA("green") );
  m_Owned->set_id( "Owned" );
//   m_Owned->rotate( M_PI_4 );
//   g->add( m_Owned );
  m_Boxed->add( m_Owned );
//   canvas->add( m_Boxed );

  m_Watched = Papyrus::Annulus::create( 50, 40 );
  m_Watched->set_fill( Papyrus::RGBA("gold") );
  m_Watched->set_stroke( Papyrus::RGBA("goldenrod") );
  m_Watched->translate( 100, -100 );
  canvas->add( m_Watched );
  
  m_Boxed->watch( m_Watched );

//   m_Boxed->scale( 0.5, 0.5 );
//   m_Boxed->rotate( M_PI / 3.0 );
//   g->scale( 0.5, 0.5 );
//   g->add( m_Boxed );
//   canvas->add( g , Papyrus::Boxed::DEFAULT_LEVEL );
  canvas->add( m_Boxed, Papyrus::Boxed::DEFAULT_LEVEL );
  
  this->add( m_Viewport );
  show_all();
}

Example_Boxed::~Example_Boxed()
{
}


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
