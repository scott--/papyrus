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
#ifndef PAPYRUSSHAPE_H
#define PAPYRUSSHAPE_H

#include <papyrus/enums.h>
#include <papyrus/drawable.h>
#include <papyrus/fill.h>
#include <papyrus/rgba.h>
#include <papyrus/stroke.h>

namespace Papyrus
{

  /**
   * Papyrus::Shape inherits the concepts of spatial placement and meaningful affine transforms
   * from its parent Papyrus::Drawable, and extends it with the concept of stroking and filling.
   *
   * When inheriting from Papyrus::Shape you should provide a child specific implementation
   * of the draw_shape() method (and not the draw() method from Papyrus::Drawable). This method
   * should use cairo methods to draw the structure of your shape that will be filled with the
   * pattern set by calling the set_fill() method.
   *
   * In most cases, providing a child specific implementation of the draw_shape() method will
   * be sufficient. However, if your child needs specific methods to perform outlining you
   * should also override the stroke() method.
   *
   * @author Rick L Vinyard Jr
   */
  class Shape : public Drawable
  {
    protected:

      /** Constructor that accepts a fill and stroke */
      Shape ( const Glib::ustring& id=Glib::ustring(), Fill::pointer fill = Fill::pointer(), Stroke::pointer stroke = Stroke::pointer() );

    public:
      PAPYRUS_RENDERABLE(Shape);

      /** Destructor */
      virtual ~Shape();

      virtual void set( const AttributeValueMap& avmap );

      /**
       * Implement Drawable's virtual draw method that takes care of filling
       * and stroking the shape when the fill and/or stroke patterns are present.
       */
      virtual void draw ( Context& cairo ) const;

      /**
       * Children should provide their own implementations of this pure virtual
       * method. A child should create the necessary path that will be filled
       * by the draw() method.
       */
      virtual void draw_shape ( Context& cairo ) const = 0;

      /**
       * The default implementation calls upon draw_shape() to create the path,
       * but a child should provide their own implementation if the draw_shape()
       * is not sufficient for stroking.
       */
      virtual void draw_stroke_path ( Context& cairo ) const;

      /** The pattern that will be used to fill this shape. */
      Fill::pointer fill();

      /** Sets the pattern that will be used to fill this shape. */
      void set_fill ( Fill::pointer fill );

      /**
       * Creates a new Fill object for the paint and replaces the current fill
       * with the new fill object.
       */
      void set_fill ( Paint::pointer paint );

      /**
       * Creates a new Fill object for the pattern and replaces the current fill
       * with the new fill object.
       */
      void set_fill ( Cairo::RefPtr<Cairo::Pattern> pattern );

      /**
       * Creates a new Fill object for the color and replaces the current fill
       * with the new fill object.
       */
      void set_fill( const RGBA& color );

      /**
       * Creates a new Fill object for the color and replaces the current fill
       * with the new fill object.
       */
      void set_fill( const Glib::ustring& fill );

      /**
       * Sets only the fill paint (not other fill characteristics) to the named paint.
       *
       * Shapes do not inherently have a set of paints, therefore they must
       * look to their parents. If they do not have a parent, this will
       * have no effect.
       */
      void set_fill_paint( const Glib::ustring& paint_name );

      /** The Stroke that will be used to draw the stroke */
      Stroke::pointer stroke();

      /**
       * Sets the stroke style that will be used to stroke this shape.
       */
      void set_stroke ( Stroke::pointer stroke );

      /**
       * Creates a new Stroke object for the paint and replaces the current stroke
       * with the new stroke object.
       */
      void set_stroke ( Paint::pointer paint );

      /**
       * Creates a new Stroke object for the pattern and replaces the current stroke
       * with the new stroke object.
       */
      void set_stroke ( Cairo::RefPtr<Cairo::Pattern> pattern );

      /**
       * Creates a new Stroke object for the pattern and replaces the current stroke
       * with the new stroke object.
       */
      void set_stroke ( const RGBA& color );

      /**
       * Creates a new Stroke object for the pattern and replaces the current stroke
       * with the new stroke object.
       */
      void set_stroke ( const Glib::ustring& stroke );

      /**
       * Sets only the stroke paint (not other stroke characteristics) to the named paint.
       *
       * Shapes do not inherently have a set of paints, therefore they must
       * look to their parents. If they do not have a parent, this will
       * have no effect.
       */
      void set_stroke_paint( const Glib::ustring& paint_name );

      void operator=( const Shape& other );

    protected:
      /**
       * The fill and stroke patterns for this shape.
       */
      Fill::pointer m_fill;
      Stroke::pointer m_stroke;
      mutable Cairo::Path* m_fill_path;
      mutable Cairo::Path* m_stroke_path;

      sigc::connection m_fill_changed_connection;
      sigc::connection m_stroke_changed_connection;

      virtual void on_fill_changed();

      virtual void on_stroke_changed();

      virtual void shape_changed ( unsigned which=FILL|STROKE );

      Glib::ustring svg_fill();

  };

}

#endif
