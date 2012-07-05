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

demo_DATA = example_affine_controller.cpp example_affineanimator.cpp \
	example_drawables.cpp example_freehandsketcher.cpp example_handlebox_scaler.cpp \
	example_markers.cpp example_operators.cpp example_rotator.cpp example_scaler.cpp \
	example_selector.cpp example_translator.cpp example_viewbox.cpp papyrus-icon.png

EXTRA_DIST = $(demo_DATA)

demodir = $(datadir)/$(PACKAGE)-$(VERSION)/demo

bin_PROGRAMS = papyrus-extras-demo
papyrus_extras_demo_SOURCES = demo-common.cc demowindow.cc \
	example_affine_controller.cpp example_affineanimator.cpp example_drawables.cpp \
	example_freehandsketcher.cpp example_handlebox_scaler.cpp example_markers.cpp example_operators.cpp \
	example_rotator.cpp example_scaler.cpp example_selector.cpp example_translator.cpp \
	example_viewbox.cpp main.cc textwidget.cc
noinst_HEADERS = demo-common.h demos.h demowindow.h textwidget.h
papyrus_extras_demo_LDADD = $(top_builddir)/papyrus/libpapyrus.la \
	$(top_builddir)/papyrus-extras/libpapyrus-extras.la $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la $(PAPYRUS_GTKMM_LIBS) \
	$(PAPYRUS_LIBS)
