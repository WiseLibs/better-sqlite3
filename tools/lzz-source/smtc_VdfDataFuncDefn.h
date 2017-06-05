// smtc_VdfDataFuncDefn.h
//

#ifndef LZZ_smtc_VdfDataFuncDefn_h
#define LZZ_smtc_VdfDataFuncDefn_h
// semantic
#include "smtc_FuncDecl.h"
#include "smtc_ObjPtrVector.h"

// gram
#include "gram_Block.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class VdfDataFuncDefn : public FuncDecl
  {
    util::String m_cmt;
    ObjPtrVector m_obj_set;
    gram::Block m_ret_stmt;
  public:
    VdfDataFuncDefn (int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, util::String const & cmt);
    ~ VdfDataFuncDefn ();
    util::String const & getComment () const;
    void addObj (ObjPtr const & obj);
    ObjPtrVector const & getObjSet () const;
    bool hasReturnStmt () const;
    gram::Block const & getReturnStmt () const;
    void setReturnStmt (gram::Block const & stmt);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_VdfDataFuncDefn.inl"
#endif
#endif
