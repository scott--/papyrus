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
#ifndef PAPYRUSMATRIX_H
#define PAPYRUSMATRIX_H

#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <cairomm/cairomm.h>

#include <papyrus/pointer.h>
#include <papyrus/enums.h>

namespace Papyrus
{

  /**
   * This class wraps the cairo matrix class.
   *
   * Although the affine transform methods are convenient, the
   * primary motivation behind this class is to provide a signal
   * that is emitted when the matrix is modified.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Matrix : public sigc::trackable
  {
    public:

      typedef PapyrusPointer<Matrix> pointer;

      /** Constructs an identity matrix */
      Matrix();

      /** Constructor that applies an initial translate/scale/rotate matrix */
      Matrix ( double tx, double ty, double sx = 1.0, double sy = 1.0, double r = 0.0 );

      /** Initializes the matrix to the specified values*/
      Matrix ( double xx, double yx, double xy, double yy, double x0, double y0 );

      /** Constructs a matrix identical to the supplied matrix */
      Matrix ( const Cairo::Matrix& matrix );

      /**
       * Copy constructor
       * Ensures that both matrices have independent signals
       */
      Matrix ( const Matrix& other );

      /**
       * Construct a matrix from an SVG transform string
       */
      Matrix ( const char* svg_transform );

      /**
       * Construct a matrix from an SVG transform string
       */
      Matrix ( const Glib::ustring& svg_transform );

      /** Constructs an identity matrix */
      static pointer create();

