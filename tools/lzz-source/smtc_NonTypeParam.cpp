// smtc_NonTypeParam.cpp
//

#include "smtc_NonTypeParam.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_NonTypeParam.inl"
#endif
// semantic
#include "smtc_SpecFlagsToString.h"
#include "smtc_NameToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  NonTypeParam::~ NonTypeParam ()
    {}
}
namespace smtc
{
  int NonTypeParam::getDeclSpec () const
    {
      return m_flags;
    }
}
namespace smtc
{
  util::String NonTypeParam::toString (bool is_decl) const
    {
      using namespace util;
      String str = specFlagsToString (m_flags);
      String dcl_str = nameToString (getName ());
      appendWithSpace (str, m_cv_type.toString (dcl_str));
      if (is_decl && m_def_arg.isSet ())
      {
        appendWithSpace (str, '=');
        appendWithSpace (str, m_def_arg.toString ());
      }
      return str;
    }
}
#undef LZZ_INLINE
