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
#include "affinecontroller.h"

namespace Papyrus
{

  AffineController::AffineController ( const Glib::ustring& id, DrawableSet::pointer drawables, double tx, double ty, double sx, double sy, double r ):
      DrawableController(id, drawables),
      m_tx ( tx ),
      m_ty ( ty ),
      m_sx ( sx ),
      m_sy ( sy ),
      m_r ( r ),
      m_skewx ( 0.0 ),
      m_skewy ( 0.0 ),
      m_centroid_x ( 0.0 ),
      m_centroid_y ( 0.0 ),
      m_matrix_level( -1 )
  {
    m_matrix = Matrix::create();
    if ( m_sx < 0.0 ) m_sx = 1.0;
    if ( m_sy < 0.0 ) m_sy = 1.0;
    
    this->recalculate_matrix();

    // Make sure that any drawables that we start with have the matrix installed
    for ( iterator i = m_drawables.begin(); i != m_drawables.end(); i++ )
      this->on_drawable_added( *i );
  }


  AffineController::pointer AffineController::create ( const Glib::ustring& id, double tx, double ty, double sx, double sy, double r )
  {
    PAPYRUS_CREATE( AffineController ( id, DrawableSet::pointer(), tx, ty, sx, sy, r ) );
  }

  AffineController::pointer AffineController::create ( const Glib::ustring& id, DrawableSet::pointer drawables, double tx, double ty, double sx, double sy, double r )
  {
    PAPYRUS_CREATE( AffineController ( id, drawables, tx, ty, sx, sy, r ) );
  }

  AffineController::pointer AffineController::create ( double tx, double ty, double sx, double sy, double r )
  {
    PAPYRUS_CREATE( AffineController ( Glib::ustring(), DrawableSet::pointer(), tx, ty, sx, sy, r ) );
  }

  AffineController::pointer AffineController::create ( DrawableSet::pointer drawables, double tx, double ty, double sx, double sy, double r )
  {
    PAPYRUS_CREATE( AffineController ( Glib::ustring(), drawables, tx, ty, sx, sy, r ) );
  }

  AffineController::~AffineController()
  {}

  double AffineController::get_translate_x()
  {
    return m_tx;
  }

  double AffineController::get_translate_y()
  {
    return m_ty;
  }

  void AffineController::get_translate ( double& tx, double& ty )
  {
    tx = m_tx;
    ty = m_ty;
  }

  void AffineController::set_translate_x ( double tx )
  {
    m_tx = tx;
    this->recalculate_matrix();
    m_signal_xy.emit();
  }

  void AffineController::set_translate_y ( double ty )
  {
    m_ty = ty;
    this->recalculate_matrix();
    m_signal_xy.emit();
  }

  void AffineController::set_translate ( double tx, double ty )
  {
    m_tx = tx;
    m_ty = ty;
    this->recalculate_matrix();
    m_signal_xy.emit();
  }

  void AffineController::translate( double x, double y )
  {
    m_tx += x;
    m_ty += y;
    this->recalculate_matrix();
    m_signal_xy.emit();
  }

  void AffineController::get_scale ( double& sx, double& sy )
  {
    sx = m_sx;
    sy = m_sy;
  }

  void AffineController::set_scale_x ( double sx )
  {
    if ( sx <= 0.0 ) return;
    m_sx = sx;
    this->recalculate_matrix();
    m_signal_scale.emit();
  }

  void AffineController::set_scale_y ( double sy )
  {
    if ( sy <= 0.0 ) return;
    m_sy = sy;
    this->recalculate_matrix();
    m_signal_scale.emit();
  }

  void AffineController::set_scale ( double sx, double sy )
  {
    if ( sx > 0.0 ) m_sx = sx;
    if ( sy > 0.0 ) m_sy = sy;

    this->recalculate_matrix();
    m_signal_scale.emit();
  }

  void AffineController::set_scale ( double s )
  {
    if ( s <= 0.0 )
      return ;

    m_sx = s;
    m_sy = s;
    this->recalculate_matrix();
    m_signal_scale.emit();
  }

  void AffineController::scale( double x, double y )
  {
    if ( x > 0.0 )
      m_sx *= x;
    if ( y > 0.0 )
      m_sy *= y;

    this->recalculate_matrix();
    m_signal_scale.emit();
  }

  void AffineController::scale( double s )
  {
    if ( s > 0.0 )
    {
      m_sx *= s;
      m_sy *= s;
      this->recalculate_matrix();
      m_signal_scale.emit();
    }
  }

  double AffineController::get_rotation(DegRad unit)
  {
    if ( unit == DEGREES ) return m_r * 180.0 / M_PI;
    else return m_r;
  }

  void AffineController::set_rotation( double r, DegRad unit )
  {
    if ( unit == DEGREES ) r *= M_PI / 180.0;
    m_r = r;
    this->recalculate_matrix();
    m_signal_rotation.emit();
  }

  void AffineController::rotate( double r, DegRad unit )
  {
    if ( unit == DEGREES ) r *= M_PI / 180.0;
    m_r += r;
    this->recalculate_matrix();
    m_signal_rotation.emit();
  }

