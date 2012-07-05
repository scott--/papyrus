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
#ifndef PAPYRUSBOXED_H
#define PAPYRUSBOXED_H

#include <papyrus/rectangle.h>
#include <papyrus/drawablewatcher.h>
#include <papyrus/drawablesinglecontainer.h>

/**
 * \page guide_boxed Boxed Groups
 *
 * Boxed groups, as the name implies are simply a group that in addition to maintaining
 * a group, also maintains a rectangle that implicitly resizes whenever children are
 * added to or removed from the group.
 *
 * The following contains an example that adds several shapes to a boxed group,
 * then rotates the entire group by 45 degrees counter-clockwise.
 *
 * \image html boxed.png "Boxed group and shapes drawn by example code below"
 *
 * \dontinclude factory.cpp
 * \skip example_boxed
 * \until }
 *
 */

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr
   */
  class Boxed : public Drawable, public DrawableSingleContainer, public DrawableWatcher
  {
    protected:

      Boxed ( const Glib::ustring& id, Fill::pointer fill = Fill::create( RGBA(1.0, 0.85, 1.0, 0.9)), Stroke::pointer stroke = Stroke::create( RGBA(1.0, 0.0, 1.0, 0.9) ) );

    public:
      PAPYRUS_DRAWABLE(Boxed);

      static const int DEFAULT_LEVEL;

      static pointer create ( const Glib::ustring& id = Glib::ustring(),
                              Fill::pointer fill = Fill::create( RGBA(1.0, 0.85, 1.0, 0.9) ),
                              Stroke::pointer stroke = Stroke::create( RGBA(1.0, 0.0, 1.0, 0.9) ) );

      virtual ~Boxed();

      Rectangle::pointer box();

      OverUnder box_position() const;

      void set_box_position(OverUnder ou);

      virtual void draw ( Context& cairo ) const;

    protected:
      Rectangle::pointer m_box;

      OverUnder m_box_position;

      void on_child_added(Drawable::pointer added);

      void on_child_removed(Drawable::pointer removed);

      void on_cleared();
      
      virtual void on_child_changed(Drawable::pointer changed);

      /**
       * Reimplemented to calculate the group's size and set the box. Then returns
       * the extents of the box.
       */
      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

      void on_watched_event ( Drawable::pointer watched );
  };

}

#endif
