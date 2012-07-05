/*
 *
 * bison/yacc C++ Implementation: path_data_grammar
 *
 * Description:
 * This is an implementation of the SVG 1.1 path data grammar
 * as specified by W3C int the SVG 1.1 standard.
 *
 *
 * Author: Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>, (C) 2007
 *
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
 *
 */

/*
 *
 * Use options
 *
 *    %name-prefix="foo"
 *    %yacc
 *
 * to create multiple parsers in one project.
 *
 */

%name-prefix="path_data_"
%yacc
%defines
/* %verbose */

%{

// #define YYDEBUG 1
// #define YYERROR_VERBOSE 1

#include <cstdio>
#include <list>
#include <papyrus/path_element.h>

extern "C"
{
  int path_data_parse(void);
  int path_data_lex(void);
  int path_data_wrap() { return 1; }
  
  void path_data_error(char const* s) {
    // printf("YACC Error: %s\n", s);
  }

}

std::list<Papyrus::PathElement::pointer> path_data_list;

%}

%union {
        unsigned unsignedval;
        double doubleval;
        char charval;
        struct {
          double x;
          double y;
        } pair;
        struct {
          double x1, y1, x2, y2, x, y;
        } curveto_arg; 
}

%token MOVETO REL_MOVETO CLOSEPATH
%token LINETO REL_LINETO VERTICAL_LINETO REL_VERTICAL_LINETO HORIZONTAL_LINETO REL_HORIZONTAL_LINETO
%token CURVETO REL_CURVETO SMOOTH_CURVETO REL_SMOOTH_CURVETO QUADRATIC_BEZIER_CURVETO SMOOTH_QUADRATIC_BEZIER_CURVETO
%token ELLIPTICAL_ARC
%token EXPONENT

%token <charval> SIGN
%token <unsignedval> DIGIT_SEQUENCE
%token <doubleval> FRACTIONAL_CONSTANT

%type <unsignedval> exponent
%type <doubleval> floating_point_constant
%type <unsignedval> integer_constant
%type <doubleval> number
%type <doubleval> nonnegative_number
%type <doubleval> coordinate
%type <pair> coordinate_pair
%type <curveto_arg> curveto_argument;
%type <curveto_arg> smooth_curveto_argument;

%debug

%%

svg_path:
    /** empty set **/
  | moveto_drawto_command_groups
  ;

moveto_drawto_command_groups:
    moveto_drawto_command_groups moveto drawto_commands
  | moveto drawto_commands
  ;

drawto_commands:
    drawto_commands drawto_command
  | drawto_command
  ;

drawto_command:
    closepath
  | lineto
  | horizontal_lineto
  | vertical_lineto
  | curveto
  | smooth_curveto
  | quadratic_bezier_curveto
  | smooth_quadratic_bezier_curveto
  | elliptical_arc
  ;

moveto:
    MOVETO moveto_argument_sequence
  | REL_MOVETO rel_moveto_argument_sequence
  ;

moveto_argument_sequence:
    coordinate_pair ',' lineto_argument_sequence { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_MOVETO, $1.x, $1.y) ); }
  | coordinate_pair lineto_argument_sequence { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_MOVETO, $1.x, $1.y) ); }
  | coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_MOVETO, $1.x, $1.y) ); }
  ;

rel_moveto_argument_sequence:
    coordinate_pair ',' rel_lineto_argument_sequence { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_MOVETO, $1.x, $1.y) ); }
  | coordinate_pair rel_lineto_argument_sequence { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_MOVETO, $1.x, $1.y) ); }
  | coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_MOVETO, $1.x, $1.y) ); }
  ;

closepath:
    CLOSEPATH { path_data_list.push_back( Papyrus::PathElement::create( Papyrus::PATH_CLOSE ) ); }
  ;

lineto:
    LINETO lineto_argument_sequence
  | REL_LINETO rel_lineto_argument_sequence
  ;

lineto_argument_sequence:
    lineto_argument_sequence ',' coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_LINETO, $3.x, $3.y) ); }
  | lineto_argument_sequence coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_LINETO, $2.x, $2.y) ); }
  | coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_LINETO, $1.x, $1.y) ); }
  ;

rel_lineto_argument_sequence:
    rel_lineto_argument_sequence ',' coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_LINETO, $3.x, $3.y) ); }
  | rel_lineto_argument_sequence coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_LINETO, $2.x, $2.y) ); }
  | coordinate_pair { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_LINETO, $1.x, $1.y) ); }
  ;

horizontal_lineto:
    HORIZONTAL_LINETO horizontal_lineto_argument_sequence
  | REL_HORIZONTAL_LINETO rel_horizontal_lineto_argument_sequence
  ;

