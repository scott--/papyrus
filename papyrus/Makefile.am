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
METASOURCES = AUTO
lib_LTLIBRARIES = libpapyrus.la

AM_YFLAGS = -d -v

BUILT_SOURCES = 		\
	path_data_lexer.cc 	\
	path_data_parser.h 	\
	path_data_parser.cc

CLEANFILES = 			\
	path_data_lexer.cc 	\
	path_data_parser.h 	\
	path_data_parser.cc 	\
	path_data_parser.output

library_includedir = $(includedir)/papyrus-@PACKAGE_RELEASE@/papyrus
libpapyrus_la_SOURCES = affineanimator.cpp affinecontroller.cpp animator.cpp \
	annulus.cpp arc.cpp beziergon.cpp bezierline.cpp boxed.cpp canvas.cpp circle.cpp \
	color.cpp color_scheme.cpp controller.cpp drawable.cpp drawablecontroller.cpp \
	drawableset.cpp drawablesinglecontainer.cpp drawablewatcher.cpp fill.cpp flasher.cpp \
	freehandsketcher.cpp gradient.cpp grid.cpp group.cpp handlebox.cpp hsba.cpp hsla.cpp \
	image.cpp lineargradient.cpp marker.cpp matrix.cpp paint.cpp path.cpp \
	path_data_lexer.ll path_data_parser.yy path_element.cpp polygon.cpp polyline.cpp \
	radialgradient.cpp rectangle.cpp reference.cpp region.cpp regularpolygon.cpp rgba.cpp \
	rotator.cpp scaler.cpp selector.cpp shape.cpp stroke.cpp svg.cpp text.cpp \
	translator.cpp utility.cpp utility2.cpp viewbox.cpp x11_color.cpp x11_color1.cpp \
	x11_color2.cpp x11_color3.cpp x11_color4.cpp yuva.cpp zoomer.cpp
libpapyrus_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@
libpapyrus_la_LIBADD = $(PAPYRUS_LIBS)

INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_CFLAGS)
library_include_HEADERS = affineanimator.h affinecontroller.h animator.h \
	annulus.h arc.h beziergon.h bezierline.h boxed.h canvas.h circle.h color.h \
	color_scheme.h color_utility.h controller.h drawable.h drawablecontainer.h \
	drawablecontroller.h drawableset.h drawablesinglecontainer.h drawablewatcher.h enums.h \
	event.h fill.h flasher.h freehandsketcher.h gradient.h grid.h group.h \
	handlebox.h hsba.h hsla.h image.h lineargradient.h marker.h matrix.h object.h \
	paint.h papyrus-config.h path.h path_data_parser.h path_element.h pointer.h \
	polygon.h polyline.h primitives.h radialgradient.h rectangle.h reference.h \
	region.h regularpolygon.h renderable.h rgba.h rotator.h scaler.h selector.h \
	shape.h stroke.h svg.h text.h translator.h utility.h utility2.h viewbox.h \
	x11_color.h yuva.h zoomer.h
