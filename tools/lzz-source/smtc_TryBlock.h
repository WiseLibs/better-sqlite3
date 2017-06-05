// smtc_TryBlock.h
//

#ifndef LZZ_smtc_TryBlock_h
#define LZZ_smtc_TryBlock_h
// sematnic
#include "smtc_HandlerPtrVector.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TryBlock
  {
    util::Loc m_loc;
    HandlerPtrVector m_handler_seq;
  public:
    TryBlock (util::Loc const & loc, HandlerPtrVector const & handler_seq);
    ~ TryBlock ();
    util::Loc const & getLoc () const;
    HandlerPtrVector const & getHandlerSeq () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TryBlock.inl"
#endif
#endif
