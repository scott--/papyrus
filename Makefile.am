#############################################################################
##   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            ##
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

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	papyrus.kdevelop \
	autogen.sh \
	papyrus.spec \
    papyrus.spec.m4

SUBDIRS = papyrus papyrus-extras papyrus-gtkmm demos doc examples unit-tests

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = papyrus-$(PKGCONFIG_VERSION).pc \
	papyrus-gtkmm-$(PKGCONFIG_VERSION).pc \
	papyrus-extras-$(PKGCONFIG_VERSION).pc

INCLUDES = -I$(top_srcdir)/. $(PAPYRUS_CFLAGS)

top_includedir = $(includedir)/papyrus-$(PACKAGE_RELEASE)
top_include_HEADERS = papyrus.h papyrus-gtkmm.h papyrus-extras.h

PACKAGE_RELEASEHOST="${USER},libpapyrus@frs.sourceforge.net:/home/frs/project/l/li/libpapyrus/papyrus"

docs:
	cd doc && make docs

upload-docs:
	cd doc && make upload-docs

upload-docs-only:
	cd doc && make upload-docs-only

TO_UPLOAD = $(PACKAGE)-$(VERSION).tar.bz2 $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION).zip $(PACKAGE)-$(VERSION)-doc.tar.bz2 $(PACKAGE)-$(VERSION)-doc.tar.gz $(PACKAGE)-$(VERSION)-doc.zip
RELEASE_NOTES = doc/release-notes/$(PACKAGE)-$(VERSION)-release-notes.txt
TO_UPLOAD_RN = $(TO_UPLOAD) $(RELEASE_NOTES)

release-notes:
	echo "papyrus is a C++ scenegraph library based on cairo" > $(RELEASE_NOTES)
	echo "http://libpapyrus.sourceforge.net" >> $(RELEASE_NOTES)
	echo >> $(RELEASE_NOTES)
	echo "===== $(VERSION) =====" >> $(RELEASE_NOTES)
	echo >> $(RELEASE_NOTES)
	echo >> $(RELEASE_NOTES)

	gedit $(RELEASE_NOTES) ChangeLog

upload-release-only:
	rm -rf $(VERSION)
	mkdir $(VERSION)
	if test -e $(RELEASE_NOTES); \
          then \
            cp -a $(TO_UPLOAD_RN) $(VERSION); \
          else \
            cp -a $(TO_UPLOAD) $(VERSION); \
        fi
	scp -Crp $(VERSION) $(PACKAGE_RELEASEHOST)
	rm -rf $(VERSION)

upload-release: changelog release-notes dist upload-release-only

spec:
	m4 -D PACKAGE_VERSION=$(PACKAGE_VERSION) \
		-D PACKAGE_RELEASE=$(PACKAGE_RELEASE) \
		-D PKGCONFIG_VERSION=$(PKGCONFIG_VERSION) \
		-D API_VERSION=$(PACKAGE_RELEASE) \
		papyrus.spec.m4 >papyrus.spec

changelog:
	svn2cl --authors=svn2cl.authors -r HEAD:1 --group-by-day -a
	cat ChangeLog.old >> ChangeLog

rpm: spec dist-bzip2
	cp $(PACKAGE)-$(VERSION).tar.bz2 ~/rpmbuild/SOURCES/
	cp $(PACKAGE_NAME).spec ~/rpmbuild/SPECS/
	rpmbuild -ba $(PACKAGE_NAME).spec

srpm: spec dist-bzip2
	cp $(PACKAGE)-$(VERSION).tar.bz2 ~/rpmbuild/SOURCES/
	cp $(PACKAGE)-$(VERSION)-doc.tar.bz2 ~/rpmbuild/SOURCES/
	cp $(PACKAGE_NAME).spec ~/rpmbuild/SPECS/
	rpmbuild -bs $(PACKAGE_NAME).spec

mockbuild: srpm
	mock --rebuild ~/rpmbuild/SRPMS/$(PACKAGE)-$(VERSION)*.src.rpm

dist-hook:
	cd doc && make docsdist
	mv doc/$(PACKAGE)-$(VERSION)-doc.tar.gz .
	mv doc/$(PACKAGE)-$(VERSION)-doc.tar.bz2 .
	mv doc/$(PACKAGE)-$(VERSION)-doc.zip .
