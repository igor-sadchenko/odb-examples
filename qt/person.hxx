// file      : qt/person.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef EMPLOYEE_HXX
#define EMPLOYEE_HXX

#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>

#pragma db object
struct time_punchcard
{
  #pragma db id auto
  unsigned long id;

  QDateTime date_time;
};

#pragma db object
struct person
{
  bool
  operator== (const person& x) const
  {
    return name == x.name &&
      date_of_birth == x.date_of_birth &&
      time_of_birth == x.time_of_birth;
  }

  #pragma db id
  QString name;

  #pragma db type("DATE NOT NULL")
  QDate date_of_birth;
  QTime time_of_birth;
};

#endif // EMPLOYEE_HXX
