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
#ifndef PAPYRUSZOOMER_H
#define PAPYRUSZOOMER_H

#include <papyrus/affinecontroller.h>

namespace Papyrus
{

  /**
    @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Zoomer : public AffineController
  {
    protected:
      
      Zoomer ( const Glib::ustring& id, DrawableSet::pointer drawables, double zoom_step=1.0 );

    public:
      
      typedef PapyrusPointer<Zoomer> pointer;

      static Zoomer::pointer create ( double zoom_step=0.25 );

      static Zoomer::pointer create ( const Glib::ustring& id, DrawableSet::pointer drawables, double zoom_step=1.0 );

      static Zoomer::pointer create ( const Glib::ustring& id, double zoom_step=1.0 );

      static Zoomer::pointer create ( DrawableSet::pointer drawables, double zoom_step=1.0 );

      virtual ~Zoomer();

      void zoom_in();

      void zoom_out();

      double zoom_step();

      void set_zoom_step( double zs );

      unsigned zoom_in_buttons();

      unsigned zoom_out_buttons();

      void set_zoom_in_buttons( unsigned b );

      void set_zoom_out_buttons( unsigned b );

      void set_zoom_buttons( unsigned in, unsigned out );

      void set_zoom_buttons( unsigned set );

      void add_zoom_buttons( unsigned in, unsigned out );

      void add_zoom_buttons( unsigned set );

      void perform_button_action( Event::ButtonID b );

    protected:

      double m_zoom_step;

      unsigned m_zoom_in_buttons;

      unsigned m_zoom_out_buttons;

      virtual bool on_button_press ( const Event::ButtonPress& event );

      virtual bool on_scroll ( const Event::Scroll& event );

  };

}

#endif
