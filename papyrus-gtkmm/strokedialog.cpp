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
#include "strokedialog.h"

namespace Papyrus
{
  namespace Gtk
  {

    StrokeDialog::StrokeDialog()
        : Dialog()
    {
      this->set_title ( "Set Line Style" );
      m_apply_button = this->add_button ( ::Gtk::Stock::APPLY, ::Gtk::RESPONSE_APPLY );
      m_cancel_button = this->add_button ( ::Gtk::Stock::CANCEL, ::Gtk::RESPONSE_CANCEL );
      m_ok_button = this->add_button ( ::Gtk::Stock::OK, ::Gtk::RESPONSE_OK );

      this->get_vbox()->add ( m_stroke_widget );

      this->show_all();
    }


    StrokeDialog::~StrokeDialog()
    {}

    const ::Gtk::Button * StrokeDialog::get_apply_button( ) const
    {
      return m_apply_button;
    }

    ::Gtk::Button * StrokeDialog::get_apply_button( )
    {
      return m_apply_button;
    }

    const ::Gtk::Button * StrokeDialog::get_cancel_button( ) const
    {
      return m_cancel_button;
    }

    ::Gtk::Button * StrokeDialog::get_cancel_button( )
    {
      return m_cancel_button;
    }

    const ::Gtk::Button * StrokeDialog::get_ok_button( ) const
    {
      return m_ok_button;
    }

    ::Gtk::Button * StrokeDialog::get_ok_button( )
    {
      return m_ok_button;
    }

    Papyrus::Stroke::pointer StrokeDialog::stroke( ) const
    {
      return m_stroke_widget.stroke();
    }

  }

}
