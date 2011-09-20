// file      : composite/driver.cxx
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
using namespace odb::core;

int
main (int argc, char* argv[])
{
  try
  {
    auto_ptr<database> db (create_database (argc, argv));

    // Create a person object.
    //
    unsigned int id;
    {
      person p ("Joe", "Dirt", "Mr");

      transaction t (db->begin ());
      id = db->persist (p);
      t.commit ();
    }

    // Update the extra name information.
    //
    {
      transaction t (db->begin ());

      auto_ptr<person> joe (db->load<person> (id));
      name_extras& ne (joe->name ().extras ());
      ne.nickname ("Squeaky");
      ne.aliases ().push_back (basic_name ("Anthony", "Clean"));

      db->update (*joe);

      t.commit ();
    }

    // Print the name information.
    //
    {
      transaction t (db->begin ());
      auto_ptr<person> joe (db->load<person> (id));
      t.commit ();

      name& n (joe->name ());

      cout << n.title () << " " << n.first () << " " << n.last () << endl;

      name_extras& ne (n.extras ());

      if (!ne.nickname ().empty ())
        cout << "  nickname: " << ne.nickname () << endl;

      for (basic_names::iterator i (ne.aliases ().begin ());
           i != ne.aliases ().end ();
           ++i)
      {
        cout << "  alias: " << i->first () << " " << i->last () << endl;
      }
    }

    // Query the database for a person object.
    //
    {
      typedef odb::query<person> query;
      typedef odb::result<person> result;

      transaction t (db->begin ());

      result r (db->query<person> (
                  query::name.extras.nickname == "Squeaky"));

      if (!r.empty ())
      {
        name& n (r.begin ()->name ());
        cout << n.title () << " " << n.first () << " " << n.last () << endl;
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
