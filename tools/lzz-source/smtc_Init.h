// smtc_Init.h
//

#ifndef LZZ_smtc_Init_h
#define LZZ_smtc_Init_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_SectionKind.h"

// util
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Init
  {
    util::Loc m_loc;
  public:
    Init (util::Loc const & loc);
    virtual ~ Init ();
    util::Loc const & getLoc () const;
    virtual bool isCopy () const = 0;
    bool isDirect () const;
    virtual util::String toString () const = 0;
    virtual void print (FilePtr const & file, SectionKind skind) const = 0;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Init.inl"
#endif
#endif
