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
#include "scrolleddrawabletreeview.h"

namespace Papyrus
{

  namespace Gtk
  {

    ScrolledDrawableTreeView::ScrolledDrawableTreeView ( Drawable::pointer d )
        : m_tree_view ( d )
    {
      this->add( m_tree_view );
      this->set_policy( ::Gtk::POLICY_AUTOMATIC, ::Gtk::POLICY_AUTOMATIC );
    }


    ScrolledDrawableTreeView::~ScrolledDrawableTreeView()
    {
    }

    DrawableTreeView & ScrolledDrawableTreeView::tree_view()
    {
      return m_tree_view;
    }

    const DrawableTreeView & ScrolledDrawableTreeView::tree_view() const
    {
      return m_tree_view;
    }

    void ScrolledDrawableTreeView::set_drawable ( Drawable::pointer d )
    {
      m_tree_view.set_drawable ( d );
    }

  }

}

