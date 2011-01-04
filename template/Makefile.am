# file      : template/Makefile.am
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : not copyrighted - public domain

EXTRA_DIST = __file__(extra_dist)

noinst_PROGRAMS = driver
driver_SOURCES = driver.cxx database.hxx __path__(extra_sources) __path__(extra_headers)

if DATABASE_MYSQL
AM_CPPFLAGS = -DDATABASE_MYSQL
endif

TESTS=$(top_builddir)/tester
TESTS_ENVIRONMENT=top_builddir=$(top_builddir); export top_builddir;

# ODB compilation.
#
driver_SOURCES += __path__(odb_header_stem).hxx
nodist_driver_SOURCES = __path__(odb_header_stem)-odb.cxx
BUILT_SOURCES = __path__(odb_header_stem)-odb.hxx
CLEANFILES = __path__(odb_header_stem)-odb.hxx __path__(odb_header_stem)-odb.ixx __path__(odb_header_stem)-odb.cxx

ODB = @ODB@
ODBFLAGS = @ODBFLAGS@
ODBCPPFLAGS = @ODBCPPFLAGS@

__path__(odb_header_stem)-odb.hxx: __path__(odb_header_stem).hxx
	$(ODB) $(ODBCPPFLAGS) $(CPPFLAGS) $(ODBFLAGS)  __value__(odb_options) $<
