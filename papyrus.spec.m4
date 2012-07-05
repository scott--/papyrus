Summary:          Cairo based C++ scenegraph library
Name:             papyrus
Version:          PACKAGE_VERSION
Release:          1%{?dist}
License:          LGPLv3
URL:              http://libpapyrus.sourceforge.net/
Group:            System Environment/Libraries
Source0:          http://downloads.sourceforge.net/libpapyrus/%{name}-%{version}.tar.bz2
Source1:          http://downloads.sourceforge.net/libpapyrus/%{name}-%{version}-doc.tar.bz2
BuildRoot:        %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:    gtkmm24-devel >= 2.10
BuildRequires:    cairomm-devel >= 1.2
BuildRequires:    libxml++-devel >= 2.6
BuildRequires:    expat-devel
BuildRequires:    pkgconfig
BuildRequires:    m4

%description
Cairo based C++ scenegraph library

%package          devel
Summary:          Headers for developing programs that will use %{name}
Group:            Development/Libraries
Requires:         papyrus = %{version}-%{release}
Requires:         cairomm-devel >= 1.2
Requires:         glibmm24-devel >= 2.14
Requires:         libxml++-devel >= 2.6
Requires:         pkgconfig

%description      devel
This package contains the libraries and header files needed for
developing papyrus applications. Papyrus is a cairo based C++
scenegraph library.

%package          doc
Summary:          Developer's documentation for the Papyrus library
Group:            Documentation
Requires:         gtk-doc
Requires:         devhelp
%if 0%{?fedora} > 9 || 0%{?rhel} > 5
BuildArch:        noarch
%endif

%description      doc
This package contains developer's documentation for the Papyrus
library. Papyrus is a cairo based C++ scenegraph library.

The documentation can be viewed either through the devhelp
documentation browser or through a web browser. 

If using a web browser the documentation is installed in the gtk-doc
hierarchy and can be found at /usr/share/gtk-doc/html/papyrus-API_VERSION

%package          extras
Summary:          Extra shapes for the papyrus scenegraph library
Group:            System Environment/Libraries
Requires:         papyrus = %{version}-%{release}

%description      extras
This package contains extra drawables, renderables and shape objects
for the papyrus scenegraph library.

%package          extras-devel
Summary:          Headers for developing programs that will use papyrus-extras
Group:            Development/Libraries
Requires:         papyrus-extras = %{version}-%{release}
Requires:         papyrus-devel = %{version}-%{release}

%description      extras-devel
This package contains the libraries and header files needed for
developing papyrus-extras applications.

%package          gtkmm
Summary:          Gtkmm UI widgets for the papyrus scenegraph library
Group:            System Environment/Libraries
Requires:         papyrus-extras = %{version}-%{release}

%description      gtkmm
This package contains gtkmm widgets associated with the papyrus library.

%package          gtkmm-devel
Summary:          Headers for developing programs that will use papyrus-gtkmm
Group:            Development/Libraries
Requires:         papyrus-gtkmm = %{version}-%{release}
Requires:         papyrus-extras-devel = %{version}-%{release}
Requires:         gtkmm24-devel >= 2.6

%description    gtkmm-devel
This package contains the libraries and header files needed for
developing papyrus-gtkmm applications.


%prep
%setup -q -b 1

%build
%configure --enable-demos --enable-papyrus-gtkmm --enable-papyrus-extras --enable-static=no
%{__make} %{?_smp_mflags}

%install
%{__rm} -rf %{buildroot}
%{__make} DESTDIR=%{buildroot} INSTALL="%{__install} -p" install
find %{buildroot} -type f -name "*.la" -exec rm -f {} ';'

