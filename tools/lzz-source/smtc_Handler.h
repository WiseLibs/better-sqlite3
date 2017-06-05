// smtc_Handler.h
//

#ifndef LZZ_smtc_Handler_h
#define LZZ_smtc_Handler_h
// semantic
#include "smtc_ParamPtr.h"

// gram
#include "gram_Block.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Handler
  {
    util::Loc m_loc;
    ParamPtr m_catch_decl;
    gram::Block m_body;
  public:
    Handler (util::Loc const & loc, ParamPtr const & catch_decl, gram::Block const & body);
    ~ Handler ();
    util::Loc const & getLoc () const;
    bool hasCatchParam () const;
    ParamPtr const & getCatchParam () const;
    gram::Block const & getBody () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Handler.inl"
#endif
#endif
