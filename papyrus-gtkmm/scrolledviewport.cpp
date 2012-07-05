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
#include "scrolledviewport.h"

#include <iostream>

namespace Papyrus
{

  namespace Gtk
  {

    ScrolledViewport::ScrolledViewport() :
        ::Gtk::Table(),
        m_x_low ( 0.0 ), m_x_high ( 0.0 ), m_y_low ( 0.0 ), m_y_high ( 0.0 ),
        m_corner_type ( ::Gtk::CORNER_TOP_LEFT ),
        m_hscrollbar_policy ( ::Gtk::POLICY_AUTOMATIC ),
        m_vscrollbar_policy ( ::Gtk::POLICY_AUTOMATIC )

    {
      // Setup the canvas and connect to necessary signals
      this->on_canvas_replaced();

      // This we can do once since we will only ever have the one viewport
      m_viewport.signal_canvas_replaced().connect( sigc::mem_fun( *this, &ScrolledViewport::on_canvas_replaced) );

      // Attach the children passing true for the construction parameter to indicate this is the constructor
      this->layout_children ( true );

      // Add the viewport to the frame since the frame was added in layout_children()
      m_frame.add ( m_viewport );
      m_frame.set_shadow_type ( ::Gtk::SHADOW_OUT );
      
      // Set some default increments
      m_hscrollbar.set_increments ( 10, 20 );
      m_vscrollbar.set_increments ( 10, 20 );

      // Set some default values to create a full bar
      m_hscrollbar.set_range ( 0.0, 1.0 );
      m_vscrollbar.set_range ( 0.0, 1.0 );
      m_hscrollbar.get_adjustment()->set_page_size ( 1.0 );
      m_vscrollbar.get_adjustment()->set_page_size ( 1.0 );
      m_hscrollbar.hide();
      m_vscrollbar.hide();
      m_corner.hide();
      m_hscrollbar.set_no_show_all();
      m_vscrollbar.set_no_show_all();
      m_corner.set_no_show_all();

      // Connect to the scrollbars and the corner button
      m_hscrollbar.signal_change_value().connect ( sigc::mem_fun ( *this, &ScrolledViewport::on_hscrollbar_changed ) );
      m_vscrollbar.signal_change_value().connect ( sigc::mem_fun ( *this, &ScrolledViewport::on_vscrollbar_changed ) );
      m_corner.signal_clicked().connect ( sigc::mem_fun ( *this, &ScrolledViewport::on_corner_clicked ) );

    }


    ScrolledViewport::~ScrolledViewport()
    {
    }

    ::Gtk::CornerType ScrolledViewport::get_placement() const
    {
      return m_corner_type;
    }

    void ScrolledViewport::get_policy ( ::Gtk::PolicyType & hscrollbar_policy, ::Gtk::PolicyType & vscrollbar_policy ) const
    {
      hscrollbar_policy = m_hscrollbar_policy;
      vscrollbar_policy = m_vscrollbar_policy;
    }

    ::Gtk::ShadowType ScrolledViewport::get_shadow_type() const
    {
      return m_frame.get_shadow_type();
    }

    void ScrolledViewport::get_hincrements(double & hstep_increment, double & hpage_increment) const
    {
      hstep_increment = m_hscrollbar.get_adjustment()->get_step_increment();
      hpage_increment = m_hscrollbar.get_adjustment()->get_page_increment();
    }

    void ScrolledViewport::get_vincrements(double & vstep_increment, double & vpage_increment) const
    {
      vstep_increment = m_vscrollbar.get_adjustment()->get_step_increment();
      vpage_increment = m_vscrollbar.get_adjustment()->get_page_increment();
    }

    void ScrolledViewport::get_increments(double & hstep_increment, double & hpage_increment, double & vstep_increment, double & vpage_increment) const
    {
      hstep_increment = m_hscrollbar.get_adjustment()->get_step_increment();
      hpage_increment = m_hscrollbar.get_adjustment()->get_page_increment();
      vstep_increment = m_vscrollbar.get_adjustment()->get_step_increment();
      vpage_increment = m_vscrollbar.get_adjustment()->get_page_increment();
    }

    bool ScrolledViewport::get_hscrollbar_visible() const
    {
      return m_hscrollbar.is_visible();
    }

    bool ScrolledViewport::get_vscrollbar_visible() const
    {
      return m_vscrollbar.is_visible();
    }

    void ScrolledViewport::set_placement ( ::Gtk::CornerType window_placement )
    {
      m_corner_type = window_placement;
      this->layout_children();
    }

