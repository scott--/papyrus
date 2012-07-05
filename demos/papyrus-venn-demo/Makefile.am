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
INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_GTKMM_CFLAGS) $(PAPYRUS_CFLAGS) \
	-DDEMOCODEDIR="\"$(demodir)\""

METASOURCES = AUTO

if PAPYRUS_VENN

demo_DATA = example_Venn2Controller.cpp example_Venn3Controller.cpp papyrus-icon.png

EXTRA_DIST = $(demo_DATA)

demodir = $(datadir)/$(PACKAGE)-$(VERSION)/demo

bin_PROGRAMS = papyrus-venn-demo
papyrus_venn_demo_SOURCES = demo-common.cc demowindow.cc \
	example_Venn2Controller.cpp example_Venn3Controller.cpp \
	main.cc textwidget.cc
noinst_HEADERS = demo-common.h demos.h demowindow.h textwidget.h
papyrus_venn_demo_LDADD = $(top_builddir)/papyrus/libpapyrus.la \
	$(top_builddir)/papyrus-extras/libpapyrus-extras.la $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la \
	$(top_builddir)/papyrus-venn/libpapyrus-venn.la $(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS)

endif
