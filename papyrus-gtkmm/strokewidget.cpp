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
#include "strokewidget.h"

namespace Papyrus
{
  namespace Gtk
  {

    StrokeWidget::StrokeWidget ( bool use_preview )
        : m_expander ( 0x00 ),
        m_width_adjustment ( 1.0, 0.0, 1000.0, 0.5, 2.0 ),
        m_width_entry ( m_width_adjustment, 0.0, 3 ),
        m_miter_limit_adjustment ( 0.0, 0.0, 1000.0, 1.0, 5.0 ),
        m_miter_limit_entry ( m_miter_limit_adjustment, 0.0, 3 ),
        m_stroke ( Papyrus::Stroke::create() )
    {
      this->set_row_spacings ( 5 );
      this->set_col_spacings ( 5 );
      this->set_border_width ( 10 );
      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Pattern:", ::Gtk::ALIGN_RIGHT ) ),       0, 1, 0, 1 );
      this->attach ( m_color_button, 1, 2, 0, 1 );
      m_color_button.set_use_alpha();
      m_color_button.signal_color_set().connect ( sigc::mem_fun ( *this, &StrokeWidget::on_color_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Width:", ::Gtk::ALIGN_RIGHT ) ),         0, 1, 1, 2 );
      this->attach ( m_width_entry, 1, 2, 1, 2 );
      m_width_entry.signal_value_changed().connect ( sigc::mem_fun ( *this, &StrokeWidget::on_width_changed ) );

      m_line_join_buttonbox.set_size ( SIZE_SMALL );
      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Join:", ::Gtk::ALIGN_RIGHT ) ),          0, 1, 2, 3 );
      this->attach ( m_line_join_buttonbox, 1, 2, 2, 3 );
      m_line_join_buttonbox.signal_selected().connect ( sigc::mem_fun ( *this, &StrokeWidget::on_line_join_changed ) );

//  this->attach( *::Gtk::manage( new ::Gtk::Label("Miter Limit:", ::Gtk::ALIGN_RIGHT) ),   0, 1, 3, 4 );
//  this->attach( m_miter_limit_entry, 1, 2, 3, 4 );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Cap:", ::Gtk::ALIGN_RIGHT ) ),           0, 1, 4, 5 );
      this->attach ( m_line_cap_buttonbox, 1, 2, 4, 5 );
      m_line_cap_buttonbox.signal_selected().connect ( sigc::mem_fun ( *this, &StrokeWidget::on_line_cap_changed ) );

//  this->attach( *::Gtk::manage( new ::Gtk::Label("Dash:", ::Gtk::ALIGN_RIGHT) ),          0, 1, 5, 6 );

      this->set_use_preview ( use_preview );
    }


    StrokeWidget::~StrokeWidget()
    {
    }

    bool StrokeWidget::use_preview( )
    {
      return m_expander != 0x00;
    }

    void StrokeWidget::set_use_preview ( bool use )
    {
      if ( m_expander == 0x00 && use )
      {
        m_expander = ::Gtk::manage ( new ::Gtk::Expander ( "Line Style Preview" ) );

        m_line = Papyrus::Polyline::create();
        m_line->add_vertex ( -40, 10 );
        m_line->add_vertex ( 0, -10 );
        m_line->add_vertex ( 40, 10 );
        m_stroke->set_paint ( RGBA( 0.0, 0.0, 0.0 ) );
        m_line->set_stroke ( m_stroke );

        m_viewport = ::Gtk::manage ( new Papyrus::Gtk::Viewport() );
        m_viewport->canvas()->add ( m_line );
        m_viewport->set_size_request ( -1, 60 );

        ::Gtk::Frame* frame = ::Gtk::manage ( new ::Gtk::Frame() );
        frame->set_shadow_type ( ::Gtk::SHADOW_ETCHED_IN );
        frame->add ( *m_viewport );

        m_expander->add ( *frame );
        m_expander->set_expanded();
        m_expander->show_all();

        this->attach ( *m_expander, 1, 2, 9, 10 );
      }
      else if ( m_expander != 0x00 && ( !use ) )
      {
        this->remove ( *m_expander );
        m_line.reset();
      }
    }

    Stroke::pointer StrokeWidget::stroke( ) const
    {
      return m_stroke;
    }

    void StrokeWidget::on_color_changed( )
    {
      double r, g, b, a;
      r = m_color_button.get_color().get_red_p();
      g = m_color_button.get_color().get_green_p();
      b = m_color_button.get_color().get_blue_p();
      a = m_color_button.get_alpha() / 65535.0;
      m_stroke->set_paint( RGBA( r, g, b, a ) );
    }

    void StrokeWidget::on_width_changed( )
    {
      m_stroke->set_width ( m_width_entry.get_value() );
    }

    void StrokeWidget::on_line_join_changed ( Cairo::LineJoin join )
    {
      m_stroke->set_join ( join );
    }

    void StrokeWidget::on_line_cap_changed ( Cairo::LineCap cap )
    {
      m_stroke->set_cap ( cap );
    }

  }

}
