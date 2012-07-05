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
#ifndef PAPYRUSREFERENCE_H
#define PAPYRUSREFERENCE_H

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
   * An instance of Reference holds a reference to another drawable without
   * becoming the parent of the other drawable.
   *
   * The reference's transformation matrix is applied before calling the
   * referenced object to perform drawing. Therefore, the same drawing object
   * may appear differently if two or more Reference instances apply different
   * transformation matrices before performing actual drawing.
   *
   * This class was motivated by the SVG 'use' element.
   *
   * As a container, a Reference only holds a single object. If you need more
   * than one object, add them to groups and then add the group to the reference.
   *
   * If you don't want the group to take ownership, add the items individually
   * to instances of Reference, then add the instances to a Group.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Reference : public Drawable
  {
    protected:
      Reference ( const Glib::ustring& id, Drawable::pointer ref );

    public:
      PAPYRUS_DRAWABLE(Reference);

      /** Accepts an object to reference, or sets to a null pointer if no object. */
      static pointer create ( Drawable::pointer ref = Drawable::pointer() );

      /**
       * Accepts an object to reference, or sets to a null pointer if no object
       * and names the reference with an id string.
       */
      static pointer create ( const Glib::ustring& id, Drawable::pointer ref = Drawable::pointer() );

      /** Destructor */
      ~Reference();

      /** Override of Drawable's virtual draw method that draws the referenced drawable */
      virtual void draw ( Context& cairo ) const;

      /**
       * Returns the current referenced object, or a null smart pointer if no object
       * is currently reference.
       */
      Drawable::pointer referenced();

      /**
       * Sets the current referenced object. Set to a null smart pointer to
       * remove the referenced object.
       */
      void set_referenced ( Drawable::pointer d );
      
      /**
       * Removes the referenced object
       */
      void clear_referenced( );

      /** Override of Drawable's global matrix to include the matrix of the referenced drawable. */
      virtual Matrix global_matrix() const;

      virtual Glib::ustring svg(unsigned depth=0);

    protected:
      /** The referenced object */
      Drawable::pointer m_referenced;
      
      /** Extends Drawable's version to include the referenced object's matrix */
      virtual Matrix calculate_composed_matrix() const;
      
      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

      /** 
       * Used to track connection to referenced drawable's matrix invalidation
       * signal.
       */
      sigc::connection m_connection_referenced_composed_matrix_invalidated;

  };

}

#endif
