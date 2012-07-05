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
#ifndef PAPYRUSSVG_H
#define PAPYRUSSVG_H

#include <istream>
#include <libxml++/libxml++.h>
#include <map>
#include <stack>

#include <expat.h>
#include <papyrus/group.h>

namespace Papyrus
{

  /**
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class SVG : public Group
  {
    public:
      
      typedef enum StrType {
        FILE,
        MEMORY
      } StrType;

    protected:
      SVG ( );
      
      SVG ( const Glib::ustring& id, const Glib::ustring& filename, StrType st );

    public:
      PAPYRUS_DRAWABLE(SVG);

      static pointer create( );
      
      static pointer create ( const Glib::ustring& s, StrType st = FILE );

      static pointer create ( const Glib::ustring& id, const Glib::ustring& s, StrType st );

      virtual ~SVG();

      bool set_from_file( const Glib::ustring& svg_filename );

      bool set_from_memory( const Glib::ustring& svg );

      bool set_from_memory( const unsigned char* contents, size_t bytes );

      bool set_from_stream( std::istream& in );

      bool set_from_document( const xmlpp::Document* doc );

      bool set_from_element( const xmlpp::Element* element );

      virtual Glib::ustring svg(unsigned depth=0);

    protected:

      bool process_element( const xmlpp::Element* element, Group& parent, bool in_defs_section, bool is_root=false );

    private:

      std::vector<Cairo::ColorStop> m_color_stops;

      Glib::ustring extract_id_from_uri( const Glib::ustring& uri );
      
      static void initialize_uri_regular_expression();


  };

}

#endif
