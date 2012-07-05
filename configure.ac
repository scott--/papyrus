#############################################################################
##   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            ##
##   rvinyard@cs.nmsu.edu                                                  ##
##                                                                         ##
##   This file is part of the papyrus library.                             ##
##                                                                         ##
##   papyrus is free software; you can redistribute it and/or modify       ##
##   it under the terms of the GNU Lesser General Public License           ##
##   version 3.0 as published by the Free Software Foundation.             ##
##                                                                         ##
##   papyrus is distributed in the hope that it will be useful,            ##
##   but WITHOUT ANY WARRANTY; without even the implied warranty of        ##
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ##
##   GNU Lesser General Public License version 3.0 for more details.       ##
##                                                                         ##
##   You should have received a copy of the GNU Lesser General Public      ##
##   License along with the papyrus library. If not, see                   ##
##   <http://www.gnu.org/licenses/>.                                       ##
#############################################################################

#########################################################################
#  package specific values
#########################################################################
pushdef([PACKAGE_MAJOR_VERSION], [0])
pushdef([PACKAGE_MINOR_VERSION], [13])
pushdef([PACKAGE_MICRO_VERSION], [3])
pushdef([PKG_VERSION], PACKAGE_MAJOR_VERSION.PACKAGE_MINOR_VERSION.PACKAGE_MICRO_VERSION)

AC_INIT([papyrus], PKG_VERSION, [rvinyard@cs.nmsu.edu])

[PACKAGE_MAJOR_VERSION]=PACKAGE_MAJOR_VERSION
[PACKAGE_MINOR_VERSION]=PACKAGE_MINOR_VERSION
[PACKAGE_MICRO_VERSION]=PACKAGE_MICRO_VERSION

popdef([PACKAGE_MAJOR_VERSION])
popdef([PACKAGE_MINOR_VERSION])
popdef([PACKAGE_MICRO_VERSION])
popdef([PKG_VERSION])

#
# +1 :  ? : +1 == new interface that does not break old one
# +1 :  ? :  0 == new interface that breaks old one
#  ? :  ? :  0 == no new interfaces, but breaks apps
#  ? : +1 :  ? == just some internal changes, nothing breaks but might work better
# CURRENT : REVISION : AGE
LIBTOOL_SO_VERSION=0:0:0
LIBTOOL_SO_VERSION_MAJOR=0
AC_SUBST(LIBTOOL_SO_VERSION)
AC_SUBST(LIBTOOL_SO_VERSION_MAJOR)

PAPYRUS_PKGCONFIG="glib-2.0 >= 2.0 cairomm-1.0 >= 0.6 sigc++-2.0 glibmm-2.4 >= 2.14 libxml++-2.6"
PAPYRUS_GTKMM_PKGCONFIG="gtkmm-2.4 >= 2.10"
PAPYRUS_EXTRAS_PKGCONFIG=""

PKGCONFIG_VERSION="1.0"

#########################################################################
#  don't touch this
#########################################################################
PACKAGE_RELEASE=$PACKAGE_MAJOR_VERSION.$PACKAGE_MINOR_VERSION
AC_SUBST(PACKAGE_RELEASE)
AC_SUBST(PKGCONFIG_VERSION)

AC_DEFINE_UNQUOTED(PACKAGE_MAJOR_VERSION, $PACKAGE_MAJOR_VERSION, [Major version])
AC_DEFINE_UNQUOTED(PACKAGE_MINOR_VERSION, $PACKAGE_MINOR_VERSION, [Minor version])
AC_DEFINE_UNQUOTED(PACKAGE_MICRO_VERSION, $PACKAGE_MICRO_VERSION, [Micro version])
AC_SUBST(PACKAGE_MAJOR_VERSION)
AC_SUBST(PACKAGE_MINOR_VERSION)
AC_SUBST(PACKAGE_MICRO_VERSION)

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-bzip2 dist-zip -Wno-portability])
AM_CONFIG_HEADER([config.h])
AX_PREFIX_CONFIG_H([papyrus/papyrus-config.h],[PAPYRUS],[config.h])

dnl this package needs m4
AC_CHECK_PROGS(M4, gm4 m4, m4)

AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LEX
AC_PROG_YACC
AC_CXX_COMPILE_STDCXX_0X

