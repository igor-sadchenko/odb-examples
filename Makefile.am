# file      : Makefile.am
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
# license   : GNU GPL v2; see accompanying LICENSE file

SUBDIRS = __path__(dirs)

if HAVE_TR1_MEMORY
SUBDIRS += __path__(tr1_dirs)
endif

if ODB_EXAMPLES_BOOST
SUBDIRS += __path__(boost_dirs)
endif

if ODB_EXAMPLES_QT
SUBDIRS += __path__(qt_dirs)
endif

EXTRA_DIST = __file__(extra_dist)
ACLOCAL_AMFLAGS = -I m4
