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
#ifndef PAPYRUSDRAWABLE_H
#define PAPYRUSDRAWABLE_H

#include <map>

#include <papyrus/pointer.h>
#include <papyrus/enums.h>
#include <papyrus/utility.h>
#include <papyrus/renderable.h>
#include <papyrus/region.h>
#include <papyrus/viewbox.h>
#include <papyrus/matrix.h>

namespace Papyrus
{

  class Group;

  /**
   * Drawable is the base class for objects capable of being drawn into a cairo context that
   * also have spatial properties; i.e. affine transforms can be meaningfully applied to
   * drawables. It is the presence of meaningful affine transforms that differentiates
   * Drawable from its parent Renderable.
   *
   * However Drawable lacks a concept of filling and outlining which differentiates
   * it from its child Shape.
   *
   *
   * \par Affine Transforms
   * Drawable provides a common interface for managing a transformation matrix that
   * is applied before the object is drawn. These transformations include translation,
   * scaling and shearing (skewing) in the x and y dimensions as well as rotation in
   * the x-y plane.
   *
   * \par
   * The methods for effecting the transformation matrix can be effectively grouped
   * into three categories:
   * -# Methods causing relative transforms
   *   - Use a verb form ( Drawable::translate, Drawable::rotate, Drawable::scale, et. al.)
   *   - As an example \c rotate(90,DEGREES) causes the current rotation value
   *     to increase by 90'. Thus, if the rotation angle before the call
   *     to \c rotate was 0.00, the resulting rotation angle will be 90'.
   *     However, if the previous value was 180' the current value will
   *     now be 270'.
   * -# Methods causing absolute transforms
   *   - Use a \c set_[noun] form ( Drawable::set_x, Drawable::set_y, Drawable::set_rotation )
   *   - As an example \c set_rotation(90,DEGREES) causes the current rotation
   *     value to be set to 90'. The previous rotation value doesn't matter.
   * -# Accessors for current transformation values
   *   - With the exception of the translation values accessors use the form
   *     \c get_[noun] ( Drawable::get_rotation, Drawable::get_scale, Drawable::get_scale_x, Drawable::get_scale_y )
   *   - The translation values use the form Drawable::x, Drawable::y and Drawable::xy rather than
   *     (in the author's option more cumbersome) \c get_translation_x() ,
   *     \c get_translation_y() and \c get_translation_xy() .
   *
   * \par Composition of the Drawable's Internal Matrix
   * The drawable's internal matrix is composed from the currently set x, y, scaling,
   * rotation, skewing and centroid values.
   *
   * \par
   * First, the object is translated to the (x,y) position. It is then scaled
   * along the x and y axes. Before rotation occurs the object is then translated
   * according to the centroid values, rotated so that rotation occurs about the centroid,
   * and then translated back. Finally, skewing is applied.
   *
   * \par
   * Specifically, the order of these transforms are:
   * -# translate( x, y )
   * -# scale( xscale, yscale )
   * -# translate( xcentroid, ycentroid )
   * -# rotate( r )
   * -# translate( -xcentroid, -ycentroid )
   * -# skew( xskew, yskew )
   *
   * \par External Matrices
   * The final rendering matrix is created by composing external matrices with the
   * drawable's own transformation matrix.
   *
   * \par
   * The order of composition is as follows:
   * - All external matrices with a level < 0 are applied in level order
   * - The internal matrix is applied
   * - All external matrices with a level >= 0 are applied in level order
   * - External matrices at the same level are applied in the order they were added
   *
   * \par Rendering
   * Drawable implements the pure virtual ::render method of parent
   * Renderable by pushing the current cairo state onto the cairo
   * stack, applying any necessary transformation matrix, calling
   * the pure virtual draw method, and popping the cairo stack to
   * restore the state.
   *
   * \par
   * Since this class handles the matrices directly, children only
   * need to override the draw method and draw themselves with a
   * local coordinate frame reference.
   *
   * \par Inheriting from Drawable
   * When inheriting from Drawable you should provide a child specific implementation
   * of the draw() method. You should probably also override the extents() method to return
   * a Region object that is meaningful to your child, along with providing a child specific
   * implementation of intersects(x,y) to provide a meaningful (and efficient) method of
   * determining whether your child includes the point (x,y).
   *
   * @author Rick L Vinyard Jr
   */
  class Drawable : public Renderable
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
      Drawable ( const Glib::ustring& id=Glib::ustring(), double tx = 0.0, double ty = 0.0, double sx = 1.0, double sy = 1.0, double r = 0.0 );

