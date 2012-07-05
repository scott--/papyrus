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
#ifndef PAPYRUSFREEHANDSKETCHER_H
#define PAPYRUSFREEHANDSKETCHER_H

#include <set>

#include <papyrus/pointer.h>
#include <papyrus/stroke.h>
#include <papyrus/controller.h>
#include <papyrus/group.h>
#include <papyrus/polygon.h>

namespace Papyrus
{

  typedef enum SKETCH
  {
    SKETCH_LINE,
    SKETCH_POLYGON
  } SKETCH;

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class FreehandSketcher: public Controller
  {
    protected:

      FreehandSketcher ( const Glib::ustring& id, SKETCH mode=SKETCH_LINE, Stroke::pointer stroke=Stroke::pointer() );

    public:
      typedef PapyrusPointer<FreehandSketcher> pointer;
      typedef std::set<Group::pointer> Sketchpads;

      static FreehandSketcher::pointer create ( const Glib::ustring& id, SKETCH mode=SKETCH_LINE, Stroke::pointer stroke=Stroke::pointer() );

      static FreehandSketcher::pointer create ( SKETCH mode=SKETCH_LINE, Stroke::pointer stroke=Stroke::pointer() );

      virtual ~FreehandSketcher();

      const Sketchpads& sketchpads();
      void add_sketchpad ( Group::pointer sketchpad );
      void remove_sketchpad ( Group::pointer sketchpad );

      SKETCH sketch_mode();
      void set_sketch_mode ( SKETCH mode );

      Stroke::pointer stroke();
      void set_stroke ( Stroke::pointer stroke );

      Fill::pointer fill();
      void set_fill ( Fill::pointer fill );

      void set_movement_threshhold ( double t );
      double get_movement_threshhold();

    protected:
      typedef std::map< Group::pointer, Polyline::pointer > Lines;

      SKETCH m_mode;
      Fill::pointer m_fill;
      Stroke::pointer m_stroke;
      Lines m_lines;
      Papyrus::Polyline::pointer m_current_line;
      Sketchpads m_sketchpads;
      bool m_drawing;
      double m_last_position[2], m_movement_threshhold;

      virtual bool on_button_press ( const Event::ButtonPress& event );
      virtual bool on_button_release ( const Event::ButtonRelease& event );
      virtual bool on_motion ( const Event::Motion& event );

  };

}

#endif
