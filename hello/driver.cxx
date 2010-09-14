// file      : hello/driver.cxx
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

    // Create a few persistent person objects.
    //
    {
      person john_doe ("John", "Doe", 29);
      person jane_doe ("Jane", "Doe", 28);
      person joe_dirt ("Joe", "Dirt", 31);

      transaction t (db->begin_transaction ());

      db->persist (john_doe);
      db->persist (jane_doe);
      db->persist (joe_dirt);

      t.commit ();
    }

    // Say hello to those under 30.
    //
    {
      typedef odb::query<person> query;
      typedef odb::result<person> result;

      transaction t (db->begin_transaction ());

      result r (db->query<person> (query::age < 30));

      for (result::iterator i (r.begin ()); i != r.end (); ++i)
      {
        cout << "Hello, " << i->first () << " " << i->last () << "!" << endl;
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
