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

if PAPYRUS_VENN

lib_LTLIBRARIES = libpapyrus-venn.la

library_includedir = $(includedir)/papyrus-@PACKAGE_RELEASE@/papyrus-venn
library_include_HEADERS = venn2.h venn2selectcontroller.h venn3.h \
	venn3selectcontroller.h
libpapyrus_venn_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@
libpapyrus_venn_la_LIBADD = $(PAPYRUS_LIBS)
libpapyrus_venn_la_SOURCES = venn2.cpp venn2selectcontroller.cpp venn3.cpp \
	venn3selectcontroller.cpp

endif