for top_builddir in . .. ../.. $ac_auxdir $ac_auxdir/..; do
test -f $top_builddir/configure && break
done
AC_PROG_LIBTOOL

AC_HEADER_STDC

AC_CONFIG_MACRO_DIR([m4])

#########################################################################
#  header check utility macros
#########################################################################
AC_DEFUN([AC_REQUIRE_HEADERS],[AC_CHECK_HEADERS($1,,AC_MSG_ERROR([Header $1 not found]))])
AC_DEFUN([AC_REQUIRE_LIB],[AC_CHECK_LIB($1,$2,,AC_MSG_ERROR(Library $1 not found))])

AC_REQUIRE_HEADERS(expat.h)
AC_REQUIRE_HEADERS(stdint.h)
AC_REQUIRE_LIB(expat,XML_ParserCreate)

#AC_CHECK_HEADER(
#  [cstdint],
#  [AC_DEFINE(STDINT,[<cstdint>],[Use C++ stdint header cstdint])],
#  [  AC_CHECK_HEADER(
#       [tr1/stdint.h],
#       [AC_DEFINE(STDINT,[tr1/stdint.h>],[Use C++ tr1 stdint header tr1/stdint.h])],
#       [  AC_CHECK_HEADER(
#            [stdint.h],
#            [AC_DEFINE(STDINT,[<stdint.h>],[Use C stdint header stdint.h])],
#            [  AC_CHECK_HEADER(
#                 [boost/cstdint.hpp],
#                 [ AC_DEFINE(STDINT,[<boost/cstdint.hpp>],[Use boost stdint header cstdint.hpp])],
#                 [ AC_MSG_ERROR([No usable stdint header found])
#                 ] )
#            ] )
#       ] )
#  ] )

#########################################################################
#  Look for smart pointers in either tr1 or boost
#########################################################################
AC_DEFUN(
  [CHECK_FOR_BOOST_SMART_POINTER],
  [AC_MSG_CHECKING([for Boost smart pointers])
   AC_CHECK_HEADER( [boost/shared_ptr.hpp],
                     [AC_DEFINE(USE_BOOST_SMART_POINTER,[],[If defined, boost library smart pointers will be used])
                     ],
                     [AC_MSG_ERROR([No usable smart pointer library found])
                     ]
                   )
  ]
)

AC_DEFUN(
  [CHECK_FOR_TR1_SMART_POINTER],
  [AC_MSG_CHECKING([for TR1 smart pointers])
   AC_CHECK_HEADER( [tr1/boost_shared_ptr.h],
                     [AC_DEFINE(USE_TR1_SMART_POINTER,[],[If defined TR1 smart pointers will be used])
                     ],
                     [CHECK_FOR_BOOST_SMART_POINTER
                     ],
                     [
                       #include <typeinfo>
                       #include <memory>
                       #include <functional>
                       #include <bits/concurrence.h>
                       #include <ext/mt_allocator.h>
                     ]
                   )
  ]
)

AC_MSG_CHECKING([for c++0x smart pointers])
AS_IF([test "$ac_cv_cxx_compile_cxx0x_native" = yes ||
       test "$ac_cv_cxx_compile_cxx0x_cxx" = yes],
      [
        AS_IF([test "$ac_cv_cxx_compile_cxx0x_cxx" = yes],
              [ CXXFLAGS="$CXXFLAGS -std=c++0x"
                AC_SUBST(CXXFLAGS)
                CPP0XFLAGS="-std=c++0x"
                AC_SUBST(CPP0XFLAGS) ])
        AC_DEFINE(USE_CXX0X_SMART_POINTER,[],[If defined c++0x smart pointers will be used])
        AC_MSG_RESULT(yes)
      ],
      [ AC_MSG_RESULT(no)
        CPP0XFLAGS=""
        AC_SUBST(CPP0XFLAGS)
        CHECK_FOR_TR1_SMART_POINTER
      ]
     )


#########################################################################
#  pkgconfig package requirements
#########################################################################
PKG_CHECK_MODULES([PAPYRUS],[${PAPYRUS_PKGCONFIG}])
AC_SUBST(PAPYRUS_PKGCONFIG)
AC_SUBST(PAPYRUS_LIBS)
AC_SUBST(PAPYRUS_CFLAGS)


