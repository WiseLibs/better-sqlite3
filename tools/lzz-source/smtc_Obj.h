// smtc_Obj.h
//

#ifndef LZZ_smtc_Obj_h
#define LZZ_smtc_Obj_h
// semantic
#include "smtc_CvType.h"
#include "smtc_InitPtr.h"
#include "smtc_Linkage.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Obj
  {
    Linkage m_linkage;
    int m_flags;
    CvType m_cv_type;
    NamePtr m_name;
    InitPtr m_init;
  public:
    Obj (Linkage const & linkage, int flags, CvType const & cv_type, NamePtr const & name, InitPtr const & init);
    ~ Obj ();
    bool hasLinkage () const;
    Linkage const & getLinkage () const;
    int getFlags () const;
    bool isStatic () const;
    bool isExtern () const;
    bool hasInit () const;
    CvType const & getCvType () const;
    NamePtr const & getName () const;
    InitPtr const & getInit () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Obj.inl"
#endif
#endif
