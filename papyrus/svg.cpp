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
#include "svg.h"

#include <libxml++/libxml++.h>
#include <cstring>
#include <fstream>
#include <iostream>

#include "circle.h"
#include "reference.h"
#include "rectangle.h"
#include "path.h"
#include "color.h"

namespace Papyrus
{

  SVG::SVG( ) :
      Group(Glib::ustring())
  {
  }
  
  SVG::SVG ( const Glib::ustring& id, const Glib::ustring& s, StrType st ) :
      Group ( id )
  {
    switch ( st )
    {
      case FILE:
        this->set_from_file( s );
        break;
      case MEMORY:
        this->set_from_memory( s );
        break;
    }
  }

  SVG::pointer SVG::create( )
  {
    PAPYRUS_CREATE( SVG( ) );
  }
  
  SVG::pointer SVG::create ( const Glib::ustring & s, StrType st )
  {
    PAPYRUS_CREATE ( SVG ( Glib::ustring(), s, st ) );
  }

  SVG::pointer SVG::create ( const Glib::ustring& id, const Glib::ustring & s, StrType st )
  {
    PAPYRUS_CREATE ( SVG ( id, s, st ) );
  }

  SVG::~SVG()
  {}

  bool SVG::set_from_file(const Glib::ustring & svg_filename)
  {
    xmlpp::DomParser parser;

//     parser.set_validate();
    parser.set_substitute_entities();
    parser.parse_file(svg_filename);

    if ( not parser ) return false;

    return this->set_from_document( parser.get_document() );
  }

  bool SVG::set_from_memory(const Glib::ustring & svg)
  {
    xmlpp::DomParser parser;

//     parser.set_validate();
    parser.set_substitute_entities();
    parser.parse_memory(svg);

    if ( not parser ) return false;
  
    return this->set_from_document( parser.get_document() );
  }

  bool SVG::set_from_memory(const unsigned char * contents, size_t bytes)
  {
    xmlpp::DomParser parser;

//     parser.set_validate();
    parser.set_substitute_entities();
    parser.parse_memory_raw(contents, bytes);

    if ( not parser ) return false;

    return this->set_from_document( parser.get_document() );
  }

  bool SVG::set_from_stream(std::istream & in)
  {
    xmlpp::DomParser parser;

//     parser.set_validate();
    parser.set_substitute_entities();
    parser.parse_stream(in);

    if ( not parser ) return false;
    
    return this->set_from_document( parser.get_document() );
  }

  bool SVG::set_from_document(const xmlpp::Document * doc)
  {
    if ( not doc ) return false;
    return this->set_from_element( doc->get_root_node() );
  }

  bool SVG::set_from_element(const xmlpp::Element * element)
  {
    if ( not element ) return false;
    return this->process_element( element, *this, false, true );
  }

  Glib::ustring SVG::svg( unsigned depth )
  {
    Glib::ustring s;
    s += svg_spacing(depth) + "<svg " + svg_id() + ">\n";

    // TODO move this to Group
//     if ( ! m_named_drawables.empty() )
//     {
//       s += svg_spacing(depth+1) + "<defs>\n";
//       NamedDrawables::iterator ndi;
//       for ( ndi = m_named_drawables.begin(); ndi != m_named_drawables.end(); ndi++ )
//         s += ndi->second->svg(depth+1);
//       s += svg_spacing(depth+1) + "</defs>\n";
//     }

    Layers::iterator ix;
    Layer::iterator iy;
    for (ix = m_layers.begin(); ix != m_layers.end(); ix++ )
      for ( iy = ix->second.begin(); iy != ix->second.end(); iy++ )
        s += (*iy)->svg(depth+1);

    s += svg_spacing(depth) + "</svg>\n";

    return s;
  }
  
  bool process_drawable( Group& parent, Drawable::pointer d, const AttributeValueMap& avmap, bool in_defs_section )
  {
    AttributeValueMap::const_iterator i = avmap.find("id");

    if ( in_defs_section and i == avmap.end() and i->second.size() == 0 ) return false;
    
    if ( in_defs_section )
      parent.add_drawable_to_dictionary( i->second, d );
    else
      parent.add( d );

    d->set( avmap );

    return true;
  }

