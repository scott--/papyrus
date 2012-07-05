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
#ifndef PAPYRUSCANVAS_H
#define PAPYRUSCANVAS_H

#include <papyrus/enums.h>
#include <papyrus/group.h>

#include <cairomm/cairomm.h>

namespace Papyrus
{

  /**
   *
  @author Rick L Vinyard Jr
  */
  class Canvas: public Group
  {

      // TODO change inheritance to eliminate the drawable matrix transformation functions

    protected:

      Canvas ( const Glib::ustring& id, double width, double height, double scale );

    public:
      PAPYRUS_DRAWABLE(Canvas);

      static pointer create ( double width=0.0, double height=0.0, double scale=1.0 );

      static pointer create ( const Glib::ustring& id, double width=0.0, double height=0.0, double scale=1.0 );

      virtual ~Canvas();

      virtual Matrix global_matrix() const;

      virtual Region global_extents() const;

      Region anchor_extents() const;

      double width() const;

      double height() const;

      void size ( double& width, double& height ) const;

      void set_width ( double width );

      void set_height ( double height );

      void set_size ( double width, double height );

      Units units() const;

      void set_units( Units u );

      void device_resolution( double& x, double& y ) const;

      bool set_device_resolution( double x, double y );

      Paint::pointer background() const;

      void set_background ( Paint::pointer background );

      void scroll_to ( double offset_x, double offset_y );

      void scroll_to_x( double offset_x );

      void scroll_to_y( double offset_y );

      void scroll_to_center();

      void scroll_position ( double& x, double& y ) const;

      double scroll_x() const;

      double scroll_y() const;

      void set_scroll_anchor ( ScrollAnchor scroll_achor = SCROLL_ANCHOR_CENTER );

      ScrollAnchor scroll_anchor() const;

      void scroll_anchor_offsets( double& x, double& y ) const;

      double scroll_anchor_x_offset() const;

      double scroll_anchor_y_offset() const;

      /**
       * Convert window coordinates to canvas coordinates.
       * \param[in] x The window x coordinate
       * \param[in] y The window y coordinate
       * \param[out] x The canvas x coordinate
       * \param[out] y The canvas y coordinate
       */
      void window_to_canvas ( double& x, double& y ) const;

      /**
       * Convert canvas coordinates to window coordinates.
       * \param[in] x The canvas x coordinate
       * \param[in] y The canvas y coordinate
       * \param[out] x The window x coordinate
       * \param[out] y The window y coordinate
       */
      void canvas_to_window ( double& x, double& y ) const;

      virtual Selection select ( double x, double y, unsigned depth = 1 );

      sigc::signal<void> signal_size_changed();

      sigc::signal<void,Units> signal_units();

      sigc::signal<void,double,double> signal_display_resolution();

      sigc::signal<void,double,double> signal_scrolled();

      sigc::signal<void,ScrollAnchor> signal_scroll_anchor_changed();
      
    protected:
      double m_width, m_height;
      double m_scale;

      /**
       * Determines the default scroll position and the result of
       * scroll_to_center()
       */
      ScrollAnchor m_scroll_anchor;

      /** Stores the default scroll anchor x offset */
      double m_scroll_anchor_offset_x;
      
      /** Stores the default scroll anchor y offset */
      double m_scroll_anchor_offset_y;

      /** Stores the current scroll x offset */
      double m_scroll_x;

      /** Stores the current scroll y offset */
      double m_scroll_y;
      
      Units m_units;
      double m_display_x_resolution, m_display_y_resolution;

      Paint::pointer m_background;

      sigc::signal<void> m_signal_size_changed;

      sigc::signal<void,Units> m_signal_units;

      sigc::signal<void,double,double> m_signal_display_resolution;

      sigc::signal<void,double,double> m_signal_scrolled;

      sigc::signal<void,ScrollAnchor> m_signal_scroll_anchor_changed;

      virtual void draw ( Context& cairo ) const;

      virtual Matrix calculate_composed_matrix() const;
  
      void update_scroll_anchor_offsets();

//       virtual void calculate_raw_extents();


  };

