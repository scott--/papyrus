/*
 *
 * flex C++ implementation: path_data_lexer
 *
 * Description:
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
 * 	%option prefix="foo"
 * 	%option outfile="lex.yy.c"
 *
 * to create multiple flex scanner in one project.
 *
 *
 * To create scanner class:
 *
 *	%option c++
 *
 * (see '%option yyclass' also!)
 *
 */

/* prefix option for separating the message lexer from other lexers */
%option prefix="path_data_"

/* needed to make output file compatible with automake rules */
%option outfile="lex.yy.c"

/* prefix option messes up yywrap call */
%option noyywrap

%{

#include "path_data_parser.h"
#include <cstring>
#include <papyrus/path.h>

extern "C"
{
  int path_data_lex (void);
}

/* Parse in-memory data */
static YY_BUFFER_STATE buffer_state;
void init_path_data_lexer(const char* src) { buffer_state = yy_scan_string(src); }
void finalize_path_data_lexer() { yy_delete_buffer(buffer_state); }

%}

/*%option debug*/

%%

[M]             return MOVETO;
[m]             return REL_MOVETO;
[zZ]            return CLOSEPATH;
[L]             return LINETO;
[l]             return REL_LINETO;
[H]             return HORIZONTAL_LINETO;
[h]             return REL_HORIZONTAL_LINETO;
[V]             return VERTICAL_LINETO;
[v]             return REL_VERTICAL_LINETO;
[C]             return CURVETO;
[c]             return REL_CURVETO;
[S]             return SMOOTH_CURVETO;
[s]             return REL_SMOOTH_CURVETO;
[qQ]            return QUADRATIC_BEZIER_CURVETO;
[tT]            return SMOOTH_QUADRATIC_BEZIER_CURVETO;
[aA]            return ELLIPTICAL_ARC;
[eE]            return EXPONENT;
[-+]            path_data_lval.charval=yytext[0]; return SIGN;
[0-9]*[.][0-9]* sscanf(yytext,"%lf",&(path_data_lval.doubleval)); return FRACTIONAL_CONSTANT;
[0-9]+          path_data_lval.unsignedval=atoi(yytext); return DIGIT_SEQUENCE;
[ \t\r\n]*      /** trim whitespace **/;

%%
