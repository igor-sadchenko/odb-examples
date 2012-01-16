// file      : mapping/traits.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef TRAITS_HXX
#define TRAITS_HXX

// Include one of the database system-specific traits implementations.
//
#if defined(DATABASE_MYSQL)
#  include "traits-mysql.hxx"
#elif defined(DATABASE_SQLITE)
#  include "traits-sqlite.hxx"
#elif defined(DATABASE_PGSQL)
#  include "traits-pgsql.hxx"
#elif defined(DATABASE_ORACLE)
#  include "traits-oracle.hxx"
#elif defined(DATABASE_MSSQL)
#  include "traits-mssql.hxx"
#endif

#endif // TRAITS_HXX
