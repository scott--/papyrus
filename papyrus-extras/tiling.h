/***************************************************************************
 *   Copyright (C) 2004,2009 by Rick L. Vinyard, Jr.                       *
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
#ifndef PAPYRUSTILING_H
#define PAPYRUSTILING_H

#include <papyrus/enums.h>
#include <papyrus/drawable.h>
#include <papyrus/fill.h>
#include <papyrus/rgba.h>
#include <papyrus/stroke.h>

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Tiling : public Drawable
  {
    protected:

      Tiling ( const Glib::ustring& id, unsigned rows, unsigned columns, double side_length );

    public:
      PAPYRUS_RENDERABLE(Tiling);

      virtual ~Tiling();

      unsigned rows() const;
      
      void set_rows( unsigned r );
      
      unsigned columns() const;
      
      void set_columns( unsigned c );
      
      /**
       * Sets the number of columns and rows in the quadrille
       * 
       * a.k.a the width and height in squares
       */
      void set_columns_rows( unsigned c, unsigned r );
      
      double side_length() const;
      
      void set_side_length( double l );
      
      /** 
       * The pattern that will be used to fill the cell at the given position.
       * 
       * Parameters are in column,row order to relate to x,y order
       */
      Fill::pointer fill(unsigned column, unsigned row);

      /** Sets the pattern that will be used to fill the cell at the given position. */
      void set_fill ( Fill::pointer fill, unsigned column, unsigned row );

      /**
       * Creates a new Fill object for the paint and replaces the current cell 
       * fill with the new fill object.
       */
      void set_fill ( Paint::pointer paint, unsigned column, unsigned row );

      /**
       * Creates a new Fill object for the pattern and replaces the current cell 
       * fill with the new fill object.
       */
      void set_fill ( Cairo::RefPtr<Cairo::Pattern> pattern, unsigned column, unsigned row );

      /**
       * Creates a new Fill object for the color and replaces the current cell
       * fill with the new fill object.
       */
      void set_fill( const RGBA& color, unsigned column, unsigned row );

      /**
       * Creates a new Fill object for the color and replaces the current cell
       * fill with the new fill object.
       */
      void set_fill( const Glib::ustring& fill, unsigned column, unsigned row );

      /**
       * Sets only the fill paint (not other fill characteristics) to the named paint.
       *
       * Shapes do not inherently have a set of paints, therefore they must
       * look to their parents. If they do not have a parent, this will
       * have no effect.
       */
      void set_fill_paint( const Glib::ustring& paint_name, unsigned column, unsigned row );

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
       * Sets the stroke style that will be used to stroke all cells of the quadrille.
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

    protected:
      unsigned m_rows;
      unsigned m_columns;
      double m_side_length;
      
      Fill::pointer** m_fill;
      
      sigc::connection** m_fill_changed_connection;

      Fill::pointer m_default_fill;
      Stroke::pointer m_stroke;
//       mutable Cairo::Path* m_path;

      sigc::connection m_default_fill_changed_connection;
      sigc::connection m_stroke_changed_connection;

      virtual void on_default_fill_changed();
      
      virtual void on_fill_changed(unsigned column, unsigned row);

      virtual void on_stroke_changed();

      virtual void shape_changed ( );
      
      virtual void update_centroid_x() = 0;
      
      virtual void update_centroid_y() = 0;
      
      virtual void update_centroid() = 0;

  };

}

#endif