AC_ARG_ENABLE([doc],[AS_HELP_STRING([--enable-doc],[Build papyrus documentation [default=no]])],[enable_doc=$enableval],[enable_doc=no])
AM_CONDITIONAL(PAPYRUS_DOC, [test "x${enable_doc}" == xyes])

AC_ARG_ENABLE([demos],[AS_HELP_STRING([--enable-demos],[Build papyrus demos (also enables extras and gtkmm) [default=no]])],[enable_demos=$enableval],[enable_demos=no])
AM_CONDITIONAL(PAPYRUS_DEMOS, [test "x${enable_demos}" == xyes])

AC_ARG_ENABLE([gtkmm],[AS_HELP_STRING([--enable-gtkmm],[Build gtkmm UI widgets [default=no]])],[enable_gtkmm=$enableval],[enable_gtkmm=no])
# if demos are enabled, then gtkmm must be enabled no matter what option was given
AS_IF([test "x${enable_demos}" == xyes],[enable_gtkmm=yes],[])
AS_IF([test "x${enable_gtkmm}" == xyes],
  [ PKG_CHECK_MODULES([PAPYRUS_GTKMM],[${PAPYRUS_GTKMM_PKGCONFIG}])
  ],
  [])
AM_CONDITIONAL(PAPYRUS_GTKMM, [test "x${enable_gtkmm}" == xyes])
AC_SUBST(PAPYRUS_GTKMM_PKGCONFIG)
AC_SUBST(PAPYRUS_GTKMM_LIBS)
AC_SUBST(PAPYRUS_GTKMM_CFLAGS)

AC_ARG_ENABLE([extras],[AS_HELP_STRING([--enable-extras],[Build extra papyrus drawables [default=yes]])],[enable_extras=$enableval],[enable_extras=yes])
# if demos are enabled, then extras must be enabled no matter what option was given
AS_IF([test "x${enable_demos}" == xyes],[enable_extras=yes],[])
AM_CONDITIONAL(PAPYRUS_EXTRAS, [test "x${enable_extras}" == xyes])
AC_SUBST(PAPYRUS_EXTRAS_PKGCONFIG)
AC_SUBST(PAPYRUS_EXTRAS_LIBS)
AC_SUBST(PAPYRUS_EXTRAS_CFLAGS)


AC_ARG_ENABLE([venn],[AS_HELP_STRING([--enable-venn],[Build the papyrus venn diagram library [default=no]])],[enable_venn=$enableval],[enable_venn=no])
# if demos are enabled, then venn must be enabled no matter what option was given
AS_IF([test "x${enable_demos}" == xyes],[enable_venn=yes],[])
AM_CONDITIONAL(PAPYRUS_VENN, [test "x${enable_venn}" == xyes])


AC_ARG_ENABLE([examples],[AS_HELP_STRING([--enable-examples],[Build example papyrus applications [default=no]])],[enable_example==$enableval],[enable_examples=no])
AM_CONDITIONAL(PAPYRUS_EXAMPLES, [test "x${enable_examples}" == xyes])

AC_ARG_ENABLE([unit-tests],[AS_HELP_STRING([--enable-unit-tests],[Build papyrus unit test applications [default=no]])],[enable_unit_tests=$enableval],[enable_unit_tests=no])
AS_IF([test "x${enable_unit_tests}" == xyes],
  [ PKG_CHECK_MODULES([PAPYRUS_UNIT_TESTS],[cppunit])
  ],
  [])
AM_CONDITIONAL(PAPYRUS_UNIT_TESTS, [test "x${enable_unit_tests}" == xyes])
AC_SUBST(PAPYRUS_UNIT_TESTS_LIBS)
AC_SUBST(PAPYRUS_UNIT_TESTS_CFLAGS)


AC_OUTPUT(Makefile demos/Makefile demos/papyrus-demo/Makefile \
	demos/papyrus-extras-demo/Makefile demos/papyrus-gtkmm-demo/Makefile doc/Makefile examples/Makefile \
	examples/button/Makefile examples/color_schemes/Makefile examples/pick/Makefile \
	examples/shapes/Makefile examples/simple_zoom/Makefile examples/viewbox/Makefile papyrus-1.0.pc \
	papyrus-extras-1.0.pc papyrus-extras/Makefile papyrus-gtkmm-1.0.pc papyrus-gtkmm/Makefile \
	papyrus/Makefile unit-tests/Makefile)
