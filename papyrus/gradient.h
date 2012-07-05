/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
#ifndef PAPYRUSGRADIENT_H
#define PAPYRUSGRADIENT_H

#include <papyrus/paint.h>
#include <papyrus/rgba.h>

namespace Papyrus
{

  /**
   * Base class for linear and radial gradients (LinearGradient and RadialGradient)
   *
   * This is similar to the cairo linear and radial gradient base class. However,
   * several items have been added to support SVG style gradients.
   *
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Gradient : public Paint
  {
    protected:
      
      Gradient();

    public:
      
      typedef PapyrusPointer<Gradient> pointer;
      
      ~Gradient();
      
      GradientUnits units() const;
      
      void set_units( GradientUnits gu );
      
      GradientSpread spread() const;
      
      void set_spread( GradientSpread s );
      
      const Matrix& transform() const;
      
      Matrix& transform();
      
      void set_transform( const Matrix& m );
      
      Gradient::pointer parent();
      
      void set_parent( Gradient::pointer p );

    /**
     * A gradient stop for use with LinearGradient or RadialGradient
     *
     * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
     */
    class Stop : public Object
      {
        public:
          
          Stop( );

          Stop ( const RGBA& rgba, double offset );

          Stop ( const RGBA& rgba, double offset, double alpha );

          Stop ( const Glib::ustring& id );

          Stop ( const Glib::ustring& id, const RGBA& rgba, double offset );

          Stop ( const Glib::ustring& id, const RGBA& rgba, double offset, double alpha );

          ~Stop();

          double offset() const;

          void set_offset ( double off );

          const RGBA& color() const;

          RGBA& color();

          void set_color ( const RGBA& rgba );

          void unset_color();
          
          double red() const;
          
          double green() const;
          
          double blue() const;

          double alpha() const;

          void set_alpha ( double opa );

        protected:

          bool m_offset_set, m_color_set, m_alpha_set;

          double m_offset;

          RGBA m_color;

          double m_alpha;

      };
      
    typedef std::vector<Stop> Stops;
    
    const Stops& stops() const;
    
    void push_front( const Stop& s );
    
    void push_back( const Stop& s );
    
    void insert( Stops::iterator pos, const Stop& s );
    
    void remove( Stops::iterator pos );
    
    void clear_stops();

    protected:
      
      GradientUnits m_units;
      
      GradientSpread m_spread;
      
      Matrix m_transform;
      
      Gradient::pointer m_parent;
      
      sigc::connection m_parent_changed_connection;
      
      Stops m_stops;
      
      void on_parent_changed();
      
      void on_transform_changed();
      
      


  };

}

#endif
