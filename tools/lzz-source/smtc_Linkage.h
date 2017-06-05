// smtc_Linkage.h
//

#ifndef LZZ_smtc_Linkage_h
#define LZZ_smtc_Linkage_h
// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Linkage
  {
    util::Ident m_lang;
  public:
    Linkage ();
    explicit Linkage (util::Ident const & lang);
    bool isSet () const;
    util::Ident const & getLanguage () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Linkage.inl"
#endif
#endif