  void AffineController::get_skew ( double& skewx, double& skewy, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        skewx = m_skewx * 180.0 / M_PI;
        skewy = m_skewy * 180.0 / M_PI;
        break;
      case RADIANS:
        skewx = m_skewx;
        skewy = m_skewy;
        break;
    }
  }

  void AffineController::set_skew_x ( double skewx, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        m_skewx = skewx * M_PI / 180.0;
        break;
      case RADIANS:
        m_skewx = skewx;
        break;
    }
    this->recalculate_matrix();
    m_signal_skew.emit();
  }

  void AffineController::set_skew_y ( double skewy, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        m_skewy = skewy * M_PI / 180.0;
        break;
      case RADIANS:
        m_skewy = skewy;
        break;
    }
    this->recalculate_matrix();
    m_signal_skew.emit();
  }

  void AffineController::set_skew ( double skewx, double skewy, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        m_skewx = skewx * M_PI / 180.0;
        m_skewy = skewy * M_PI / 180.0;
        break;
      case RADIANS:
        m_skewx = skewx;
        m_skewy = skewy;
        break;
    }
    this->recalculate_matrix();
    m_signal_skew.emit();
  }

  void AffineController::set_skew ( double s, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        m_skewx = s * M_PI / 180.0;
        m_skewy = s * M_PI / 180.0;
        break;
      case RADIANS:
        m_skewx = s;
        m_skewy = s;
        break;
    }
    this->recalculate_matrix();
    m_signal_skew.emit();
  }

  void AffineController::skew ( double x, double y, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        m_skewx += x * M_PI / 180.0;
        m_skewy += y * M_PI / 180.0;
        break;
      case RADIANS:
        m_skewx += x;
        m_skewy += y;
        break;
    }
    this->recalculate_matrix();
    m_signal_skew.emit();
  }

  void AffineController::skew ( double s, DegRad units )
  {
    switch(units)
    {
      case DEGREES:
        m_skewx += s * M_PI / 180.0;
        m_skewy += s * M_PI / 180.0;
        break;
      case RADIANS:
        m_skewx += s;
        m_skewy += s;
        break;
    }
    this->recalculate_matrix();
    m_signal_skew.emit();
  }

  double AffineController::centroid_x()
  {
    return m_centroid_x;
  }

  void AffineController::set_centroid_x ( double centroid_x )
  {
    m_centroid_x = centroid_x;
    this->recalculate_matrix();
    m_signal_centroid.emit();
  }

  double AffineController::centroid_y()
  {
    return m_centroid_y;
  }

  void AffineController::set_centroid_y ( double centroid_y )
  {
    m_centroid_y = centroid_y;
    this->recalculate_matrix();
    m_signal_centroid.emit();
  }

  void AffineController::get_centroid ( double& centroid_x, double& centroid_y )
  {
    centroid_x = m_centroid_x;
    centroid_y = m_centroid_y;
  }

  void AffineController::set_centroid ( double centroid_x, double centroid_y )
  {
    m_centroid_x = centroid_x;
    m_centroid_y = centroid_y;
    this->recalculate_matrix();
    m_signal_centroid.emit();
  }

  Matrix& AffineController::matrix()
  {
    return *m_matrix;
  }

  const Matrix& AffineController::matrix() const
  {
    return *m_matrix;
  }

  int AffineController::matrix_level( ) const
  {
    return m_matrix_level;
  }

  void AffineController::set_matrix_level( int level )
  {
    for ( iterator i = m_drawables.begin(); i != m_drawables.end(); i++ )
    {
      (*i)->remove_matrix( m_matrix, m_matrix_level );
      (*i)->add_matrix( m_matrix, level );
    }
    
    m_matrix_level = level;
  }

  void AffineController::reset_position( )
  {
    m_tx = 0.0;
    m_ty = 0.0;
    m_sx = 1.0;
    m_sy = 1.0;
    m_r = 0.0;
    m_skewx = 0.0;
    m_skewy = 0.0;
    m_centroid_x = 0.0;
    m_centroid_y = 0.0;

    this->recalculate_matrix();
    m_signal_xy.emit();
    m_signal_scale.emit();
    m_signal_rotation.emit();
    m_signal_skew.emit();
    m_signal_centroid.emit();
  }

  void AffineController::recalculate_matrix( )
  {
    Matrix temp_matrix;

    temp_matrix.translate( m_tx + m_centroid_x, m_ty + m_centroid_y );
    temp_matrix.rotate( m_r );
    temp_matrix.translate( -m_centroid_x, -m_centroid_y );
    temp_matrix.skew( m_skewx, m_skewy );
    temp_matrix.scale( m_sx, m_sy );

    *m_matrix = temp_matrix;
  }

  sigc::signal<void> AffineController::signal_xy()
  {
    return m_signal_xy;
  }

  sigc::signal<void> AffineController::signal_scale()
  {
    return m_signal_scale;
  }

  sigc::signal<void> AffineController::signal_rotation()
  {
    return m_signal_rotation;
  }

  sigc::signal<void> AffineController::signal_skew()
  {
    return m_signal_skew;
  }

  sigc::signal<void> AffineController::signal_centroid()
  {
    return m_signal_centroid;
  }

  void AffineController::on_drawable_added( Drawable::pointer d )
  {
    if ( d ) d->add_matrix( m_matrix, m_matrix_level );
  }

  void AffineController::on_drawable_removed( Drawable::pointer d )
  {
    if ( d ) d->remove_matrix( m_matrix );
  }

}


