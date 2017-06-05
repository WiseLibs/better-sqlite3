// conf_Option.cpp
//

#include "conf_Option.h"
#ifndef LZZ_ENABLE_INLINE
#include "conf_Option.inl"
#endif
// std lib
#include <cstdlib>

// util
#include "util_GetIdent.h"
#include "util_IntToString.h"
#define LZZ_INLINE inline
namespace conf
{
  using namespace util;
}
namespace conf
{
  Option::Option ()
    {}
}
namespace conf
{
  bool Option::isBoolOption () const
    {
      return getKind () == BOOL_OPTION;
    }
}
namespace conf
{
  StringOption::StringOption (util::String const & default_value)
    : m_value (default_value)
    {}
}
namespace conf
{
  OptionKind StringOption::getKind () const
    {
      return STRING_OPTION;
    }
}
namespace conf
{
  void StringOption::setValue (util::String const & value)
    {
      m_value = value;
    }
}
namespace conf
{
  util::String StringOption::getValueAsString () const
    {
      return m_value;
    }
}
namespace conf
{
  IdentListOption::IdentListOption ()
    {}
}
namespace conf
{
  OptionKind IdentListOption::getKind () const
    {
      return IDENT_LIST_OPTION;
    }
}
namespace conf
{
  void IdentListOption::setValue (util::String const & value)
    {
      m_value.push_back (util::getIdent (value.c_str ()));
    }
}
namespace conf
{
  util::String IdentListOption::getValueAsString () const
    {
      util::String str;
      if (! m_value.empty ())
      {
        for (IdentListConstIter i = m_value.begin ();;)
        {
          str += (* i).c_str ();
          if (++ i == m_value.end ())
          {
            break;
          }
          str += ' ';
        }
      }
      return str;
    }
}
namespace conf
{
  bool IdentListOption::hasValue () const
    {
      return ! m_value.empty ();
    }
}
namespace conf
{
  BoolOption::BoolOption (bool default_value)
    : m_value (default_value)
    {}
}
namespace conf
{
  OptionKind BoolOption::getKind () const
    {
      return BOOL_OPTION;
    }
}
namespace conf
{
  void BoolOption::setValue (util::String const & value)
    {
      m_value = (value == "yes" || value == "on");
    }
}
namespace conf
{
  util::String BoolOption::getValueAsString () const
    {
      return m_value ? "on" : "off";
    }
}
namespace conf
{
  void BoolOption::setValue (bool value)
    {
      m_value = value;
    }
}
namespace conf
{
  IntOption::IntOption (int default_value)
    : m_value (default_value)
    {}
}
namespace conf
{
  OptionKind IntOption::getKind () const
    {
      return INT_OPTION;
    }
}
namespace conf
{
  void IntOption::setValue (util::String const & value)
    {
      m_value = atoi (value.c_str ());
    }
}
namespace conf
{
  util::String IntOption::getValueAsString () const
    {
      return util::intToString (m_value);
    }
}
namespace conf
{
  void IntOption::setValue (int value)
    {
      m_value = value;
    }
}
namespace conf
{
  StringSetOption::StringSetOption ()
    {}
}
namespace conf
{
  OptionKind StringSetOption::getKind () const
    {
      return STRING_SET_OPTION;
    }
}
namespace conf
{
  void StringSetOption::setValue (util::String const & value)
    {
      m_value_set.push_back (value);
    }
}
namespace conf
{
  util::String StringSetOption::getValueAsString () const
    {
      return util::String ();
    }
}
#undef LZZ_INLINE
