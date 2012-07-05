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
#ifndef PAPYRUSROTATOR_H
#define PAPYRUSROTATOR_H

#include <papyrus/affinecontroller.h>

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Rotator : public AffineController
  {
    protected:
      
      Rotator(const Glib::ustring& id, DrawableSet::pointer drawables, double radian_interval = 0.0);

    public:

      typedef PapyrusPointer<Rotator> pointer;

    static Rotator::pointer create(double radian_interval = 0.0);

    static Rotator::pointer create(const Glib::ustring& id, DrawableSet::pointer drawables, double radian_interval = 0.0);

    static Rotator::pointer create(const Glib::ustring& id, double radian_interval = 0.0);

    static Rotator::pointer create(DrawableSet::pointer drawables, double radian_interval = 0.0);

    virtual ~Rotator();

//     double radian_interval();

//     void set_radian_interval( double radian_interval );

  protected:
    double m_original_position[2], m_last_position[2], m_centroid[2];
    double m_radian_interval;
    double m_last_angle;

    virtual bool on_motion(const Event::Motion& event);
    virtual bool on_button_press(const Event::ButtonPress& event);

  };

}

#endif