horizontal_lineto_argument_sequence:
    horizontal_lineto_argument_sequence ',' coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_HORIZONTAL_LINETO, $3) ); }
  | horizontal_lineto_argument_sequence coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_HORIZONTAL_LINETO, $2) ); }
  | coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_HORIZONTAL_LINETO, $1) ); }
  ;

rel_horizontal_lineto_argument_sequence:
    rel_horizontal_lineto_argument_sequence ',' coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_HORIZONTAL_LINETO, $3) ); }
  | rel_horizontal_lineto_argument_sequence coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_HORIZONTAL_LINETO, $2) ); }
  | coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_HORIZONTAL_LINETO, $1) ); }
  ;

vertical_lineto:
    VERTICAL_LINETO vertical_lineto_argument_sequence
  | REL_VERTICAL_LINETO rel_vertical_lineto_argument_sequence
  ;

vertical_lineto_argument_sequence:
    vertical_lineto_argument_sequence ',' coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_VERTICAL_LINETO, 0.0, $3) ); }
  | vertical_lineto_argument_sequence coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_VERTICAL_LINETO, 0.0, $2) ); }
  | coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_VERTICAL_LINETO, 0.0, $1) ); }
  ;

rel_vertical_lineto_argument_sequence:
    rel_vertical_lineto_argument_sequence ',' coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_VERTICAL_LINETO, 0.0, $3) ); }
  | rel_vertical_lineto_argument_sequence coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_VERTICAL_LINETO, 0.0, $2) ); }
  | coordinate { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_VERTICAL_LINETO, 0.0, $1) ); }
  ;

curveto:
    CURVETO curveto_argument_sequence
  | REL_CURVETO rel_curveto_argument_sequence
  ;

curveto_argument_sequence:
    curveto_argument_sequence ',' curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_CURVETO, $3.x, $3.y, $3.x1, $3.y1, $3.x2, $3.y2) ); }
  | curveto_argument_sequence curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_CURVETO, $2.x, $2.y, $2.x1, $2.y1, $2.x2, $2.y2) ); }
  | curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_CURVETO, $1.x, $1.y, $1.x1, $1.y1, $1.x2, $1.y2) ); }
  ;

rel_curveto_argument_sequence:
    rel_curveto_argument_sequence ',' curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_CURVETO, $3.x, $3.y, $3.x1, $3.y1, $3.x2, $3.y2) ); }
  | rel_curveto_argument_sequence curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_CURVETO, $2.x, $2.y, $2.x1, $2.y1, $2.x2, $2.y2) ); }
  | curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_CURVETO, $1.x, $1.y, $1.x1, $1.y1, $1.x2, $1.y2) ); }
  ;

curveto_argument:
    coordinate_pair ',' coordinate_pair ',' coordinate_pair { $$.x1 = $1.x; $$.y1 = $1.y; $$.x2 = $3.x; $$.y2 = $3.y; $$.x = $5.x; $$.y = $5.y; }
  | coordinate_pair ',' coordinate_pair coordinate_pair { $$.x1 = $1.x; $$.y1 = $1.y; $$.x2 = $3.x; $$.y2 = $3.y; $$.x = $4.x; $$.y = $4.y; }
  | coordinate_pair coordinate_pair ',' coordinate_pair { $$.x1 = $1.x; $$.y1 = $1.y; $$.x2 = $2.x; $$.y2 = $2.y; $$.x = $4.x; $$.y = $4.y; }
  | coordinate_pair coordinate_pair coordinate_pair { $$.x1 = $1.x; $$.y1 = $1.y; $$.x2 = $2.x; $$.y2 = $2.y; $$.x = $3.x; $$.y = $3.y; }
  ;

smooth_curveto:
    SMOOTH_CURVETO smooth_curveto_argument_sequence
  | REL_SMOOTH_CURVETO rel_smooth_curveto_argument_sequence
  ;

smooth_curveto_argument_sequence:
    smooth_curveto_argument_sequence ',' smooth_curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_SMOOTH_CURVETO, $3.x, $3.y, 0.0, 0.0, $3.x2, $3.y2) ); }
  | smooth_curveto_argument_sequence smooth_curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_SMOOTH_CURVETO, $2.x, $2.y, 0.0, 0.0, $2.x2, $2.y2) ); }
  | smooth_curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_SMOOTH_CURVETO, $1.x, $1.y, 0.0, 0.0, $1.x2, $1.y2) ); }
  ;

rel_smooth_curveto_argument_sequence:
    rel_smooth_curveto_argument_sequence ',' smooth_curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_SMOOTH_CURVETO, $3.x, $3.y, 0.0, 0.0, $3.x2, $3.y2) ); }
  | rel_smooth_curveto_argument_sequence smooth_curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_SMOOTH_CURVETO, $2.x, $2.y, 0.0, 0.0, $2.x2, $2.y2) ); }
  | smooth_curveto_argument { path_data_list.push_back( Papyrus::PathElement::create(Papyrus::PATH_REL_SMOOTH_CURVETO, $1.x, $1.y, 0.0, 0.0, $1.x2, $1.y2) ); }
  ;

