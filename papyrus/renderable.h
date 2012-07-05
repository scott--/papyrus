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
#ifndef PAPYRUSRENDERABLE_H
#define PAPYRUSRENDERABLE_H

#include <map>
#include <glibmm/ustring.h>
#include <papyrus/pointer.h>

#include <papyrus/object.h>
#include <papyrus/utility.h>
#include <papyrus/matrix.h>
#include <cairomm/cairomm.h>

namespace Papyrus
{
  
  struct Context {
    
      Context(): flags(0x00) { }
      
      Context(Cairo::RefPtr<Cairo::Context> c, uint32_t f=0x00):
          cairo(c), flags(f) { }
      
      bool is_flag_set(RenderFlags rf) { return flags & rf; }
      
      bool is_flag_unset(RenderFlags rf) { return not(flags & rf); }
      
      /**
       * Returns the previous value so that the following can be written:
       * @code
       * bool old = cairo.set_flag( RENDER_SUPPRESS_CAIRO_FILL );
       * do some work
       * cairo.set_flag( RENDER_SUPPRESS_CAIRO_FILL, old );
       * @endcode
       */
      bool set_flag(RenderFlags rf) { 
        bool old = flags&rf; 
        flags |= rf; 
        return old; 
      }
      
      /**
       * Returns the previous value so that the following can be written:
       * @code
       * bool old = cairo.set_flag( RENDER_SUPPRESS_CAIRO_FILL );
       * do some work
       * cairo.set_flag( RENDER_SUPPRESS_CAIRO_FILL, old );
       * @endcode
       */
      bool unset_flag(RenderFlags rf) { 
        bool old = flags&rf;
        flags = flags & (~rf); 
        return old;
      }
      
      void set_flag(RenderFlags rf, bool value) {
        if ( value ) set_flag(rf);
        else unset_flag(rf);
      }
      
      void clear_flags() { flags = 0x00; }
      
      operator Cairo::RefPtr<Cairo::Context>() const { return cairo; }
      
      Cairo::RefPtr<Cairo::Context> operator*() const { return cairo; }
      
      Cairo::RefPtr<Cairo::Context> operator->() const { return cairo; }
      
      operator bool() const { return static_cast<bool>(cairo); }
      
      Context& operator=(Cairo::RefPtr<Cairo::Context> c)
      {
        cairo = c;
        return *this;
      }
      
      void save() { 
        if (is_flag_unset(RENDER_SUPPRESS_CAIRO_SAVE_RESTORE) and cairo)
          cairo->save(); 
      }
       
      void transform(const Matrix& matrix) {
        if (is_flag_unset(RENDER_SUPPRESS_MATRIX) and cairo)
          cairo->transform(matrix);
      }
      
      void restore() { 
        if (is_flag_unset(RENDER_SUPPRESS_CAIRO_SAVE_RESTORE) and cairo)
          cairo->restore(); 
      }
      
      void fill() { 
        if (is_flag_unset(RENDER_SUPPRESS_CAIRO_FILL) and cairo)
          cairo->fill(); 
      }
       
      void paint() { 
        if (is_flag_unset(RENDER_SUPPRESS_CAIRO_FILL) and cairo)
          cairo->paint(); 
      }
       
      void paint_with_alpha(double alpha) { 
        if (is_flag_unset(RENDER_SUPPRESS_CAIRO_FILL) and cairo)
          cairo->paint_with_alpha(alpha); 
      }
       
      void stroke() { 
        if (is_flag_unset(RENDER_SUPPRESS_CAIRO_STROKE) and cairo)
          cairo->stroke(); 
      }
       
      /** To support clear similar to smart pointer */
      void clear() {
        cairo.clear();
        flags = 0x00;
      }

       
      Cairo::RefPtr<Cairo::Context> cairo;
      uint32_t flags;
  };

  /**
   * Papyrus::Renderable is a common base for all classes capable of rendering themselves
   * into a cairomm context.
   *
   * Renderable provides the pure virtual \c render() method, which takes a
   * cairomm context as its only parameter. Descendants of Papyrus::Renderable
   * provide their own implementations of \c render() that allow them to be
   * rendered into the supplied cairomm context.
   *
   * The \c render() method makes it possible to render a hierarchy (or hierarchies)
   * of Renderables into a cairomm context employing a visitor pattern.
   *
   * <h2>Inheriting from Papyrus::Renderable</h2>
   *
   * <h3>When:</h3>
   * Inherit from Papyrus::Renderable when you want your object to be capable of being
   * rendered into a cairo context through a common interface.
   *
   * <h3>Tips:</h3>
   * Don't forget to provide your own implementation of \c render() since it's
   * a pure virtual method.
   *
   * @author Rick L Vinyard Jr
   */
  class Renderable: public Object
  {
    protected:
      Renderable ( const Glib::ustring& id ) : Object ( id )
      { }

    public:
      typedef PapyrusPointer<Renderable> pointer;

      virtual ~Renderable()
      { }

      virtual void render ( Context& cairo ) const = 0;

      virtual void render( Context& cairo, double x, double y, double w, double h ) const { this->render(cairo); }

      void render ( Cairo::RefPtr<Cairo::Context> cairo ) const
      { Context ctx(cairo); this->render(ctx); }

      void render( Cairo::RefPtr<Cairo::Context> cairo, double x, double y, double w, double h ) const 
      { Context ctx(cairo); this->render(ctx, x, y, w, h); }

      /**
       * Returns an SVG representation of the Renderable
       */
      virtual Glib::ustring svg(unsigned depth=0) /*= 0;*/ { return Glib::ustring(); }

      PAPYRUS_CLASS_NAME ( "Renderable" );

    protected:
  
      Glib::ustring svg_spacing(unsigned depth)
      {
        Glib::ustring s;
        for ( unsigned i = 0; i < depth; i++ )
          s += "  ";
        return s;
      }

      Glib::ustring svg_id()
      {
        Glib::ustring s;
        if ( ! m_id.empty() )
          s += "id=\"" + m_id + "\" ";
        return s;
      }


  };

};

#endif
