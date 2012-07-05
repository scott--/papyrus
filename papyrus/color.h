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
#ifndef PAPYRUSCOLOR_H
#define PAPYRUSCOLOR_H

#include <papyrus/paint.h>

namespace Papyrus {

/**
 * Solid color paint suitable for fills and strokes
 * 
 * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
 */
class Color : public Paint
{
  protected:
    Color ( const Glib::ustring& id, Cairo::RefPtr<Cairo::Pattern> pattern );

  public:
    PAPYRUS_RENDERABLE(Color);

    static pointer create( );

    static pointer create( const Glib::ustring& color_string );

    static pointer create( Cairo::RefPtr<Cairo::Pattern> p );

    static pointer create( const Glib::ustring& id, const Glib::ustring& color_string );

    static pointer create( const Glib::ustring& id, Cairo::RefPtr<Cairo::Pattern> p );

    ~Color();

    Color& operator=( pointer other );

    Color& operator=( Cairo::RefPtr<Cairo::Pattern> p );

    /** Sets to the current cairo pattern */
    Color& operator=( Cairo::RefPtr<Cairo::Context> c );

    Color& operator=( const Color& other );

    void set( pointer other );

    void set( Cairo::RefPtr<Cairo::Pattern> p );

    /** Sets to the current cairo pattern */
    void set( Cairo::RefPtr<Cairo::Context> cairo );

    Cairo::RefPtr<Cairo::Pattern> cairo_pattern() const;

    operator Cairo::RefPtr<Cairo::Pattern>() const;

    virtual void render ( Context& cairo ) const;

  protected:
    Cairo::RefPtr<Cairo::Pattern> m_pattern;

};

}

#endif
