/* View Boxes
 *
 * Papyrus' concept of view boxes is based directly on SVG view boxes. The concepts
 * of MEET or SLICE determine whether a shape will be scaled to fit within the
 * bounds of a box (MEET), or whether the shaped will be sliced at the boundary.
 *
 * Additional concepts include the directives XMIN, XMID, XMAX and YMIN, YMID, YMAX.
 * When MEET is used, these directives control the placement of the scaled image.
 * When SLICE is used, these directives control which section of the image is sliced.
 */

#include "gtkmm.h"

#include <papyrus-extras/face.h>
#include <papyrus/rectangle.h>
#include <papyrus-gtkmm/viewport.h>

class Example_Viewbox : public Gtk::Window
{
public:
  Example_Viewbox();
  virtual ~Example_Viewbox();

protected:
  //Member widgets:
  Papyrus::Gtk::Viewport m_Viewport[2][10][2];
  Gtk::HBox m_FrameHBox[2][10];
  Gtk::Frame m_Frame[2][10];
  Gtk::Frame m_original_frame[2];
  Papyrus::Gtk::Viewport m_original_viewport[2];
  Gtk::VBox m_VBox;
  Gtk::Frame m_mos_frame[2];
  Gtk::Table m_Table[2];
};

//Called by DemoWindow;
Gtk::Window* do_Viewbox()
{
  return new Example_Viewbox();
}

Example_Viewbox::Example_Viewbox()
{
  const char* align_string[] = {
    "None",
    "XMIN & YMIN", "XMID & YMIN", "XMAX & YMIN",
    "XMIN & YMID", "XMID & YMID", "XMAX & YMID",
    "XMIN & YMAX", "XMID & YMAX", "XMAX & YMAX"};

  set_title("View Boxes");
  set_border_width(10);

  this->add( m_VBox );

  m_original_frame[0].set_label( "Original" );
  m_original_frame[1].set_label( "Original" );
  m_mos_frame[0].set_label( "MEET" );
  m_mos_frame[1].set_label( "SLICE" );

  for (int i=0; i<=1; i++) {
    m_Table[i].set_border_width(10);
    m_mos_frame[i].add( m_Table[i] );
    m_VBox.pack_start( m_mos_frame[i], Gtk::PACK_EXPAND_WIDGET, 10);
  }

  Papyrus::Face::pointer face;
  Papyrus::Rectangle::pointer rectangle;
  int x, y;

  for ( int mos=0; mos <= 1; mos++ ) {
    for ( int n = 0; n <= 9; n++ ) {
      if ( n == 0 ) {
        x = 0;
        y = 1;
      }
      else {
        x = (n-1)%3+1;
        y = (n-1)/3;
      }
        m_Frame[mos][n].set_label( align_string[n] );
        m_Frame[mos][n].add( m_FrameHBox[mos][n] );
        m_Table[mos].attach( m_Frame[mos][n], x, x+1, y, y+1);

        m_Viewport[mos][n][0].canvas()->scroll_to(-25, -12.5);
        m_Viewport[mos][n][0].set_size_request(50, 25);
        face = Papyrus::Face::create(30.0);
        face->set_viewbox( Papyrus::Viewbox::create(0.0, 0.0, 50.0, 25.0, static_cast<Papyrus::Viewbox::ALIGN>(n), static_cast<Papyrus::Viewbox::MEET_OR_SLICE>(mos)) );
        m_Viewport[mos][n][0].canvas()->add(face);
        rectangle = Papyrus::Rectangle::create(50.0, 25.0);
        rectangle->set_stroke( Cairo::SolidPattern::create_rgba(0.0, 0.0, 1.0, 0.85) );
        m_Viewport[mos][n][0].canvas()->add( rectangle );

        m_Viewport[mos][n][1].canvas()->scroll_to(-12.5, -25);
        m_Viewport[mos][n][1].set_size_request(25, 50);
        face = Papyrus::Face::create(30.0);
        face->set_viewbox( Papyrus::Viewbox::create(0.0, 0.0, 25.0, 50.0, static_cast<Papyrus::Viewbox::ALIGN>(n), static_cast<Papyrus::Viewbox::MEET_OR_SLICE>(mos)) );
        m_Viewport[mos][n][1].canvas()->add(face);
        rectangle = Papyrus::Rectangle::create(25.0, 50.0);
        rectangle->set_stroke( Cairo::SolidPattern::create_rgba(0.0, 0.0, 1.0, 0.85) );
        m_Viewport[mos][n][1].canvas()->add( rectangle );

        m_FrameHBox[mos][n].pack_start( m_Viewport[mos][n][0], Gtk::PACK_EXPAND_WIDGET,3);
        m_FrameHBox[mos][n].pack_start( m_Viewport[mos][n][1], Gtk::PACK_EXPAND_WIDGET,3);
        m_FrameHBox[mos][n].set_border_width(3);

//                 std::cout << mos << ", " << x << ", " << y << ": " << align_string[n] << std::endl;
//         m_vbox.pack_start( m_frame[i], Gtk::PACK_EXPAND_WIDGET, 10);
    }
  }

  for ( int i = 0; i <= 1; i++ ) {
    m_original_viewport[i].canvas()->scroll_to(-30, -30);
  m_original_viewport[i].set_size_request(60, 60);
  face = Papyrus::Face::create(30.0);
  face->translate(30, 30);
  m_original_viewport[i].canvas()->add(face);
  rectangle = Papyrus::Rectangle::create(60.0, 60.0);
  rectangle->set_stroke( Cairo::SolidPattern::create_rgba(0.0, 0.0, 1.0, 0.85) );
  m_original_viewport[i].canvas()->add( rectangle );
  m_original_frame[i].add(m_original_viewport[i]);
  m_Table[i].attach( m_original_frame[i], 0, 1, 0, 1);
  }

  this->show_all();
}

Example_Viewbox::~Example_Viewbox()
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
