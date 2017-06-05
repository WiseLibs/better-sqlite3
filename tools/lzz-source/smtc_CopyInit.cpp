// smtc_CopyInit.cpp
//

#include "smtc_CopyInit.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_CopyInit.inl"
#endif
// semantic
#include "smtc_File.h"
#include "smtc_PrintCode.h"
#define LZZ_INLINE inline
namespace smtc
{
  CopyInit::~ CopyInit ()
    {}
}
namespace smtc
{
  bool CopyInit::isCopy () const
    {
      return true;
    }
}
namespace smtc
{
  util::String CopyInit::toString () const
    {
      // a bit of a hack: block is used as a member init so OK to trim
      m_block.trim ();
      return m_block.toString ();
    }
}
namespace smtc
{
  void CopyInit::print (FilePtr const & file, SectionKind skind) const
    {
      file->getStream (skind) << '=';
      printBlockAtLoc (file, skind, m_block);
    }
}
#undef LZZ_INLINE
