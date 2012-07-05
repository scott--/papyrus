/* Freezing/Thawing
 *
 */

#include <gtkmm.h>

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_FreezeThaw : public Gtk::Window
{
  public:
    Example_FreezeThaw();
    virtual ~Example_FreezeThaw();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Circle::pointer circle;
    Papyrus::Rectangle::pointer rectangle;
    Papyrus::Arc::pointer arc;
    Papyrus::Group::pointer group;
    
    Gtk::RadioButton* radio[10];
    
    Gtk::Button* button[10];
    
    void on_frozen_thawed_toggled( int which );
    
    void on_change_drawable( int which );

};

//Called by DemoWindow;
Gtk::Window* do_freeze_thaw()
{
  return new Example_FreezeThaw();
}

Example_FreezeThaw::Example_FreezeThaw()
{
  Papyrus::Canvas::pointer canvas;
  int i;
  
  const char* rb_strings[] = { "Thawed", "Frozen" };
    
  for (i = 0; i < 10; i++)
  {
    radio[i] = Gtk::manage(new Gtk::RadioButton(rb_strings[i%2]) );
    radio[i]->signal_toggled().connect( sigc::bind( sigc::mem_fun(*this, &Example_FreezeThaw::on_frozen_thawed_toggled), i ) );
    if ( i%2 == 1 ) 
    {
      Gtk::RadioButtonGroup group = radio[i-1]->get_group();
      radio[i]->set_group( group );
    }
  }
  
  set_title("Freeze/Thaw Example");
  set_border_width(10);

  canvas = m_Viewport.canvas();
  canvas->set_id( "Canvas" );
  
  canvas->set_size( 500, 400 );

  canvas->clear();
  canvas->set_background( Papyrus::RGBA("white") );

  rectangle = Papyrus::example_rectangle ( true, true );
  circle = Papyrus::example_circle ( true, true );
  arc = Papyrus::example_arc ( true, true );
  group = Papyrus::Group::create();

    // Add the shapes to the canvas and group
  group->add ( rectangle );
  group->add ( circle );
  canvas->add ( group );
  canvas->add ( arc );

    // Translate the shapes so they don't necessarily overlap
  rectangle->set_xywh ( 0, -60, 50, 30 );
  circle->translate ( 40, 20 );
  circle->set_radius ( 25 );
  arc->translate ( 0, 20 );
  
  Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox());
  
  hbox->pack_start(m_Viewport);
  
  const char* labels[] = { "Canvas", "Arc", "Circle-Rectangle Group", "Circle", "Rectangle" };
    
  Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox());
  
  vbox->pack_start(*hbox);
  
  vbox->pack_start( * Gtk::manage(new Gtk::HSeparator()), Gtk::PACK_EXPAND_WIDGET, 15 );
  
  Gtk::Table* table = Gtk::manage(new Gtk::Table(5, 7));
  
  vbox->pack_start(*table);
  table->set_col_spacings(10);
  
  for (int i=0; i<5; i++)
  {
    table->attach( *Gtk::manage(new Gtk::Label(labels[i])), i, i+1, 0, 1);
    table->attach(*radio[i*2], i, i+1, 1, 2);
    table->attach(*radio[i*2+1], i, i+1, 2, 3);
    if ( i != 0 )
    {
      button[i*2] = Gtk::manage(new Gtk::Button("Change Position"));
      button[i*2]->signal_clicked().connect( sigc::bind(sigc::mem_fun(*this, &Example_FreezeThaw::on_change_drawable), i*2));
      table->attach( *button[i*2], i, i+1, 3, 4);
      if ( i != 2 )
      {
        button[i*2+1] = Gtk::manage(new Gtk::Button("Change Fill"));
        button[i*2+1]->signal_clicked().connect( sigc::bind(sigc::mem_fun(*this, &Example_FreezeThaw::on_change_drawable), i*2+1));
        table->attach( *button[i*2+1], i, i+1, 4, 5);
      }
    }
  }
  
  this->add( *vbox );
  show_all();
}

Example_FreezeThaw::~Example_FreezeThaw()
{
}

void Example_FreezeThaw::on_frozen_thawed_toggled( int which )
{
  if ( not radio[which]->get_active() ) return;
  
  switch (which)
  {
    case 0: m_Viewport.canvas()->thaw();    break;
    case 1: m_Viewport.canvas()->freeze();  break;
    case 2: arc->thaw();                    break;
    case 3: arc->freeze();                  break;
    case 4: group->thaw();                  break;
    case 5: group->freeze();                break;
    case 6: circle->thaw();                 break;
    case 7: circle->freeze();               break;
    case 8: rectangle->thaw();              break;
    case 9: rectangle->freeze();            break;
  }
}

void change_position( Papyrus::Drawable::pointer d )
{
  Glib::Rand rand;
  int x, y;
  x = rand.get_int_range(-200, 200);
  y = rand.get_int_range(-150, 150);
  d->set_xy( x, y );
}

void change_fill( Papyrus::Shape::pointer s )
{
  Glib::Rand rand;
  double r, g, b;
  r = rand.get_double_range(0.3, 1.0);
  g = rand.get_double_range(0.3, 1.0);
  b = rand.get_double_range(0.3, 1.0);
  s->set_fill( Papyrus::RGBA(r, g, b) );
}

void Example_FreezeThaw::on_change_drawable( int which )
{
  switch (which)
  {
    case 2:  change_position(arc); break;
    case 3:  change_fill(arc);     break;
    case 4:  change_position(group); break;
    case 6:  change_position(circle); break;
    case 7:  change_fill(circle); break;
    case 8:  change_position(rectangle); break;
    case 9:  change_fill(rectangle); break;
  }
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
