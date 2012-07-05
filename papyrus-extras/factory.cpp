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
#include "factory.h"

#include "example_image.h"

namespace Papyrus
{

  const char* DrawableStrings[] =
  {
    "Arc",
    "Annulus",
    "Bezierline",
    "Beziergon",
    "Boxed",
    "Circle",
    "Deltille",
    "Face",
    "Grid",
    "Group",
    "Handle Box",
    "Hextille",
    "Hilbert Curve",
    "Image",
    "Koch Curve",
    "Koch Snowflake",
    "Path",
    "Polygon",
    "Polyline",
    "Quadrille",
    "Rectangle",
    "Reference",
    "Regular Polygon",
    "Sierpinski",
    "SVG",
    "Text",
  };

  Drawable::pointer example_factory ( unsigned int d, bool fill, bool stroke )
  {
    if ( d >= DRAWABLE_END )
      throw;

    switch ( d )
    {
      case ARC:
        return example_arc ( fill, stroke );
      case ANNULUS:
        return example_annulus ( fill, stroke );
      case BEZIERLINE:
        return example_bezierline ( fill, stroke );
      case BEZIERGON:
        return example_beziergon ( fill, stroke );
      case BOXED:
        return example_boxed ( fill, stroke );
      case CIRCLE:
      {
        Circle::pointer shape = Circle::create ( 20 );
        if ( fill )
          shape->set_fill ( RGBA ( "green", 0.9 ) );
        if ( stroke )
          shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 1.0, 0.0, 1.0 ) );
        return shape;
      }
      case DELTILLE:
      {
        Deltille::pointer shape = Deltille::create(10, 10, 20.0);
        if ( fill ) shape->set_fill( RGBA(0.6, 0.87, 0.73) );
        if ( stroke ) shape->set_stroke( RGBA(0.0, 0.0, 1.0) );
        shape->set_fill( RGBA(0.6, 0.73, 0.87), 5, 5 );
        return shape;
      }
      case FACE:
        return Face::create ( 20 );
      case GRID:
      {
        Grid::pointer shape = Grid::create ( -175, 175, -175, 175 );
        shape->set_x_interval ( 50.0 );
        shape->set_y_interval ( 50.0 );
        shape->set_x_interval_stroke ( Stroke::create ( RGBA ( 0.8, 0.8, 0.8, 0.9 ), 1 ) );
        shape->set_y_interval_stroke ( Stroke::create ( RGBA ( 0.8, 0.8, 0.8, 0.9 ), 1 ) );
        if ( stroke )
        {
          shape->set_x_axis_stroke ( Stroke::create ( RGBA ( "DarkGreen", 0.9 ), 5 ) );
          shape->set_y_axis_stroke ( Stroke::create ( RGBA ( "DarkBlue", 0.9 ), 5 ) );
          shape->enable_border();
          shape->set_border_stroke ( Stroke::create ( RGBA ( "DarkRed", 0.9 ), 5 ) );
        }
        return shape;
      }
      case GROUP:
        return example_group ( fill, stroke );
      case HANDLEBOX:
        return example_handlebox ( fill, stroke );
      case HEXTILLE:
      {
        Hextille::pointer shape = Hextille::create(10, 10, 15.0);
        if ( fill ) shape->set_fill( RGBA(0.73, 0.6, 0.87) );
        if ( stroke ) shape->set_stroke( RGBA(0.0, 0.0, 1.0) );
        shape->set_fill( RGBA(0.87, 0.6, 0.73), 5, 5 );
        return shape;
      }
      case HILBERT:
      {
        Hilbert::pointer shape = Hilbert::create ( 3, 100 );
        if ( fill )
          shape->set_fill ( RGBA ( "LimeGreen", 0.9 ) );
        if ( stroke )
          shape->set_stroke ( RGBA ( "IndianRed", 0.9 ) );
        return shape;
      }
      case IMAGE:
        return example_image ( fill, stroke );
      case KOCHCURVE:
      {
        KochCurve::pointer shape = KochCurve::create ( 3, 100 );
        if ( fill )
          shape->set_fill ( RGBA ( "PowderBlue", 0.9 ) );
        if ( stroke )
          shape->set_stroke ( RGBA ( "MediumBlue", 0.9 ) );
        return shape;
      }
      case KOCHSNOWFLAKE:
      {
        KochSnowflake::pointer shape = KochSnowflake::create ( 4, 100 );
        if ( fill )
          shape->set_fill ( RGBA ( "PowderBlue", 0.9 ) );
        if ( stroke )
          shape->set_stroke ( RGBA ( "MediumBlue", 0.9 ) );
        return shape;
      }
      case PATH:
      {
        Path::pointer shape = Path::create();
        shape->push_back ( PATH_MOVETO, 10, 10 );
        shape->push_back ( PATH_LINETO, 30, 10 );
        shape->push_back ( PATH_LINETO, 10, 30 );
        shape->push_back ( PATH_LINETO, 30, 30 );
        shape->push_back ( PATH_MOVETO, 10, -30 );
        shape->push_back ( PATH_REL_LINETO, 20, 0 );
        shape->push_back ( PATH_REL_LINETO, -20, 20 );
        shape->push_back ( PATH_REL_LINETO, 20, 0 );
        if ( fill )
          shape->set_fill ( Cairo::SolidPattern::create_rgb ( 1.0, 0.0, 0.0 ) );
        if ( stroke )
          shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
        return shape;
      }
      case POLYGON:
      {
        Polygon::pointer shape = Polygon::create();
        shape->add_vertex ( 0, 0 );
        shape->add_vertex ( 20, 0 );
        shape->add_vertex ( 0, 20 );
        shape->add_vertex ( 20, 20 );
        if ( fill )
          shape->set_fill ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
        if ( stroke )
          shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 1.0, 0.0, 0.0 ) );
        return shape;
      }
      case POLYLINE:
      {
        Polyline::pointer shape = Polyline::create();
        shape->add_vertex ( 0, 0 );
        shape->add_vertex ( 20, 0 );
        shape->add_vertex ( 0, 20 );
        shape->add_vertex ( 20, 20 );
        if ( fill ) shape->set_fill ( RGBA( 1.0, 0.0, 0.0 ) );
        if ( stroke ) shape->set_stroke ( RGBA( 0.0, 1.0, 1.0 ) );
        return shape;
      }
      case QUADRILLE:
      {
        Quadrille::pointer shape = Quadrille::create(10, 10, 20.0);
        if ( fill ) shape->set_fill( RGBA(1.0, 0.0, 0.0) );
        if ( stroke ) shape->set_stroke( RGBA(0.0, 0.0, 1.0) );
        shape->set_fill( RGBA(1.0, 1.0, 0.0), 5, 5 );
        return shape;
      }
      case RECTANGLE:
        return example_rectangle ( fill, stroke );
      case REGULARPOLYGON:
      {
        RegularPolygon::pointer shape = RegularPolygon::create ( 8, 40, RegularPolygon::ZERO_APOTHEM );
        if ( fill )
          shape->set_fill ( Cairo::SolidPattern::create_rgb ( 1.0, 1.0, 0.0 ) );
        if ( stroke )
          shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 1.0 ) );
        return shape;
      }
      case REFERENCE:
        return example_reference ( fill, stroke );
      case SIERPINSKI:
      {
        Sierpinski::pointer shape = Sierpinski::create ( 3, 100 );
        if ( fill )
          shape->set_fill ( RGBA ( "LimeGreen", 0.9 ) );
        if ( stroke )
          shape->set_stroke ( RGBA ( "IndianRed", 0.9 ) );
        return shape;
      }
      case SVG:
        return example_svg ( fill, stroke );
      case TEXT:
      {
        Text::pointer shape = Text::create ( "Hello World!", 40 );
        if ( fill )
          shape->set_fill ( Cairo::SolidPattern::create_rgb ( 1.0, 1.0, 1.0 ) );
        if ( stroke )
          shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 0.0 ) );
        return shape;
      }
    }
    return Drawable::pointer();
  }

  Arc::pointer example_arc ( bool fill, bool stroke )
  {
    // Create an arc with a radius of 50 that will start at 45' and stop at 315'
    Papyrus::Arc::pointer arc = Papyrus::Arc::create ( 50, M_PI_4, 3.0*M_PI_2+M_PI_4 );

    // Set the fill color with an alpha value of 0.9
    if ( fill )
      arc->set_fill ( Cairo::SolidPattern::create_rgba ( 1.0, 1.0, 0.0, 0.9 ) );

    // And set the stroke color
    if ( stroke )
      arc->set_stroke ( Cairo::SolidPattern::create_rgba ( 0.0, 0.0, 0.0, 0.9 ) );

    return arc;
  }

  Annulus::pointer example_annulus ( bool fill, bool stroke )
  {
    // Create an annulus with a radius of 50 and inner radius of 10
    Papyrus::Annulus::pointer annulus = Papyrus::Annulus::create ( 50, 40 );

    // Set the fill color with an alpha value of 0.9
    if ( fill )
      annulus->set_fill ( Cairo::SolidPattern::create_rgba ( 1.0, 0.0, 1.0, 0.9 ) );

    // And set the stroke color
    if ( stroke )
      annulus->set_stroke ( Cairo::SolidPattern::create_rgba ( 0.0, 1.0, 0.0, 0.9 ) );

    return annulus;
  }

  Bezierline::pointer example_bezierline ( bool fill, bool stroke )
  {
    Bezierline::pointer shape = Bezierline::create();
    double phi = 1.6180333989;
    double four_spline_magic_number = 0.55228475;
    double side = 100.0 / ( 1.0 + 1.0/phi );
    double yoffset = side / 2.0;
    double x0=0.0, y0=0.0, x1, y1, c0x=0.0, c0y=0.0, c1x=0.0, c1y=0.0, c2x=0.0, c2y=0.0;
    for ( int i=0; i < 10; i++ )
    {
      switch ( i%4 )
      {
        case 0:
          x1 = x0 + side;
          y1 = y0 - side;
          c1x = x0;
          c1y = y0 - side * four_spline_magic_number;
          c2x = x1 - side * four_spline_magic_number;
          c2y = y1;
          break;
        case 1:
          x1 = x0 + side;
          y1 = y0 + side;
          c1x = x0 + side * four_spline_magic_number;
          c1y = y0;
          c2x = x1;
          c2y = y1 - side * four_spline_magic_number;
          break;
        case 2:
          x1 = x0 - side;
          y1 = y0 + side;
          c1x = x0;
          c1y = y0 + side * four_spline_magic_number;
          c2x = x1 + side * four_spline_magic_number;
          c2y = y1;
          break;
        case 3:
          x1 = x0 - side;
          y1 = y0 - side;
          c1x = x0 - side * four_spline_magic_number;
          c1y = y0;
          c2x = x1;
          c2y = y1 + side * four_spline_magic_number;
          break;
      }
      shape->add_vertex ( x0, y0, c0x, c0y, c1x, c1y );
      x0 = x1;
      y0 = y1;
      c0x = c2x;
      c0y = c2y;
      side /= phi;
    }
    shape->add_vertex ( x0, y0, c0x, c0y, c1x, c1y );
//   shape->set_centroid( 50.0, -yoffset );
    shape->translate ( -50.0, yoffset );
    shape->scale ( 1.8, 1.8 );
    if ( fill )
      shape->set_fill ( Cairo::SolidPattern::create_rgba ( 0.8, 0.8, 1.0, 0.9 ) );
    if ( stroke )
    {
      shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 1.0, 0.0, 1.0 ) );
      shape->stroke()->set_width ( 2.0 );
    }
    return shape;
  }

  Beziergon::pointer example_beziergon ( bool fill, bool stroke )
  {
    Beziergon::pointer shape = Beziergon::create();
    double phi = 1.6180333989;
    double four_spline_magic_number = 0.55228475;
    double side = 100.0 / ( 1.0 + 1.0/phi );
    double yoffset = side / 2.0;
    double x0=0.0, y0=0.0, x1, y1, c0x=0.0, c0y=0.0, c1x=0.0, c1y=0.0, c2x=0.0, c2y=0.0;
    for ( int i=0; i < 10; i++ )
    {
      switch ( i%4 )
      {
        case 0:
          x1 = x0 + side;
          y1 = y0 - side;
          c1x = x0;
          c1y = y0 - side * four_spline_magic_number;
          c2x = x1 - side * four_spline_magic_number;
          c2y = y1;
          break;
        case 1:
          x1 = x0 + side;
          y1 = y0 + side;
          c1x = x0 + side * four_spline_magic_number;
          c1y = y0;
          c2x = x1;
          c2y = y1 - side * four_spline_magic_number;
          break;
        case 2:
          x1 = x0 - side;
          y1 = y0 + side;
          c1x = x0;
          c1y = y0 + side * four_spline_magic_number;
          c2x = x1 + side * four_spline_magic_number;
          c2y = y1;
          break;
        case 3:
          x1 = x0 - side;
          y1 = y0 - side;
          c1x = x0 - side * four_spline_magic_number;
          c1y = y0;
          c2x = x1;
          c2y = y1 + side * four_spline_magic_number;
          break;
      }
      shape->add_vertex ( x0, y0, c0x, c0y, c1x, c1y );
      x0 = x1;
      y0 = y1;
      c0x = c2x;
      c0y = c2y;
      side /= phi;
    }
    shape->add_vertex ( x0, y0, c0x, c0y, c1x, c1y );
    shape->translate ( -50.0*1.8, yoffset*1.8 );
    shape->scale ( 1.8, 1.8 );
    if ( fill )
      shape->set_fill ( Cairo::SolidPattern::create_rgba ( 1.0, 1.0, 0.0, 0.9 ) );
    if ( stroke )
    {
      shape->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 0.0 ) );
      shape->stroke()->set_width ( 2.0 );
    }
    return shape;
  }

  Circle::pointer example_circle ( bool fill, bool stroke )
  {
    // Create a circle with a radius of 50
    Papyrus::Circle::pointer circle = Papyrus::Circle::create ( 50 );

    // Set the fill color to green, with an alpha value of 0.9
    if ( fill ) circle->set_fill ( Cairo::SolidPattern::create_rgba ( 0.0, 1.0, 0.0, 0.9 ) );

    // And the stroke color to black
    if ( stroke ) circle->set_stroke ( Cairo::SolidPattern::create_rgba ( 0.0, 0.0, 0.0, 0.9 ) );

    return circle;
  }

  Rectangle::pointer example_rectangle ( bool fill, bool stroke )
  {
    // Create a rectangle
    Papyrus::Rectangle::pointer rectangle = Papyrus::Rectangle::create ( 80, 50 );

    // Set the fill color to red, with an alpha value of 0.9
    if ( fill ) rectangle->set_fill ( Cairo::SolidPattern::create_rgba ( 1.0, 0.0, 0.0, 0.9 ) );
    
    rectangle->translate( 40, 25 );

    // And the stroke color to black
    if ( stroke ) {
      rectangle->set_stroke ( Cairo::SolidPattern::create_rgba ( 0.0, 0.0, 0.0, 0.9 ) );
      rectangle->stroke()->set_width(1);
    }

    return rectangle;
  }

  Group::pointer example_group ( bool fill, bool stroke )
  {
    // Create a group to contain several shapes
    Papyrus::Group::pointer group = Papyrus::Group::create( );

    // Create some shapes to add to the group
    Papyrus::Rectangle::pointer rectangle = example_rectangle ( fill, stroke );
    Papyrus::Circle::pointer circle = example_circle ( fill, stroke );
    Papyrus::Arc::pointer arc = example_arc ( fill, stroke );

    // Add the shapes to the group
    group->add ( rectangle );
    group->add ( circle );
    group->add ( arc );

    // Translate the shapes so they don't necessarily overlap
    rectangle->set_xywh ( 0, -60, 50, 30 );
    circle->translate ( 40, 20 );
    circle->set_radius ( 25 );
    arc->translate ( 0, 20 );

    // Rotate the entire group by 45 degrees counter-clockwise
//     group->rotate ( -M_PI_4 );

    return group;
  }

  Group::pointer example_reference ( bool fill, bool stroke )
  {
    // Create a group to contain the references
    Papyrus::Group::pointer group = Papyrus::Group::create( );

    // Create a shape to refer to
    Papyrus::Circle::pointer circle = example_circle ( fill, stroke );

    Papyrus::Reference::pointer reference[4];
    int i;

    // Create the references and add to the group
    for ( i=0; i < 4; i++ )
    {
      reference[i] = Papyrus::Reference::create ( circle );
      group->add ( reference[i] );
    }

    // Translate the references so they don't necessarily overlap
    reference[0]->translate ( -35, -35 );
    reference[1]->translate ( 35, -35 );
    reference[2]->translate ( -35,  35 );
    reference[3]->translate ( 35,  35 );

    circle->set_radius ( 25 );

    return group;
  }

  Handlebox::pointer example_handlebox ( bool fill, bool stroke )
  {
    // Create a handlebox to contain several shapes
    Papyrus::Handlebox::pointer handlebox = Papyrus::Handlebox::create( );
    if ( fill ) handlebox->box()->set_fill ( Cairo::SolidPattern::create_rgba ( 1.0, 0.85, 1.0, 0.9 ) );
    if ( stroke ) handlebox->box()->set_stroke ( Cairo::SolidPattern::create_rgba ( 1.0, 0.0, 1.0, 0.9 ) );

    // TODO fix out of date comments on this section
    Papyrus::Group::pointer group = Papyrus::Group::create();
    
    // Create some shapes to add to the handlebox
    Papyrus::Rectangle::pointer rectangle = Papyrus::Rectangle::create ( 0.0, -60.0, 50.0, 30.0, Papyrus::RGBA ( "red", 0.9 ) );
    Papyrus::Circle::pointer circle = Papyrus::Circle::create ( 25, Papyrus::RGBA ( "green", 0.9 ) );
    circle->set_xy( 40, 20 );
    Papyrus::Arc::pointer arc = Papyrus::Arc::create ( 50, M_PI_4, 3.0*M_PI_2+M_PI_4, Papyrus::RGBA ( "yellow", 0.9 ) );
    arc->set_xy( 0, 20 );

    // Add the shapes to the handlebox
    group->add ( rectangle );
    group->add ( circle );
    group->add ( arc );
    handlebox->add( group );

    return handlebox;
  }

  Boxed::pointer example_boxed ( bool fill, bool stroke )
  {
    // Create a boxed group to contain several shapes
    Papyrus::Boxed::pointer boxed = Papyrus::Boxed::create( );
    if ( fill ) boxed->box()->set_fill ( Cairo::SolidPattern::create_rgba ( 1.0, 0.85, 1.0, 0.9 ) );
    if ( stroke ) boxed->box()->set_stroke ( Cairo::SolidPattern::create_rgba ( 1.0, 0.0, 1.0, 0.9 ) );

    // Create some shapes to add to the boxed group
    Papyrus::Group::pointer group = Papyrus::Group::create();
    
    Papyrus::Rectangle::pointer rectangle = Papyrus::Rectangle::create ( 0.0, -60.0, 50.0, 30.0, Papyrus::RGBA ( "red", 0.9 ) );
    Papyrus::Circle::pointer circle = Papyrus::Circle::create ( 25, Papyrus::RGBA ( "green", 0.9 ) );
    circle->set_xy( 40, 20 );
    Papyrus::Arc::pointer arc = Papyrus::Arc::create ( 50, M_PI_4, 3.0*M_PI_2+M_PI_4, Papyrus::RGBA ( "yellow", 0.9 ) );
    arc->set_xy( 0, 20 );

    // Add the shapes to the boxed group
    group->add( rectangle );
    group->add( circle );
    group->add( arc );
    boxed->add( group );

    return boxed;
  }

  Image::pointer example_image ( bool, bool )
  {
    static bool convert = true;
    Image::pointer image;

    image = Image::create ( papyrus_example_image.pixel_data,
                            Cairo::FORMAT_RGB24,
                            papyrus_example_image.width,
                            papyrus_example_image.height,
                            papyrus_example_image.width * papyrus_example_image.bytes_per_pixel,
                            convert
                          );
    convert = false;

    return image;
  }

  SVG::pointer example_svg ( bool, bool )
  {
    SVG::pointer svg;
    svg = SVG::create ( "cairo_logo_no_text.svg" );
    svg->scale ( 0.5, 0.5 );
    return svg;
  }

  Group::pointer example_line_join ( Cairo::LineJoin line_join )
  {
    Polyline::pointer line = Polyline::create();
    line->add_vertex ( -20, 15 );
    line->add_vertex ( 0, -10 );
    line->add_vertex ( 20, 15 );
    line->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 0.0 ) );
    line->stroke()->set_join ( line_join );
    line->stroke()->set_width ( 25 );

    Circle::pointer circle = Circle::create ( 3 );
    circle->set_fill ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
    circle->translate ( 0, -10 );

    Polyline::pointer inside_line = Polyline::create();
    inside_line->add_vertex ( -20, 15 );
    inside_line->add_vertex ( 0, -10 );
    inside_line->add_vertex ( 20, 15 );
    inside_line->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
    inside_line->stroke()->set_cap ( Cairo::LINE_CAP_BUTT );
    inside_line->stroke()->set_width ( 1 );

    Group::pointer group = Group::create();
    group->add ( line );
    group->add ( circle );
    group->add ( inside_line );
    return group;
  }

  Group::pointer example_line_cap ( Cairo::LineCap line_cap )
  {
    Polyline::pointer inside_line = Polyline::create();
    inside_line->add_vertex ( -15, 0 );
    inside_line->add_vertex ( 15, 0 );
    inside_line->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
    inside_line->stroke()->set_cap ( Cairo::LINE_CAP_BUTT );
    inside_line->stroke()->set_width ( 1 );

    Circle::pointer left_circle = Circle::create ( 3 );
    left_circle->set_fill ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
    left_circle->translate ( -15, 0 );

    Circle::pointer right_circle = Circle::create ( 3 );
    right_circle->set_fill ( Cairo::SolidPattern::create_rgb ( 0.0, 1.0, 1.0 ) );
    right_circle->translate ( 15, 0 );

    Polyline::pointer line = Polyline::create();
    line->add_vertex ( -15, 0 );
    line->add_vertex ( 15, 0 );
    line->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 0.0 ) );
    line->stroke()->set_cap ( line_cap );
    line->stroke()->set_width ( 20 );

    Group::pointer group = Group::create();
    group->add ( line );
    group->add ( left_circle );
    group->add ( right_circle );
    group->add ( inside_line );
    return group;
  }

  Polyline::pointer  example_marker ( Papyrus::Marker::Style style, Papyrus::Marker::Facing facing, bool fill, bool stroke )
  {
    Polyline::pointer line = Polyline::create();
    line->add_vertex ( -17, 0 );
    line->add_vertex ( 17, 0 );
    line->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 0.0 ) );
    line->stroke()->set_width ( 2 );

    Marker::pointer marker = Marker::create ( style, 15, 15, facing );
    if ( fill )
      marker->set_fill ( Cairo::SolidPattern::create_rgb ( 1.0, 1.0, 1.0 ) );
    if ( stroke )
      marker->set_stroke ( Cairo::SolidPattern::create_rgb ( 0.0, 0.0, 0.0 ) );
    marker->stroke()->set_width ( 2 );
    if ( facing == Papyrus::Marker::LEFT )
      line->set_marker ( START_MARKER, marker );
    else
      line->set_marker ( END_MARKER, marker );

    return line;
  }


}

