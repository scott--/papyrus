
METASOURCES = AUTO

INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_GTKMM_CFLAGS) $(PAPYRUS_CFLAGS)

if PAPYRUS_EXAMPLES

SUBDIRS = button color_schemes pick shapes simple_zoom viewbox
noinst_PROGRAMS = reference simple
simple_SOURCES = simple.cpp
simple_LDADD = $(top_builddir)/papyrus/libpapyrus.la \
	$(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la $(top_builddir)/papyrus-extras/libpapyrus-extras.la $(PAPYRUS_LIBS) \
	$(PAPYRUS_GTKMM_LIBS)

reference_SOURCES = reference.cpp
reference_LDADD = $(top_builddir)/papyrus-gtkmm/libpapyrus-gtkmm.la \
	$(top_builddir)/papyrus-extras/libpapyrus-extras.la $(top_builddir)/papyrus/libpapyrus.la $(PAPYRUS_LIBS) \
	$(PAPYRUS_GTKMM_LIBS)

endif
