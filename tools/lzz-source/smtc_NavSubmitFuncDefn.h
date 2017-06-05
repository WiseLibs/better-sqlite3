// smtc_NavSubmitFuncDefn.h
//

#ifndef LZZ_smtc_NavSubmitFuncDefn_h
#define LZZ_smtc_NavSubmitFuncDefn_h
// semantic
#include "smtc_FuncDecl.h"
#include "smtc_ObjPtrVector.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  class NavSubmitFuncDefn : public FuncDecl
  {
    NamePtr m_nav_name;
    ObjPtrVector m_obj_set;
    gram::Block m_ret_stmt;
  public:
    NavSubmitFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, NamePtr const & nav_name, ObjPtrVector const & obj_set, gram::Block const & ret_stmt);
    ~ NavSubmitFuncDefn ();
    NamePtr const & getNavName () const;
    ObjPtrVector const & getObjSet () const;
    gram::Block const & getReturnStmt () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_NavSubmitFuncDefn.inl"
#endif
#endif
