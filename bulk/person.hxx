// file      : hello/person.hxx
// copyright : not copyrighted - public domain

#ifndef PERSON_HXX
#define PERSON_HXX

#include <string>

#include <odb/core.hxx>

#pragma db object bulk(3)
class person
{
public:
  #pragma db id auto
  unsigned long id;

  #pragma db unique
  unsigned int num;

#ifdef ODB_DATABASE_MSSQL
  #pragma db type("VARCHAR(max)")
#else
  #pragma db type("CLOB")
#endif
  std::string str;
};

#endif // PERSON_HXX
