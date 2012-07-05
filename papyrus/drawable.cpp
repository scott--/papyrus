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
#include "drawable.h"
#include "group.h"

#include <iostream>

namespace Papyrus
{

  Cairo::RefPtr<Cairo::ImageSurface> Drawable::m_sidebuffer_image(Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 1, 1));
  
  Context Drawable::m_sidebuffer_cairo(Cairo::Context::create(m_sidebuffer_image));

  Drawable::Drawable ( const Glib::ustring& id, double tx, double ty, double sx, double sy, double r ) :
      Renderable ( id ),
      m_parent ( NULL ),
      m_composite_operator ( -1 ),
      m_visible ( true ),
      m_alpha( -1.0 ),
      m_frozen( false ),
      m_frozen_by_parent( false ),
      m_need_redraw( false ),
      m_selectable ( true ),
      m_exclude_from_extents ( false ),
      m_x(tx),
      m_y(ty),
      m_sx(sx),
      m_sy(sy),
      m_r(r),
      m_skewx ( 0.0 ),
      m_skewy ( 0.0 ),
      m_centroid_x ( 0.0 ),
      m_centroid_y ( 0.0 ),
      m_composed_matrix_invalid(true),
      m_matrix_invalid(true),
      m_extents_invalid(true),
      m_pre_viewbox_extents_invalid(true)
  {
    if ( m_sx <= 0.0 ) m_sx = 1.0;
    if ( m_sy <= 0.0 ) m_sy = 1.0;
  }

  Drawable::~Drawable()
  {
    m_signal_destroyed.emit();
  }

  void Drawable::set( const AttributeValueMap& avmap )
  {
    Renderable::set( avmap );
    
    AttributeValueMap::const_iterator i;
    for ( i = avmap.begin(); i != avmap.end(); i++ )
    {
      if      ( strcaseeq( i->first, "transform" ) )  this->add_matrix( Matrix::create( i->second ) , -1 );
      else if ( strcaseeq( i->first, "x" ) )          this->set_x( atof( i->second.c_str() ) );
      else if ( strcaseeq( i->first, "y" ) )          this->set_y( atof( i->second.c_str() ) );
    }
  }

  bool Drawable::is_visible() const
  {
    return m_visible;
  }

  void Drawable::show()
  {
    if ( m_visible ) return;
    m_visible = true;
    this->redraw();
  }

  void Drawable::hide()
  {
    if ( ! m_visible ) return;
    m_visible = false;
    this->redraw();
  }

  double Drawable::alpha() const
  {
    return m_alpha;
  }

  void Drawable::set_alpha( double a )
  {
    m_alpha = a;
    this->redraw();
  }

  double Drawable::x() const
  {
    return m_x;
  }

  double Drawable::y() const
  {
    return m_y;
  }

  void Drawable::get_xy( double& x, double& y )
  {
    x = m_x;
    y = m_y;
  }

  void Drawable::set_x( double x )
  {
    m_x = x;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_y( double y )
  {
    m_y = y;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_xy( double x, double y )
  {
    m_x = x;
    m_y = y;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::translate( double x, double y )
  {
    m_x += x;
    m_y += y;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::get_scale ( double& sx, double& sy )
  {
    sx = m_sx;
    sy = m_sy;
  }
  
  double Drawable::get_scale_x() const
  {
    return m_sx;
  }
  
  double Drawable::get_scale_y() const
  {
    return m_sy;
  }

  void Drawable::set_scale_x ( double sx )
  {
    if ( sx > 0.0 ) m_sx = sx;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_scale_y ( double sy )
  {
    if ( sy > 0.0 ) m_sy = sy;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_scale ( double sx, double sy )
  {
    if ( sx > 0.0 ) m_sx = sx;
    if ( sy > 0.0 ) m_sy = sy;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_scale ( double s )
  {
    if ( s <= 0.0 ) return ;
    m_sx = s;
    m_sy = s;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::scale ( double s )
  {
    if ( s <= 0.0 ) return;
    m_sx *= s;
    m_sy *= s;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::scale ( double sx, double sy )
  {
    if ( sx > 0.0 ) m_sx *= sx;
    if ( sy > 0.0 ) m_sy *= sy;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  double Drawable::get_rotation(DegRad unit) const
  {
    return rad2units(m_r, unit);
  }

  void Drawable::set_rotation( double r, DegRad unit )
  {
    m_r = units2rad(r, unit);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::rotate ( double r, DegRad unit )
  {
    m_r += units2rad(r, unit);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::get_skew ( double& skewx, double& skewy, DegRad units )
  {
    skewx = rad2units(m_skewx, units);
    skewy = rad2units(m_skewy, units);
  }
  
  double Drawable::get_skew_x( DegRad units) const
  {
    return rad2units(m_skewx, units);
  }

  double Drawable::get_skew_y( DegRad units) const
  {
    return rad2units(m_skewy, units);
  }

  void Drawable::set_skew_x ( double skewx, DegRad units )
  {
    m_skewx = units2rad(skewx, units);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_skew_y ( double skewy, DegRad units )
  {
    m_skewy = units2rad(skewy, units);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_skew ( double skewx, double skewy, DegRad units )
  {
    m_skewx = units2rad(skewx, units);
    m_skewy = units2rad(skewy, units);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::set_skew ( double s, DegRad units )
  {
    m_skewy = m_skewx = units2rad(s, units);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::skew ( double x, double y, DegRad units )
  {
    m_skewx += units2rad(x, units);
    m_skewy += units2rad(y, units);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::skew ( double s, DegRad units )
  {
    m_skewx += units2rad(s, units);
    m_skewy += units2rad(s, units);
    this->invalidate_composed_matrix();
    this->redraw();
  }

  double Drawable::centroid_x() const
  {
    return m_centroid_x;
  }

  void Drawable::set_centroid_x ( double centroid_x )
  {
    m_centroid_x = centroid_x;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  double Drawable::centroid_y() const
  {
    return m_centroid_y;
  }

  void Drawable::set_centroid_y ( double centroid_y )
  {
    m_centroid_y = centroid_y;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::get_centroid ( double& centroid_x, double& centroid_y )
  {
    centroid_x = m_centroid_x;
    centroid_y = m_centroid_y;
  }

  void Drawable::set_centroid ( double centroid_x, double centroid_y )
  {
    m_centroid_x = centroid_x;
    m_centroid_y = centroid_y;
    this->invalidate_composed_matrix();
    this->redraw();
  }

  const Matrix& Drawable::matrix() const
  {
    if ( m_matrix_invalid )
    {
      if ( m_viewbox )
      {
        Matrix vbmatrix;
        vbmatrix = m_viewbox->transformation_matrix( this->pre_viewbox_extents() );
        const_cast<Drawable*>(this)->m_matrix = this->composed_matrix() * vbmatrix;
        const_cast<Drawable*>(this)->m_matrix_invalid = false;
        const_cast<Drawable*>(this)->m_extents = this->pre_viewbox_extents();
        const_cast<Drawable*>(this)->m_extents.transform(vbmatrix);
        const_cast<Drawable*>(this)->m_extents_invalid = true;
      }
      else
      {
        const_cast<Drawable*>(this)->m_matrix = this->composed_matrix();
        const_cast<Drawable*>(this)->invalidate_extents();
        const_cast<Drawable*>(this)->m_matrix_invalid = false;
      }
    }
    
    return m_matrix;
  }
  
  const Matrix& Drawable::composed_matrix() const
  {
    if ( m_composed_matrix_invalid )
    {
      const_cast<Drawable*>(this)->m_composed_matrix = this->calculate_composed_matrix();
      const_cast<Drawable*>(this)->invalidate_matrix();
      const_cast<Drawable*>(this)->m_composed_matrix_invalid = false;
    }
    return m_composed_matrix;
  }

  void Drawable::add_matrix(const Matrix::pointer m, int level)
  {
    MatrixConnMap::iterator conniter;
    
    if ( not m ) return;
    m_matrices[level].push_back(m);
    
    // Look to see if we have a signal_changed connection for this matrix
    conniter = m_matrix_connections.find(m);
    
    // If we do, increment the count
    if ( conniter != m_matrix_connections.end() )
    {
      conniter->second.count += 1;
    }
    // Otherwise create a new connection and set the count to 1
    else
    {
      m_matrix_connections[m].connection = m->signal_changed().connect( sigc::mem_fun(*this, &Drawable::on_matrix_changed) );
      m_matrix_connections[m].count = 1;
    }
    
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::remove_matrix(const Matrix::pointer m)
  {
    MatrixMap::iterator mapiter;
    MatrixList::iterator listiter;
    MatrixConnMap::iterator conniter;
    
    for (mapiter = m_matrices.begin(); mapiter != m_matrices.end(); mapiter++)
    {
      listiter = mapiter->second.begin();
      while ( listiter != mapiter->second.end() )
      {
        if ( *listiter == m ) 
          listiter = mapiter->second.erase(listiter);
        else 
          listiter++;
      }
    }
    
    // Find the signal_changed connection
    conniter = m_matrix_connections.find(m);
    if ( conniter != m_matrix_connections.end() )
    {
      // Don't worry about the count. We'll just disconnect it.
      conniter->second.connection.disconnect();
      m_matrix_connections.erase(conniter);
    }
    
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::remove_matrix(const Matrix::pointer m, int level)
  {
    MatrixList::iterator listiter;
    MatrixConnMap::iterator conniter;
    unsigned int num_found = 0;
    
    if ( m_matrices.find(level) == m_matrices.end() ) return;
    
    listiter = m_matrices[level].begin();
    
    while ( listiter != m_matrices[level].end() )
    {
      if ( *listiter == m ) 
      {
        listiter = m_matrices[level].erase(listiter);
        
        // Increment the number of instances found at this level
        num_found++;
      }
      else
      {
        listiter++;
      }
    }
    
    // Find the signal_changed connection for this matrix
    conniter = m_matrix_connections.find(m);
    if ( conniter != m_matrix_connections.end() )
    {
      // Was this the last instance of this matrix?
      if ( num_found >= conniter->second.count )
      {
        // If it was, disconnect the changed signal
        conniter->second.connection.disconnect();
        m_matrix_connections.erase(conniter);
      }
      else
      {
        // Otherwise, we still have the matrix at another level
        // so we'll decrement the count
        conniter->second.count -= num_found;
      }
    }
    
    this->invalidate_composed_matrix();
    this->redraw();
  }

  const Drawable::MatrixMap& Drawable::matrices()
  {
    return m_matrices;
  }
  
  const Drawable::MatrixConnMap & Drawable::matrix_connection_map()
  {
    return m_matrix_connections;
  }

  Matrix Drawable::global_matrix() const
  {
    if ( m_parent )
      return m_parent->global_matrix() * this->matrix();
    else
      return this->composed_matrix();
  }

  void Drawable::global_to_local ( double& x, double& y ) const
  {
    Matrix matrix = this->global_matrix();
    matrix.invert();
    matrix.transform_point ( x, y );
  }

  void Drawable::local_to_global ( double& x, double& y ) const
  {
    this->global_matrix().transform_point ( x, y );
  }

  void Drawable::distance_global_to_local ( double& x, double& y ) const
  {
    Matrix matrix = this->global_matrix();
    matrix.invert( );
    matrix.transform_distance ( x, y );
  }

  void Drawable::distance_local_to_global ( double& x, double& y ) const
  {
    this->global_matrix().transform_distance ( x, y );
  }

  void Drawable::render ( Context& cairo ) const
  {
    // We're not going to render if we're invisible
    if ( not m_visible and not (cairo.flags & RENDER_FORCE) ) return;

    cairo.save();

#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 2, 0)
    cairo->begin_new_path();
#else
    cairo->clear_path();
#endif

    if ( m_viewbox and m_viewbox->meet_or_slice() == Viewbox::SLICE )
    {
      double x, y, w, h;
      m_viewbox->xywh(x, y, w, h);
      cairo->rectangle( x, y, w, h );
      cairo->clip();
    }

    cairo.transform( this->matrix() );

    if ( m_composite_operator != -1 )
      cairo->set_operator ( (Cairo::Operator) m_composite_operator );

    if ( m_alpha >= 0.0 and m_alpha <= 1.0 ) cairo->push_group();
    
    this->draw ( cairo );
    
    if ( m_alpha >= 0.0 and m_alpha <= 1.0 )
    {
      cairo->pop_group_to_source();
      cairo.paint_with_alpha( m_alpha );
    }

    cairo.restore();
  }

  void Drawable::render(Context& cairo, double x, double y, double w, double h) const
  {
    if ( not this->extents().overlaps(Region(x, y, w, h)) ) return;
    this->render(cairo);
  }

  void Drawable::freeze()
  {
    m_frozen = true;
    m_signal_frozen.emit(FROZEN);
  }

  void Drawable::thaw(bool force_redraw)
  {
    m_frozen = false;
    if ( not m_frozen_by_parent and (force_redraw or m_need_redraw) ) 
    {
      m_signal_frozen.emit(THAWED);
      this->redraw();
      m_signal_changed.emit();
    }
  }

  bool Drawable::is_frozen()
  {
    return m_frozen or m_frozen_by_parent;
  }

  int Drawable::composite_operator()
  {
    return m_composite_operator;
  }

  void Drawable::set_composite_operator ( Cairo::Operator op )
  {
    m_composite_operator = op;
    this->redraw();
  }

  void Drawable::clear_composite_operator( )
  {
    m_composite_operator = -1;
    this->redraw();
  }

  Region Drawable::extents( const Matrix& m, ExtentsPerformance ep ) const
  {
    Region e;
    
    switch ( ep )
    {
      case EXTENTS_QUICK:
        if ( m_extents_invalid )
        {
//           std::cout << "\n========================================\nextents()" << std::endl;
    
          const_cast<Drawable*>(this)->m_redraw_extents.include(m_extents);

          Matrix m = this->composed_matrix();

          if ( m_viewbox )
          {
            Matrix vbmatrix;
            vbmatrix = m_viewbox->transformation_matrix( this->pre_viewbox_extents() );
            m *= vbmatrix;
            const_cast<Drawable*>(this)->m_extents = this->calculate_extents( m );
          }
          else
          {
            const_cast<Drawable*>(this)->m_extents = this->pre_viewbox_extents();
          }

          const_cast<Drawable*>(this)->m_extents_invalid = false;
        }

        e = m_extents;
        e.transform(m);
        return e;

      case EXTENTS_PRECISE:
        return this->calculate_extents( m * this->matrix() );
    }
    
    return Region();
  }

  Region Drawable::pre_viewbox_extents( const Matrix& m, ExtentsPerformance ep ) const
  {
    Region prevb_extents;

    switch ( ep )
    {
      case EXTENTS_QUICK:
        if ( m_pre_viewbox_extents_invalid )
        {
//           std::cout << "\n========================================\npre_viewbox_extents()" << std::endl;
    
          const_cast<Drawable*>(this)->m_pre_viewbox_extents = this->calculate_extents(this->composed_matrix());
          const_cast<Drawable*>(this)->invalidate_matrix();
          const_cast<Drawable*>(this)->m_pre_viewbox_extents_invalid = false;
        }

        prevb_extents = m_pre_viewbox_extents;
        prevb_extents.transform(m);
        return prevb_extents;
      case EXTENTS_PRECISE:
        return this->calculate_extents( m * this->composed_matrix() );
    }

    return Region();
  }

  Region Drawable::raw_extents() const
  {
//     std::cout << "\n========================================\nraw_extents()" << std::endl;
    return this->calculate_extents();
  }

  Region Drawable::global_extents() const
  {
    Matrix m;
    
    if ( m_parent ) m = m_parent->global_matrix();

    m *= this->composed_matrix();

    Region r;

    r = this->calculate_extents( m );

    return r;
  }
  
//   Region Drawable::global_extents( )
//   {
//     Matrix inverse_matrix;
//     Region xformed_extents = this->extents();
  //
//     if ( m_viewbox )
//     {
//       Matrix viewbox_matrix = m_viewbox->transformation_matrix ( this->extents() );
//       inverse_matrix = this->composed_matrix() * viewbox_matrix;
//     }
//     else
//       inverse_matrix = this->composed_matrix();
  //
//     inverse_matrix.invert();
  //
//     xformed_extents.transform ( this->composed_matrix() );
  //
//     return xformed_extents;
//   }

  bool Drawable::inside ( double x, double y )
  {
    bool inside = false;

    m_sidebuffer_cairo->set_identity_matrix();

    // Suppress the stroke and fill and render the path and/or set
    // the fill/stroke sources
    m_sidebuffer_cairo.flags = RENDER_SUPPRESS_CAIRO_STROKE | RENDER_SUPPRESS_CAIRO_FILL | RENDER_FORCE;
    this->render(m_sidebuffer_cairo);

    // Necessary to ensure the CTM isn't applied to x and y
    // so that x and y are relative to the global perspective before the CTM
    m_sidebuffer_cairo->save();
    m_sidebuffer_cairo->set_identity_matrix();

    // Test for the fill
    inside = m_sidebuffer_cairo->in_fill(x, y);

    // If it's not in the fill, is it in the stroke (if there is a stroke)?
    if ( not inside ) inside = m_sidebuffer_cairo->in_stroke(x, y);

    m_sidebuffer_cairo->restore();

    return inside;
  }

  bool Drawable::exclude_from_extents()
  {
    return m_exclude_from_extents;
  }

  void Drawable::set_exclude_from_extents ( bool b )
  {
    m_exclude_from_extents = b;
    this->redraw();
  }

  void Drawable::redraw()
  {
    double x, y, w, h;

    if ( m_frozen or m_frozen_by_parent )
    {
      m_need_redraw = true;
      return;
    }
    
    m_need_redraw = false;
    
    m_redraw_extents.include(this->extents());

    // If we still don't have any extents we won't do anything
    if ( m_redraw_extents )
    {
      m_redraw_extents.xywh ( x, y, w, h );
      m_redraw_extents.invalidate();
      w = ceil( x - floor(x) + w);
      h = ceil( y - floor(y) + h);
      x = floor(x);
      y = floor(y);
      m_signal_redraw.emit ( x, y, w, h );
    }

    m_signal_changed.emit();
  }

  void Drawable::redraw_proxy()
  {
    this->redraw();
  }

  Region Drawable::calculate_extents(const Matrix& m, ExtentsPerformance ep) const
  {
    double x1, y1, x2, y2;

//     std::cout << std::endl << "\n===================================================\ncalculate_extents()\n\nInput matrix: " << m.svg() << std::endl;
    
    m_sidebuffer_cairo.flags = RENDER_SUPPRESS_MATRIX | RENDER_SUPPRESS_CAIRO_STROKE | RENDER_SUPPRESS_CAIRO_FILL | RENDER_SUPPRESS_CAIRO_SAVE_RESTORE | RENDER_FORCE;

    m_sidebuffer_cairo->save();
    m_sidebuffer_cairo->set_identity_matrix();
    m_sidebuffer_cairo->transform( m );
    
    this->render(m_sidebuffer_cairo);

    m_sidebuffer_cairo->set_identity_matrix();

//     std::cout << "Line width: " << m_sidebuffer_cairo->get_line_width() << std::endl;

//     cairo_matrix_t cm;
//     m_sidebuffer_cairo->get_matrix(cm);
//     Matrix m2 = cm;
//     std::cout << "Matrix before get_stroke_extents(): " << m2.svg() << std::endl;

//     m_sidebuffer_cairo->get_fill_extents(x1, y1, x2, y2);
//     printf("Fill Extents: (%f, %f) (%f, %f) w=%f h=%f\n", x1, y1, x2, y2, x2-x1, y2-y1 );
    
    m_sidebuffer_cairo->get_stroke_extents(x1, y1, x2, y2);

    if ( x1 == 0.0 and y1 == 0.0 and x2 == 0.0 and y2 == 0.0 )
    {
      m_sidebuffer_cairo->set_source_rgb(0.0, 0.0, 0.0);
      m_sidebuffer_cairo->get_fill_extents(x1, y1, x2, y2);
    }

    m_sidebuffer_cairo->restore();

//     printf("Stroke Extents: (%f, %f) (%f, %f) w=%f h=%f\n", x1, y1, x2, y2, x2-x1, y2-y1 );
    
    if ( x1 != 0.0 or y1 != 0.0 or x2 != 0.0 or y2 != 0.0 )
      return Region( x1, y1, x2-x1, y2-y1 );
    else
      return Region();
  }

  Viewbox::pointer Drawable::viewbox()
  {
    return m_viewbox;
  }

  void Drawable::set_viewbox ( Viewbox::pointer viewbox )
  {
    if ( m_viewbox_connection ) m_viewbox_connection.disconnect();

    m_viewbox = viewbox;

    if ( m_viewbox )
      m_viewbox_connection = m_viewbox->signal_changed().connect ( sigc::mem_fun ( *this, &Drawable::on_matrix_changed ) );
    
    this->invalidate_matrix();

    this->redraw();
  }

  void Drawable::set_viewbox(double x, double y, double w, double h, Viewbox::ALIGN align, Viewbox::MEET_OR_SLICE meet_or_slice)
  {
    this->set_viewbox( Papyrus::Viewbox::create(x, y, w, h, align, meet_or_slice) );
  }

  void Drawable::set_viewbox(const Region & region, Viewbox::ALIGN align, Viewbox::MEET_OR_SLICE meet_or_slice)
  {
    this->set_viewbox( Papyrus::Viewbox::create(region, align, meet_or_slice) );
  }

  void Drawable::set_viewbox ( const Viewbox& viewbox )
  {
    Viewbox::pointer vb = Viewbox::create();
    *vb = viewbox;
    this->set_viewbox ( vb );
  }

  void Drawable::set_selectable ( bool selectable )
  {
    m_selectable = selectable;
  }

  bool Drawable::is_selectable()
  {
    return m_selectable;
  }

  bool Drawable::is_group()
  {
    return false;
  }

  Group* Drawable::parent()
  {
    return m_parent;
  }

  Drawable::operator Drawable::pointer( )
  {
    return this->self();
  }

  Drawable::pointer Drawable::self( )
  {
    return pointer ( m_self );
  }

  sigc::signal<void, double, double, double, double>& Drawable::signal_redraw()
  {
    return m_signal_redraw;
  }

  sigc::signal<void>& Drawable::signal_selectable()
  {
    return m_signal_selectable;
  }

  sigc::signal<void>& Drawable::signal_destroyed()
  {
    return m_signal_destroyed;
  }

  sigc::signal< void, FrozenThawed >& Drawable::signal_frozen()
  {
    return m_signal_frozen;
  }
  
  sigc::signal< void > & Drawable::signal_composed_matrix_invalidated()
  {
    return m_signal_composed_matrix_invalidated;
  }

  sigc::signal< void > & Drawable::signal_extents_changed()
  {
    return m_signal_extents_changed;
  }

  void Drawable::reset_position( )
  {
    m_x = 0.0;
    m_y = 0.0;
    m_sx = 1.0;
    m_sy = 1.0;
    m_r = 0.0;
    m_skewx = 0.0;
    m_skewy = 0.0;
    m_centroid_x = 0.0;
    m_centroid_y = 0.0;

    this->invalidate_composed_matrix();
    
    this->redraw();
  }

  Matrix Drawable::calculate_composed_matrix( ) const
  {
    Matrix m;
    
    m.set_identity();
    
    m.translate( m_x, m_y );
    m.scale( m_sx, m_sy );
    m.translate( m_centroid_x, m_centroid_y );
    m.rotate( m_r );
    m.translate( -m_centroid_x, -m_centroid_y );
    m.skew( m_skewx, m_skewy );

    this->apply_external_matrices( m );
    return m;
  }

  void Drawable::apply_external_matrices(Matrix& m) const
  {
    Matrix applied;
    
    MatrixMap::const_iterator mapiter;
    MatrixList::const_iterator listiter;

    /* apply all external matrices with a level < 0 */
    for ( mapiter = m_matrices.begin(); mapiter != m_matrices.end() and mapiter->first < 0; mapiter++ )
      for ( listiter = mapiter->second.begin(); listiter != mapiter->second.end(); listiter++ )
        applied *= (*listiter);

    /* apply the supplied matrix */
    applied *= m;

    /* apply all external matrices with a level >= 0 */
    for ( /* no initializer, pick up where we left off above */; mapiter != m_matrices.end(); mapiter++ )
      for ( listiter = mapiter->second.begin(); listiter != mapiter->second.end(); listiter++ )
        applied *= (*listiter);

    m = applied;
  }
  
  Glib::ustring Drawable::svg_transform()
  {
    Glib::ustring s = "transform=\"";
//     ExternalMatrices::iterator iter;
    bool local_applied = false;

//     for ( iter = m_external_matrices.begin(); iter != m_external_matrices.end(); iter++ )
//     {
//       if ( !local_applied && iter->first >= 0 )
//       {
//         s += m_local_matrix.svg();
//         local_applied = true;
//       }
// 
//       s += iter->second->svg();
//     }
    
    if ( ! local_applied )
      s += this->composed_matrix().svg();

    if ( s.size() == 11 )
      return Glib::ustring();
    
    s += "\"";
    
    return s;
  }

 void Drawable::on_matrix_changed()
  {
    this->invalidate_composed_matrix();
    this->redraw();
  }

  void Drawable::on_viewbox_changed()
  {
    this->invalidate_matrix();
    this->redraw();
  }

  void Drawable::invalidate_matrix()
  {
    m_matrix_invalid = true;
    m_extents_invalid = true;
  }

  void Drawable::invalidate_composed_matrix()
  {
    m_matrix_invalid = true;
    m_composed_matrix_invalid = true;
    m_extents_invalid = true;
    m_pre_viewbox_extents_invalid = true;
    m_signal_composed_matrix_invalidated.emit();
  }

  void Drawable::invalidate_extents()
  {
    m_matrix_invalid = true;
    m_extents_invalid = true;
    m_pre_viewbox_extents_invalid = true;
    m_signal_extents_changed.emit();
  }

}

