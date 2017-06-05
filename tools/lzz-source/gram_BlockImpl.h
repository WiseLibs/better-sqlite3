// gram_BlockImpl.h
//

#ifndef LZZ_gram_BlockImpl_h
#define LZZ_gram_BlockImpl_h
// util
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  class BlockImpl
  {
    util::Loc m_loc;
  public:
    BlockImpl (util::Loc const & loc);
    virtual ~ BlockImpl ();
    virtual bool isCharBlock () const = 0;
    bool isTokenBlock () const;
    void setLoc (util::Loc const & loc);
    util::Loc const & getLoc () const;
    virtual util::String toString () const = 0;
    virtual void trim ();
    virtual bool isEmpty () const = 0;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_BlockImpl.inl"
#endif
#endif
