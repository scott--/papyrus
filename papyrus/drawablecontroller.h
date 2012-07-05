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
#ifndef PAPYRUSDRAWABLECONTROLLER_H
#define PAPYRUSDRAWABLECONTROLLER_H

#include <papyrus/enums.h>
#include <papyrus/pointer.h>
#include <papyrus/drawableset.h>
#include <papyrus/controller.h>

namespace Papyrus
{

  /**
   * DrawableController combines the event handling interface from Controller
   * with the drawable list management of DrawableSet.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class DrawableController : public Controller, public DrawableSet
  {
    protected:
      
      DrawableController( const Glib::ustring& id, DrawableSet::pointer drawables );

    public:

      typedef PapyrusPointer<DrawableController> pointer;

      static pointer create( const Glib::ustring& id=Glib::ustring(), DrawableSet::pointer drawables=DrawableSet::pointer() );

      static pointer create( DrawableSet::pointer drawables );

      virtual ~DrawableController();

    protected:

      virtual void on_drawable_added( Drawable::pointer d );

      virtual void on_drawable_removed( Drawable::pointer d );

      virtual void on_drawables_cleared( );

    private:

      void on_drawable_added_proxy( Drawable::pointer d );

      void on_drawable_removed_proxy( Drawable::pointer d );

      void on_drawables_cleared_proxy( );

  };

}

#endif
