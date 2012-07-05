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
#ifndef PAPYRUSHANDLEBOX_H
#define PAPYRUSHANDLEBOX_H

#include <papyrus/boxed.h>

namespace Papyrus
{

  /**
    @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
  */
  class Handlebox : public Boxed
  {
    protected:

      Handlebox ( const Glib::ustring& id, Handles handles );

    public:
      PAPYRUS_DRAWABLE(Handlebox);

      static pointer create ( Handles handles=CORNER_HANDLES );

      static pointer create ( const Glib::ustring& id, Handles handles=CORNER_HANDLES );

      virtual ~Handlebox();

      void set_handle_shape ( Position p, Drawable::pointer shape, bool activate=true );

      void set_handle_shape ( Handles h, Drawable::pointer shape, bool activate=true );

      Drawable::pointer get_handle_shape ( Position p );

      void activate_handle ( Position p, bool activate=true );

      void activate_handle ( Handles h, bool activate=true );

      void deactivate_handle ( Position p );

      void deactivate_handle ( Handles h );

      bool is_active ( Position p );

      bool is_active ( Handles h );

      int inside_handle ( double x, double y );

    protected:
      Drawable::pointer m_handle_shape[ 8 ];
      bool m_handle_active[8];
      bool m_initializing;

      /**
       * Reimplements Boxed' behavior when extents need to be updated.
       * Performs same behavior, but also adjusts handle shapes to their proper places.
       */
      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

      virtual void position_handle ( Drawable::pointer, double x, double y );

      virtual void on_child_added ( Drawable::pointer child );

      virtual void on_child_removed ( Drawable::pointer child );

  };

}

#endif
