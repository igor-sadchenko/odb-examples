// file      : mapping/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include "database.hxx" // create_database

#include "person.hxx"
#include "person-odb.hxx"

using namespace std;
using namespace odb;

int
main (int argc, char* argv[])
{
  try
  {
    auto_ptr<database> db (create_database (argc, argv));

    {
      person john ("John", "Doe", date (1978, 10, 13), true);
      person jane ("Jane", "Doe", date (1975, 11, 23), false);
      person joe ("Joe", "Dirt", date (1973, 12, 28), true);

      transaction t (db->begin ());

      db->persist (john);
      db->persist (jane);
      db->persist (joe);

      t.commit ();
    }

    {
      typedef odb::query<person> query;
      typedef odb::result<person> result;

      transaction t (db->begin ());

      result r (db->query<person> (query::married &&
                                   query::born == date (1978, 10, 13)));

      for (result::iterator i (r.begin ()); i != r.end (); ++i)
      {
        cout << i->first () << " " << i->last () << endl;
      }

      t.commit ();
    }
  }
  catch (const odb::exception& e)
  {
    cerr << e.what () << endl;
    return 1;
  }
}
