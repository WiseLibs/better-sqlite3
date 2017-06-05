// smtc_PrintObjDefn.cpp
//

#include "smtc_PrintObjDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintObjDefn.inl"
#endif
// semantic
#define LZZ_INLINE inline
namespace smtc
{
  void PrintObjDefn::print (FilePtr const & file, SectionKind skind, ObjPtr const & obj, NsPtr const & ns) const
    {
      PrintObjDecl::print (file, skind, obj, ns);
    }
}
namespace smtc
{
  void PrintObjDefn::print (FilePtr const & file, SectionKind skind, ObjPtr const & obj) const
    {
      PrintObjDecl::print (file, skind, obj);
    }
}
#undef LZZ_INLINE
