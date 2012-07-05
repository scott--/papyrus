INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_GTKMM_CFLAGS) $(PAPYRUS_CFLAGS)
METASOURCES = AUTO
EXTRA_DIST=new_mexico_desert_spring_sm.png
noinst_PROGRAMS = simple_zoom
simple_zoom_SOURCES = simple.cpp
noinst_HEADERS = simple.h
simple_zoom_LDADD = $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la \
	$(top_builddir)/papyrus/libpapyrus.la $(top_builddir)/papyrus-extras/libpapyrus-extras.la \
	$(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS)
