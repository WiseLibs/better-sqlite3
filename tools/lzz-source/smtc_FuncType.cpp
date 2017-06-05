// smtc_FuncType.cpp
//

#include "smtc_FuncType.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FuncType.inl"
#endif
// semantic
#include "smtc_AppendCv.h"
#include "smtc_CvTypeSetToString.h"
#include "smtc_ThrowSpecToString.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncType::FuncType (CvType const & ret_type, CvTypeVector const & param_type_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
    : m_ret_type (ret_type), m_param_type_set (param_type_set), m_vararg (vararg), m_cv (cv), m_throw_spec (throw_spec)
    {}
}
namespace smtc
{
  TypeKind FuncType::getKind () const
    {
      return FUNC_TYPE;
    }
}
namespace smtc
{
  util::String FuncType::toString (util::String const & dcl, bool c, bool v) const
    {
      using namespace util;
      String str;
      if (! dcl.empty ())
      {
        str += '(';
        str += dcl;
        str += ')';
      }
      appendWithSpace (str, '(');
      str += cvTypeSetToString (m_param_type_set);
      if (m_vararg)
      {
        if (! m_param_type_set.empty ())
        {
          str += ", ";
        }
        str += "...";
      }
      str += ')';
      appendCv (str, m_cv);
      if (m_throw_spec.isSet ())
      {
        appendWithSpace (str, throwSpecToString (m_throw_spec));
      }
      return m_ret_type.toString (str);
    }
}
#undef LZZ_INLINE
