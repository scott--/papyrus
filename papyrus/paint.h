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
#ifndef PAPYRUSPAINT_H
#define PAPYRUSPAINT_H

#include <papyrus/renderable.h>

namespace Papyrus
{

  /**
   * Provides a base class for various paint types. Paints can be used
   * in fills or strokes.
   * 
   * The basic paint types are:
   * - Solid colors --- Papyrus::Color
   * - Linear gradients --- Papyrus::LinearGradient
   * - Radial gradients --- Papyrus::RadialGradient
   * - Patterns --- Papyrus::Pattern (still to do)
   * 
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Paint : public Renderable
  {
    protected:
      Paint ( const Glib::ustring& id = Glib::ustring() );

    public:
      typedef PapyrusPointer<Paint> pointer;

      virtual ~Paint();

  };

  /**
   * A dictionary of paints
   */
  typedef std::map<Glib::ustring,Paint::pointer> PaintDictionary;

}

#endif
