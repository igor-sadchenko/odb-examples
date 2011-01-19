// file      : schema/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr
#include <iostream>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include "database.hxx" // create_database

#include "employee.hxx"
#include "employee-odb.hxx"

using namespace std;
using namespace odb;

int
main (int argc, char* argv[])
{
  try
  {
    auto_ptr<database> db (create_database (argc, argv));

    // Create the database schema.
    //
    {
      transaction t (db->begin ());

      // Try to drop the tables if they exist and ignore the error
      // if they don't.
      //
      try
      {
        db->execute ("DROP TABLE Employer");
        db->execute ("DROP TABLE Employee");
        db->execute ("DROP TABLE EmployeeDegree");
      }
      catch (const odb::exception&)
      {
      }

      db->execute (
        "CREATE TABLE Employer ("
        "name VARCHAR (255) NOT NULL PRIMARY KEY)");

      db->execute (
        "CREATE TABLE Employee ("
        "ssn INTEGER UNSIGNED NOT NULL PRIMARY KEY,"
        "first_name VARCHAR (255) NOT NULL,"
        "last_name VARCHAR (255) NOT NULL,"
        "employer VARCHAR (255) NOT NULL REFERENCES Employer (name))");

      db->execute (
        "CREATE TABLE EmployeeDegree ("
        "ssn INTEGER UNSIGNED NOT NULL REFERENCES Employee (ssn),"
        "degree VARCHAR (255) NOT NULL)");

      t.commit ();
    }

    // Create a few persistent objects.
    //
    {
      shared_ptr<employer> st (new employer ("Simple Tech Ltd"));

      shared_ptr<employee> john (new employee (1, "John", "Doe", st));
      shared_ptr<employee> jane (new employee (2, "Jane", "Doe", st));

      john->degrees ().push_back ("BA");
      john->degrees ().push_back ("MSc");
      jane->degrees ().push_back ("Ph.D.");

      transaction t (db->begin ());

      db->persist (st);
      db->persist (john);
      db->persist (jane);

      t.commit ();
    }

    // Load employees with "Doe" as the last name and print what we've got.
    //
    {
      typedef odb::query<employee> query;
      typedef odb::result<employee> result;

      session s;
      transaction t (db->begin ());

      result r (db->query<employee> (query::name::last == "Doe"));

      for (result::iterator i (r.begin ()); i != r.end (); ++i)
      {
        cout << i->name ().first () << " " << i->name ().last () << endl
             << "  employer: " << i->employer ()->name () << endl;

        for (degrees::iterator j (i->degrees ().begin ());
             j != i->degrees ().end ();
             ++j)
        {
          cout << "  degree: " << *j << endl;
        }

        cout << endl;
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