    public:
      PAPYRUS_RENDERABLE(Drawable);

      virtual ~Drawable();

      virtual void set( const AttributeValueMap& avmap );

      bool is_visible() const;

      void show();

      void hide();

      double alpha() const;

      void set_alpha( double a );
      
      /** X position */
      double x() const;

      /**
       * Absolute move of the x position
       *
       * If previous position was (x',y') new position is (x,y').
       */
      void set_x( double x );

      /** Y position */
      double y() const;

      /**
       * Absolute move of the y position
       *
       * If previous position was (x',y') new position is (x',y).
       */
      void set_y( double y );

      /** (X,Y) position */
      void get_xy( double& x, double& y );

      /**
       * Absolute move to (x,y)
       */
      void set_xy( double x, double y );

      /**
       * Relative translation of the current position by (tx, ty)
       *
       * If previous position was (x',y') new position is (x'+tx, y'+ty).
       */
      void translate ( double tx, double ty );

      /** convenience method to get scaling in x and y dimensions with a single function call */
      void get_scale( double& sx, double& sy );

      /** The current x dimension scaling value */
      double get_scale_x() const;

      /** The current y dimension scaling value */
      double get_scale_y() const;

      /**
       * Absolute set of the x dimension scaling value
       * @param sx The new x dimension scaling; must be > 0.0 or no change to x scaling will occur
       */
      void set_scale_x( double sx );

      /**
       * Absolute set of the y dimension scaling value
       * @param sy The new y dimension scaling; must be > 0.0 or no change to y scaling will occur
       */
      void set_scale_y( double sy );
      
      /**
       * Absolute set of the x and y dimension scalings using independent values for each
       *
       * @param scale_x The new x dimension scaling; must be > 0.0 or no change to x scaling will occur
       * @param scale_y The new y dimension scaling; must be > 0.0 or no change to y scaling will occur
       */
      void set_scale( double scale_x, double scale_y );

      /**
       * Absolute set of the x and y dimension scalings using a uniform scaling value
       *
       * @param s The amount to scale the x and y dimensions by; must be > 0.0 or no change will occur
       */
      void set_scale( double s );

      /**
       * Uniformly scales the current x and y scaling values by s
       *
       * @param s The amount to scale the x and y dimensions by; must be > 0.0 or no change will occur
       */
      void scale ( double s );

      /**
       * Independently scales the current x and y scaling values
       *
       * @param scale_x The amount to scale the x dimension by; must be > 0.0 or no change will occur
       * @param scale_y The amount to scale the y dimension by; must be > 0.0 or no change will occur
       */
      void scale ( double scale_x, double scale_y );

      /** Get rotation r in the specified units */
      double get_rotation(DegRad unit=RADIANS) const;

      /** Absolute set of the current rotation value to r using the specified units */
      void set_rotation( double r, DegRad unit=RADIANS );

      /**
       * Relative rotation of the current value by r
       *
       * If previous rotation was pr then new rotation is pr+r
       */
      void rotate ( double r, DegRad unit=RADIANS );

      /** Get the x and y skewing angles */
      void get_skew ( double& skewx, double& skewy, DegRad unit=RADIANS );

      /** Gets the current x-axis skew angle */
      double get_skew_x(DegRad unit=RADIANS) const;

      /** Gets the current y-axis skew angle */
      double get_skew_y(DegRad unit=RADIANS) const;

      /** Absolute set of the x-axis skewing angle */
      void set_skew_x ( double skewx, DegRad unit=RADIANS );

      /** Absolute set of the y-axis skewing angle */
      void set_skew_y ( double skewy, DegRad unit=RADIANS );

      /** Absolute set of the x-axis and y-axis skewing angles using separate values for each axis */
      void set_skew ( double skewx, double skewy, DegRad unit=RADIANS );

      /** Absolute set of the x-axis and y-axis skewing angles using the same value for each axis */
      void set_skew ( double s, DegRad unit=RADIANS );

      /** Relative skewing of the x-axis and y-axis angles using separate values for each axis */
      void skew ( double x, double y, DegRad unit=RADIANS );

      /** Relative skewing of the x-axis and y-axis angles by the same value for each axis */
      void skew ( double s, DegRad unit=RADIANS );

      /** Get centroid x position about which the Drawable is rotated */
      double centroid_x() const;

      /** Set the x value of the centroid about which the Drawable will be rotated */
      void set_centroid_x ( double centroid_x );

      /** Get centroid y position about which the Drawable is rotated */
      double centroid_y() const;