  bool process_stop(const xmlpp::Element* element, Cairo::RefPtr<Cairo::Gradient> pattern )
  {
    if ( not element or element->get_name() != "stop" ) return false;
    if ( not pattern ) return false;

    Glib::ustring offsetstr, stop_colorstr, stop_opacitystr;
    double offset, stop_opacity=1.0;
    RGBA stop_color("black");

    offsetstr = element->get_attribute_value("offset");
    stop_colorstr = element->get_attribute_value("stop-color");
    stop_opacitystr = element->get_attribute_value("stop-opacity");

    if ( offsetstr.size() == 0 ) return false;
    offset = atof( offsetstr.c_str() );
    if ( offsetstr.find('%') != Glib::ustring::npos ) offset /= 100.0;

    if ( offset < 0.0 or offset > 1.0 ) return false;

    if ( stop_colorstr.size() > 0 ) stop_color = RGBA(stop_colorstr);

    if ( stop_opacitystr.size() > 0 ) stop_color.alpha = atof( stop_opacitystr.c_str() );

    pattern->add_color_stop_rgba( offset, stop_color.red, stop_color.green, stop_color.blue, stop_color.alpha );
    
    return true;
  }

  Cairo::RefPtr<Cairo::LinearGradient> process_linear_gradient(const xmlpp::Element* element)
  {
    if ( not element or element->get_name() != "linearGradient" ) return Cairo::RefPtr<Cairo::LinearGradient>();
    
    Glib::ustring transformstr, x1str, y1str, x2str, y2str, spreadstr;
    double x1=0.0, y1=0.0, x2=1.0, y2=0.0;
    
    transformstr = element->get_attribute_value("gradientTransform");
    x1str = element->get_attribute_value("x1");
    y1str = element->get_attribute_value("y1");
    x2str = element->get_attribute_value("x2");
    y2str = element->get_attribute_value("y2");
    spreadstr = element->get_attribute_value("spreadMethod");

    if ( x1str.size() > 0 )
    {
      x1 = atof( x1str.c_str() );
      if ( x1str.find('%') != Glib::ustring::npos ) x1 /= 100.0;
    }
    
    if ( y1str.size() > 0 )
    {
      y1 = atof( y1str.c_str() );
      if ( y1str.find('%') != Glib::ustring::npos ) y1 /= 100.0;
    }
    
    if ( x2str.size() > 0 )
    {
      x2 = atof( x2str.c_str() );
      if ( x2str.find('%') != Glib::ustring::npos ) x2 /= 100.0;
    }
    
    if ( y2str.size() > 0 )
    {
      y2 = atof( y2str.c_str() );
      if ( y2str.find('%') != Glib::ustring::npos ) y2 /= 100.0;
    }

    Cairo::RefPtr<Cairo::LinearGradient> gradient = Cairo::LinearGradient::create( x1, y1, x2, y2 );

    xmlpp::Node::NodeList::iterator citer;
    xmlpp::Node::NodeList children = element->get_children();
    for ( citer = children.begin(); citer != children.end(); citer++ )
      process_stop( dynamic_cast<const xmlpp::Element*>(*citer), gradient );

    return gradient;
  }

  Cairo::RefPtr<Cairo::RadialGradient> process_radial_gradient(const xmlpp::Element* element)
  {
    if ( element->get_name() != "radialGradient" ) return Cairo::RefPtr<Cairo::RadialGradient>();
    
    xmlpp::Node::NodeList::iterator citer;
    xmlpp::Node::NodeList children = element->get_children();
    
    return Cairo::RefPtr<Cairo::RadialGradient>();
  }

