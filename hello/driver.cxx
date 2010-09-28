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

    unsigned long john_id, jane_id, joe_id;

    // Create a few persistent person objects.
    //
    {
      person john ("John", "Doe", 33);
      person jane ("Jane", "Doe", 32);
      person joe ("Joe", "Dirt", 30);

      transaction t (db->begin ());

      db->persist (john);
      db->persist (jane);
      db->persist (joe);

      t.commit ();

      // Save object ids for later use.
      //
      john_id = john.id ();
      jane_id = jane.id ();
      joe_id = joe.id ();
    }

    typedef odb::query<person> query;
    typedef odb::result<person> result;

    // Say hello to those over 30.
    //
    {
      transaction t (db->begin ());

      result r (db->query<person> (query::age > 30));

      for (result::iterator i (r.begin ()); i != r.end (); ++i)
      {
        cout << "Hello, " << i->first () << " " << i->last () << "!" << endl;
      }

      t.commit ();
    }

    // Joe Dirt just had a birthday, so update his age.
    //
    {
      transaction t (db->begin ());

      auto_ptr<person> joe (db->load<person> (joe_id));
      joe->age (joe->age () + 1);
      db->update (*joe);

      t.commit ();
    }

    // Alternative implementation without using the id.
    //
    /*
    {
      transaction t (db->begin ());

      result r (db->query<person> (query::first == "Joe" &&
                                   query::last == "Dirt"));

      result::iterator i (r.begin ());

      if (i != r.end ())
      {
        auto_ptr<person> joe (i.load ());
        joe->age (joe->age () + 1);
        db->update (*joe);
      }

      t.commit ();
    }
    */


    // John Doe is no longer in our database.
    //
    {
      transaction t (db->begin ());
      db->erase<person> (john_id);
      t.commit ();
    }
  }
  catch (const odb::exception& e)
  {
    cerr << e.what () << endl;
    return 1;
  }
}