    void ScrolledViewport::set_policy ( ::Gtk::PolicyType hscrollbar_policy, ::Gtk::PolicyType vscrollbar_policy )
    {
      m_hscrollbar_policy = hscrollbar_policy;
      m_vscrollbar_policy = vscrollbar_policy;

      switch ( m_hscrollbar_policy )
      {
        case ::Gtk::POLICY_ALWAYS: m_hscrollbar.show(); break;
        case ::Gtk::POLICY_NEVER:  m_hscrollbar.hide(); break;
        default:                   break;
      }

      switch ( m_vscrollbar_policy )
      {
        case ::Gtk::POLICY_ALWAYS: m_vscrollbar.show(); break;
        case ::Gtk::POLICY_NEVER:  m_vscrollbar.hide(); break;
        default:                   break;
      }

      if ( not m_hscrollbar.is_visible() or not m_vscrollbar.is_visible() )
        m_corner.hide();
      else
        m_corner.show();

      if ( m_hscrollbar_policy == ::Gtk::POLICY_AUTOMATIC or m_vscrollbar_policy == ::Gtk::POLICY_AUTOMATIC )
        this->on_canvas_extents_changed();
    }

    void ScrolledViewport::set_shadow_type ( ::Gtk::ShadowType type )
    {
      m_frame.set_shadow_type ( type );
    }

    void ScrolledViewport::set_hincrements(double hstep_increment, double hpage_increment)
    {
      m_hscrollbar.set_increments( hstep_increment, hpage_increment );
    }

    void ScrolledViewport::set_vincrements(double vstep_increment, double vpage_increment)
    {
      m_vscrollbar.set_increments( vstep_increment, vpage_increment );
    }

    void ScrolledViewport::set_increments(double hstep_increment, double hpage_increment, double vstep_increment, double vpage_increment)
    {
      m_hscrollbar.set_increments( hstep_increment, hpage_increment );
      m_vscrollbar.set_increments( vstep_increment, vpage_increment );
    }

    Viewport & ScrolledViewport::viewport()
    {
      return m_viewport;
    }

    const Viewport & ScrolledViewport::viewport() const
    {
      return m_viewport;
    }

    Papyrus::Canvas::pointer ScrolledViewport::canvas()
    {
      return m_viewport.canvas();
    }
      
    ::Gtk::Button & ScrolledViewport::corner_button()
    {
      return m_corner;
    }

    void ScrolledViewport::layout_children ( bool construction )
    {
      if ( not construction )
      {
        this->remove ( m_frame );
        this->remove ( m_corner );
        this->remove ( m_hscrollbar );
        this->remove ( m_vscrollbar );
      }

      switch ( m_corner_type )
      {
        case ::Gtk::CORNER_TOP_LEFT:
          this->attach ( m_frame, 0, 1, 0, 1 );
          this->attach ( m_vscrollbar, 1, 2, 0, 1, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_hscrollbar, 0, 1, 1, 2, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_corner, 1, 2, 1, 2, ::Gtk::SHRINK, ::Gtk::SHRINK );
          break;
        case ::Gtk::CORNER_BOTTOM_LEFT:
          this->attach ( m_frame, 0, 1, 1, 2 );
          this->attach ( m_vscrollbar, 1, 2, 1, 2, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_hscrollbar, 0, 1, 0, 1, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_corner, 1, 2, 0, 1, ::Gtk::SHRINK, ::Gtk::SHRINK );
          break;
        case ::Gtk::CORNER_TOP_RIGHT:
          this->attach ( m_frame, 1, 2, 0, 1 );
          this->attach ( m_vscrollbar, 0, 1, 0, 1, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_hscrollbar, 1, 2, 1, 2, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_corner, 0, 1, 1, 2, ::Gtk::SHRINK, ::Gtk::SHRINK );
          break;
        case ::Gtk::CORNER_BOTTOM_RIGHT:
          this->attach ( m_frame, 1, 2, 1, 2 );
          this->attach ( m_vscrollbar, 0, 1, 1, 2, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_hscrollbar, 1, 2, 0, 1, ::Gtk::FILL | ::Gtk::SHRINK, ::Gtk::FILL | ::Gtk::SHRINK );
          this->attach ( m_corner, 0, 1, 0, 1, ::Gtk::SHRINK, ::Gtk::SHRINK );
          break;
      }
    }

