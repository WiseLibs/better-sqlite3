// smtc_FuncDefn.h
//

#ifndef LZZ_smtc_FuncDefn_h
#define LZZ_smtc_FuncDefn_h
// semantic
#include "smtc_CtorInitPtr.h"
#include "smtc_FuncDecl.h"
#include "smtc_TryBlockPtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDefn : public FuncDecl
  {
    CtorInitPtr m_ctor_init;
    gram::Block m_body;
    TryBlockPtr m_try_block;
  public:
    FuncDefn (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec, CtorInitPtr const & ctor_init, gram::Block const & body, TryBlockPtr const & try_block);
    ~ FuncDefn ();
    CtorInitPtr const & getCtorInit () const;
    gram::Block const & getBody () const;
    TryBlockPtr const & getTryBlock () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FuncDefn.inl"
#endif
#endif
