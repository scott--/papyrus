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
#include "linewidthcombobox.h"

#include <papyrus/polyline.h>
#include <papyrus/canvas.h>
#include <papyrus-extras/factory.h>
#include <papyrus-gtkmm/utility.h>

namespace Papyrus
{
  namespace Gtk
  {

    LineWidthComboBox::LineWidthComboBox ( int active, double start, double stop, INCREMENT increment, double factor )
        : ::Gtk::ComboBox(),
        m_start ( start ),
        m_stop ( stop ),
        m_increment ( increment ),
        m_factor ( factor )
    {

      if ( m_stop < m_start )
        m_stop = m_start;

      m_store = ::Gtk::ListStore::create ( m_columns );
      this->set_model ( m_store );

      this->load_pixbufs();

      this->pack_start ( m_columns.picture );

      this->set_active ( active );
    }


    LineWidthComboBox::~LineWidthComboBox() {}

    double LineWidthComboBox::width()
    {
      if ( m_increment == INCREMENT_LINEAR )
        return m_stop + this->get_active_row_number() * m_factor;
      else
        return m_stop + pow ( m_factor, this->get_active() );
    }

    double LineWidthComboBox::start()
    {
      return m_start;
    }

    double LineWidthComboBox::stop()
    {
      return m_stop;
    }

    void LineWidthComboBox::start_stop ( double& start, double& stop )
    {
      start = m_start;
      stop = m_stop;
    }

    void LineWidthComboBox::set_start ( double start )
    {
      int row = this->get_active_row_number();
      if ( start > m_stop )
        m_start = m_stop;
      else
        m_start = start;
      load_pixbufs();
      this->set_active ( row );
    }

    void LineWidthComboBox::set_stop ( double stop )
    {
      int row = this->get_active_row_number();
      if ( stop < m_start )
        m_stop = m_start;
      else
        m_stop = stop;
      load_pixbufs();
      this->set_active ( row );
    }

    void LineWidthComboBox::set_start_stop ( double start, double stop )
    {
      int row = this->get_active_row_number();
      m_start = start;
      if ( stop < m_start )
        m_stop = m_start;
      else
        m_stop = stop;
      load_pixbufs();
      this->set_active ( row );
    }

    double LineWidthComboBox::factor()
    {
      return m_factor;
    }

    void LineWidthComboBox::set_factor ( double factor )
    {
      int row = this->get_active_row_number();
      m_factor = factor;
      load_pixbufs();
      this->set_active ( row );
    }

    INCREMENT LineWidthComboBox::increment_type()
    {
      return m_increment;
    }

    void LineWidthComboBox::set_increment_type ( INCREMENT increment )
    {
      int row = this->get_active_row_number();
      m_increment = increment;
      load_pixbufs();
      this->set_active ( row );
    }

    void LineWidthComboBox::load_pixbufs()
    {
      Glib::RefPtr<Gdk::Pixbuf> pixbuf;
      Papyrus::Canvas::pointer canvas = Papyrus::Canvas::create();
      ::Gtk::TreeModel::Row row;
      Papyrus::Polyline::pointer line;
      double line_width;

      m_store->clear();
      m_pixbufs.clear();

      line = Papyrus::Polyline::create();
      line->add_vertex ( -20, 0.0 );
      line->add_vertex ( 20, 0.0 );
      line->set_stroke ( Papyrus::Stroke::create() );
      line->stroke()->set_cap ( Cairo::LINE_CAP_BUTT );
      line->stroke()->set_paint( RGBA( 0.0, 0.0, 0.0 ) );
      canvas->add ( line );

      line_width = m_start;
      while ( line_width <= m_stop )
      {

        line->stroke()->set_width ( line_width );
        canvas->translate ( 25, ( line_width + 4 ) /2.0 );
        pixbuf = create_pixbuf ( canvas, 50, static_cast<int> ( line_width ) + 4 );
        m_pixbufs.push_back ( pixbuf );

        row = * ( m_store->append() );
        row[ m_columns.picture ] = pixbuf;

        if ( m_increment == INCREMENT_LINEAR )
        {
          line_width += m_factor;
        }
        else
        {
          line_width *= m_factor;
          if ( m_factor == 1.0 ||
                  ( m_start < m_stop && m_factor < 1.0 ) ||
                  ( m_start > m_stop && m_factor > 1.0 )
             )
            break;
        }
      }
    }

  }

}
