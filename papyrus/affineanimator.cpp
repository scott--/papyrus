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
#include "affineanimator.h"

namespace Papyrus
{

  AffineAnimator::AffineAnimator ( const Glib::ustring&  id,
                                   double tx, double ty,
                                   double scalex, double scaley,
                                   double rotation,
                                   double skewx, double skewy
                                 ):
      Animator(id),
      m_tx ( tx ), m_ty ( ty ),
      m_scalex ( scalex ), m_scaley ( scaley ),
      m_r ( rotation ),
      m_skewx ( skewx ), m_skewy ( skewy )
  {
    if ( scalex == 0.0 )
      m_revscalex = 1.0;
    else
      m_revscalex = 1.0 / scalex;

    if ( scaley == 0.0 )
      m_revscaley = 1.0;
    else
      m_revscaley = 1.0 / scaley;
  }

  AffineAnimator::pointer AffineAnimator::create ( const Glib::ustring& id,
                                                   double tx, double ty,
                                                   double scalex, double scaley,
                                                   double rotation,
                                                   double skewx, double skewy
                                                 )
  {
    return AffineAnimator::pointer ( new AffineAnimator ( id, tx, ty, scalex, scaley, rotation, skewx, skewy ) );
  }

  AffineAnimator::pointer AffineAnimator::create ( double tx, double ty,
                                                   double scalex, double scaley,
                                                   double rotation,
                                                   double skewx, double skewy
                                                 )
  {
    return AffineAnimator::pointer ( new AffineAnimator ( Glib::ustring(), tx, ty, scalex, scaley, rotation, skewx, skewy ) );
  }

  AffineAnimator::~AffineAnimator()
  {}

  int AffineAnimator::animate ( int n )
  {
    Drawables::iterator i;

    if ( n == 0 || m_drawables.size() == 0 )
      return 1;

    if ( n > 0 )   // Forward
    {
      for ( i = m_drawables.begin(); i != m_drawables.end(); i++ )
      {
        if ( m_tx != 0.0 || m_ty != 0.0 )
          ( *i )->translate ( m_tx*n, m_ty*n );
        if ( m_scalex != 1.0 || m_scaley != 1.0 )
          ( *i )->scale ( pow ( m_scalex,n ), pow ( m_scaley,n ) );
        if ( m_r != 0.0 )
          ( *i )->rotate ( m_r*n );
        if ( m_skewx != 0.0 || m_skewy != 0.0 )
          ( *i )->skew ( m_skewx*n, m_skewy*n );
      }
    }
    else   // Reverse
    {
      for ( i = m_drawables.begin(); i != m_drawables.end(); i++ )
      {
        if ( m_tx != 0.0 || m_ty != 0.0 )
          ( *i )->translate ( m_tx*n, m_ty*n );
        if ( m_scalex != 1.0 || m_scaley != 1.0 )
          ( *i )->scale ( pow ( m_revscalex,1.0/-n ), pow ( m_revscaley,1.0/-n ) );
        if ( m_r != 0.0 )
          ( *i )->rotate ( m_r*n );
        if ( m_skewx != 0.0 || m_skewy != 0.0 )
          ( *i )->skew ( m_skewx*n, m_skewy*n );
      }
    }

    return n;
  }

  void AffineAnimator::add ( Drawable::pointer d )
  {
    m_drawables.insert ( d );
  }

  void AffineAnimator::remove ( Drawable::pointer d )
  {
    m_drawables.erase ( d );
  }

  const AffineAnimator::Drawables& AffineAnimator::drawables()
  {
    return m_drawables;
  }

  double AffineAnimator::get_translate_x()
  {
    return m_tx;
  }

  double AffineAnimator::get_translate_y()
  {
    return m_ty;
  }

  void AffineAnimator::get_translate ( double& tx, double& ty )
  {
    tx = m_tx;
    ty = m_ty;
  }

  void AffineAnimator::set_translate_x ( double tx )
  {
    m_tx = tx;
  }

  void AffineAnimator::set_translate_y ( double ty )
  {
    m_ty = ty;
  }

  void AffineAnimator::set_translate ( double tx, double ty )
  {
    m_tx = tx;
    m_ty = ty;
  }

  double AffineAnimator::get_scale_x()
  {
    return m_scalex;
  }

  double AffineAnimator::get_scale_y()
  {
    return m_scaley;
  }

  void AffineAnimator::get_scale ( double& sx, double& sy )
  {
    sx = m_scalex;
    sy = m_scaley;
  }

  void AffineAnimator::set_scale_x ( double sx )
  {
    m_scalex = sx;
    if ( sx == 0.0 )
      m_revscalex = 1.0;
    else
      m_revscalex = 1.0 / sx;
  }

  void AffineAnimator::set_scale_y ( double sy )
  {
    m_scaley = sy;
    if ( sy == 0.0 )
      m_revscaley = 1.0;
    else
      m_revscaley = 1.0 / sy;
  }

  void AffineAnimator::set_scale ( double scale_x, double scale_y )
  {
    m_scalex = scale_x;
    m_scaley = scale_y;
    if ( scale_x == 0.0 )
      m_revscalex = 1.0;
    else
      m_revscalex = 1.0 / scale_x;
    if ( scale_y == 0.0 )
      m_revscaley = 1.0;
    else
      m_revscaley = 1.0 / scale_y;
  }

  void AffineAnimator::set_scale ( double s )
  {
    m_scalex = m_scaley = s;
    if ( s == 0.0 )
      m_revscalex = m_revscaley = 1.0;
    else
      m_revscalex = m_revscaley = 1.0 / s;
  }

  double AffineAnimator::get_rotate()
  {
    return m_r;
  }

  void AffineAnimator::set_rotate ( double r )
  {
    m_r = r;
  }

  double AffineAnimator::get_skew_x()
  {
    return m_skewx;
  }

  void AffineAnimator::set_skew_x ( double skewx )
  {
    m_skewx = skewx;
  }

  double AffineAnimator::get_skew_y()
  {
    return m_skewy;
  }

  void AffineAnimator::set_skew_y ( double skewy )
  {
    m_skewy = skewy;
  }

  void AffineAnimator::get_skew ( double& skewx, double& skewy )
  {
    skewx = m_skewx;
    skewy = m_skewy;
  }

  void AffineAnimator::set_skew ( double skewx, double skewy )
  {
    m_skewx = skewx;
    m_skewy = skewy;
  }


}