# Put docs under gtk-doc
%{__mkdir} -p %{buildroot}%{_datadir}/gtk-doc/html/papyrus-API_VERSION/reference/html/
%{__install} -p --mode=0664 -t %{buildroot}%{_datadir}/gtk-doc/html/papyrus-API_VERSION/reference/html/ doc/reference/html/*
%{__install} -p --mode=0664 -t %{buildroot}%{_datadir}/gtk-doc/html/papyrus-API_VERSION/ doc/papyrus-API_VERSION.devhelp


%clean
%{__rm} -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%post extras -p /sbin/ldconfig

%postun extras -p /sbin/ldconfig

%post gtkmm -p /sbin/ldconfig

%postun gtkmm -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%doc AUTHORS COPYING
%{_libdir}/libpapyrus.so.*

%files devel
%defattr(-,root,root,-)
%{_libdir}/libpapyrus.so
%{_libdir}/pkgconfig/papyrus-1.0.pc
%{_includedir}/papyrus-PACKAGE_RELEASE/papyrus.h
%{_includedir}/papyrus-PACKAGE_RELEASE/papyrus/
%dir %{_includedir}/papyrus-PACKAGE_RELEASE/
%{_bindir}/papyrus-demo
%{_datadir}/papyrus-PACKAGE_VERSION/
%doc ChangeLog

%files doc
%defattr(-,root,root,-)
%doc %{_datadir}/gtk-doc/html/papyrus-API_VERSION/

%files extras
%defattr(-,root,root,-)
%doc AUTHORS COPYING
%{_libdir}/libpapyrus-extras.so.*

%files extras-devel
%defattr(-,root,root,-)
%{_libdir}/libpapyrus-extras.so
%{_libdir}/pkgconfig/papyrus-extras-1.0.pc
%{_includedir}/papyrus-PACKAGE_RELEASE/papyrus-extras.h
%{_includedir}/papyrus-PACKAGE_RELEASE/papyrus-extras/
%{_bindir}/papyrus-extras-demo
%doc AUTHORS COPYING

%files gtkmm
%defattr(-,root,root,-)
%doc AUTHORS COPYING
%{_libdir}/libpapyrus-gtkmm.so.*

%files gtkmm-devel
%defattr(-,root,root,-)
%{_libdir}/libpapyrus-gtkmm.so
%{_libdir}/pkgconfig/papyrus-gtkmm-1.0.pc
%{_includedir}/papyrus-PACKAGE_RELEASE/papyrus-gtkmm.h
%{_includedir}/papyrus-PACKAGE_RELEASE/papyrus-gtkmm/
%{_bindir}/papyrus-gtkmm-demo
%{_datadir}/papyrus-gtkmm-PACKAGE_VERSION/
%doc AUTHORS COPYING


%changelog
* Fri Apr 16 2010 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.13.2-1
- New release

* Wed Dec 09 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.13.1-1
- New release

* Tue Nov 17 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.13.0-1
- New release

* Tue Sep  1 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.12.1-1
- New release

* Wed Aug  5 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.12.0-1
- New release
- Made doc subpackage noarch conditional
- Added separate doc source

* Sat Jul 25 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.11.1-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Tue May 26 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.11.1-2
- Rebuild for cairomm-1.8

* Thu May 14 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.11.1-1
- New release
- Added doc subpackage

* Wed Mar 18 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.11.0-1
- New release

* Fri Mar 06 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.10.2-1
- New release

* Thu Mar 05 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.10.1-1
- New release

* Mon Mar 02 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.10.0-2
- Changed papyrus-gtkmm dependency from papyrus to papyrus-extras
- Changed Sourceforge url to downloads.sf.net from download.sf.net
- Added -p to doc installs

* Fri Feb 06 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.10.0-1
- New release
- Added new dependencies on glibmm and libxml++ for new release
- Added devhelp install in -devel package

* Fri Feb 06 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.9.0-1
- New release
- Added --enable-demos --enable-papyrus-gtkmm --enable-papyrus-extras
- Fix unowned /usr/include/papyrus-RELEASE directory

* Thu Jan 15 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.8.1-1
- New release fixes pkgconfig files

* Tue Jan 13 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.8.0-1
- New release

* Sat Jan 05 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.7.91-1
- New release

* Wed Jan 02 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.7.90-1
- New release

* Thu Jan 01 2009 Tim Niemueller <tim@niemueller.de> - 0.7.1-6
- Make all dtors virtual to fix compile warnings (errors with -Wall -Werror)

* Sun Dec 21 2008 Tim Niemueller <tim@niemueller.de> - 0.7.1-5
- Header fixes for F-10
- Drawing fixes (invalid use of std::valarray)

* Sun Sep 21 2008 Ville Skyttä <ville.skytta at iki.fi> - 0.7.1-4
- Fix Patch0:/%%patch mismatch.

* Mon Mar 03 2008 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.7.1-3
- Added boost-devel dependency
- Added INT_MAX patch

* Tue Feb 19 2008 Fedora Release Engineering <rel-eng@fedoraproject.org> - 0.7.1-2
- Autorebuild for GCC 4.3

* Sat Mar 10 2007 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.7.1-1
- New release

* Sat Jan 20 2007 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.7.0-1
- New release

* Sun Jan 07 2007 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.6.1-1
- New release

* Tue Jan 02 2007 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.6.0-1
- New release
- Add install option to preserve timestamps
- Fix doc installation directories

* Fri Sep 08 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.5.1-2
- Bump release for new sources and make tag

* Fri Sep 08 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.5.1-1
- New release fixes packaging error

* Fri Sep 08 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.5.0-1
- New release

* Sun Aug 27 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.4.0-2
- Bumped release for mass rebuild

* Sun Aug 24 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.4.0-1
- New release
- Removed /demo/ suffix from datadir
- Added papyrusmm data and include dirs

* Thu Aug 24 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.3.1-2
- Bump release for make tag

* Thu Aug 24 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.3.1-1
- New release

* Sun Aug 13 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.3.0-1
- New release
- Removed /demo/ suffix from datadir
- Added papyrusmm data and include dirs

* Sun Aug  6 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.2.3-1
- New release
- Added m4 to BuildRequires

* Mon Jul 31 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.2.2-1
- New release
- Removed pkgconfig from BuildRequires
- Added pkgconfig to -devel Requires

* Sat Jul 29 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.2.1-2
- Changed make to %%{__make}
- Changed %%{name} to autoconf subst that puts specific name in devel requires
- Added comment regarding why cp occurs for docs
- Removed doxygen, graphviz and pkgconfig from devel requires
- Added package name to globs in so libs, .pc and demos

* Fri Jul 21 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.2.1-1
- New release
- Added papyrus-demo and papyrusmm-demo to devel package
- Remove rm -rf /usr/bin
- Changed mv of docs to cp of docs

* Fri May 26 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.12-1
- New release
- Changed sourceforge download location to download.sourceforge.net

* Sun May  7 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.11-1
- New release

* Sun Apr  9 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.10-1
- New release

* Fri Mar 24 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.9-1
- New release
- Cleaned up spec file and added pkgconfig to BuildRequires

* Fri Mar 17 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.8-1
- New release

* Sun Mar 12 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.7-1
- New release

* Sun Mar 05 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.6-1
- Removed Requires tag, relying on BuildRequires instead
- Cleaned up Source tag and changed to bz2 files
- New upstream release (upstream is me, it's just easier to say it that way)

* Tue Feb 28 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.5-1
- Initial version (at least the inital version with a changelog in the .spec)
