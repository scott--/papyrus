INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_GTKMM_CFLAGS) $(PAPYRUS_CFLAGS)
METASOURCES = AUTO
noinst_PROGRAMS = pick
noinst_HEADERS = pick_simple.h
pick_SOURCES = pick_main.cc pick_simple.cpp
pick_LDADD = $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la \
	$(top_builddir)/papyrus/libpapyrus.la $(top_builddir)/papyrus-extras/libpapyrus-extras.la \
	$(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS)