      /** Constructor that applies an initial translate/scale/rotate matrix */
      static pointer create ( double tx, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

      /** Initializes the matrix to the specified values*/
      static pointer create ( double xx, double yx, double xy, double yy, double x0, double y0 );

      /** Constructs a matrix identical to the supplied matrix */
      static pointer create ( const Cairo::Matrix& matrix );

      /** Constructs a matrix identical to the supplied matrix */
      static pointer create ( const Matrix& other );

      /** Constructs a matrix from an SVG transform string */
      static pointer create ( const char* svg_string );

      /** Constructs a matrix from an SVG transform string */
      static pointer create ( const Glib::ustring& svg_string );

      static Matrix Identity;

      ~Matrix();

      /** Translate current position by (tx, ty) */
      void translate ( double tx, double ty );

      /** Scales the current x and y dimensions by s */
      void scale ( double s );

      /** Scales the current x dimension by sx and the y dimension by sy */
      void scale ( double scale_x, double scale_y );

      /** Rotate by r radians */
      void rotate ( double r, DegRad degrad = RADIANS );

      /**
       * Rotate by r radians about the point cx, cy
       *
       * Inspired by the SVG transform rotate( r [cx cy] ) this is equivalent to the follow
       * series of transforms:
       * -# translate( cx, cy )
       * -# rotate( r )
       * -# translate( -cx, -cy )
       */
      void rotate( double r, double cx, double cy, DegRad degrad = RADIANS );

      /** Skew the x and y axes uniformly */
      void skew ( double s, DegRad degrad = RADIANS );

      /** Skew the x and y axes independently */
      void skew ( double skewx, double skewy, DegRad degrad = RADIANS );

      /** Skew only the x axis */
      void skew_x( double s, DegRad degrad = RADIANS );

      /** Skew only the y axis */
      void skew_y( double s, DegRad degrad = RADIANS );

      /** Invert the matrix */
      void invert();
      
      /** Return an inverse matrix */
      Matrix inverse() const;

      /** Transforms the distance vector @em (dx,dy) by the matrix */
      void transform_distance ( double& dx, double& dy ) const;

      /** Transforms the distance vector @em (dx,dy) by the inverse of this matrix */
      void transform_distance_inverse ( double& dx, double& dy ) const;

      /** Transforms the point @em (x,y) by the matrix */
      void transform_point ( double& x, double& y ) const;

      /** Transforms the point @em (x,y) by the inverse of this matrix */
      void transform_point_inverse ( double& x, double& y ) const;

      /** Overloaded operator= to set this matrix equal to a cairo matrix */
      Matrix& operator= ( const Cairo::Matrix& other );

      /** Overloaded operator= to set this matrix equal to the specified matrix */
      Matrix& operator= ( const Matrix& other );

      /** Overloaded operator= to set this matrix equal to the specified matrix */
      Matrix& operator= ( const Matrix::pointer other );

      /** Overloaded operator= to set this matrix equal to the SVG transform matrix */
      Matrix& operator= ( const char* svg_transform );

      /** Overloaded operator= to set this matrix equal to the SVG transform matrix */
      Matrix& operator= ( const Glib::ustring& svg_transform );

      /** Multiplies this matrix by @param other matrix and returns the result */
      Matrix operator* ( const Matrix& other ) const;

      /** Multiplies this matrix by @param other matrix and returns the result */
      Matrix operator* ( const Matrix::pointer other ) const;

      /** Multiplies this matrix by a SVG transform string and returns the result */
      Matrix operator* ( const char* svg_transform ) const;

      /** Multiplies this matrix by a SVG transform string and returns the result */
      Matrix operator* ( const Glib::ustring& svg_transform ) const;

      /** Arithmetic assignment to multiply this matrix by the @param other matrix */
      Matrix& operator*= ( const Matrix& other );
      
      /** Arithmetic assignment to multiply this matrix by the @param other matrix */
      Matrix& operator*= ( const Matrix::pointer other );

      /** Arithmetic assignment to multiply this matrix by an SVG transform string matrix */
      Matrix& operator*= ( const char* svg_transform );

      /** Arithmetic assignment to multiply this matrix by an SVG transform string matrix */
      Matrix& operator*= ( const Glib::ustring& svg_transform );

      /** Tests equality of two matrices */
      bool operator==( const Matrix& other ) const;

      /** Tests inequality of two matrices */
      bool operator!=( const Matrix& other ) const;
      
      /** Tests equality of two matrices */
      bool operator==( const pointer other ) const;

      /** Tests inequality of two matrices */
      bool operator!=( const pointer other ) const;

      /** Return this matrix as a cairo matrix */
      operator const Cairo::Matrix&() const;

      /**
       * Sets the matrix to string s formatted according to the SVG syntax for transform attributes.
       *
       * The string can consist of list of transform definitions that are applied in the order listed.
       * Individual transforms can be separated by whitespace or commas.
       *
       * The recognized transforms are:
       *  - \b matrix( \e a \e b \e c \e d \e e \e f \b) : specifies a transformation matrix of six values
       *  - \b translate( \e tx \e [ty] \b ) : specifies a translation of \e tx and \e ty. If \e ty is not
       *    provided it is assumed to be zero.
       *  - \b scale( \e sx \e [sy] \b ) : specifies a scale operation by \e sx and \e sy. If \e sy is not
       *    provided it is assumed to be equal to \e sx.
       *  - \b rotate( \e r \e [cx \e cy] \b ) : specified a rotation of \e r degrees. If optional parameters
       *    \e cx and \e cy are supplied the rotation is about the point \e (cx, \e cy).
       *  - \b skewX( \e s \b ) : Specifies a skew transformation of angle \e s degrees along the x-axis.
       *  - \b skewY( \e s \b ) : Specifies a skew transformation of angle \e s degrees along the y-axis.
       */
      bool set(const Glib::ustring& s);

      /** Set the transformation matrix to the identity matrix */
      void set_identity();

      /** Returns the SVG transform string of this matrix */
      Glib::ustring svg() const;

      /** Signal emitted when the matrix is modified */
      sigc::signal<void> signal_changed();

    protected:
      /** The cairo matrix maintained by this controller */
      Cairo::Matrix m_matrix;

      /** Signal emitted when this matrix is changed */
      sigc::signal<void> m_signal_changed;

  };

}

  bool operator==( const Papyrus::Matrix::pointer m1, const Papyrus::Matrix& m2);

  bool operator!=( const Papyrus::Matrix::pointer m1, const Papyrus::Matrix& m2);


#endif
