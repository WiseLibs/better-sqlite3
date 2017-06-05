// smtc_TypeParam.cpp
//

#include "smtc_TypeParam.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_TypeParam.inl"
#endif
// semantic
#include "smtc_NameToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  TypeParam::TypeParam (NamePtr const & name, CvType const & def_type)
    : Param (name), m_def_type (def_type)
    {}
}
namespace smtc
{
  TypeParam::~ TypeParam ()
    {}
}
namespace smtc
{
  util::String TypeParam::toString (bool is_decl) const
    {
      using namespace util;
      String str = "typename";
      appendWithSpace (str, nameToString (getName ()));
      if (is_decl && m_def_type.isSet ())
      {
        appendWithSpace (str, '=');
        appendWithSpace (str, m_def_type.toString ());
      }
      return str;
    }
}
#undef LZZ_INLINE