  /**
   * \mainpage Papyrus C++ Cairo Scenegraph Library
   *
   * <br><hr>
   *
   * \par About
   * Papyrus uses cairomm, and thus cairo, to perform rendering of a 2-D scenegraph into a
   * cairo context.Thus, papyrus scenegraphs can be rendered on-screen (such as X11 windows)
   * as well as PDF documents, PNG images, SVG documents and any other surface cairo supports
   * ( Microsoft Windows surfaces, Quartz surfaces, postscript, OpenGL to name a few more).
   *
   * \par
   * Examples of papyrus rendering scenegraphs into PNG images can be found throughout this
   * documentation. The example images of papyrus drawables were all created by the papyrus
   * example programs.
   *
   * \par
   * A key feature of papyrus is the ability to create customized shapes through inheritance,
   * and papyrus is designed to allow multiple points at which this can occur such as:
   *  - Inherit from Renderable if you want complete control over the drawing process.
   *  - Inherit from Drawable and reimplement the pure virtual method Drawable::draw if you want control over the drawing process, but want to leverage concepts such as the Viewbox.
   *  - Inherit from Shape and reimplement the pure virtual method Shape::draw_shape and/or the virtual method Shape::draw_outline if all you need to do is customize the cairo drawing path.
   *
   * \htmlonly
   * <script type="text/javascript" src="http://www.ohloh.net/p/92670/widgets/project_users.js?style=rainbow"></script><br>
   * <script type="text/javascript" src="http://www.ohloh.net/p/92670/widgets/project_partner_badge.js"></script>
   * \endhtmlonly
   *
   * <br><hr>
   * 
   * \par Payrus Sourceforge Project Page
   * The papyrus sourceforge project page can be found here:
   *
   * \par
   * <a href="http://sourceforge.net/projects/libpapyrus">http://sourceforge.net/projects/libpapyrus</a>
   *
   * \par
   * <a href="http://sourceforge.net/news/?group_id=149649">News</a>
   *
   * <br><hr>
   *
   * \par Download papyrus rpms or get the source code
   * This section is pretty large so it has its own page here: \ref get_papyrus
   * 
   * <br><hr>
   *
   * \par Dependencies... and where to get them
   * \htmlonly <img src="cairo-logo.png" alt="cairomm Logo"/> \endhtmlonly
   * \b cairomm: <a href="http://www.cairographics.org/cairomm">http://www.cairographics.org/cairomm</a>
   *
   * \par
   * \htmlonly <img src="gtkmm-logo.png" alt="gtkmm"/> \endhtmlonly
   * <a href="http://www.gtkmm.org">   http://www.gtkmm.org</a>
   *
   * <br><hr>
   *
   * \htmlonly <img src="documents-small.png" alt=""/> \endhtmlonly
   * \par Documentation, Tutorials, Guides, Quick Start, et. al.
   * This section is pretty large so it has its own page here: \ref documentation
   *
   * <br><hr>
   *
   * \htmlonly <img src="envelope-small.png" alt=""/> \endhtmlonly
   * \par Mailing Lists
   * - Users List (for those using papyrus in their applications)
   *   - <a href="http://sourceforge.net/mailarchive/forum.php?forum_name=libpapyrus-users">Archives</a>
   *   - <a href="http://lists.sourceforge.net/mailman/listinfo/libpapyrus-users">Subscribe/Unsubscribe</a>
   * - Development List (for discussion related to the development of papyrus itself)
   *   - <a href="http://sourceforge.net/mailarchive/forum.php?forum_name=libpapyrus-devel">Archives</a>
   *   - <a href="http://lists.sourceforge.net/mailman/listinfo/libpapyrus-devel">Subscribe/Unsubscribe</a>
   *
   * <br><hr>
   *
   * \par Sourceforge Forums
   * Although mailing lists are preferred, the sourceforge forums are available for discussion as well.
   * - <a href="http://sourceforge.net/forum/forum.php?forum_id=500340">Users forum</a> (for those using papyrus in their applications)
   * - <a href="http://sourceforge.net/forum/forum.php?forum_id=500341">Development forum</a> (for discussion related to the development of papyrus itself)
   * 
   * <br><hr>
   *
   * \par Bugs
   * \htmlonly <img src="bugs-small.png" alt=""/> \endhtmlonly
   * <a href="http://sourceforge.net/tracker/?atid=775465&group_id=149649&func=browse">View reported bugs in the bug tracker</a>
   *
   * \par
   * \htmlonly <img src="bug-small.png" alt=""/> \endhtmlonly
   * <a href="http://sourceforge.net/tracker/?atid=775465&group_id=149649&func=add">Submit a bug report here</a>
   * 
   * <br><hr>
   *
   * \par License
   * Papyrus is released under the \htmlonly <a href="http://www.gnu.org/licenses/lgpl-3.0-standalone.html"><img src="lgplv3.png" alt="LGPLv3"/></a> \endhtmlonly
   *
   */

