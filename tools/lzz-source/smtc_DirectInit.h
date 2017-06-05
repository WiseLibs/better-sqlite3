// smtc_DirectInit.h
//

#ifndef LZZ_smtc_DirectInit_h
#define LZZ_smtc_DirectInit_h
// semantic
#include "smtc_Init.h"

// gram
#include "gram_BlockVector.h"
#define LZZ_INLINE inline
namespace smtc
{
  class DirectInit : public Init
  {
    gram::BlockVector m_block_set;
  public:
    DirectInit (util::Loc const & loc, gram::BlockVector const & block_set);
    ~ DirectInit ();
    bool isCopy () const;
    gram::BlockVector const & getBlockSet () const;
    util::String toString () const;
    void print (FilePtr const & file, SectionKind skind) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_DirectInit.inl"
#endif
#endif
