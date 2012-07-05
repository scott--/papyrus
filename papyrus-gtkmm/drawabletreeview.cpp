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
#include "drawabletreeview.h"

#include <papyrus/reference.h>

#include <sstream>

namespace Papyrus
{

  namespace Gtk
  {

    DrawableTreeView::DrawableTreeView ( Drawable::pointer d ):
        m_show_layers(false)
    {
      m_store = ::Gtk::TreeStore::create ( m_column_record );

      this->set_model ( m_store );
      this->append_column ( "", m_column_record.pixbuf );
      this->append_column ( "Type", m_column_record.type );
      this->append_column ( "Id", m_column_record.id );

      if ( d ) this->set_drawable ( d );

    }

    void DrawableTreeView::set_drawable ( Drawable::pointer d )
    {
      m_store->clear();

      if ( not d ) return;

      ::Gtk::TreeModel::iterator iter = m_store->append();
      iter->set_value ( m_column_record.type, Glib::ustring ( d->class_name() ) );
      iter->set_value ( m_column_record.id, Glib::ustring ( d->id() ) );

      if ( d->is_group() )
      {
        Group::pointer group = papyrus_dynamic_pointer_cast<Group> ( d );
        this->add_group( *iter, group );
      }
      else if ( d->class_name() == "Reference" )
      {
        Reference::pointer ref = papyrus_dynamic_pointer_cast<Reference>(d);
        this->add_drawable( *iter, ref->referenced() );
      }

    }

    DrawableTreeView::~DrawableTreeView()
    {
    }

    void DrawableTreeView::add_group ( const ::Gtk::TreeRow & row, Group::pointer group )
    {
      ::Gtk::TreeModel::iterator iter, liter;
      Group::Layers::const_iterator layers_iter;
      Group::Layer::const_iterator layer_iter;
      Group::pointer subgroup;

      for ( layers_iter = group->layers().begin(); layers_iter != group->layers().end(); layers_iter++ )
      {
        if ( m_show_layers )
        {
          std::ostringstream sout;
          sout.str("");
          sout << "Layer " << layers_iter->first;
          liter = m_store->append(row.children());
          liter->set_value( m_column_record.type, Glib::ustring(sout.str()) );
        }

        for ( layer_iter = layers_iter->second.begin(); layer_iter != layers_iter->second.end(); layer_iter++ )
        {
          if ( m_show_layers )
          {
            this->add_drawable( *liter, *layer_iter );
          }
          else
          {
            this->add_drawable( row, *layer_iter );
          }
        }
      }

    }

    void DrawableTreeView::add_drawable ( const ::Gtk::TreeRow & row, Drawable::pointer d )
    {
        ::Gtk::TreeModel::iterator iter;
        Group::pointer group;

        if ( not d ) return;

        iter = m_store->append(row.children());
        iter->set_value ( m_column_record.type, Glib::ustring ( d->class_name() ) );
        iter->set_value ( m_column_record.id, Glib::ustring ( d->id() ) );

        if ( d->is_group() )
        {
          Group::pointer group = papyrus_dynamic_pointer_cast<Group> ( d );
          this->add_group( *iter, group );
        }
        else if ( d->class_name() == "Reference" )
        {
          Reference::pointer ref = papyrus_dynamic_pointer_cast<Reference>(d);
          this->add_drawable( *iter, ref->referenced() );
        }
  
    }

    void DrawableTreeView::set_show_layers(bool set)
    {
      if ( m_show_layers == set ) return;
      
      m_show_layers = set;
      this->set_drawable(m_drawable);
    }

    bool DrawableTreeView::is_show_layers_set()
    {
      return m_show_layers;
    }
    
  }

}



