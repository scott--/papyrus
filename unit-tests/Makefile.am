#############################################################################
##   Copyright (C) 2001 by Rick L. Vinyard, Jr.                            ##
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
INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_CFLAGS) $(PAPYRUS_GTKMM_CFLAGS) $(PAPYRUS_EXTRAS_CFLAGS) $(PAPYRUS_UNIT_TESTS_CFLAGS)
METASOURCES = AUTO

if PAPYRUS_UNIT_TESTS

noinst_HEADERS = canvasextentstest.h circleextentstest.h drawablematrixtests.h \
	groupextentstest.h helper.h matrixparsertest.h rectangleextentstest.h svgparsertest.h
noinst_PROGRAMS = papyrus_unit_tests
papyrus_unit_tests_LDADD = $(top_builddir)/papyrus/libpapyrus.la \
	$(top_builddir)/papyrus-extras/libpapyrus-extras.la $(PAPYRUS_EXTRAS_LIBS) $(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS) \
	$(PAPYRUS_UNIT_TESTS_LIBS)
papyrus_unit_tests_SOURCES = canvasextentstest.cpp circleextentstest.cpp \
	drawablematrixtests.cpp groupextentstest.cpp helper.cpp matrixparsertest.cpp \
	papyrus_unit_tests.cpp rectangleextentstest.cpp svgparsertest.cpp

endif
