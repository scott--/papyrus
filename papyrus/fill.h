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
#ifndef PAPYRUSFILL_H
#define PAPYRUSFILL_H

#include <cmath>
#include <papyrus/renderable.h>
#include <papyrus/drawable.h>
#include <papyrus/paint.h>

namespace Papyrus
{

  class RGBA;

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Fill : public Renderable
  {
    public:
      
    // TODO figure out how to handle fill ids and not step on the string color constructor... probably with an explicit color class
    protected:
      Fill ( Paint::pointer paint, Cairo::FillRule rule );
      
    public:
      PAPYRUS_RENDERABLE(Fill);

      static pointer create( Paint::pointer paint = Paint::pointer(), Cairo::FillRule rule = Cairo::FILL_RULE_WINDING );

      static pointer create( Cairo::RefPtr<Cairo::Pattern> pattern, Cairo::FillRule rule=Cairo::FILL_RULE_WINDING );

      static pointer create( const RGBA& rgba, Cairo::FillRule rule=Cairo::FILL_RULE_WINDING );
      
      static pointer create( const Glib::ustring& color, Cairo::FillRule rule=Cairo::FILL_RULE_WINDING );
      
      ~Fill();

      Fill& operator= ( const Fill& other );

      bool operator== ( const Fill& other ) const;

      bool operator!= ( const Fill& other ) const;

      Paint::pointer paint();

      void set_paint ( Paint::pointer paint = Paint::pointer() );

      Cairo::FillRule fill_rule();

      void set_fill_rule( Cairo::FillRule rule );

      virtual void render ( Context& cairo ) const;

      virtual Glib::ustring svg(unsigned depth=0);

      sigc::signal<void> signal_paint_changed();
      sigc::signal<void> signal_fill_rule_changed();

    protected:
      Paint::pointer m_paint;
      Cairo::FillRule m_fill_rule;

      sigc::signal<void> m_signal_paint_changed;
      sigc::signal<void> m_signal_fill_rule_changed;

      sigc::connection m_paint_changed_connection;
      void on_paint_changed();

  };

}

#endif
