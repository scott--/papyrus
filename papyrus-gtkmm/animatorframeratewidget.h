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
#ifndef PAPYRUSGTKANIMATORFRAMERATEWIDGET_H
#define PAPYRUSGTKANIMATORFRAMERATEWIDGET_H

#include <set>

#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/label.h>

#include <papyrus/animator.h>


namespace Papyrus
{
  namespace Gtk
  {

    /**
      @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
    */
    class AnimatorFrameRateWidget : public ::Gtk::HBox
    {
      public:
        typedef std::set<Papyrus::Animator::pointer> Animators;

        AnimatorFrameRateWidget();

        ~AnimatorFrameRateWidget();

        ::Gtk::Label& label();

        ::Gtk::SpinButton& spinbutton();

        ::Gtk::Adjustment& spinadjustment();

        void add ( Papyrus::Animator::pointer animator );

        void remove ( Papyrus::Animator::pointer animator );

        const Animators& animators() const;

      protected:
        Animators m_animators;
        ::Gtk::Label m_label;
        ::Gtk::Adjustment m_spinadjustment;
        ::Gtk::SpinButton m_spinbutton;

        void on_spinbutton_value_changed();
    };

  }

}

#endif
