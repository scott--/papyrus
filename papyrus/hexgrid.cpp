/***************************************************************************
 *   Copyright (C) 2004 by Rick L Vinyard Jr                               *
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
#include "hexgrid.h"

#include <pixbufplus.h>

#define COSINE 0.8660254037844386
#define SINE 0.5

using namespace GL::Canvas;

Hexgrid::Hexgrid(Vertex upperleft, int width, int height, double hexrad)
 : Item(), _upperleft(upperleft), _width(width), _height(height), _radius(hexrad), _style(SIDE)
{
  _apothem = COSINE * _radius;
  _halfedge = SINE * _radius;
  _colors = new RGBA[_width*_height];
}

Hexgrid::Hexgrid(Vertex upperleft, std::string filename, double hexrad)
 : Item(), _upperleft(upperleft), _radius(hexrad), _style(SIDE)
{
  _apothem = COSINE * _radius;
  _halfedge = SINE * _radius;

  PixbufPlus pbp(filename);
  RGBA color;

  _width = pbp.pixbuf()->get_width();
  _height = pbp.pixbuf()->get_height();
  _colors = new RGBA[_width*_height];
  for (int x=0; x<_width; x++)
    for (int y=0; y<_width; y++) {
      color = pbp.get_pixel(x, y);
      set_color(x, y, color);
    }
}



Hexgrid::~Hexgrid()
{
  delete[] _colors;
}

void Hexgrid::set_color(int x, int y, RGBA& color) {
  _colors[x*_height+y] = color;
}



void printpoint(double v[]) {
  std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
}

void Hexgrid::pl_insert() {
  int x, y;
  double xcenter, ycenter;
  double vertex[3];
  RGBA* clr = _colors;

  vertex[2] = _upperleft[2];

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);

  // this really needs to be cleaned up to use OpenGL vertex and color arrays
  switch(_style) {
    case SIDE:
      for (x=0; x < _width; x++) {
        for (y=0; y < _height; y++) {
            xcenter = _upperleft[0] + (_radius + _halfedge) * x;
            ycenter = _upperleft[1] - _apothem * y * 2 - _apothem * (x % 2);
            glBegin(GL_POLYGON);
            clr++->pl_insert();
            vertex[0] = xcenter - _radius;       vertex[1] = ycenter;                      glVertex3dv(vertex);
            vertex[0] = xcenter - _halfedge;   vertex[1] = ycenter - _apothem;     glVertex3dv(vertex);
            vertex[0] = xcenter + _halfedge;                                                    glVertex3dv(vertex);
            vertex[0] = xcenter + _radius;       vertex[1] = ycenter;                     glVertex3dv(vertex);
            vertex[0] = xcenter + _halfedge;   vertex[1] = ycenter + _apothem;   glVertex3dv(vertex);
            vertex[0] = xcenter - _halfedge;                                                     glVertex3dv(vertex);
            vertex[0] = xcenter - _radius;       vertex[1] = ycenter;                      glVertex3dv(vertex);
            glEnd();
        }
      }
      break;
    case VERTEX:
      break;
  }

  glDisable(GL_POLYGON_OFFSET_FILL);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  switch(_style) {
    case SIDE:
      for (x=0; x < _width; x++) {
        for (y=0; y < _height; y++) {
            xcenter = _upperleft[0] + (_radius + _halfedge) * x;
            ycenter = _upperleft[1] - _apothem * y * 2 - _apothem * (x % 2);
            glBegin(GL_POLYGON);
            _outline.pl_insert();
            vertex[0] = xcenter - _radius;       vertex[1] = ycenter;                      glVertex3dv(vertex);
            vertex[0] = xcenter - _halfedge;   vertex[1] = ycenter - _apothem;     glVertex3dv(vertex);
            vertex[0] = xcenter + _halfedge;                                                    glVertex3dv(vertex);
            vertex[0] = xcenter + _radius;       vertex[1] = ycenter;                     glVertex3dv(vertex);
            vertex[0] = xcenter + _halfedge;   vertex[1] = ycenter + _apothem;   glVertex3dv(vertex);
            vertex[0] = xcenter - _halfedge;                                                     glVertex3dv(vertex);
            vertex[0] = xcenter - _radius;       vertex[1] = ycenter;                      glVertex3dv(vertex);
            glEnd();
        }
      }
      break;
    case VERTEX:
      break;
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Hexgrid::set_radius(double radius) {
  _radius = radius;
  _apothem = COSINE * _radius;
  _halfedge = SINE * _radius;
}
