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
#ifndef PAPYRUSTRANSLATOR_H
#define PAPYRUSTRANSLATOR_H

#include <papyrus/affinecontroller.h>

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Translator : public AffineController
  {
    protected:

      Translator ( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned transforms = TRANSLATE_X|TRANSLATE_Y );

    public:

      typedef PapyrusPointer<Translator> pointer;

      static Translator::pointer create ( unsigned transforms = TRANSLATE_X|TRANSLATE_Y );

      static Translator::pointer create ( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned transforms = TRANSLATE_X|TRANSLATE_Y );

      static Translator::pointer create ( const Glib::ustring& id, unsigned transforms = TRANSLATE_X|TRANSLATE_Y );

      static Translator::pointer create ( DrawableSet::pointer drawables, unsigned transforms = TRANSLATE_X|TRANSLATE_Y );

      virtual ~Translator();

      unsigned transforms();

      void set_transforms ( unsigned transforms );

      void enable_transforms ( unsigned transforms );

      void disable_transforms ( unsigned transforms );

      /** Gets the current grid size */
      void grid ( double& x, double& y );

      /**
       * Sets the grid x and y sizes. If either is <= 0.0 then the
       * grid will be turned off for that dimension.
       */
      void set_grid ( double x, double y );

      void set_grid_x ( double x );

      void set_grid_y ( double y );

    protected:
      double m_last_position[2], m_original_position[2];
      unsigned m_transforms;
      double m_grid[2];

      virtual bool on_motion ( const Event::Motion& event );
      virtual bool on_button_press ( const Event::ButtonPress& event );

  };

}

#endif
