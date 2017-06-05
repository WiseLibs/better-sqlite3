// smtc_FuncDecl.h
//

#ifndef LZZ_smtc_FuncDecl_h
#define LZZ_smtc_FuncDecl_h
// semantic
#include "smtc_CvType.h"
#include "smtc_Linkage.h"
#include "smtc_NamePtr.h"
#include "smtc_ParamPtrVector.h"
#include "smtc_ThrowSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncDecl
  {
    Linkage m_linkage;
    int m_flags;
    CvType m_ret_type;
    NamePtr m_name;
    ParamPtrVector m_param_set;
    bool m_vararg;
    Cv m_cv;
    ThrowSpecPtr m_throw_spec;
    CvType m_alt_ret_type;
  public:
    FuncDecl (Linkage const & linkage, int flags, CvType const & ret_type, NamePtr const & name, ParamPtrVector const & param_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
    virtual ~ FuncDecl ();
    bool hasLinkage () const;
    Linkage const & getLinkage () const;
    int getFlags () const;
    bool isPure () const;
    bool isStatic () const;
    bool isInline () const;
    bool isExtern () const;
    CvType const & getReturnType () const;
    NamePtr const & getName () const;
    ParamPtrVector const & getParamSet () const;
    bool hasVarArg () const;
    Cv const & getCv () const;
    ThrowSpecPtr const & getThrowSpec () const;
    void setAltReturnType (CvType const & alt_ret_type);
    bool hasAltReturnType () const;
    CvType const & getAltReturnType () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FuncDecl.inl"
#endif
#endif
