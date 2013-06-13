# file      : template/Makefile.am
# copyright : not copyrighted - public domain

EXTRA_DIST = __file__(extra_dist)

noinst_PROGRAMS = driver
driver_SOURCES = driver.cxx database.hxx __path__(extra_sources) __path__(extra_headers)

AM_CPPFLAGS = -I'$(builddir)' -I'$(srcdir)'

if DATABASE_MYSQL
AM_CPPFLAGS += -DDATABASE_MYSQL
endif

if DATABASE_SQLITE
AM_CPPFLAGS += -DDATABASE_SQLITE
endif

if DATABASE_PGSQL
AM_CPPFLAGS += -DDATABASE_PGSQL
endif

if DATABASE_ORACLE
AM_CPPFLAGS += -DDATABASE_ORACLE
endif

if DATABASE_MSSQL
AM_CPPFLAGS += -DDATABASE_MSSQL
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

if HAVE_CXX11
ODBFLAGS += --std c++11
endif

__path__(odb_header_stem)-odb.hxx: __path__(odb_header_stem).hxx
	$(ODB) $(ODBCPPFLAGS) $(CPPFLAGS) $(ODBFLAGS) --database @database@ __value__(odb_options) $<
