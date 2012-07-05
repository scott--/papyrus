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
#ifndef PAPYRUSAFFINEANIMATOR_H
#define PAPYRUSAFFINEANIMATOR_H

#include <set>

#include <papyrus/animator.h>

#include <papyrus/drawable.h>

namespace Papyrus
{

  /**
    @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
  */
  class AffineAnimator : public Animator
  {
    protected:
      AffineAnimator ( const Glib::ustring& id,
                       double tx=0.0, double ty=0.0,
                       double scalex=1.0, double scaley=1.0,
                       double rotation=0.0,
                       double skewx=0.0, double skewy=0.0
                     );

    public:
      /** Class level typedef to container for items to transform */
      typedef std::set<Drawable::pointer> Drawables;

      /** Class level smart pointer typedef */
      typedef PapyrusPointer<AffineAnimator> pointer;

      static AffineAnimator::pointer create ( const Glib::ustring& id=Glib::ustring(),
                                              double tx=0.0, double ty=0.0,
                                              double scalex=1.0, double scaley=1.0,
                                              double rotation=0.0,
                                              double skewx=0.0, double skewy=0.0
                                            );

      static AffineAnimator::pointer create ( double tx, double ty,
                                              double scalex=1.0, double scaley=1.0,
                                              double rotation=0.0,
                                              double skewx=0.0, double skewy=0.0
                                            );
      
      virtual ~AffineAnimator();

      void add ( Drawable::pointer d );

      void remove ( Drawable::pointer d );

      const Drawables& drawables();

      double get_translate_x();

      double get_translate_y();

      void get_translate ( double& tx, double& ty );

      void set_translate_x ( double tx );

      void set_translate_y ( double ty );

      void set_translate ( double tx, double ty );

      double get_scale_x();

      double get_scale_y();

      void get_scale ( double& sx, double& sy );

      void set_scale_x ( double sx );

      void set_scale_y ( double sy );

      void set_scale ( double scale_x, double scale_y );

      void set_scale ( double s );

      double get_rotate();

      void set_rotate ( double r );

      double get_skew_x();

      void set_skew_x ( double skewx );

      double get_skew_y();

      void set_skew_y ( double skewy );

      void get_skew ( double& skewx, double& skewy );

      void set_skew ( double skewx, double skewy );

    protected:
      double m_tx, m_ty, m_scalex, m_scaley, m_r, m_skewx, m_skewy, m_revscalex, m_revscaley;
      Drawables m_drawables;

      virtual int animate ( int n=1 );

  };

}

#endif
