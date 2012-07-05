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
#include "gradientstopwidget.h"

namespace Papyrus
{

  namespace Gtk
  {

    GradientStopWidget::GradientStopWidget(unsigned num_stops, bool show_header, bool show_stop_num):
        m_num_stops(0),
        m_show_header(show_header),
        m_show_stop_num(show_stop_num)
    {
      ::Gtk::Label* label;

      label = ::Gtk::manage( new ::Gtk::Label() );
      label->set_use_markup(true);
      label->set_markup("<b>Offset</b>");
      this->attach(*label, 1, 2, 0, 1);
      m_headers.push_back(label);
    
      label = ::Gtk::manage( new ::Gtk::Label() );
      label->set_use_markup(true);
      label->set_markup("<b>Color</b>");
      this->attach(*label, 2, 3, 0, 1);
      m_headers.push_back(label);

      label = ::Gtk::manage( new ::Gtk::Label() );
      label->set_use_markup(true);
      label->set_markup("<b>Alpha</b>");
      this->attach(*label, 3, 4, 0, 1);
      m_headers.push_back(label);

      this->show_header(show_header);

      this->set_num_stops(num_stops);
    }

    GradientStopWidget::~GradientStopWidget()
    {
    }

    unsigned GradientStopWidget::num_stops()
    {
      return m_num_stops;
    }

    void GradientStopWidget::set_num_stops(unsigned num_stops)
    {
      if ( num_stops == m_num_stops ) {
        return;
      }
      if ( num_stops > m_num_stops ) {
        for ( size_t i = m_num_stops; i < num_stops; i++ )
        {
          std::ostringstream sout;
          sout << i+1;
          ::Gtk::Label* label = ::Gtk::manage( new ::Gtk::Label(sout.str()) );
          this->attach(*label, 0, 1, i+1, i+2);
          m_stop_nums.push_back(label);
          if ( not m_show_stop_num ) label->hide();

          ::Gtk::SpinButton* sb = ::Gtk::manage( new ::Gtk::SpinButton(0.1, 2) );
          this->attach(*sb, 1, 2, i+1, i+2 );
          double value = 0.0;
          if ( not m_stops.empty() ) value = (1.0 - m_stops.back().offset())/2.0 + m_stops.back().offset();
          sb->get_adjustment()->configure( 1.0, 0.0, 1.0, 0.01, 0.1, 0.0 );
          m_offsets.push_back(sb);

          ::Gtk::ColorButton* cb = ::Gtk::manage( new ::Gtk::ColorButton() );
          this->attach(*cb, 2, 3, i+1, i+2 );
          m_colorbuttons.push_back(cb);

          sb = ::Gtk::manage( new ::Gtk::SpinButton(0.1, 2) );
          this->attach(*sb, 3, 4, i+1, i+2 );
          sb->get_adjustment()->configure( 1.0, 0.0, 1.0, 0.01, 0.1, 0.0 );
          m_offsets.push_back(sb);
        }
      }
      else /* num_stops < m_num_stops */ {
      }
      
      m_num_stops = num_stops;
      
      m_signal_stops_changed.emit();
    }

    void GradientStopWidget::show_header(bool show)
    {
      m_show_header = show;
      for ( size_t i=0; i < m_headers.size(); i++ ) {
        if ( show )
          m_headers[i]->show();
        else
          m_headers[i]->hide();
      }
    }

    void GradientStopWidget::show_stop_num(bool show)
    {
      m_show_stop_num = show;
      for ( size_t i=0; i < m_stop_nums.size(); i++ ) {
        if ( show )
          m_stop_nums[i]->show();
        else
          m_stop_nums[i]->hide();
      }
    }

    sigc::signal< void > GradientStopWidget::signal_stops_changed()
    {
      return m_signal_stops_changed;
    }

    Gradient::Stops GradientStopWidget::stops()
    {
    }

    void GradientStopWidget::on_color_changed(int which)
    {
      m_signal_stops_changed.emit();
    }

    void GradientStopWidget::on_offset_changed(int which)
    {
      m_signal_stops_changed.emit();
    }

    void GradientStopWidget::on_alpha_changed(int which)
    {
      m_signal_stops_changed.emit();
    }

  }

}

