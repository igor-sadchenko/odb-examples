// file      : hello/driver.cxx
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

    //@@ Run all the tests with and without auto id (templatize)

    //person p[3];
    std::vector<person> p (5, person ());

    p[0].id = 1;
    p[0].num = 1;
    p[0].str = "aaa";

    p[1].id = 2;
    p[1].num = 2;
    p[1].str = "bbb";

    p[2].id = 3;
    p[2].num = 3;
    p[2].str = "ccc";

    p[3].id = 4;
    p[3].num = 4;
    p[3].str = "ccc";

    p[4].id = 5;
    p[4].num = 5;
    p[4].str = "ccc";

    std::vector<person*> pp (5);
    pp[0] = &p[0];
    pp[1] = &p[1];
    pp[2] = &p[2];
    pp[3] = &p[3];
    pp[4] = &p[4];

    {
      transaction t (db->begin ());

      t.tracer (stderr_tracer);

      //db->persist (p, p + 3);
      //db->persist (p.begin (), p.end ());

      try
      {
        db->persist (pp.begin (), pp.end ());
      }
      catch (const odb::multiple_exceptions& e)
      {
        if (!e.fatal ())
          cerr << e.what () << endl;
        else
          throw;
      }

      cerr << pp[0]->id << endl
           << pp[1]->id << endl
           << pp[2]->id << endl
           << pp[3]->id << endl
           << pp[4]->id << endl;


      // Test error detection in batch of 1.
      //
      try
      {
        //p[0].num += 100;
        db->persist (p.begin (), p.begin () + 1);
      }
      catch (const odb::multiple_exceptions& e)
      {
        cerr << e.what () << endl;
      }

      try
      {
        p[0].num += 200;
        //p[1].num += 200;
        db->persist (p.begin (), p.begin () + 2);
      }
      catch (const odb::multiple_exceptions& e)
      {
        cerr << e.what () << endl;
      }

      t.commit ();
    }

    {
      transaction t (db->begin ());

      auto_ptr<person> p1 (db->find<person> (1));
      auto_ptr<person> p2 (db->find<person> (2));
      auto_ptr<person> p3 (db->find<person> (3));
      auto_ptr<person> p4 (db->find<person> (4));
      auto_ptr<person> p5 (db->find<person> (5));

      if (p1.get ()) cerr << p1->id << " " << p1->num << " " << p1->str << endl;
      if (p2.get ()) cerr << p2->id << " " << p2->num << " " << p2->str << endl;
      if (p3.get ()) cerr << p3->id << " " << p3->num << " " << p3->str << endl;
      if (p4.get ()) cerr << p4->id << " " << p4->num << " " << p4->str << endl;
      if (p5.get ()) cerr << p5->id << " " << p5->num << " " << p5->str << endl;

      t.commit ();
    }

    // update()
    //
    {
      transaction t (db->begin ());
      t.tracer (stderr_tracer);

      p[0].num ++;
      p[1].num ++;
      p[2].num ++;
      p[3].num ++;
      p[4].num ++;


      p[0].num += 10;
      p[1].num += 10;
      p[2].num += 10;
      p[3].num += 10;
      p[4].num += 10;


      db->update (p.begin (), p.end ());

      /*
      {
        auto_ptr<person> a[2];
        a[0].reset (new person);
        a[1].reset (new person);

        *a[0] = p[0];
        a[0]->id = 1;

        *a[1] = p[1];
        a[1]->id = 2;
        a[1]->num += 10;

        db->update (a, a + sizeof (a) / sizeof (a[0]));
      }
      */


      t.commit ();
    }

    // Erase via id.
    //
#if 1
    {
      transaction t (db->begin ());
      t.tracer (stderr_tracer);

      unsigned long ids[] = {
        pp[0]->id,
        pp[1]->id,
        pp[2]->id,
        pp[3]->id//,
        /*
        pp[4]->id,

        123
        */

        /*
        123,
        pp[4]->id,
        125,

        126,
        pp[3]->id,
        127
        */
      };

      db->erase<person> (ids, ids + sizeof (ids)/sizeof (ids[0]));

      t.commit ();
    }
#endif

#if 0
    // Erase via references/pointers.
    //
    {
      transaction t (db->begin ());

      //db->erase (p.begin (), p.end ());

      /*
      {
        const std::vector<person>& cp (p);
        db->erase (cp.begin (), cp.end ());
      }
      */

      //db->erase (pp.begin (), pp.end ());

      /*
      {
        const std::vector<person*>& cpp (pp);
        db->erase (cpp.begin (), cpp.end ());
      }
      */

      {
        auto_ptr<person> a[2];
        a[0].reset (new person);
        a[1].reset (new person);

        a[0]->id = 1;
        a[1]->id = 2;

        db->erase (a, a + sizeof (a) / sizeof (a[0]));
      }

      t.commit ();
    }
#endif

  }
  catch (const odb::exception& e)
  {
    cerr << "'" << e.what () << "'" << endl;
    return 1;
  }
}
