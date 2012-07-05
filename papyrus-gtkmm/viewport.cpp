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
#include "viewport.h"

#include <cstdlib>
#include <math.h>

#include <assert.h>

#include <iostream>

namespace Papyrus
{
  namespace Gtk
  {

    Viewport::Viewport() :
        m_tie_canvas_size_to_viewport ( true ),
        m_tie_viewport_size_to_canvas ( true )
    {
      m_canvas = Papyrus::Canvas::create();
      m_canvas->set_selectable ( false );
      m_canvas_size_connection = m_canvas->signal_size_changed().connect ( sigc::mem_fun ( *this, &Viewport::on_canvas_size_changed ) );
      m_canvas_redraw_connection = m_canvas->signal_redraw().connect ( sigc::mem_fun ( *this, &Viewport::on_redraw ) );

      this->signal_expose_event().connect ( sigc::mem_fun ( *this, &Viewport::expose_event_callback ) );

      this->signal_size_allocate().connect ( sigc::mem_fun ( *this, &Viewport::size_allocate_callback ) );

      this->signal_button_press_event().connect ( sigc::mem_fun ( *this, &Viewport::button_press_event_callback ) );

      this->signal_button_release_event().connect ( sigc::mem_fun ( *this, &Viewport::button_release_event_callback ) );

      this->signal_key_press_event().connect ( sigc::mem_fun ( *this, &Viewport::key_press_event_callback ) );

      this->signal_key_release_event().connect ( sigc::mem_fun ( *this, &Viewport::key_release_event_callback ) );

      this->signal_motion_notify_event().connect ( sigc::mem_fun ( *this, &Viewport::motion_notify_event_callback ) );

      this->signal_scroll_event().connect ( sigc::mem_fun ( *this, &Viewport::scroll_event_callback ) );

    }

    Viewport::~Viewport()
    {
      m_canvas.reset();
    }

    void Viewport::clear()
    {
      m_canvas->clear();
      this->queue_draw();
    }

    bool Viewport::expose_event_callback ( GdkEventExpose* e )
    {
      if ( ! m_context )
      {
        cairo_t * cairo;
        /**
        * We need to call the paint function passing it the bounds of the window and the cairo drawing surface.
        * To do this, we need to create the cairo surface using gdk_cairo_create which requires the gdk drawable.
        * But, we can't directly access the gdk drawable from a ::Gtk::Widget. We must obtain the Gdk::Window of the
        * ::Gtk::Widget. Gdk::Drawable is a parent of Gdk::Window, but the gdk drawable is only available in the
         * parent method. Therefore we must access it this way:
        *
        * ::Gtk::Widget -> Gdk::Window -> Gdk::Drawable -> gdk drawable
        *
         */

        // get the Gdk::Window for this ::Gtk::Widget
        Glib::RefPtr<Gdk::Window> window = get_window();

        if ( window )
        {
          // from the Gdk::Window, call the parent Gdk::Drawable gobj() method to obtain the gdk drawable
          GdkDrawable * gdkDrawable = window->Gdk::Drawable::gobj();

          if ( gdkDrawable != NULL )
          {
            // create the gdk cairo surface
            cairo = gdk_cairo_create ( gdkDrawable );

            m_context = Cairo::RefPtr<Cairo::Context> ( new Cairo::Context ( cairo, false ) );
          }
        }

      }

      m_canvas->render ( m_context, e->area.x, e->area.y, e->area.width, e->area.height );
      m_context.clear();
      return true;
    }

    void Viewport::on_canvas_size_changed()
    {
      int cw, ch;
      if ( m_tie_viewport_size_to_canvas && ! m_canvas_size_connection.blocked() )
      {
        cw = ( int ) ( ceil ( m_canvas->width() ) );
        ch = ( int ) ( ceil ( m_canvas->height() ) );
        m_canvas_size_connection.block();
        this->set_size_request ( cw, ch );
        m_canvas_size_connection.unblock();
      }
    }

    void Viewport::on_redraw ( double x, double y, double w, double h )
    {
      this->queue_draw_area ( ( int ) floor ( x ) - 1, ( int ) floor ( y ) - 1, ( int ) ceil ( w ) + 2, ( int ) ceil ( h ) + 2 );
    }

    Papyrus::Canvas::pointer Viewport::canvas( )
    {
      return m_canvas;
    }

    void Viewport::set_canvas ( Papyrus::Canvas::pointer canvas )
    {
      m_canvas_size_connection.disconnect();
      m_canvas_redraw_connection.disconnect();

      m_canvas = canvas;

      if ( m_canvas )
      {
        m_canvas_size_connection = m_canvas->signal_size_changed().connect ( sigc::mem_fun ( *this, &Viewport::on_canvas_size_changed ) );
        m_canvas_redraw_connection = m_canvas->signal_redraw().connect ( sigc::mem_fun ( *this, &Viewport::on_redraw ) );
      }

      m_signal_canvas_replaced.emit();
    }

    void Viewport::size_allocate_callback ( ::Gtk::Allocation & allocation )
    {
      m_width = allocation.get_width();
      m_height = allocation.get_height();
      if ( m_tie_canvas_size_to_viewport && ! m_canvas_size_connection.blocked() )
      {
        m_canvas_size_connection.block();
        m_canvas->set_size ( m_width, m_height );
        m_canvas_size_connection.unblock();
      }
    }

