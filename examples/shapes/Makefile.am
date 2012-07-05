INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_CFLAGS)
METASOURCES = AUTO
noinst_PROGRAMS = shapes
shapes_LDADD = $(top_builddir)/papyrus/libpapyrus.la \
	$(top_builddir)/papyrus-extras/libpapyrus-extras.la $(PAPYRUS_LIBS)
shapes_SOURCES = shapes.cpp
