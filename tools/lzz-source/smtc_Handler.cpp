// smtc_Handler.cpp
//

#include "smtc_Handler.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_Handler.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  Handler::Handler (util::Loc const & loc, ParamPtr const & catch_decl, gram::Block const & body)
    : m_loc (loc), m_catch_decl (catch_decl), m_body (body)
    {}
}
namespace smtc
{
  Handler::~ Handler ()
    {}
}
#undef LZZ_INLINE
