#############################################################################
##   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            ##
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
INCLUDES = $(PAPYRUS_CFLAGS) -I$(top_srcdir)/.
METASOURCES = AUTO

if PAPYRUS_EXTRAS

lib_LTLIBRARIES = libpapyrus-extras.la

library_includedir = $(includedir)/papyrus-@PACKAGE_RELEASE@/papyrus-extras
library_include_HEADERS = deltille.h face.h factory.h hextille.h hilbert.h \
	kochcurve.h kochsnowflake.h quadrille.h sierpinski.h tiling.h
libpapyrus_extras_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@
libpapyrus_extras_la_LIBADD = $(PAPYRUS_LIBS)
libpapyrus_extras_la_SOURCES = deltille.cpp face.cpp factory.cpp hextille.cpp \
	hilbert.cpp kochcurve.cpp kochsnowflake.cpp quadrille.cpp sierpinski.cpp tiling.cpp
noinst_HEADERS = example_image.h

endif

