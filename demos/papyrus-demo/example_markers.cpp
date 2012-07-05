/* Line Markers
 *
 */

#include <gtkmm.h>

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

class Example_markers : public Gtk::Window
{
  public:
    Example_markers();
    virtual ~Example_markers();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Polyline::pointer m_line;

    void on_marker_style_changed(Papyrus::MarkerPosition which);

    void on_marker_facing_changed(Papyrus::MarkerPosition which, Papyrus::Marker::Facing facing);

    Gtk::ComboBoxText m_start_combobox;
    Gtk::ComboBoxText m_end_combobox;

};

//Called by DemoWindow;
Gtk::Window* do_markers()
{
  return new Example_markers();
}

Example_markers::Example_markers()
{
  Gtk::VBox *vbox, *vbox2;
  Gtk::HBox *hbox;
  Gtk::RadioButton *rbutton;
  
  set_title("Line Markers Example");
  set_border_width(10);

  m_Viewport.canvas()->set_size( 500, 400 );

  vbox = Gtk::manage(new Gtk::VBox());
  vbox->pack_start( m_Viewport );
  m_line = Papyrus::Polyline::create();
  m_line->add_vertex(-100, 0);
  m_line->add_vertex(100, 0);
  m_line->set_stroke( Cairo::SolidPattern::create_rgb(0.0, 0.0, 1.0) );
  m_line->stroke()->set_width(3);

  m_line->set_marker(Papyrus::START_MARKER, Papyrus::Marker::create());
  m_line->marker(Papyrus::START_MARKER)->set_facing(Papyrus::Marker::LEFT);
  m_line->marker(Papyrus::START_MARKER)->stroke()->set_width(3);
  
  m_line->set_marker(Papyrus::END_MARKER, Papyrus::Marker::create());
  m_line->marker(Papyrus::END_MARKER)->set_facing(Papyrus::Marker::RIGHT);
  m_line->marker(Papyrus::END_MARKER)->stroke()->set_width(3);
  
  m_Viewport.canvas()->add( m_line );

  vbox->pack_start( *Gtk::manage( new Gtk::HSeparator() ) );

  hbox = Gtk::manage(new Gtk::HBox());
  vbox->pack_start( *hbox );

  vbox2 = Gtk::manage(new Gtk::VBox());
  vbox2->pack_start( *Gtk::manage(new Gtk::Label("Start Marker")) );
  vbox2->pack_start( m_start_combobox );
  Gtk::RadioButtonGroup start_facing_group;
  rbutton = Gtk::manage(new Gtk::RadioButton(start_facing_group, "Left"));
  rbutton->set_active();
  rbutton->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Example_markers::on_marker_facing_changed), Papyrus::START_MARKER, Papyrus::Marker::LEFT));
  vbox2->pack_start(*rbutton);
  rbutton = Gtk::manage(new Gtk::RadioButton(start_facing_group, "Right"));
  rbutton->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Example_markers::on_marker_facing_changed), Papyrus::START_MARKER, Papyrus::Marker::RIGHT));
  vbox2->pack_start(*rbutton);
  hbox->pack_start(*vbox2);

  vbox2 = Gtk::manage(new Gtk::VBox());
  vbox2->pack_start( *Gtk::manage(new Gtk::Label("End Marker")) );
  vbox2->pack_start( m_end_combobox );
  Gtk::RadioButtonGroup end_facing_group;
  rbutton = Gtk::manage(new Gtk::RadioButton(end_facing_group, "Left"));
  rbutton->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Example_markers::on_marker_facing_changed), Papyrus::END_MARKER, Papyrus::Marker::LEFT));
  vbox2->pack_start(*rbutton);
  rbutton = Gtk::manage(new Gtk::RadioButton(end_facing_group, "Right"));
  rbutton->set_active();
  rbutton->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &Example_markers::on_marker_facing_changed), Papyrus::END_MARKER, Papyrus::Marker::RIGHT));
  vbox2->pack_start(*rbutton);
  hbox->pack_start(*vbox2);

  for (unsigned i=Papyrus::Marker::FIRST_STYLE; i < Papyrus::Marker::LAST_STYLE; i++)
  {
    m_start_combobox.append_text( Papyrus::Marker::style_strings[i] );
    m_end_combobox.append_text( Papyrus::Marker::style_strings[i] );
  }

  m_start_combobox.signal_changed().connect( sigc::bind(sigc::mem_fun(*this, &Example_markers::on_marker_style_changed), Papyrus::START_MARKER));

  m_start_combobox.set_active(Papyrus::Marker::NONE);

  m_end_combobox.signal_changed().connect( sigc::bind(sigc::mem_fun(*this, &Example_markers::on_marker_style_changed), Papyrus::END_MARKER));

  m_end_combobox.set_active(Papyrus::Marker::NONE);

  this->add( *vbox );

  show_all();
}

Example_markers::~Example_markers()
{
}

void Example_markers::on_marker_style_changed(Papyrus::MarkerPosition which)
{
  int style;

  style = m_start_combobox.get_active_row_number();

  if ( style < 0 ) return;

  m_line->marker(which)->set_style((Papyrus::Marker::Style)style);
  
}

void Example_markers::on_marker_facing_changed(Papyrus::MarkerPosition which, Papyrus::Marker::Facing facing)
{
  m_line->marker(which)->set_facing(facing);
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