      /** Set the y value of the centroid about which the Drawable will be rotated */
      void set_centroid_y ( double centroid_y );

      /** Get the (x,y) centroid about which the Drawable will be rotated */
      void get_centroid ( double& centroid_x, double& centroid_y );

      /** Set the (x,y) centroid about which the Drawable will be rotated */
      void set_centroid ( double centroid_x, double centroid_y );

      /** Returns the matrix used for this object's drawing */
      const Matrix& matrix() const;
      
      /**
       * Return the composed matrix of this drawable
       *
       * The composed matrix is the internal matrix composed with all external
       * matrices except the viewbox matrix.
       *
       * If this drawable does not have a viewbox the composed matrix will always
       * be the final matrix when drawing.
       */
      const Matrix& composed_matrix() const;

      typedef std::list<Matrix::pointer> MatrixList;
      typedef std::map<int,MatrixList> MatrixMap;
      
      /**
       * Internal structure exposed for the unit test framework. Don't use this.
       * 
       * This simply stores a connection and a reference count. It is used
       * to count when an external matrix is added multiple times to a drawable.
       */
      struct CountedConnection {
        CountedConnection(): count(0) { }
        sigc::connection connection;
        unsigned int count;
      };
        
      /**
       * Internals exposed for the unit test framework. Don't use this.
       * 
       * This is a map between an external matrix and a structure that
       * contains a connection to the matrix' changed signal and a count
       * of how many times that matrix has been added to this drawable.
       */
      typedef std::map<Matrix::pointer, CountedConnection> MatrixConnMap;
      
      /** 
       * Add an transformation matrix at the specified level
       * 
       * All matrices at a level < 0 are composed before the object's affine matrix
       * matrix and all matrices at a level >= 0 are composed after the object's affine
       * matrix.
       * 
       * Matrices on the same level are composed in the order added.
       */
      void add_matrix( const Matrix::pointer m, int level=0 );
      
      /** Remove matrix m from all matrix levels */
      void remove_matrix( const Matrix::pointer m );
      
      /** 
       * Remove matrix m from the specified level.
       * 
       * If matrix m is not on the level specified no action will be taken.
       */
      void remove_matrix( const Matrix::pointer m, int level );
      
      /** Get the map of external matrices for this object */
      const MatrixMap& matrices();
      
      /** 
       * Internals exposed for the unit test framework. Don't use this.
       * 
       * Get the matrix connection map for this object
       */
      const MatrixConnMap& matrix_connection_map();

      /** Returns the global matrix that will be applied to this drawable. */
      virtual Matrix global_matrix() const;

      /** Transform a global point to the drawable's local coordinates */
      void global_to_local ( double& x, double& y ) const;

      /** Transform a local point to global coordinates */
      void local_to_global ( double& x, double& y ) const;

      /** Transform a global distance to the drawable's local coordinates */
      void distance_global_to_local ( double& x, double& y ) const;

      /** Transform a local distance to global coordinates */
      void distance_local_to_global ( double& x, double& y ) const;

      /**
       * Reimplemented render method from renderable.
       *
       * Generally, children should reimplement the draw method rather than this
       * method.
       *
       * Performs the following actions:
       *   1. Pushes cairo state onto the stack
       *   2. Recalculates local matrix if necessary
       *   3. Applies the local matrix to the current matrix
       *   4. Calls the virtual draw method
       *   5. Restores the cairo state
       */
      virtual void render ( Context& cairo ) const;

      /**
       * Reimplemented render method from renderable.
       *
       * Similar to the render(cairo context) method except checks to see if the renderable is within
       * the bounding box before rendering.
       */
      virtual void render( Context& cairo, double x, double y, double w, double h ) const;
      
      /**
       * Pure virtual draw method to be reimplemented by children.
       *
       * This method is called by the supplied render method after the local
       * transformation matrix has been applied to the cairo stack.
       */
      virtual void draw( Context& cairo ) const = 0;
      
      /**
       * Freeze the drawable, preventing any changes until it is thawed
       * 
       * This is an early version that prevents the redraw signal from
       * emitting. However, if other events trigger a redraw the changes
       * will be reflected.
       * 
       * @todo Fix the freeze/thaw structure so that this is a true freeze
       */
      virtual void freeze();
      
      /**
       * Thaw the drawable, causing any changes to be updated
       * 
       * Freeze/Thaw are still an early implementation that only prevents
       * the redraw signal from emitting. However, if other events trigger
       * a redraw the 'frozen' changes will still be reflected.
       * 
       * @todo Fix the freeze/thaw structure so freezing is really freezing
       */
      virtual void thaw(bool force_redraw=false);

