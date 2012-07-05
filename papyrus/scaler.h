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
#ifndef PAPYRUSSCALER_H
#define PAPYRUSSCALER_H

#include <papyrus/affinecontroller.h>
#include <papyrus/handlebox.h>

namespace Papyrus
{

  /**
    @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Scaler : public AffineController
  {
    protected:
      
      Scaler ( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned side = 0 );

    public:
      
      typedef PapyrusPointer<Scaler> pointer;

      static Scaler::pointer create ( unsigned side = TOP|RIGHT|BOTTOM|LEFT );

      static Scaler::pointer create ( const Glib::ustring& id, DrawableSet::pointer drawables, unsigned side = TOP|RIGHT|BOTTOM|LEFT );

      static Scaler::pointer create ( const Glib::ustring& id, unsigned side = TOP|RIGHT|BOTTOM|LEFT );

      static Scaler::pointer create ( DrawableSet::pointer drawables, unsigned side = TOP|RIGHT|BOTTOM|LEFT );

      virtual ~Scaler();

      unsigned sides();

      void set_sides ( unsigned sides );

      void enable_sides ( unsigned sides );

      void disable_sides ( unsigned sides );

      /** Gets the current grid size */
//     void grid( double& x, double& y );

      /**
       * Sets the grid x and y sizes. If either is <= 0.0 then the
       * grid will be turned off for that dimension.
       */
//     void set_grid( double x, double y );

//     void set_grid_x( double x );

//     void set_grid_y( double y );

    protected:
      double m_last_position[2], m_original_position[2];
      unsigned m_sides;
      double m_grid[2];

      virtual bool on_motion ( const Event::Motion& event );
      virtual bool on_button_press ( const Event::ButtonPress& event );

  };

}

#endif
