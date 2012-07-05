/* GTK widget displaying a tree view of a drawable object
 *
 * This widget demonstrates a widget derived from Gtk::TreeView that
 * displays a drawable's hierarchy in a tree format.
 */

#include "gtkmm.h"

#include <papyrus/canvas.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/viewport.h>
#include <papyrus-gtkmm/scrolleddrawabletreeview.h>

class Example_DrawableTreeView : public Gtk::Window
{
  public:
    Example_DrawableTreeView();
    virtual ~Example_DrawableTreeView();

  protected:
  //Member widgets:
    Papyrus::Gtk::ScrolledDrawableTreeView m_DrawableTreeView;
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::Drawable::pointer m_Drawable;

    Gtk::HBox m_hbox;

};

//Called by DemoWindow;
Gtk::Window* do_DrawableTreeView()
{
  return new Example_DrawableTreeView();
}

Example_DrawableTreeView::Example_DrawableTreeView()
{
  set_title("Tree View of Drawable Objects");
  set_border_width(10);

  m_DrawableTreeView.set_size_request(300, -1);

  m_Viewport.canvas()->set_size( 500, 400 );

  m_hbox.pack_start( m_DrawableTreeView );
  m_hbox.pack_start( *Gtk::manage( new Gtk::HSeparator() ) );
  m_hbox.pack_start( m_Viewport );

  this->add( m_hbox );

  m_Viewport.canvas()->clear();
  m_Viewport.canvas()->set_background( Papyrus::RGBA("white") );

  m_Drawable = Papyrus::example_factory( Papyrus::SVG );
  m_Viewport.canvas()->add( m_Drawable );
  m_DrawableTreeView.set_drawable(m_Drawable);

  show_all();
}

Example_DrawableTreeView::~Example_DrawableTreeView()
{
}

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
