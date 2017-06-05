// smtc_FuncDecl.cpp
//

#include "smtc_FuncDecl.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_FuncDecl.inl"
#endif
// semantic
#include "smtc_SpecFlags.h"

// util
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace smtc
{
  FuncDecl::FuncDecl (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec)
    : m_linkage (linkage), m_flags (flags), m_ret_type (ret_type), m_name (name), m_param_set (param_set), m_vararg (vararg), m_cv (cv), m_throw_spec (throw_spec)
    {}
}
namespace smtc
{
  FuncDecl::~ FuncDecl ()
    {}
}
namespace smtc
{
  bool FuncDecl::isPure () const
    {
      return util::hasFlag (m_flags, PURE_SPEC);
    }
}
namespace smtc
{
  bool FuncDecl::isStatic () const
    {
      return util::hasFlag (m_flags, STATIC_SPEC);
    }
}
namespace smtc
{
  bool FuncDecl::isInline () const
    {
      return util::hasFlag (m_flags, INLINE_SPEC);
    }
}
namespace smtc
{
  bool FuncDecl::isExtern () const
    {
      return util::hasFlag (m_flags, EXTERN_SPEC);
    }
}
namespace smtc
{
  void FuncDecl::setAltReturnType (CvType const & alt_ret_type)
    {
      m_alt_ret_type = alt_ret_type;
    }
}
#undef LZZ_INLINE