      /** True if the drawable is frozen */
      bool is_frozen();
      
      /**
       * Returns the Cairomm composite operator enumerated value, or
       * -1 if the composite operator is not set.
       */
      int composite_operator();

      /** Sets the composite operator of this drawable. */
      void set_composite_operator ( Cairo::Operator op );

      /**
       * Removes the composite operator. This is different than
       * setting the composite operator to the default cairo operator
       * which is the OVER operator.
       *
       * This results in a absolute removal of the operator, causing
       * the scenegraph to not explicitly set the cairo engine to
       * any state when drawing.
       */
      void clear_composite_operator();

      /**
       * Returns the extents of this drawable
       *
       * These extents are the final extents of the drawable with all matrices applied
       */
      virtual Region extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep=EXTENTS_QUICK) const;

      /** Raw extents with only the composition matrix applied */
      virtual Region pre_viewbox_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep=EXTENTS_QUICK) const;

      /** These are the extents of the drawable without any matrices applied */
      virtual Region raw_extents() const;

      /** Returns the global extents of this drawable */
      virtual Region global_extents() const;

      /**
       * Calculate a drawable's extents, applying matrix m
       *
       * This default extents calculation calls draw and uses cairo's
       * cairo_path_extents() and cairo_stroke_extents() to calculate
       * the extents.
       *
       * Algorithmically, this is not the most efficient mechanism, but
       * does provide a basic mechanism allowing for rapid drawable creation
       * if you don't want to worry about the algorithmic details.
       */
      
      /** If true, this drawable will not be included in any extents calculation of a parent */
      bool exclude_from_extents();

      /** Exclude this drawable from all extents calculations of its parent */
      void set_exclude_from_extents ( bool b=true );

      /** Calculate the extents of this drawable when the specified matrix is applied */
      virtual Region calculate_extents(const Matrix& m = Matrix::Identity, ExtentsPerformance ep = EXTENTS_QUICK) const;

      /**
       * Applies external matrices to m and returns the result
       */
      void apply_external_matrices( Matrix& m ) const;

      /**
       * True if the point (x,y) is inside this Drawable's drawing area.
       */
      virtual bool inside ( double x, double y );

      /**
       * Set to true if this Drawable will respond to the select method.
       *
       * For example, it may not be desirable to have a group respond to the
       * select method itself, and may instead pass the select(x,y) request
       * to its children.
       */
      void set_selectable ( bool selectable = true );

      /**
       * True if this Drawable will respond to the select method, or false if
       * it will not include itself in the select method.
       */
      bool is_selectable();

      /** True if this Drawable contains other drawables. */
      virtual bool is_group();

      /**
       * Returns the viewbox associated with this Drawable.
       *
       * If no viewbox is associated, the pointer returned will be a null
       * smart pointer.
       */
      Viewbox::pointer viewbox();

      /**
       * Sets this Drawable's viewbox to the provided viewbox.
       *
       * This method does not copy the viewbox, but will hold shared ownership
       * of the shared smart pointer.
       *
       * Calling set_viewbox() with no parameters sets the viewbox to a
       * null pointer, thus removing it.
       */
      void set_viewbox ( Viewbox::pointer viewbox = Viewbox::pointer() );

      void set_viewbox(double x, double y, double w, double h,
                       Viewbox::ALIGN align=Viewbox::ALIGN_XMAX_YMAX,
                       Viewbox::MEET_OR_SLICE meet_or_slice = Viewbox::MEET);

      void set_viewbox(const Region& region,
                       Viewbox::ALIGN align=Viewbox::ALIGN_XMAX_YMAX,
                       Viewbox::MEET_OR_SLICE meet_or_slice = Viewbox::MEET);

      /**
       * Sets this Drawable's viewbox to the provided viewbox.
       *
       * This method will not maintain a connection to the provided Viewbox,
       * and will create its own copy.
       */
      void set_viewbox ( const Viewbox& viewbox );

      /** Signal emitted with x,y,w,h values when this Drawable needs to be redrawn. */
      sigc::signal<void, double, double, double, double>& signal_redraw();

      /** Signal emitted when the selectable value is changed */
      sigc::signal<void>& signal_selectable();

      /** Signal emitted when this drawable is destroyed */
      sigc::signal<void>& signal_destroyed();
      
      /** Signal emitted when the frozen/thawed state is changed */
      sigc::signal<void,FrozenThawed>& signal_frozen();

      /** Signal emitted when the composed matrix is invalidated */
      sigc::signal<void>& signal_composed_matrix_invalidated();

      /** Signal emitted when the extents are changed */
      sigc::signal<void>& signal_extents_changed();
      
      /**
       * Reset position to default values of xy = (0,0), scale = (1,1),
       * rotation = 0, and shear xy = (0,0).
       */
      void reset_position();

      /**
       * This is a proxy for the virtual redraw() method. The changed signal of the
       * viewbox is connected to this proxy that in turn calls the appropriate version
       * of redraw().
       * HACK
       * For some reason child Shape can't access this parent method when protected
       */
      void redraw_proxy();

      virtual pointer clone() const = 0;

      operator pointer();

      pointer self();

      virtual Group* parent();

    protected:
      weak_pointer m_self;

      Group* m_parent;

      MatrixMap m_matrices;
      
      MatrixConnMap m_matrix_connections;
      
      void on_matrix_changed();

      /**
       * Recalculates m_matrix if m_regenerate_matrix is true and sets
       * m_regenerate_matrix to false; does nothing if m_regenerate_matrix
       * is false.
       */
      virtual Matrix calculate_composed_matrix() const;
      
      int m_composite_operator;

      bool m_visible;

      double m_alpha;
      
      /** If true the drawable is frozen */
      bool m_frozen;
      
      /** If true the drawable is frozen by parent */
      bool m_frozen_by_parent;
      
      /** If true a redraw will occur when thawed or when parent is unthawed */
      bool m_need_redraw;

      /** whether the drawable is selectable */
      bool m_selectable;

      /**
       * Pointer to a viewbox, which may be null if this Drawable doesn't have a viewbox.
       */
      Viewbox::pointer m_viewbox;

      sigc::connection m_viewbox_connection;

      void on_viewbox_changed();

      /** Signal emitted when this object has changed and needs to be redrawn. */
      sigc::signal<void, double, double, double, double> m_signal_redraw;

      /** Signal emitted when the selectable value is changed */
      sigc::signal<void> m_signal_selectable;

      /** Signal emitted when this drawable is destroyed */
      sigc::signal<void> m_signal_destroyed;
      
      /** Signal emitted when the drawable is frozen / thawed */
      sigc::signal<void,FrozenThawed> m_signal_frozen;
      
      /** Signal emitted when the composed matrix is invalidated */
      sigc::signal<void> m_signal_composed_matrix_invalidated;

      /** Signal emitted when the extents change */
      sigc::signal<void> m_signal_extents_changed;

      friend class Group;

      /**
       * Convenience method that children can call and will take care of emitting
       * the need redraw signal with the proper parameters.
       *
       * For efficiency, if a child needs less than a complete redraw the child
       * could reimplement this method.
       */
      virtual void redraw( );

      Glib::ustring svg_transform();

      static Cairo::RefPtr<Cairo::ImageSurface> m_sidebuffer_image;

      static Context m_sidebuffer_cairo;

      /**
       * If true, this object will be excluded from a parent's extents calculation
       *
       * This variable has no effect on this drawable's calculations of its own extents
       */
      bool m_exclude_from_extents;

      void invalidate_matrix();

      void invalidate_composed_matrix();
      
      void invalidate_extents();

    private:
      
      // These are private because any access needs
      // to invalidate the matrix through invalidate_matrix()
      // and invalidate_composed_matrix() to ensure everything
      // gets set properly and the signal is emitted

      /** x position */
      double m_x;

      /** y position */
      double m_y;

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

      /**
       * The drawable's local matrix.
       */
       Matrix m_composed_matrix;

      /**
       * When true, this drawable's transformation matrix is invalid and needs to be calculated
       */
      bool m_composed_matrix_invalid;
      
      /**
       * This is the final matrix applied when drawing occurs and is the composed matrix multiplied
       * by the viewbox matrix.
       */
      Matrix m_matrix;

      bool m_matrix_invalid;

      /** These are the final extents of the drawable */
      Region m_extents;

      bool m_extents_invalid;

      /** Redraw extents containing areas that need redraws including the current extents plus any old ones */
      Region m_redraw_extents;

      /** These are the extents of the drawable @b without the transformation matrix applied */
      Region m_pre_viewbox_extents;

      /** If true, calculate_pre_viewbox_extents() will be called before extents() or pre_viewbox_extents() returns */
      bool m_pre_viewbox_extents_invalid;

  };

  typedef std::map<Glib::ustring,Drawable::pointer> DrawableDictionary;



#define EXTENTS_CHECKED_CAIRO_OP(x,y) x->y()

}

#endif
