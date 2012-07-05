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
#ifndef PAPYRUSAFFINECONTROLLER_H
#define PAPYRUSAFFINECONTROLLER_H

#include <cairomm/cairomm.h>
#include <papyrus/drawablecontroller.h>

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class AffineController : public DrawableController
  {
    protected:

      /**
       * Constructor that sets initial transforms.
       *
       * If no parameters are specified, initial values set translation to (0,0) with a (1,1) scale
       * ratio and no rotation or shearing.
       *
       * If either scale parameter < 0.0, the parameter will be reset to 1.0.
       */
      AffineController ( const Glib::ustring& id, DrawableSet::pointer drawables, double tx = 0.0, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

    public:

      typedef PapyrusPointer<AffineController> pointer;

      static pointer create ( const Glib::ustring& id, double tx = 0.0, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

      static pointer create ( const Glib::ustring& id, DrawableSet::pointer drawables, double tx = 0.0, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

      static pointer create ( double tx = 0.0, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

      static pointer create ( DrawableSet::pointer drawables, double tx = 0.0, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

      ~AffineController();

      /** X position */
      double get_translate_x();

      /** Y position */
      double get_translate_y();

      /** (X,Y) position */
      void get_translate ( double& tx, double& ty );

      /**
      * Sets the X position
      *
      * If previous position was (px,py) new position is (tx,py).
       */
      void set_translate_x ( double tx );

      /**
      * Sets the Y position
      *
      * If previous position was (px,py) new position is (px,ty).
       */
      void set_translate_y ( double ty );

      /**
      * Sets position to (X,Y)
      *
      * Absolute move to (tx,ty).
       */
      void set_translate ( double tx, double ty );

      void translate ( double x, double y );

      /** convenience method to get scaling in x and y dimensions with a single function call */
      void get_scale ( double& sx, double& sy );

      /**
       * sets scaling in the x dimension and emits changed signal
       *
       * @param scale_x The new x dimension scaling; must be > 0.0 or no change to x scaling will occur
       */
      void set_scale_x ( double scale_x );

      /**
       * sets scaling in the y dimension and emits changed signal
       *
       * @param scale_y The new y dimension scaling; must be > 0.0 or no change to y scaling will occur
       */
      void set_scale_y ( double scale_y );

      /**
       * sets scaling in the x and y dimensions and emits changed signal
       *
       * @param scale_x The new x dimension scaling; must be > 0.0 or no change to x scaling will occur
       * @param scale_y The new y dimension scaling; must be > 0.0 or no change to y scaling will occur
       */
      void set_scale ( double scale_x, double scale_y );

      /**
       * sets scaling in the x and y dimensions and emits changed signal
       *
       * @param s The amount to scale the x and y dimensions by; must be > 0.0 or no change will occur
       */
      void set_scale ( double s );

      void scale ( double x, double y );

      void scale ( double s );

      /** Get rotation r in the specified units */
      double get_rotation ( DegRad unit=RADIANS );

      /** Rotate to r as the specified units */
      void set_rotation ( double r, DegRad unit=RADIANS );

      /**
       * Rotate by r as the specified units
       *
       * If previous rotation was pr then new rotation is pr+r
       */
      void rotate ( double r, DegRad unit=RADIANS );

      /** Get the x and y skewing angles */
      void get_skew ( double& skewx, double& skewy, DegRad unit=RADIANS );

      /** Set the x skewing angle */
      void set_skew_x ( double skewx, DegRad unit=RADIANS );

      /** Set the y skewing angle */
      void set_skew_y ( double skewy, DegRad unit=RADIANS );

      /** Set the x and y skewing angles */
      void set_skew ( double skewx, double skewy, DegRad unit=RADIANS );

      /** Set the x and y skewing angles to a single value */
      void set_skew ( double s, DegRad unit=RADIANS );

      /** Skew the x and y angles independently */
      void skew ( double x, double y, DegRad unit=RADIANS );

      /** Skew the x and y angles uniformly */
      void skew ( double s, DegRad unit=RADIANS );

      /** Get centroid x position about which the Drawable is rotated */
      double centroid_x();

      /** Set the x value of the centroid about which the Drawable will be rotated */
      void set_centroid_x ( double centroid_x );

      /** Get centroid y position about which the Drawable is rotated */
      double centroid_y();

      /** Set the y value of the centroid about which the Drawable will be rotated */
      void set_centroid_y ( double centroid_y );

      /** Get the (x,y) centroid about which the Drawable will be rotated */
      void get_centroid ( double& centroid_x, double& centroid_y );

      /** Set the (x,y) centroid about which the Drawable will be rotated */
      void set_centroid ( double centroid_x, double centroid_y );

      /** Return the matrix of this controller */
      Matrix& matrix();

      /** Return the matrix of this controller */
      const Matrix& matrix() const;

      int matrix_level() const;

      void set_matrix_level ( int level );

      /**
       * Reset position to default values of xy = (0,0), scale = (1,1),
       * rotation = 0, and shear xy = (0,0).
       */
      void reset_position();

      /** Signal emitted when the xy position is changed */
      sigc::signal<void> signal_xy();

      /** Signal emitted when the scale is changed */
      sigc::signal<void> signal_scale();

      /** Signal emitted when the rotation value is changed */
      sigc::signal<void> signal_rotation();

      /** Signal emitted when the skew is changed */
      sigc::signal<void> signal_skew();

      /** Signal emitted when the centroid is changed */
      sigc::signal<void> signal_centroid();

    protected:
      /** x translation value */
      double m_tx;

      /** y translation value */
      double m_ty;

      /** x scaling value */
      double m_sx;

      /** y scaling value */
      double m_sy;

      /** rotation value in radians */
      double m_r;

      /** skew x angle in radians */
      double m_skewx;

      /** skew y angle in radians */
      double m_skewy;

      /** x centroid value */
      double m_centroid_x;

      /** y centroid value */
      double m_centroid_y;

      /** The cairo matrix returned from matrix and used in rendering. */
      Matrix::pointer m_matrix;

      int m_matrix_level;

      /**
      * Recalculates m_matrix if m_regenerate_matrix is true and sets
      * m_regenerate_matrix to false; does nothing if m_regenerate_matrix
      * is false.
       */
      void recalculate_matrix();

      /** Signal emitted when the xy position is changed */
      sigc::signal<void> m_signal_xy;

      /** Signal emitted when the scale is changed */
      sigc::signal<void> m_signal_scale;

      /** Signal emitted when the rotation value is changed */
      sigc::signal<void> m_signal_rotation;

      /** Signal emitted when the skew is changed */
      sigc::signal<void> m_signal_skew;

      /** Signal emitted when the centroid is changed */
      sigc::signal<void> m_signal_centroid;

      virtual void on_drawable_added ( Drawable::pointer d );

      virtual void on_drawable_removed ( Drawable::pointer d );

  };

}

#endif
