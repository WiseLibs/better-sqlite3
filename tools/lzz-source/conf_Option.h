// conf_Option.h
//

#ifndef LZZ_conf_Option_h
#define LZZ_conf_Option_h
// util
#include "util_IdentList.h"
#include "util_StringVector.h"
#define LZZ_INLINE inline
namespace conf
{
  enum OptionKind
  {
    STRING_OPTION,
    IDENT_LIST_OPTION,
    INT_OPTION,
    BOOL_OPTION,
    STRING_SET_OPTION
  };
}
namespace conf
{
  class Option
  {
  public:
    Option ();
    virtual OptionKind getKind () const = 0;
    virtual void setValue (util::String const & value) = 0;
    virtual util::String getValueAsString () const = 0;
    bool isBoolOption () const;
  };
}
namespace conf
{
  class StringOption : public Option
  {
    util::String m_value;
  public:
    StringOption (util::String const & default_value);
    OptionKind getKind () const;
    void setValue (util::String const & value);
    util::String getValueAsString () const;
    util::String const & getValue () const;
  };
}
namespace conf
{
  class IdentListOption : public Option
  {
    util::IdentList m_value;
  public:
    IdentListOption ();
    OptionKind getKind () const;
    void setValue (util::String const & value);
    util::String getValueAsString () const;
    bool hasValue () const;
    util::IdentList const & getValue () const;
  };
}
namespace conf
{
  class BoolOption : public Option
  {
    bool m_value;
  public:
    BoolOption (bool default_value);
    OptionKind getKind () const;
    void setValue (util::String const & value);
    util::String getValueAsString () const;
    void setValue (bool value);
    bool getValue () const;
  };
}
namespace conf
{
  class IntOption : public Option
  {
    int m_value;
  public:
    IntOption (int default_value);
    OptionKind getKind () const;
    void setValue (util::String const & value);
    util::String getValueAsString () const;
    void setValue (int value);
    int getValue () const;
  };
}
namespace conf
{
  class StringSetOption : public Option
  {
    util::StringVector m_value_set;
  public:
    StringSetOption ();
    OptionKind getKind () const;
    void setValue (util::String const & value);
    util::String getValueAsString () const;
    util::StringVector const & getValue () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "conf_Option.inl"
#endif
#endif
