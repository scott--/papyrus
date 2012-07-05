/***************************************************************************
 *   Copyright (C) 2007 by Rick L. Vinyard, Jr.                            *
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
#ifndef PAPYRUS_GTKSCROLLEDDRAWABLETREEVIEW_H
#define PAPYRUS_GTKSCROLLEDDRAWABLETREEVIEW_H

#include <gtkmm.h>

#include <papyrus-gtkmm/drawabletreeview.h>

namespace Papyrus
{

  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class ScrolledDrawableTreeView : public ::Gtk::ScrolledWindow
    {
      public:
        ScrolledDrawableTreeView ( Drawable::pointer d = Drawable::pointer() );

        ~ScrolledDrawableTreeView();

        DrawableTreeView& tree_view();

        const DrawableTreeView& tree_view() const;

        void set_drawable ( Drawable::pointer d );

      protected:

        DrawableTreeView m_tree_view;

    };

  }

}

#endif