  /**
   * \page get_papyrus Get Papyrus
   *
   * \htmlonly <img src="fedora-logo-small.png" alt="Fedora"/> \endhtmlonly
   * \par
   * Papyrus packages have been available directly from the <a href="http://fedoraproject.org">Fedora Project</a> since Fedora 5.
   *
   * \par
   * Fedora 10+ packages
   * - \b papyrus - Libraries needed to run applications
   * - \b papyrus-devel - Headers, libraries and documentation for developing applications with papyrus
   * - \b papyrus-gtkmm - Libraries needed to run applications with <a href="http://www.gtkmm.org">gtkmm</a> papyrus widgets
   * - \b papyrus-gtkmm-devel - Headers, libraries and documentation for developing <a href="http://www.gtkmm.org">gtkmm</a> applications with papyrus
   * - \b papyrus-extras - Extra papyrus shapes beyond primitives et. al.
   * - \b papyrus-extras-devel - Headers, libraries and documentation for developing papyrus applications that use the extra shapes
   *
   * \par
   * Fedora 5 through Fedora 9 packages
   * - \b papyrus - Libraries needed to run applications
   * - \b papyrus-devel - Headers, libraries and documentation for developing applications with papyrus
   *
   * <br><hr>
   *
   * \htmlonly <img src="sourcecode-small.png" alt=""/> \endhtmlonly
   * \par Source Code
   * \htmlonly <img src="download-small.png" alt=""/> \endhtmlonly
   * \b Releases - (.bz2, .gz, .zip) can be found <a href="http://sourceforge.net/project/showfiles.php?group_id=149649">here</a>
   *
   * \par
   * \b Subversion \b Repository
   * - You can browse the subversion repository at this url:
   *   - <a href="http://libpapyrus.svn.sourceforge.net/viewvc/libpapyrus">http://libpapyrus.svn.sourceforge.net/viewvc/libpapyrus</a>
   * - You can also check out a copy of the repository with this command:
   *   - \verbatim svn co https://libpapyrus.svn.sourceforge.net/svnroot/libpapyrus/trunk/papyrus \endverbatim
   * 
   */
  
  /**
   * \page documentation Documentation (API reference, Tutorials, Guides, et. al.)
   *
   * <br><hr>
   *
   * \par API Reference
   * The API documentation (including the pages you are reading now) have been generated
   * with Doxygen.
   *
   * \par
   * The most current documentation for papyrus is available online here:
   * - papyrus - <a href="http://libpapyrus.sf.net/papyrus">http://libpapyrus.sf.net/papyrus</a>
   *
   * <br><hr>
   *
   * \par Key sections within the API reference
   * - Namespaces
   *   - Papyrus
   *   - Papyrus::Gtk
   *   - Papyrus::Event
   * - Detailed class documentation in the <a href="hierarchy.html">Class Hierarchy</a>
   * - <a href="annotated.html">Class List</a>
   *
   * <br><hr>
   *
   * \par Guides
   * \b Quickstart \b Guide: If you're new to papyrus you might want to start with the \ref quick_start
   *
   * \par
   * \b Drawing \b Guide:
   * The following contains a list of drawables in Papyrus (this occasionally gets out
   * of date as new shapes are added). Each of the links below leads to a page that
   * illustrates images that were generated by Papyrus, and also include the code that
   * actually generated the example images.
   * - Renderable (Base class for rendering items into a cairomm context)
   * - Drawable (Base class for drawing items with affine transforms)
   *   - Shape (Base class for shape items with strokes and fills)
   *     - \ref guide_arc
   *     - \ref guide_bezierline
   *     - \ref guide_beziergon
   *     - \ref guide_circle
   *     - \ref guide_polyline
   *     - \ref guide_polygon
   *     - \ref guide_rectangle
   *     - \ref guide_regularpolygon
   *     - \ref guide_text
   *   - \ref guide_group
   *     - \ref guide_boxed
   *   - \ref guide_image "Images"
   *
   * \par
   * \ref guide_viewbox : ViewBoxes are conceptually the same as the viewBox attribute in SVG.
   *
   * \par
   * \ref mvc : Papyrus utilizes the Model-View-Controller paradigm. Check out this page to
   * see more on how and why it is used and which classes provide the core of
   * the MVC implementation.
   */
  
