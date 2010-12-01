// file      : container/person.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef PERSON_HXX
#define PERSON_HXX

#include <set>
#include <map>
#include <vector>
#include <string>

#include <odb/core.hxx>

#pragma db object
class person
{
public:
  person (const std::string& first, const std::string& last)
      : first_ (first), last_ (last)
  {
  }

  const std::string&
  first () const
  {
    return first_;
  }

  const std::string&
  last () const
  {
    return last_;
  }

  // Nicknames.
  //
  typedef std::vector<std::string> name_list;

  const name_list&
  nicknames () const
  {
    return nicknames_;
  }

  name_list&
  nicknames ()
  {
    return nicknames_;
  }

  // Emails.
  //
  typedef std::set<std::string> email_set;

  const email_set&
  emails () const
  {
    return emails_;
  }

  email_set&
  emails ()
  {
    return emails_;
  }

  // Age-to-weight map.
  //
  typedef std::map<unsigned short, float> age_weight_map;

  const age_weight_map&
  age_weight () const
  {
    return age_weight_;
  }

  age_weight_map&
  age_weight ()
  {
    return age_weight_;
  }

private:
  friend class odb::access;

  person () {}

  #pragma db id auto
  unsigned long id_;

  std::string first_;
  std::string last_;

  name_list nicknames_;
  email_set emails_;
  age_weight_map age_weight_;
};

#endif // PERSON_HXX
