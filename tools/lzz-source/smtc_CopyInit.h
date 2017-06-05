// smtc_CopyInit.h
//

#ifndef LZZ_smtc_CopyInit_h
#define LZZ_smtc_CopyInit_h
// semantic
#include "smtc_Init.h"

// gram
#include "gram_Block.h"
#define LZZ_INLINE inline
namespace smtc
{
  class CopyInit : public Init
  {
    gram::Block m_block;
  public:
    CopyInit (util::Loc const & loc, gram::Block const & block);
    ~ CopyInit ();
    bool isCopy () const;
    gram::Block const & getBlock () const;
    util::String toString () const;
    void print (FilePtr const & file, SectionKind skind) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_CopyInit.inl"
#endif
#endif
