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
#ifndef PAPYRUSCONTROLLER_H
#define PAPYRUSCONTROLLER_H

#include <stdint.h>

#include <sigc++/sigc++.h>

#include <papyrus/object.h>
#include <papyrus/pointer.h>
#include <papyrus/event.h>
#include <papyrus/utility.h>

namespace Papyrus
{

  /**
   * \page mvc Papyrus' use of the MVC (Model-View-Controller) paradigm
   *
   * \par
   * Papyrus utilizes the MVC paradigm to separate the scenegraph from its
   * display and manipulation.
   *
   * \par The Scenegraph is the Model
   * All papyrus drawables, shapes, rectangles, circles, et. al. inherit
   * from the base class Renderable which provides Renderable::render.
   *
   * \par
   * Although the common case is that the root of a scenegraph consists
   * of a Group or Canvas object, in fact a scenegraph in papyrus can
   * consist of anything that inherits from Renderable and is capable of
   * being rendered into a cairo context.
   *
   * \par The Cairo Context is the View
   * The scenegraph by itself provides no mechanism for actually viewing
   * the scenegraph, and no mechanisms exist within the papyrus library.
   * To be viewed a scenegraph must be rendered into a cairo context.
   *
   * \par
   * Within the papyrus-gtkmm library is the Viewport class which creates
   * a cairo context suitable for rendering into a Gtkmm window. The Viewport
   * class also creates a Canvas and associates the canvas with the Gtkmm
   * cairo context. Thus, the Viewport brings together the Model and View.
   *
   * \par The Controller
   * In the MVC paradigm the controller processes and handles events
   * effecting changes upon the model. In papyrus the classes derived
   * from Renderable have mechanisms for manipulating their characteristics
   * within the scenegraph, but do not have methods for responding to
   * events such as mouse button clicks, mouse motion, et. al.
   * 
   * \par
   * Papyrus provides a framework representing the controller in the MVC
   * paradigm with the base class Controller. Derived classes such as
   * Selector, Translator, AffineAnimator, et. al. respond to events and
   * cause various effects upon the objects associated with them.
   *
   * \par
   * You'll notice that not all controllers respond to user driven events.
   * A key example of this is the Animator class which also responds to
   * time based events.
   *
   * \par
   * The aforementioned Viewport class within the papyrus-gtkmm library
   * also allows papyrus controllers to be associated with it. When a
   * controller is associated with the Viewport all Gtkmm events are
   * passed from the Viewport to the associated controllers.
   *
   * \par
   * As a result, the Viewport class is a prime example of how to bring
   * all three components of the MVC paradigm (papyrus scenegraph,
   * cairo context, papyrus controller) together.
   *
   */

  /**
   * Base class of a Controller in the MVC (Model-View-Controller) paradigm.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Controller: public Object
  {
    protected:
      
      Controller(const Glib::ustring& id=Glib::ustring());

    public:

      typedef PapyrusPointer<Controller> pointer;
      typedef PapyrusWeakPointer<Controller> weak_pointer;

      static pointer create( const Glib::ustring& id=Glib::ustring() );

      virtual ~Controller();

      virtual bool is_disabled();

      virtual bool disable ( bool value=true );

      virtual bool enable ( bool value=true );

      sigc::signal<void,bool> signal_disabled();

      bool handle_event( const Event::Event& event );
      
      virtual bool handle ( const Event::Event& event );
      virtual bool handle ( const Event::Button& event );
      virtual bool handle ( const Event::ButtonPress& event );
      virtual bool handle ( const Event::ButtonDoublePress& event );
      virtual bool handle ( const Event::ButtonTriplePress& event );
      virtual bool handle ( const Event::ButtonRelease& event );
      virtual bool handle ( const Event::Key& event );
      virtual bool handle ( const Event::KeyPress& event );
      virtual bool handle ( const Event::KeyRelease& event );
      virtual bool handle ( const Event::Motion& event );
      virtual bool handle ( const Event::Scroll& event );

    protected:
      bool m_disabled;

      weak_pointer m_self;

      sigc::signal<void,bool> m_signal_disabled;

      virtual bool on_button_press ( const Event::ButtonPress& event );
      virtual bool on_button_double_press ( const Event::ButtonDoublePress& event );
      virtual bool on_button_triple_press ( const Event::ButtonTriplePress& event );
      virtual bool on_button_release ( const Event::ButtonRelease& event );
      virtual bool on_key_press ( const Event::KeyPress& event );
      virtual bool on_key_release ( const Event::KeyRelease& event );
      virtual bool on_motion ( const Event::Motion& event );
      virtual bool on_scroll ( const Event::Scroll& event );

  };

}

#endif
