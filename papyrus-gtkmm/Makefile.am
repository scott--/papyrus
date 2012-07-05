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
INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_CFLAGS) $(PAPYRUS_GTKMM_CFLAGS)
METASOURCES = AUTO

if PAPYRUS_GTKMM

lib_LTLIBRARIES = libpapyrus-gtkmm.la

library_includedir = $(includedir)/papyrus-@PACKAGE_RELEASE@/papyrus-gtkmm
library_include_HEADERS = animatorbouncewidget.h animatorframeintervalwidget.h \
	animatorframeratewidget.h drawabletreeview.h enums.h gradientstopwidget.h linecapbuttonbox.h \
	linecapcombobox.h linejoinbuttonbox.h linejoincombobox.h linewidthcombobox.h \
	markercombobox.h markerwidget.h scrolleddrawabletreeview.h scrolledviewport.h \
	strokedialog.h strokewidget.h utility.h viewport.h
libpapyrus_gtkmm_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@
libpapyrus_gtkmm_la_LIBADD = $(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS)
libpapyrus_gtkmm_la_SOURCES = animatorbouncewidget.cpp \
	animatorframeintervalwidget.cpp animatorframeratewidget.cpp drawabletreeview.cpp gradientstopwidget.cpp \
	linecapbuttonbox.cpp linecapcombobox.cpp linejoinbuttonbox.cpp linejoincombobox.cpp \
	linewidthcombobox.cpp markercombobox.cpp markerwidget.cpp scrolleddrawabletreeview.cpp \
	scrolledviewport.cpp strokedialog.cpp strokewidget.cpp utility.cpp viewport.cpp

endif
