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
#include <papyrus/papyrus-config.h>

#ifndef PAPYRUSPOINTER_H
#define PAPYRUSPOINTER_H
  // Headers for smart pointers
  #ifdef PAPYRUS_USE_BOOST_SMART_POINTER
    #include <boost/shared_ptr.hpp>
    //#include <boost/weak_ptr.hpp>
    #define PapyrusPointer boost::shared_ptr
    #define PapyrusWeakPointer boost::weak_ptr
    #define papyrus_static_pointer_cast  boost::static_pointer_cast
    #define papyrus_const_pointer_cast   boost::const_pointer_cast
    #define papyrus_dynamic_pointer_cast boost::dynamic_pointer_cast
  #else
    #ifdef PAPYRUS_USE_CXX0X_SMART_POINTER
      #include <memory>
      #define PapyrusPointer std::shared_ptr
      #define PapyrusWeakPointer std::weak_ptr
      #define papyrus_static_pointer_cast  std::static_pointer_cast
      #define papyrus_const_pointer_cast   std::const_pointer_cast
      #define papyrus_dynamic_pointer_cast std::dynamic_pointer_cast
    #else
      #include <typeinfo>
      #include <memory>
      #include <functional>
      #include <bits/concurrence.h>
      #include <ext/mt_allocator.h>
      #include <tr1/boost_shared_ptr.h>
      #define PapyrusPointer std::tr1::shared_ptr
      #define PapyrusWeakPointer std::tr1::weak_ptr
      #define papyrus_static_pointer_cast  std::tr1::static_pointer_cast
      #define papyrus_const_pointer_cast   std::tr1::const_pointer_cast
      #define papyrus_dynamic_pointer_cast std::tr1::dynamic_pointer_cast
    #endif
  #endif
  
#endif
