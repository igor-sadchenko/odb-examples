// file      : mapping/traits-pgsql.cxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "traits-pgsql.hxx"

namespace odb
{
  namespace pgsql
  {
    namespace
    {
      tm pg_epoch_tm = {0, 0, 0, 1, 1, 100, 0, 0, 0, 0, 0};
    }

    const time_t value_traits<date, id_date>::pg_epoch_tt (
      mktime (&pg_epoch_tm));
  }
}
