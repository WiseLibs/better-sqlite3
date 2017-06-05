// smtc_DirectInit.cpp
//

#include "smtc_DirectInit.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_DirectInit.inl"
#endif
// semantic
#include "smtc_ArgListToString.h"
#include "smtc_File.h"
#define LZZ_INLINE inline
namespace smtc
{
  DirectInit::~ DirectInit ()
    {}
}
namespace smtc
{
  bool DirectInit::isCopy () const
    {
      return false;
    }
}
namespace smtc
{
  util::String DirectInit::toString () const
    {
      return argListToString (m_block_set);
    }
}
namespace smtc
{
  void DirectInit::print (FilePtr const & file, SectionKind skind) const
    {
      file->getStream (skind) << '(' << toString () << ')';
    }
}
#undef LZZ_INLINE
