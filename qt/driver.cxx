// file      : qt/driver.cxx
// author    : Constantin Michael <constantin@codesynthesis.com>
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
using namespace odb::core;

int
main (int argc, char* argv[])
{
  try
  {
    auto_ptr<database> db (create_database (argc, argv));

    employee e;
    e.name = "John Doe";

    QChar* c = e.name.data ();

    while (!c->isNull ())
    {
      cout << c->toAscii ();
      ++c;
    }

    cout << endl;
  }
  catch (const odb::exception& e)
  {
    cerr << e.what () << endl;
    return 1;
  }
}
