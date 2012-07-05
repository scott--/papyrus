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
#ifndef PAPYRUSGTKVIEWPORT_H
#define PAPYRUSGTKVIEWPORT_H

#include <set>

#include <gtkmm.h>

#include <papyrus/canvas.h>
#include <papyrus/controller.h>
#include <papyrus-gtkmm/enums.h>

namespace Papyrus
{
  namespace Gtk
  {

    /**
     * @author Rick L Vinyard Jr
     */
    class Viewport: public ::Gtk::EventBox
    {

      public:

        Viewport();
        
        virtual ~Viewport();

        typedef std::set<Papyrus::Controller::pointer> Controllers;

        // Drawing Operations
        virtual void clear();

        /** Get the root canvas object */
        Papyrus::Canvas::pointer canvas();

        /** Set the root canvas object */
        void set_canvas ( Papyrus::Canvas::pointer  canvas );

        const Controllers& controllers();

        void add_controller ( Papyrus::Controller::pointer controller );

        void remove_controller ( Papyrus::Controller::pointer controller );

        bool canvas_size_tied_to_viewport();

        void tie_canvas_size_to_viewport ( bool tie=true );

        bool viewport_size_tied_to_canvas();

        void tie_viewport_size_to_canvas ( bool tie=true );

        Papyrus::Event::signal& signal_papyrus_event();

        sigc::signal<void>& signal_canvas_replaced();

      protected:
        Papyrus::Canvas::pointer m_canvas;
        int m_width, m_height;
        bool m_tie_canvas_size_to_viewport, m_tie_viewport_size_to_canvas;

        Controllers m_controllers;

        typedef std::map<Papyrus::Controller::pointer,sigc::connection> ControllerConnections;

        ControllerConnections m_controller_connections;

        Papyrus::Event::signal m_signal_papyrus_event;

        sigc::connection m_canvas_redraw_connection;
        sigc::connection m_canvas_size_connection;

        Context m_context;

        sigc::signal<void> m_signal_canvas_replaced;

        void on_canvas_size_changed();

        void on_redraw ( double x, double y, double w, double h );

        bool expose_event_callback ( GdkEventExpose* e );

        void size_allocate_callback ( ::Gtk::Allocation& allocation );

        bool button_press_event_callback ( GdkEventButton* event );

        bool button_release_event_callback ( GdkEventButton* event );

        bool key_press_event_callback ( GdkEventKey* event );

        bool key_release_event_callback ( GdkEventKey* event );

        bool motion_notify_event_callback ( GdkEventMotion* event );

        bool scroll_event_callback ( GdkEventScroll* event );

    };

  }

}

#endif
