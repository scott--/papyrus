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
#ifndef HEXGRID_H
#define HEXGRID_H

#include <item.h>
#include <matrix2d.h>

namespace Papyrus {

/**
 * This class is still not ported from the old glcanvasmm library.
 * @author Rick L Vinyard Jr
 */
class Hexgrid : public Group
{
public:
    typedef enum STYLE {SIDE, VERTEX} Style;

    Hexgrid(Vertex upperleft, int width, int height, double hexrad);
    Hexgrid(Vertex upperleft, Glib::ustring filename, double hexrad);

    ~Hexgrid();

    virtual void pl_insert();

    bool has_outline() { return _use_outline; }
    bool use_outline(bool uo) { _use_outline = uo; }
    RGBA get_outline() { return _outline; }
    void set_outline(RGBA& outline) { _use_outline = true; _outline = outline; }

    double get_edge() { return _halfedge*2.0; }
    double get_apothem() { return _apothem; }

    double get_radius() { return _radius; }
    void set_radius(double radius);

    Vertex& get_upperleft() { return _upperleft; }
    void set_upperleft(Vertex& upperleft) { _upperleft = upperleft; }

    Style get_style() { return _style; }
    void set_style(Style s) { _style = s; }

    void set_color(int x, int y, RGBA& color);

protected:
  RGBA* _colors;
  bool _use_outline;
  RGBA _outline;
  Vertex _upperleft;
  int _width, _height;
  double _radius, _apothem, _halfedge;
  Style _style;

}; // class Hexgrid

}; // namespace Papyrus


#endif