// smtc_FuncType.h
//

#ifndef LZZ_smtc_FuncType_h
#define LZZ_smtc_FuncType_h
// semantic
#include "smtc_CvTypeVector.h"
#include "smtc_ThrowSpecPtr.h"
#include "smtc_Type.h"
#define LZZ_INLINE inline
namespace smtc
{
  class FuncType : public Type
  {
    CvType m_ret_type;
    CvTypeVector m_param_type_set;
    bool m_vararg;
    Cv m_cv;
    ThrowSpecPtr m_throw_spec;
  public:
    FuncType (CvType const & ret_type, CvTypeVector const & param_type_set, bool vararg, Cv const & cv, ThrowSpecPtr const & throw_spec);
    TypeKind getKind () const;
    util::String toString (util::String const & dcl, bool c, bool v) const;
    CvType const & getReturnCvType () const;
    CvTypeVector const & getParamTypeSet () const;
    bool hasVarArgs () const;
    Cv const & getCv () const;
    ThrowSpecPtr const & getThrowSpec () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_FuncType.inl"
#endif
#endif
