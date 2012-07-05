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
#ifndef PAPYRUS_GTKSCROLLEDVIEWPORT_H
#define PAPYRUS_GTKSCROLLEDVIEWPORT_H

#include <gtkmm/table.h>
#include <papyrus-gtkmm/viewport.h>

namespace Papyrus
{

  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class ScrolledViewport : public ::Gtk::Table
    {
      public:
        ScrolledViewport();

        ~ScrolledViewport();

        ::Gtk::CornerType get_placement() const;

        void get_policy ( ::Gtk::PolicyType& hscrollbar_policy, ::Gtk::PolicyType& vscrollbar_policy ) const;

        ::Gtk::ShadowType get_shadow_type() const;

        void get_hincrements( double& hstep_increment, double& hpage_increment ) const;

        void get_vincrements( double& vstep_increment, double& vpage_increment ) const;

        void get_increments( double& hstep_increment, double& hpage_increment, double& vstep_increment, double& vpage_increment ) const;

        bool get_hscrollbar_visible() const;

        bool get_vscrollbar_visible() const;

        void set_placement ( ::Gtk::CornerType window_placement );

        void set_policy ( ::Gtk::PolicyType hscrollbar_policy, ::Gtk::PolicyType vscrollbar_policy );

        void set_shadow_type(::Gtk::ShadowType type);

        void set_hincrements( double hstep_increment, double hpage_increment );

        void set_vincrements( double vstep_increment, double vpage_increment );

        void set_increments( double hstep_increment, double hpage_increment, double vstep_increment, double vpage_increment );

        // TODO implement this
        // void unset_placement();

        Viewport& viewport();

        const Viewport& viewport() const;
        
        /** Get the root canvas object from the viewport */
        Papyrus::Canvas::pointer canvas();
        
        ::Gtk::Button& corner_button();

      protected:
        double m_x_low, m_x_high, m_y_low, m_y_high;

        Canvas::pointer m_canvas;
        
        ::Gtk::CornerType m_corner_type;
        ::Gtk::PolicyType m_hscrollbar_policy;
        ::Gtk::PolicyType m_vscrollbar_policy;

        Viewport m_viewport;
        ::Gtk::Frame m_frame;
        ::Gtk::Button m_corner;
        ::Gtk::HScrollbar m_hscrollbar;
        ::Gtk::VScrollbar m_vscrollbar;

        Region m_last_global_extents;

        sigc::connection m_canvas_extents_connection;
        sigc::connection m_canvas_scrolled_connection;
        sigc::connection m_canvas_size_connection;

        void layout_children(bool construction=false);

        void on_canvas_extents_changed();

        void on_canvas_scrolled( double x, double y );

        bool on_hscrollbar_changed(::Gtk::ScrollType, double);

        bool on_vscrollbar_changed(::Gtk::ScrollType, double);

        virtual void on_corner_clicked();

        void on_canvas_replaced();

    };

  }

}

#endif
