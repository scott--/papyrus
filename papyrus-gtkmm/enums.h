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
#ifndef PAPYRUSGTKENUMS_H
#define PAPYRUSGTKENUMS_H

namespace Papyrus
{
  namespace Gtk
  {

    typedef enum SIZE
    {
      SIZE_XSMALL,
      SIZE_SMALL,
      SIZE_MEDIUM,
      SIZE_LARGE,
      SIZE_XLARGE
    } SIZE;

    typedef enum INCREMENT
    {
      INCREMENT_LINEAR,
      INCREMENT_EXPONENTIAL,
    } INCREMENT;

    typedef enum SKETCH
    {
      SKETCH_LINE,
      SKETCH_POLYGON
    } SKETCH;

  };

}

#endif // PAPYRUSGTKENUMS_H