    void ScrolledViewport::on_canvas_extents_changed()
    {
      if ( not m_canvas ) return;

      Region global_extents = m_canvas->global_extents();

      if ( m_last_global_extents == global_extents ) return;

      m_last_global_extents = global_extents;

      double gel, ger, get, geb;
      global_extents.lrtb ( gel, ger, get, geb );

      double ael, aer, aet, aeb;
      m_canvas->anchor_extents().lrtb ( ael, aer, aet, aeb );

      double w, h;
      m_canvas->size ( w, h );

      m_x_low = std::min ( gel - ael, 0.0 );
      m_x_high = std::max ( ger - aer, 0.0 );
      m_y_low = std::min ( get - aet, 0.0 );
      m_y_high = std::max ( geb - aeb, 0.0 );

      if ( w == 0.0 or h == 0.0 or 
           isnan(m_x_low) or isnan(m_x_high) or 
           isnan(m_y_low) or isnan(m_y_high) 
         )
      {
        m_hscrollbar.set_range ( 0.0, 1.0 );
        m_vscrollbar.set_range ( 0.0, 1.0 );
        m_hscrollbar.get_adjustment()->set_page_size ( 1.0 );
        m_vscrollbar.get_adjustment()->set_page_size ( 1.0 );
        if ( m_hscrollbar_policy == ::Gtk::POLICY_AUTOMATIC ) m_hscrollbar.hide();
        if ( m_vscrollbar_policy == ::Gtk::POLICY_AUTOMATIC ) m_vscrollbar.hide();
        return;
      }

      if ( m_hscrollbar_policy == ::Gtk::POLICY_AUTOMATIC )
      {
        if ( m_x_low == 0.0 and m_x_high == 0.0 )
          m_hscrollbar.hide();
        else
          m_hscrollbar.show();
      }

      if ( m_vscrollbar_policy == ::Gtk::POLICY_AUTOMATIC )
      {
        if ( m_y_low == 0.0 and m_y_high == 0.0 )
          m_vscrollbar.hide();
        else
          m_vscrollbar.show();
      }

      if ( not m_hscrollbar.is_visible() or not m_vscrollbar.is_visible() )
        m_corner.hide();
      else
        m_corner.show();

      m_hscrollbar.set_range ( m_x_low, m_x_high+w );
      m_vscrollbar.set_range ( m_y_low, m_y_high+h );

      double scroll_x, scroll_y;

      m_canvas->scroll_position ( scroll_x, scroll_y );

      if ( scroll_x < m_x_low ) scroll_x = m_x_low;
      if ( scroll_x > m_x_high ) scroll_x = m_x_high;

      if ( scroll_y < m_y_low ) scroll_y = m_y_low;
      if ( scroll_y > m_y_high ) scroll_y = m_y_high;

      m_canvas->scroll_to ( scroll_x, scroll_y );

      m_hscrollbar.get_adjustment()->set_page_size ( w );
      m_vscrollbar.get_adjustment()->set_page_size ( h );

    }

    void ScrolledViewport::on_canvas_scrolled ( double sx, double sy )
    {
      if ( not m_canvas ) return;

      m_hscrollbar.set_value ( sx );
      m_vscrollbar.set_value ( sy );
    }

    bool ScrolledViewport::on_hscrollbar_changed ( ::Gtk::ScrollType , double value )
    {
      if ( value == 0.0 ) return false;

      if ( value < m_x_low or value > m_x_high ) return false;

      if ( not m_canvas ) return false;

      m_canvas->scroll_to_x ( value );

      return true;
    }

    bool ScrolledViewport::on_vscrollbar_changed ( ::Gtk::ScrollType , double value )
    {
      if ( value == 0.0 ) return false;

      if ( value < m_y_low or value > m_y_high ) return false;

      if ( not m_canvas ) return false;

      m_canvas->scroll_to_y ( value );

      return true;
    }

    void ScrolledViewport::on_corner_clicked()
    {
      if ( not m_canvas ) return;
      m_canvas->scroll_to_center( );
    }

    void ScrolledViewport::on_canvas_replaced()
    {
      m_canvas_extents_connection.disconnect();
      m_canvas_scrolled_connection.disconnect();
      m_canvas_size_connection.disconnect();

      m_canvas = m_viewport.canvas();

      if ( m_canvas )
      {
        m_canvas_extents_connection = m_canvas->signal_extents_changed().connect( sigc::mem_fun ( *this, &ScrolledViewport::on_canvas_extents_changed ) );

        m_canvas_scrolled_connection = m_canvas->signal_scrolled().connect ( sigc::mem_fun ( *this, &ScrolledViewport::on_canvas_scrolled ) );

        m_canvas_size_connection = m_canvas->signal_size_changed().connect( sigc::mem_fun ( *this, &ScrolledViewport::on_canvas_extents_changed ) );
      }
      
    }

  }

}
