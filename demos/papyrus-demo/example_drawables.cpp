/* Drawables
 *
 */

#include <gtkmm.h>

#include <papyrus-extras.h>
#include <papyrus-gtkmm/scrolledviewport.h>

class Example_drawables : public Gtk::Window
{
  public:
    Example_drawables();
    virtual ~Example_drawables();

  protected:
  //Member widgets:
    Papyrus::Gtk::ScrolledViewport m_ScrolledViewport;
    Papyrus::Zoomer::pointer m_Zoomer;
    Papyrus::Drawable::pointer m_Drawable;

    void redraw_canvas();

    Gtk::CheckButton m_fill_button, m_stroke_button;
    Gtk::VBox m_vbox;
    Gtk::ComboBoxText m_combobox;
};

//Called by DemoWindow;
Gtk::Window* do_drawables()
{
  return new Example_drawables();
}

Example_drawables::Example_drawables():
    m_fill_button("Fill"),
    m_stroke_button("Stroke")
{
  set_title("drawables Example");
  set_border_width(10);

  Papyrus::Gtk::Viewport& viewport = m_ScrolledViewport.viewport();

  m_Zoomer = Papyrus::Zoomer::create( );
  viewport.add_controller( m_Zoomer );
  viewport.set_size_request( 500, 400 );
  m_Zoomer->add( m_ScrolledViewport.canvas() );

  m_vbox.pack_start( m_ScrolledViewport );
  m_vbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  m_vbox.pack_start( m_combobox );
  m_vbox.pack_start( m_fill_button );
  m_vbox.pack_start( m_stroke_button );

  for (unsigned i=Papyrus::DRAWABLE_START; i < Papyrus::DRAWABLE_END; i++)
    m_combobox.append_text( Papyrus::DrawableStrings[i] );

  m_combobox.signal_changed().connect( sigc::mem_fun(*this, &Example_drawables::redraw_canvas));
  m_fill_button.signal_toggled().connect( sigc::mem_fun(*this, &Example_drawables::redraw_canvas));
  m_stroke_button.signal_toggled().connect( sigc::mem_fun(*this, &Example_drawables::redraw_canvas));

  m_fill_button.set_active(true);
  m_stroke_button.set_active(true);
  m_combobox.set_active(Papyrus::KOCHSNOWFLAKE);

  this->add( m_vbox );

  show_all();
}

Example_drawables::~Example_drawables()
{
}

void Example_drawables::redraw_canvas( )
{
  int which;
  Papyrus::Polyline::pointer line;

  which = m_combobox.get_active_row_number();

  if ( which < 0 )
    return;

  m_ScrolledViewport.canvas()->clear();
  m_ScrolledViewport.canvas()->set_background( Papyrus::RGBA("white") );

  line = Papyrus::Polyline::create();
  line->add_vertex(0, -500);
  line->add_vertex(0, 500);
  line->set_stroke( Cairo::SolidPattern::create_rgb(0.0, 0.0, 1.0) );
  line->stroke()->set_width(1);
  m_ScrolledViewport.canvas()->add( line );

  line = Papyrus::Polyline::create();
  line->add_vertex(-500, 0);
  line->add_vertex(500, 0);
  line->set_stroke( Cairo::SolidPattern::create_rgb(0.0, 0.0, 1.0) );
  line->stroke()->set_width(1);
  m_ScrolledViewport.canvas()->add( line );

  m_Drawable = Papyrus::example_factory( which,
                                         m_fill_button.get_active(),
                                         m_stroke_button.get_active() );

  m_ScrolledViewport.canvas()->add( m_Drawable );
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
