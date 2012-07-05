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
#ifndef PAPYRUS_GTKDRAWABLETREEVIEW_H
#define PAPYRUS_GTKDRAWABLETREEVIEW_H

#include <gtkmm.h>
#include <papyrus/drawable.h>
#include <papyrus/group.h>

namespace Papyrus {

namespace Gtk {

/**
 * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
 */
class DrawableModelColumnRecord : public ::Gtk::TreeModelColumnRecord
{
  public:
    DrawableModelColumnRecord()
    {
      this->add(pixbuf);
      this->add(type);
      this->add(id);
    }

  ::Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > pixbuf;
  ::Gtk::TreeModelColumn<Glib::ustring> type;
  ::Gtk::TreeModelColumn<Glib::ustring> id;
};

/**
 * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
 */
class DrawableTreeView : public ::Gtk::TreeView
{
public:
    DrawableTreeView( Drawable::pointer d = Drawable::pointer() );

    ~DrawableTreeView();

    void set_drawable( Drawable::pointer d );

    void set_show_layers( bool set=true );

    bool is_show_layers_set();

  protected:
    Drawable::pointer m_drawable;
    
    Glib::RefPtr< ::Gtk::TreeStore > m_store;
    DrawableModelColumnRecord m_column_record;

    void add_group( const ::Gtk::TreeRow& row, Group::pointer group );
    
    void add_drawable( const ::Gtk::TreeRow& row, Drawable::pointer d );
    
    bool m_show_layers;

};

}

}

#endif
