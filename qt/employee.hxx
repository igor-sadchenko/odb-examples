// file      : qt/employee.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef EMPLOYEE_HXX
#define EMPLOYEE_HXX

#include <vector>

#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QSharedPointer>

#include <odb/core.hxx>

#include <odb/qt/lazy-ptr.hxx>

// Forward declarations.
//
class employer;
class employee;

typedef std::vector<QLazyWeakPointer<employee> > employees;

#pragma db object
class employer
{
public:
  employer (const QString& name)
      : name_ (name)
  {
  }

  const QString&
  name () const
  {
    return name_;
  }

  // Employees of this employer.
  //
  typedef ::employees employees_type;

  const employees_type&
  employees () const
  {
    return employees_;
  }

  employees_type&
  employees ()
  {
    return employees_;
  }

private:
  friend class odb::access;

  employer () {}

  #pragma db id
  QString name_;

  #pragma db not_null inverse(employer_)
  employees_type employees_;
};

#pragma db object
class employee
{
public:
  typedef ::employer employer_type;

  employee (const QString& first,
            const QString& last,
            const QDate& born,
            const QByteArray& public_key,
            QSharedPointer<employer_type> employer)
      : first_ (first),
        last_ (last),
        born_ (born),
        public_key_ (public_key),
        employer_ (employer)
  {
  }

  // Name.
  //
  const QString&
  first () const
  {
    return first_;
  }

  const QString&
  last () const
  {
    return last_;
  }

  // Date of birth.
  //
  const QDate&
  born () const
  {
    return born_;
  }

  // Public key.
  //
  const QByteArray&
  public_key () const
  {
    return public_key_;
  }

  // Employer.
  //
  QLazySharedPointer<employer_type>
  employer () const
  {
    return employer_;
  }

  void
  employer (QSharedPointer<employer_type> employer)
  {
    employer_ = employer;
  }

private:
  friend class odb::access;

  employee () {}

  #pragma db id auto
  unsigned long id_;

  QString first_;
  QString last_;

  QDate born_;

  QByteArray public_key_;

  #pragma db not_null
  QLazySharedPointer<employer_type> employer_;
};

#endif // EMPLOYEE_HXX
