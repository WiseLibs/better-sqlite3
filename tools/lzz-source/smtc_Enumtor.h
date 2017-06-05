// smtc_Enumtor.h
//

#ifndef LZZ_smtc_Enumtor_h
#define LZZ_smtc_Enumtor_h
// semantic
#include "smtc_NamePtr.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Enumtor
  {
    NamePtr m_name;
    gram::Block m_init;
  public:
    Enumtor (NamePtr const & name, gram::Block const & init);
    ~ Enumtor ();
    NamePtr const & getName () const;
    bool hasInit () const;
    gram::Block const & getInit () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Enumtor.inl"
#endif
#endif
