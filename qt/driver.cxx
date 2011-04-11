// file      : qt/driver.cxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include "database.hxx" // create_database

#include "employee.hxx"
#include "employee-odb.hxx"

using namespace std;
using namespace odb::core;

ostream& operator << (ostream& os, const QString& s)
{
  return os << s.toStdString ();
}

int
main (int argc, char* argv[])
{
  try
  {
    auto_ptr<database> db (create_database (argc, argv));

    // Create a few persistent objects.
    //
    {
      // Simple Tech Ltd.
      //
      {
        shared_ptr<employer> er (new employer ("Simple Tech Ltd"));

        shared_ptr<employee> john (
          new employee ("John",
                        "Doe",
                        QDate (1974, 5, 23),
                        QByteArray ("\0xF1\0x00\0x34\0x45\0x00\0xDE", 6),
                        er));

        shared_ptr<employee> jane (
          new employee ("Jane",
                        "Doe",
                        QDate (1983, 1, 18),
                        QByteArray ("\0xD7\0x00\0x14", 3),
                        er));

        // Set the inverse side of the employee-employer relationship.
        //
        er->employees ().push_back (john);
        er->employees ().push_back (jane);

        transaction t (db->begin ());

        db->persist (er);

        db->persist (john);
        db->persist (jane);

        t.commit ();
      }

      // Complex Systems Inc.
      //
      {
        shared_ptr<employer> er (new employer ("Complex Systems Inc"));

        shared_ptr<employee> john (
          new employee ("John",
                        "Smith",
                        QDate (1954, 8, 1),
                        QByteArray ("\0x23\0xFD\0x8F\0x00", 4),
                        er));

        shared_ptr<employee> jane (
          new employee ("Jane",
                        "Smith",
                        QDate (1976, 12, 31),
                        QByteArray ("0x00\0x32\0x00\0x01\0x00", 5),
                        er));

        // Set the inverse side of the employee-employer relationship.
        //
        er->employees ().push_back (john);
        er->employees ().push_back (jane);

        transaction t (db->begin ());

        db->persist (er);

        db->persist (john);
        db->persist (jane);

        t.commit ();
      }
    }


    // Load Simple Tech Ltd and print its employees.
    //
    {
      session s;
      transaction t (db->begin ());

      shared_ptr<employer> stl (db->load<employer> ("Simple Tech Ltd"));

      employees& es (stl->employees ());

      for (employees::iterator i (es.begin ()); i != es.end (); ++i)
      {
        lazy_weak_ptr<employee>& lwp (*i);

        // Load and lock the employee and his employer.
        //
        shared_ptr<employee> p (lwp.load ());
        shared_ptr<employer> pe (p->employer ().load ());

        cout << p->first () << " " << p->last ()  << endl
             << "  born: " << p->born ().toString () << endl
             << "  public key length: " << p->public_key ().size () << endl
             << "  employer: "
             << pe->name ().toAscii ().data () << endl;

        cout << endl;
      }

      t.commit ();
    }

    // Search for Complex Systems Inc employees.
    //
    {
      typedef odb::query<employee> query;
      typedef odb::result<employee> result;

      session s;
      transaction t (db->begin ());

      result r (db->query<employee> (
                  query::employer::name == "Complex Systems Inc"));

      for (result::iterator i (r.begin ()); i != r.end (); ++i)
        cout << i->first () << " " << i->last () << endl;

      t.commit ();
    }
  }
  catch (const odb::exception& e)
  {
    cerr << e.what () << endl;
    return 1;
  }
}
