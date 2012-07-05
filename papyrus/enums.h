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
#ifndef PAPYRUSENUMS_H
#define PAPYRUSENUMS_H

#include <cairomm/enums.h>

namespace Papyrus
{

  /**
   * The selection mode determines what events trigger an attempt
   * to select an object in the canvas.
   *
   * The values have been selected to allow multiple events to trigger
   * a selection.
   */
  typedef enum SelectionMode {
    SELECT_PRESS = 1 << 0,   /**< Selection occurs when a button is pressed */
    SELECT_RELEASE = 1 << 1,   /**< Selection occurs when a button is released */
    SELECT_FOLLOW = 1 << 2,   /**< Selection follows the mouse */
  } SelectionMode;

  typedef enum AffineTransform {
    TRANSLATE_X = 1 << 0,
    TRANSLATE_Y = 1 << 1,
    SCALE_X = 1 << 2,
    SCALE_Y = 1 << 3,
    ROTATE = 1 << 4,
    SKEW_X = 1 << 5,
    SKEW_Y = 1 << 6,
  } AffineTransform;

  enum {
    FILL = 1<<0,
    STROKE = 1<<1
  };

  typedef enum Side {
    TOP = 1<<0,
    RIGHT = 1<<1,
    BOTTOM = 1<<2,
    LEFT = 1<<3,
  } Side;

  typedef enum Position {
    START_POSITION,
    TOP_CENTER=START_POSITION,
    TOP_RIGHT,
    CENTER_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_CENTER,
    BOTTOM_LEFT,
    CENTER_LEFT,
    TOP_LEFT,
    END_POSITION,
  } Position;

  typedef enum Axis {
    X_AXIS = 1<<0,
    Y_AXIS = 1<<1,
  } Axis;

  typedef enum Handles {
    NO_HANDLES = 0,
    CORNER_HANDLES = 1<<0,
    ALL_HANDLES = 1<<1,
  } Handles;

  typedef enum ScrollAnchor {
    SCROLL_ANCHOR_CENTER,
    SCROLL_ANCHOR_TOP_LEFT,
    SCROLL_ANCHOR_TOP_RIGHT,
    SCROLL_ANCHOR_BOTTOM_LEFT,
    SCROLL_ANCHOR_BOTTOM_RIGHT
  } ScrollAnchor;

  typedef enum PathElementType {
    PATH_UNDEFINED,
    PATH_MOVETO,
    PATH_REL_MOVETO,
    PATH_CLOSE,
    PATH_LINETO,
    PATH_REL_LINETO,
    PATH_HORIZONTAL_LINETO,
    PATH_REL_HORIZONTAL_LINETO,
    PATH_VERTICAL_LINETO,
    PATH_REL_VERTICAL_LINETO,
    PATH_CURVETO,
    PATH_REL_CURVETO,
    PATH_SMOOTH_CURVETO,
    PATH_REL_SMOOTH_CURVETO,
    PATH_QUADRATIC_BEZIER_CURVETO,
    PATH_REL_QUADRATIC_BEZIER_CURVETO,
    PATH_SMOOTH_QUADRATIC_BEZIER_CURVETO,
    PATH_REL_SMOOTH_QUADRATIC_BEZIER_CURVETO,
    PATH_ELIPTICAL_ARC,
    PATH_REL_ELIPTICAL_ARC,
  } PathElementType;

  typedef enum Units {
    UNIT_PIXEL,
    UNIT_POINTS,
    UNIT_INCH,
    UNIT_MM,
  } Units;

  typedef enum DegRad {
    DEGREES,
    RADIANS,
  } DegRad;

  typedef enum MarkerPosition {
    START_MARKER,
    VERTEX_MARKER,
    END_MARKER
  } MarkerPosition;

  typedef enum ExtentsPerformance {
    EXTENTS_QUICK=1,
    EXTENTS_PRECISE,
  } ExtentsPerformance;

  typedef enum OverUnder {
    OVER=1,
    UNDER,
  } OverUnder;
  
  /**
   * FROZEN was selected to be 1 so that tests can look like:
   * FrozenThawed frozen;
   * if ( frozen ) ...
   */
  typedef enum FrozenThawed {
    THAWED=0,
    FROZEN=1
  } FrozenThawed;
  
  typedef enum GradientUnits {
    GRADIENT_UNITS_NONE,
    GRADIENT_UNITS_USER_SPACE,
    GRADIENT_UNITS_OBJECT,
  } GradientUnits;
  
  typedef enum GradientSpread {
    GRADIENT_SPREAD_NONE = Cairo::EXTEND_NONE,
    GRADIENT_SPREAD_PAD = Cairo::EXTEND_PAD,
    GRADIENT_SPREAD_REFLECT = Cairo::EXTEND_REFLECT,
    GRADIENT_SPREAD_REPEAT = Cairo::EXTEND_REPEAT,
  } GradientSpread;
  
  typedef enum RenderFlags {
    RENDER_FLAGS_NONE                  =0,
    RENDER_SUPPRESS_MATRIX             =1<<0, /**< if set the internal matrices will not be applied */
    RENDER_SUPPRESS_CAIRO_FILL         =1<<1, /**< if set render() / draw() should not call cairo_fill() */
    RENDER_SUPPRESS_CAIRO_STROKE       =1<<2, /**< if set render() / draw() should not call cairo_stroke() */
    RENDER_SUPPRESS_CAIRO_SAVE_RESTORE =1<<3, /**< if set render() / draw() should not call cairo_save() or cairo_restore() */
    RENDER_HINT_FILL                   =1<<4, /**< provides a hint that the rendered item will be filled */
    RENDER_HINT_STROKE                 =1<<5, /**< provides a hint that the rendered item will be stroked */
    RENDER_FORCE                       =1<<6, /**< force rendering even if the item is invisible */
  } RenderFlags;

  typedef enum Quantity {
    ABSOLUTE,
    PERCENT,
  } Quantity;

}

#endif
