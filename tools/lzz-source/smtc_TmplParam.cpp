// smtc_TmplParam.cpp
//

#include "smtc_TmplParam.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TmplParam.inl"
#endif
// semantic
#include "smtc_NameToString.h"
#include "smtc_ParamSetToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  TmplParam::TmplParam (NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & def_name)
    : Param (name), m_param_set (param_set), m_def_name (def_name)
    {}
}
namespace smtc
{
  TmplParam::~ TmplParam ()
    {}
}
namespace smtc
{
  util::String TmplParam::toString (bool is_decl) const
    {
      using namespace util;
      String str = "template";
      appendWithSpace (str, '<');
      str += paramSetToString (m_param_set, is_decl);
      if (str [str.length () - 1] == '>')
      {
        str += ' ';
      }
      str += '>';
      appendWithSpace (str, "class");
      appendWithSpace (str, nameToString (getName ()));
      if (is_decl && m_def_name.isSet ())
      {
        appendWithSpace (str, '=');
        appendWithSpace (str, nameToString (m_def_name));
      }
      return str;
    }
}
#undef LZZ_INLINE