    const Viewport::Controllers& Viewport::controllers()
    {
      return m_controllers;
    }

    void Viewport::add_controller ( Papyrus::Controller::pointer controller )
    {
      sigc::connection conn;

      if ( not controller ) return;
      if ( m_controllers.find(controller) != m_controllers.end() ) return;

      m_controllers.insert ( controller );
      m_controller_connections[controller] = m_signal_papyrus_event.connect(sigc::mem_fun(*controller, &Controller::handle_event));
    }

    void Viewport::remove_controller ( Papyrus::Controller::pointer controller )
    {
      ControllerConnections::iterator i;

      if ( not controller ) return;
      if ( m_controllers.find(controller) != m_controllers.end() ) return;

      m_controllers.erase ( controller );
      i = m_controller_connections.find(controller);
      i->second.disconnect();
      m_controller_connections.erase(i);
    }

    bool Viewport::button_press_event_callback ( GdkEventButton * event )
    {
      double x, y;

      x = event->x;
      y = event->y;
      m_canvas->window_to_canvas ( x, y );

      switch ( event->type )
      {
        case GDK_BUTTON_PRESS:
          return m_signal_papyrus_event.emit ( Event::ButtonPress ( event->time,
                                                                    event->state,
                                                                    event->button,
                                                                    x, y )
                                             );
        case GDK_2BUTTON_PRESS:
          return m_signal_papyrus_event.emit ( Event::ButtonDoublePress ( event->time,
                                                                          event->state,
                                                                          event->button,
                                                                          x, y )
                                             );
        case GDK_3BUTTON_PRESS:
          return m_signal_papyrus_event.emit ( Event::ButtonTriplePress ( event->time,
                                                                          event->state,
                                                                          event->button,
                                                                          x, y )
                                             );
        default:
          return false;
      }
    }

    bool Viewport::button_release_event_callback ( GdkEventButton * event )
    {
      double x, y;

      x = event->x;
      y = event->y;
      m_canvas->window_to_canvas ( x, y );

      return m_signal_papyrus_event.emit ( Event::ButtonRelease ( event->time, event->state, event->button, x, y ) );
    }

    bool Viewport::key_press_event_callback ( GdkEventKey * event )
    {
      return m_signal_papyrus_event.emit ( Event::KeyPress ( event->time, event->state, event->keyval, event->hardware_keycode, event->group ) );
    }

    bool Viewport::key_release_event_callback ( GdkEventKey * event )
    {
      return m_signal_papyrus_event.emit ( Event::KeyRelease ( event->time, event->state, event->keyval, event->hardware_keycode, event->group ) );
    }

    bool Viewport::motion_notify_event_callback ( GdkEventMotion * event )
    {
      double x, y;

      x = event->x;
      y = event->y;
      m_canvas->window_to_canvas ( x, y );

      return m_signal_papyrus_event.emit ( Event::Motion ( event->time, event->state, x, y ) );
    }

    bool Viewport::scroll_event_callback ( GdkEventScroll * event )
    {
      Papyrus::Event::ScrollDirection direction;
      double x, y;

      x = event->x;
      y = event->y;
      m_canvas->window_to_canvas ( x, y );

      switch ( event->direction )
      {
        case GDK_SCROLL_UP:
          direction = Papyrus::Event::SCROLL_UP;
          break;
        case GDK_SCROLL_DOWN:
          direction = Papyrus::Event::SCROLL_DOWN;
          break;
        case GDK_SCROLL_LEFT:
          direction = Papyrus::Event::SCROLL_LEFT;
          break;
        case GDK_SCROLL_RIGHT:
          direction = Papyrus::Event::SCROLL_RIGHT;
          break;
      }

      return m_signal_papyrus_event.emit ( Event::Scroll ( event->time, event->state, direction, x, y ) );
    }

    bool Viewport::canvas_size_tied_to_viewport( )
    {
      return m_tie_canvas_size_to_viewport;
    }

    void Viewport::tie_canvas_size_to_viewport ( bool tie )
    {
      if ( tie == m_tie_canvas_size_to_viewport )
        return;

      m_tie_canvas_size_to_viewport = tie;

      if ( m_tie_canvas_size_to_viewport )
      {
        int w, h;
        this->get_size_request ( w, h );
        m_canvas->set_size ( w, h );
      }
    }

    bool Viewport::viewport_size_tied_to_canvas( )
    {
      return m_tie_viewport_size_to_canvas;
    }

    void Viewport::tie_viewport_size_to_canvas ( bool tie )
    {
      if ( tie == m_tie_viewport_size_to_canvas )
        return;

      m_tie_viewport_size_to_canvas = tie;

      if ( m_tie_canvas_size_to_viewport )
      {
        if ( m_canvas_size_connection )
          m_canvas_size_connection.disconnect();

        m_canvas_size_connection = m_canvas->signal_size_changed().connect ( sigc::mem_fun ( *this, &Viewport::on_canvas_size_changed ) );

        this->on_canvas_size_changed();
      }
      else
      {
        if ( m_canvas_size_connection )
          m_canvas_size_connection.disconnect();
      }
    }

    Papyrus::Event::signal& Viewport::signal_papyrus_event()
    {
      return m_signal_papyrus_event;
    }

    sigc::signal< void >& Viewport::signal_canvas_replaced()
    {
      return m_signal_canvas_replaced;
    }

  }
}

