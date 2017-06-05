// smtc_PrintHandler.h
//

#ifndef LZZ_smtc_PrintHandler_h
#define LZZ_smtc_PrintHandler_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_HandlerPtr.h"
#include "smtc_SectionKind.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printHandler (FilePtr const & file, SectionKind skind, HandlerPtr const & handler);
}
namespace smtc
{
  struct PrintHandler
  {
    FilePtr const & file;
    SectionKind skind;
    void operator () (HandlerPtr const & handler) const;
  public:
    explicit PrintHandler (FilePtr const & file, SectionKind skind);
    ~ PrintHandler ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintHandler.inl"
#endif
#endif
