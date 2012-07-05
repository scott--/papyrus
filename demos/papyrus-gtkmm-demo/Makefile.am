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

EXTRA_DIST = papyrus-icon.png

METASOURCES = AUTO

demo_DATA = example_animatorbouncewidget.cpp \
	example_animatorframeintervalwidget.cpp example_animatorframeratewidget.cpp example_drawabletreeview.cpp \
	example_lineargradient.cpp example_linecapbuttonbox.cpp example_linecapcombobox.cpp \
	example_linejoinbuttonbox.cpp example_linejoincombobox.cpp example_linewidthcombobox.cpp \
	example_markercombobox.cpp example_markerwidget.cpp example_pixbuf.cpp \
	example_scrolledviewport.cpp example_strokewidget.cpp example_viewport.cpp papyrus-icon.png

demodir = $(datadir)/papyrus-gtkmm-$(VERSION)/demo

bin_PROGRAMS = papyrus-gtkmm-demo
papyrus_gtkmm_demo_SOURCES = demo-common.cc demowindow.cc \
	example_animatorbouncewidget.cpp example_animatorframeintervalwidget.cpp \
	example_animatorframeratewidget.cpp example_drawabletreeview.cpp example_lineargradient.cpp \
	example_linecapbuttonbox.cpp example_linecapcombobox.cpp example_linejoinbuttonbox.cpp \
	example_linejoincombobox.cpp example_linewidthcombobox.cpp example_markercombobox.cpp \
	example_markerwidget.cpp example_pixbuf.cpp example_scrolledviewport.cpp \
	example_strokewidget.cpp example_viewport.cpp main.cc textwidget.cc
papyrus_gtkmm_demo_LDADD = $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la \
	$(top_builddir)/papyrus/libpapyrus.la $(top_builddir)/papyrus-extras/libpapyrus-extras.la \
	$(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS)
noinst_HEADERS = demo-common.h demos.h demowindow.h textwidget.h