smooth_curveto_argument:
    coordinate_pair ',' coordinate_pair { $$.x2 = $1.x; $$.y2 = $1.y; $$.x = $3.x; $$.y = $3.y; }
  | coordinate_pair coordinate_pair { $$.x2 = $1.x; $$.y2 = $1.y; $$.x = $2.x; $$.y = $2.y; }
  ;

quadratic_bezier_curveto:
    QUADRATIC_BEZIER_CURVETO quadratic_bezier_curveto_argument_sequence  { perror("Quadratic bezier curveto parser not implemented"); }
  ;

quadratic_bezier_curveto_argument_sequence:
    quadratic_bezier_curveto_argument_sequence ',' quadratic_bezier_curveto_argument
  | quadratic_bezier_curveto_argument_sequence quadratic_bezier_curveto_argument
  | quadratic_bezier_curveto_argument
  ;

quadratic_bezier_curveto_argument:
    coordinate_pair ',' coordinate_pair
  | coordinate_pair coordinate_pair
  ;

smooth_quadratic_bezier_curveto:
    SMOOTH_QUADRATIC_BEZIER_CURVETO smooth_quadratic_bezier_curveto_argument_sequence { perror("Smooth quadratic bezier curveto parser not implemented"); }
  ;

smooth_quadratic_bezier_curveto_argument_sequence:
    smooth_quadratic_bezier_curveto_argument_sequence ',' coordinate_pair
  | smooth_quadratic_bezier_curveto_argument_sequence coordinate_pair
  | coordinate_pair
  ;

elliptical_arc:
    ELLIPTICAL_ARC elliptical_arc_argument_sequence { perror("Elliptical arc parser not implemented"); }
  ;

elliptical_arc_argument_sequence:
    elliptical_arc_argument_sequence ',' elliptical_arc_argument
  | elliptical_arc_argument_sequence elliptical_arc_argument
  | elliptical_arc_argument
  ;

elliptical_arc_argument:
    nonnegative_number ',' nonnegative_number ',' number ',' flag ',' flag ',' coordinate_pair
  | nonnegative_number ',' nonnegative_number number ',' flag ',' flag ',' coordinate_pair
  | nonnegative_number nonnegative_number ',' number ',' flag ',' flag ',' coordinate_pair
  | nonnegative_number nonnegative_number number ',' flag ',' flag ',' coordinate_pair
  ;

coordinate_pair:
    coordinate ',' coordinate { $$.x = $1; $$.y = $3; }
  | coordinate coordinate     { $$.x = $1; $$.y = $2; }
  ;

coordinate:
    number                        { $$ = $1; }
  ;

nonnegative_number:
    integer_constant              { $$ = $1; }
  | floating_point_constant       { $$ = $1; }
  ;

number:
    SIGN integer_constant         { $$ = (( $1 =='+')?1:-1) * (long)$2; }
  | integer_constant              { $$ = $1; }
  | SIGN floating_point_constant  { $$ = (( $1 =='+')?1:-1) * $2; }
  | floating_point_constant       { $$ = $1; }
  ;

flag:
    '0'
  | '1'
  ;

integer_constant:
    DIGIT_SEQUENCE  { $$ = $1; }
  ;

floating_point_constant:
    FRACTIONAL_CONSTANT exponent { $$ = $1 * pow(10,$2); }
  | FRACTIONAL_CONSTANT          { $$ = $1; }
  | DIGIT_SEQUENCE exponent      { $$ = $1 * pow(10,$2); }
  ;

exponent:
    EXPONENT SIGN DIGIT_SEQUENCE { $$ = (($2=='+')?1:-1) * $3; }
  | EXPONENT DIGIT_SEQUENCE      { $$ = $2; }
  ;

%%

extern void init_path_data_lexer(const char* src);
extern void finalize_path_data_lexer();

namespace Papyrus
{

  std::list<PathElement::pointer> path_data_parser(const char* src)
  {
    //std::cout << "Parsing " << src << std::endl;
    //yydebug = 1;
    init_path_data_lexer(src);
    path_data_list.clear();
    path_data_parse();
    finalize_path_data_lexer();
    //std::list<PathElement::pointer>::iterator i;
    //std::cout << "Parsed " << path_data_list.size() << " elements" << std::endl;
    //for ( i = path_data_list.begin(); i != path_data_list.end(); i++ )
    //  std::cout << "\tElement: " << (*i)->svg();
    return path_data_list;
  }

}
