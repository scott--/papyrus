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
#include "markerwidget.h"

namespace Papyrus
{
  namespace Gtk
  {

    MarkerWidget::MarkerWidget ( bool use_preview )
        : m_expander ( 0x00 ),
        m_marker_width_adjustment ( 15.0, 0.0, 100.0, 0.25, 2.0 ),
        m_marker_width_entry ( m_marker_width_adjustment, 0.0, 3 ),
        m_marker_height_adjustment ( 15.0, 0.0, 100.0, 0.25, 2.0 ),
        m_marker_height_entry ( m_marker_height_adjustment, 0.0, 3 ),
        m_line_width_adjustment ( 2.0, 0.0, 1000.0, 0.5, 2.0 ),
        m_line_width_entry ( m_line_width_adjustment, 0.0, 3 )
    {
      m_marker = Papyrus::Marker::create ( Papyrus::Marker::NONE, 15, 15 );
      m_marker->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 0.0 ) );
      m_marker->stroke()->set_width ( 2 );

      this->set_row_spacings ( 5 );
      this->set_col_spacings ( 5 );
      this->set_border_width ( 10 );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Style:", ::Gtk::ALIGN_RIGHT ) ),       0, 1, 0, 1 );
      this->attach ( m_marker_combobox, 1, 2, 0, 1 );
      m_marker_combobox.signal_changed().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_marker_style_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Marker Width:", ::Gtk::ALIGN_RIGHT ) ),         0, 1, 1, 2 );
      this->attach ( m_marker_width_entry, 1, 2, 1, 2 );
      m_marker_width_entry.signal_value_changed().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_marker_width_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Marker Height:", ::Gtk::ALIGN_RIGHT ) ),         0, 1, 2, 3 );
      this->attach ( m_marker_height_entry, 1, 2, 2, 3 );
      m_marker_height_entry.signal_value_changed().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_marker_height_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Fill Color:", ::Gtk::ALIGN_RIGHT ) ),       0, 1, 3, 4 );
      this->attach ( m_fill_color_button, 1, 2, 3, 4 );
      m_fill_color_button.set_use_alpha();
      m_fill_color_button.signal_color_set().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_fill_color_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Outline Color:", ::Gtk::ALIGN_RIGHT ) ),       0, 1, 4, 5 );
      this->attach ( m_stroke_color_button, 1, 2, 4, 5 );
      m_stroke_color_button.set_use_alpha();
      m_stroke_color_button.signal_color_set().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_stroke_color_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Line Width:", ::Gtk::ALIGN_RIGHT ) ),         0, 1, 5, 6 );
      this->attach ( m_line_width_entry, 1, 2, 5, 6 );
      m_line_width_entry.signal_value_changed().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_line_width_changed ) );

      m_line_join_buttonbox.set_size ( SIZE_SMALL );
      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Join:", ::Gtk::ALIGN_RIGHT ) ),          0, 1, 6, 7 );
      this->attach ( m_line_join_buttonbox, 1, 2, 6, 7 );
      m_line_join_buttonbox.signal_selected().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_line_join_changed ) );

      this->attach ( *::Gtk::manage ( new ::Gtk::Label ( "Cap:", ::Gtk::ALIGN_RIGHT ) ),           0, 1, 7, 8 );
      this->attach ( m_line_cap_buttonbox, 1, 2, 7, 8 );
      m_line_cap_buttonbox.signal_selected().connect ( sigc::mem_fun ( *this, &MarkerWidget::on_line_cap_changed ) );

      this->set_use_preview ( use_preview );
    }


    MarkerWidget::~MarkerWidget()
    {
    }

    Papyrus::Marker::pointer MarkerWidget::get_marker( )
    {
      return papyrus_dynamic_pointer_cast<Papyrus::Marker> ( m_marker->clone() );
    }

    bool MarkerWidget::use_preview( )
    {
      return m_expander != 0x00;
    }

    void MarkerWidget::set_use_preview ( bool use )
    {
      if ( m_expander == 0x00 && use )
      {
        m_expander = ::Gtk::manage ( new ::Gtk::Expander ( "Marker Preview" ) );

        m_line = Papyrus::Polyline::create();
        m_line->add_vertex ( -40, 10 );
        m_line->add_vertex ( 0, -10 );
        m_line->add_vertex ( 40, 10 );
        m_line->set_stroke( Stroke::create() );

        this->update_line_marker();

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

    void MarkerWidget::on_marker_style_changed()
    {
      m_marker->set_style ( m_marker_combobox.style() );
      m_marker->set_facing ( m_marker_combobox.facing() );
      this->update_line_marker();
    }

    void MarkerWidget::on_fill_color_changed( )
    {
      double r, g, b, a;
      r = m_fill_color_button.get_color().get_red_p();
      g = m_fill_color_button.get_color().get_green_p();
      b = m_fill_color_button.get_color().get_blue_p();
      a = m_fill_color_button.get_alpha() / 65535.0;
      m_marker->set_fill( Cairo::SolidPattern::create_rgba ( r, g, b, a ) );
      this->update_line_marker();
    }

    void MarkerWidget::on_stroke_color_changed( )
    {
      double r, g, b, a;
      r = m_stroke_color_button.get_color().get_red_p();
      g = m_stroke_color_button.get_color().get_green_p();
      b = m_stroke_color_button.get_color().get_blue_p();
      a = m_stroke_color_button.get_alpha() / 65535.0;
      m_marker->stroke()->set_paint( RGBA( r, g, b, a ) );
      if ( m_line )
      {
        m_line->stroke()->set_paint( RGBA( r, g, b, a ) );
        this->update_line_marker();
      }
    }

    void MarkerWidget::on_marker_width_changed()
    {
      m_marker->set_width ( m_marker_width_entry.get_value() );
      this->update_line_marker();
    }

    void MarkerWidget::on_marker_height_changed()
    {
      m_marker->set_height ( m_marker_height_entry.get_value() );
      this->update_line_marker();
    }

    void MarkerWidget::on_line_width_changed( )
    {
      m_marker->stroke()->set_width ( m_line_width_entry.get_value() );

      if ( m_line )
      {
        m_line->stroke()->set_width ( m_line_width_entry.get_value() );
        this->update_line_marker();
      }
    }

    void MarkerWidget::on_line_join_changed ( Cairo::LineJoin join )
    {
      m_marker->stroke()->set_join ( join );

      if ( m_line )
      {
        m_line->stroke()->set_join ( join );
        this->update_line_marker();
      }
    }

    void MarkerWidget::on_line_cap_changed ( Cairo::LineCap cap )
    {
      m_marker->stroke()->set_cap ( cap );

      if ( m_line )
      {
        m_line->stroke()->set_cap ( cap );
        this->update_line_marker();
      }
    }

    void MarkerWidget::update_line_marker( )
    {
      if ( ! m_line )
        return;

      if ( m_marker->facing() == Papyrus::Marker::RIGHT )
      {
        m_line->set_marker ( START_MARKER, m_marker );
        m_line->set_marker ( END_MARKER, Papyrus::Marker::pointer() );
      }
      else
      {
        m_line->set_marker ( START_MARKER, m_marker );
        m_line->set_marker ( END_MARKER, Papyrus::Marker::pointer() );
      }
    }

  }

}