  bool SVG::process_element(const xmlpp::Element * element, Group& parent, bool in_defs_section, bool is_root)
  {
    if ( not element ) return false;

    xmlpp::Element::AttributeList::iterator aiter;
    xmlpp::Element::AttributeList attributes = element->get_attributes();

    xmlpp::Node::NodeList::iterator citer;
    xmlpp::Node::NodeList children = element->get_children();

//     std::cout << "START Processing tag " << element->get_name() << std::endl;

    AttributeValueMap avmap;
    AttributeValueMap::iterator aviter;

    // Build the attribute value map
    for ( aiter = attributes.begin(); aiter != attributes.end(); aiter++ )
      avmap[ (*aiter)->get_name() ] = (*aiter)->get_value();
    
    if ( is_root )
    {
      // Is this an SVG tag?
      if ( element->get_name() != "svg" ) return false;
      this->clear();
      // TODO handle width and height attributes
      for ( citer = children.begin(); citer != children.end(); citer++ )
      {
        const xmlpp::Element* child = dynamic_cast<const xmlpp::Element*>( *citer );
        if ( child ) this->process_element( child, *this, false );
      }
      this->set_fill( RGBA(0.0, 0.0, 0.0) );
    }

    else if ( element->get_name() == "linearGradient" )
    {
      Glib::ustring id = element->get_attribute_value("id");

      if ( id.size() > 0 )
      {
        Cairo::RefPtr<Cairo::Pattern> pattern = process_linear_gradient(element);
        if ( pattern ) parent.add_paint_to_dictionary( id, Color::create(pattern) );
      }
    }

    // Descend into defs section
    else if ( strcaseeq(element->get_name(), "defs" ) )
    {
      for ( citer = children.begin(); citer != children.end(); citer++ )
      {
        const xmlpp::Element* child = dynamic_cast<const xmlpp::Element*>( *citer );
        if ( child ) this->process_element( child, parent, true );
      }
    }

    else if ( strcaseeq( element->get_name(), "title" ) )
    {
      const xmlpp::TextNode* text = element->get_child_text();
      if ( text ) this->set_title( text->get_content() );
    }

    else if ( strcaseeq( element->get_name(), "desc" ) )
    {
      const xmlpp::TextNode* text = element->get_child_text();
      if ( text ) this->set_description( text->get_content() );
    }

    else if ( element->get_name() == "use" )
    {
      Group::pointer g = Group::create(avmap);

      for ( aviter = avmap.begin(); aviter != avmap.end(); aviter++ )
      {
        if ( aviter->first == "href" )
        {
          if ( aviter->second.size() > 0 and aviter->second[0] == '#' )
          {
            aviter->second.erase(0,1);
            Drawable::pointer d = parent.lookup_drawable( aviter->second );
            if ( d )
            {
              // FIXME SVG use cases are broken
//               Drawable::pointer d2 = d->clone();
//               g->add( d2 );
//               process_drawable( parent, g, AttributeValueMap(), in_defs_section );
            }
          }
        }
      }
    }
    
    // Handle group elements
    else if ( strcaseeq(element->get_name(), "g") )
    {
      Group::pointer g = Group::create();

      process_drawable( parent, g, avmap, in_defs_section );

      for ( citer = children.begin(); citer != children.end(); citer++ )
      {
        const xmlpp::Element* child = dynamic_cast<const xmlpp::Element*>( *citer );
        if ( child ) this->process_element( child, *g, false );
      }

    }

    else if ( strcaseeq( element->get_name(), "rect" ) )   process_drawable( parent, Rectangle::create(), avmap, in_defs_section );
    else if ( strcaseeq( element->get_name(), "circle" ) ) process_drawable( parent, Circle::create(), avmap, in_defs_section );
    else if ( strcaseeq( element->get_name(), "path" ) )   process_drawable( parent, Path::create(), avmap, in_defs_section );
    
//     std::cout << "FINISH Processing tag " << element->get_name() << std::endl;

    return true;
  }


  Glib::ustring SVG::extract_id_from_uri(const Glib::ustring & uri)
  {
    regmatch_t match;

//     if ( not m_uri_regex_initialized ) this->initialize_uri_regular_expression();

//     if ( regexec( &m_uri_regular_expression, uri.c_str(), 1, &match, 0 ) == 0 )
//     {
//     }
    
    return Glib::ustring();
  }

  void SVG::initialize_uri_regular_expression()
  {
    int result;
    const char* expression = "[[:alpha:]]*\\(#[[:alnum:]]*\\)";

//     result = regcomp( &m_uri_regular_expression, expression, REG_EXTENDED|REG_ICASE );
    if ( result != 0 ) throw;
    
//     m_uri_regex_initialized = true;
  }

}



