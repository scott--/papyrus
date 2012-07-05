INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_GTKMM_CFLAGS) $(PAPYRUS_CFLAGS)
METASOURCES = AUTO
noinst_PROGRAMS = button
button_SOURCES = button.cpp main.cc
noinst_HEADERS = button.h
button_LDADD = $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la \
	$(top_builddir)/papyrus/libpapyrus.la $(top_builddir)/papyrus-extras/libpapyrus-extras.la \
	$(PAPYRUS_GTKMM_LIBS) $(PAPYRUS_LIBS)
