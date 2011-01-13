// file      : composite/person.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef PERSON_HXX
#define PERSON_HXX

#include <vector>
#include <string>

#include <odb/core.hxx>

#pragma db value
class basic_name
{
public:
  basic_name (const std::string& first, const std::string& last)
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

private:
  friend class odb::access;

  basic_name () {} // Needed for storing basic_name in containers.

  std::string first_;
  std::string last_;
};

typedef std::vector<basic_name> basic_names;


#pragma db value
class name_extras
{
public:
  // Nickname.
  //
  const std::string&
  nickname () const
  {
    return nickname_;
  }

  void
  nickname (const std::string& nickname)
  {
    nickname_ = nickname;
  }

  // Aliases.
  //
  const basic_names&
  aliases () const
  {
    return aliases_;
  }

  basic_names&
  aliases ()
  {
    return aliases_;
  }

private:
  friend class odb::access;

  std::string nickname_;
  basic_names aliases_;
};


#pragma db value
class name: public basic_name
{
public:
  name (const std::string& first,
        const std::string& last,
        const std::string& title)
      : basic_name (first, last), title_ (title)
  {
  }

  // Title.
  //
  const std::string&
  title () const
  {
    return title_;
  }

  // Extras.
  //
  const name_extras&
  extras () const
  {
    return extras_;
  }

  name_extras&
  extras ()
  {
    return extras_;
  }

private:
  friend class odb::access;

  std::string title_;
  name_extras extras_;
};


#pragma db object
class person
{
public:
  person (const std::string& first,
          const std::string& last,
          const std::string& title)
      : name_ (first, last, title)
  {
  }

  // Name.
  //
  typedef ::name name_type;

  const name_type&
  name () const
  {
    return name_;
  }

  name_type&
  name ()
  {
    return name_;
  }

private:
  friend class odb::access;

  person (): name_ ("", "", "") {}

  #pragma db id auto
  unsigned long id_;

  name_type name_;
};

#endif // PERSON_HXX
