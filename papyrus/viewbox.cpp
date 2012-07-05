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
#include "viewbox.h"

namespace Papyrus {

Viewbox::Viewbox( double x, double y, double w, double h, ALIGN align, MEET_OR_SLICE meet_or_slice ):
    Region( x, y, w, h ),
    m_align(align),
    m_meet_or_slice(meet_or_slice) {}

Viewbox::Viewbox( const Region& region, ALIGN align, MEET_OR_SLICE meet_or_slice ):
    Region( region ),
    m_align(align),
    m_meet_or_slice(meet_or_slice) {}

Viewbox::pointer Viewbox::create(double x, double y, double w, double h, ALIGN align, MEET_OR_SLICE meet_or_slice) {
    return Viewbox::pointer( new Viewbox(x, y, w, h, align, meet_or_slice) );
}

Viewbox::pointer Viewbox::create(const Region& region, ALIGN align, MEET_OR_SLICE meet_or_slice) {
  return Viewbox::pointer( new Viewbox(region, align, meet_or_slice) );
}

Viewbox::~Viewbox() {}

void Viewbox::set_preserve_aspect_ratio( ALIGN align, MEET_OR_SLICE meet_or_slice ) {
    m_align = align;
    m_meet_or_slice = meet_or_slice;
    m_signal_changed.emit();
}

Viewbox::ALIGN Viewbox::alignment() const {
    return m_align;
}

Viewbox::MEET_OR_SLICE Viewbox::meet_or_slice() const {
    return m_meet_or_slice;
}

Viewbox & Viewbox::operator =( const Region & other )
{
  this->Region::operator=(other);
  return *this;
}

Viewbox & Viewbox::operator =( const Viewbox & other )
{
  m_align = other.m_align;
  m_meet_or_slice = other.m_meet_or_slice;
  this->Region::operator=(other);
  return *this;
}

bool Viewbox::operator ==( const Region & other )
{
  return this->Region::operator==(other);
}

bool Viewbox::operator ==( const Viewbox & other )
{
  return this->Region::operator==(other) &&
         m_align == other.m_align &&
         m_meet_or_slice == other.m_meet_or_slice;
}

Matrix Viewbox::transformation_matrix( const Region& box ) const {
    double xscale, yscale, xoffset=0, yoffset=0;
    bool need_x_offset=true, need_y_offset=true;
    double bx, by, bw, bh;
    box.xywh(bx, by, bw, bh);

    xscale = m_w / box.width();
    yscale = m_h / box.height();

    if (m_meet_or_slice == MEET && m_align != ALIGN_NONE) {
        if (xscale < yscale) {
            yscale = xscale;
            need_x_offset = false;
        } else {
            xscale = yscale;
            need_y_offset = false;
        }
    } else if (m_meet_or_slice == SLICE) {
        if (xscale > yscale) {
            yscale = xscale;
            need_x_offset = false;
        } else {
            xscale = yscale;
            need_y_offset = false;
        }
    }

    if (need_x_offset)
        switch (m_align) {
        case ALIGN_XMID_YMIN:
        case ALIGN_XMID_YMID:
        case ALIGN_XMID_YMAX:
            xoffset = m_w / 2.0 - box.width() * xscale / 2.0;
            break;
        case ALIGN_XMAX_YMIN:
        case ALIGN_XMAX_YMID:
        case ALIGN_XMAX_YMAX:
            xoffset = m_w - box.width() * xscale;
            break;
        default: // Catches ALIGN_NONE and ALIGN_XMIN_*
            break;
        }

    if (need_y_offset)
        switch (m_align) {
        case ALIGN_XMIN_YMID:
        case ALIGN_XMID_YMID:
        case ALIGN_XMAX_YMID:
            yoffset = m_h / 2.0 - box.height() * yscale / 2.0;
            break;
        case ALIGN_XMIN_YMAX:
        case ALIGN_XMID_YMAX:
        case ALIGN_XMAX_YMAX:
            yoffset = m_h - box.height() * yscale;
            break;
        default: // Catches ALIGN_NONE and ALIGN_*_YMIN
            break;
        }

    xoffset += m_x - box.x() * xscale;
    yoffset += m_y - box.y() * yscale;

    Matrix matrix;
    matrix.translate(xoffset, yoffset);
    matrix.scale(xscale, yscale);

    return matrix;
}

}