  /**
   * \page quick_start Quick Start Guide to Papyrus
   *
   * <br>
   * This is intended to be a very succinct guide to papyrus, and is \b not
   * intended as a general tutorial.
   * <br>
   *
   * <h2>Concept #1: The canvas</h2>
   * Papyrus is structured around the concept of a model-view separation. In the Papyrus library,
   * there are no views... only models, including Papyrus::Canvas itself. <i>(Read on to find out
   * where the views are)</i>
   * <br> <br>
   *
   * <h2>Concept #2: Drawables</h2>
   * Drawables are added to a Papyrus::Canvas. Most drawables inherit from Papyrus::Shape.
   * <br> <br>
   *
   * <h2>Concept #3: Rendering <i>(or moving from models to eye candy)</i></h2>
   * A papyrus model is made 'tangible' by rendering into a cairo context. Papyrus::Canvas and most
   * other objects in Papyrus inherit from Papyrus::Renderable which has a \c render()
   * method. Thus, rendering into a cairomm context is the way to view a Papyrus::Canvas.
   * <br> <br>
   *
   * <h2>Concept #4: Cairo Contexts</h2>
   * In cairo, a context is created from a surface. Cairo supports numerous surfaces including:
   *   - Gdk and Gdkmm widgets
   *   - PDF Surfaces
   *   - PostScript Surfaces
   *   - Image Surfaces (in-memory buffers and PNG)
   *   - SVG Surfaces
   *   - Glitz (OpenGL) Surfaces
   *
   * This quick-start won't go into the specifics of cairomm surfaces (I'll leave that to the cairomm
   * library), but suffice it to say that a Papyrus::Renderable (including the Papyrus::Canvas) is rendered
   * into a cairomm context which results in drawing a papyrus object to any of the above surfaces.
   * <br> <br>
   *
   * <h2>Concept #5: Viewports </h2>
   * PapyrusGtk::Viewport is a Gtkmm widget that serves as a view on a Papyrus::Canvas model, and
   * creates a cairomm context 'behind the scenes'. This provides a viewport into the world of the
   * canvas model you have created.
   *
   * Viewports are only one of many ways to display a Papyrus model in a Gtkmm widget.
   * <br> <br>
   *
   * <h2>Concepts #6, #7 and #8: Smart Pointers, \c pointer and \c create() </h2>
   * An early design decision was made to focus on the use of smart pointers as defined in the ANSI C++
   * committee's \c tr1 (Technical Report 1), which as of this writing has been accepted by the committee
   * and recommended to ISO for incorporation as the first revision to the C++ standard. A reference
   * implementation can be found in the boost library or in the \c std::tr1 namespace of gcc 4.0 or
   * greater.
   *
   * Two key concepts are the \c pointer typedef and the \c create method defined in each Papyrus class.
   *
   * The \c pointer typedef is defined within each class and is typedefed to a smart pointer
   * to that class. Thus, \c Papyrus::Rectangle::pointer is a smart pointer to a rectangle,
   * and \c Papyrus::Circle::pointer is a smart pointer to a circle.
   *
   * Each class also has static \c create() methods with parameters that are identical to
   * the class' constructors. The \c create() method returns a smart pointer to that object,
   * similar to the way the \c new operator returns a pointer. Since the \c create() method is
   * static, you do not need an instance of the class to call it; \c Classname::create() is sufficient.
   *
   * Naturally, the smart pointer returned from \c create() can be assigned to the class' \c pointer
   * type, which allows you to use a syntax such as:
   * \code Classname::pointer my_variable = Classname::create(); \endcode
   * <br> <br>
   *
   * <h2>Putting it all together</h2>
   * <br>
   * Create a PapyrusGtk viewport
   * \code PapyrusGtk::Viewport my_viewport; \endcode
   * <br>
   *
   * Set the viewport to an initial size of 200 x 200 and center the view
   * \code
   * my_viewport.canvas->set_size(200, 200);
   * my_viewport.set_scroll_point( PapyrusGtk::SCROLL_TO_CENTER );
   * \endcode
   * <br>
   *
   * Create a rectangle of length 100 and width 50
   * \code Papyrus::Rectangle::pointer my_rectangle = Papyrus::Rectangle::create(100, 50); \endcode
   * <br>
   *
   * Color your rectangle red and make it slightly transparent by setting alpha to 0.9
   * \code my_rectangle->set_fill( Papyrus::RGBA(1.0, 0.0, 0.0, 0.9) ); \endcode
   * <br>
   *
   * Add your red (and slightly transparent) rectangle to the viewport's canvas
   * \code my_viewport.canvas()->add( my_rectangle ); \endcode
   * <br>
   *
   * At this point you have a Gtkmm widget named \c my_viewport that you can incorporate
   * into your program as you would any other Gtkmm widget by adding it to a container, window, etc.
   * \code
   * Gtk::Window my_window;
   * my_window.add( my_viewport );
   * \endcode
   * <br>
   *
   * Since this isn't a tutorial on Gtkmm (they have a fine one
   * <a href="http://gtkmm.org/docs/gtkmm-2.4/docs/tutorial/html/">here</a>) I'll bring this
   * quick start to an end.
   * <br> <br>
   *
   */

}

#endif
