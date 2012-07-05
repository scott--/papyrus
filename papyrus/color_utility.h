/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
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
#ifndef PAPYRUSCOLORUTILITY_H
#define PAPYRUSCOLORUTILITY_H

namespace Papyrus {

template <typename T>
inline
void get_min_max(T& min, T& max, const T& first, const T& second, const T& third) {
    if (first > second) {
      if (first > third) {
        max = first;
        min = (third>second)?second:third;
      }
      else {
        max = third;
        min = second;
      }
    }
    else {
      if (first < third) {
        min = first;
        max = (third>second)?third:second;
      }
      else {
        min = third;
        max = second;
      }
    }
}

}

#endif
