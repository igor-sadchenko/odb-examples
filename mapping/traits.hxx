// file      : mapping/traits.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef TRAITS_HXX
#define TRAITS_HXX

#include <cstring>

#include "person.hxx"  // date

// MySQL implementation.
//
#if defined(DATABASE_MYSQL)

#include <odb/mysql/traits.hxx>

namespace odb
{
  namespace mysql
  {
    template <>
    class value_traits<bool, details::buffer, id_string>
    {
    public:
      typedef bool value_type;
      typedef bool query_type;
      typedef details::buffer image_type;

      static void
      set_value (bool& v,
                 const details::buffer& b,
                 std::size_t n,
                 bool is_null)
      {
        v = (!is_null && n == 4 && std::strncmp ("true", b.data (), n) == 0);
      }

      static void
      set_image (details::buffer& b,
                 std::size_t& n,
                 bool& is_null,
                 bool v)
      {
        is_null = false;
        n = v ? 4 : 5;

        if (n > b.capacity ())
          b.capacity (n);

        std::memcpy (b.data (), (v ? "true" : "false"), n);
      }
    };

    template <>
    class value_traits<date, MYSQL_TIME, id_date>
    {
    public:
      typedef date value_type;
      typedef date query_type;
      typedef MYSQL_TIME image_type;

      static void
      set_value (date& v, const MYSQL_TIME& i, bool is_null)
      {
        if (!is_null)
          v = date (i.year, i.month, i.day);
        else
          v = date (0, 0, 0);
      }

      static void
      set_image (MYSQL_TIME& i, bool& is_null, const date& v)
      {
        is_null = false;
        i.neg = false;
        i.year = v.year ();
        i.month = v.month ();
        i.day = v.day ();
      }
    };
  }
}

#endif // DATABASE_MYSQL

#endif // TRAITS_HXX
