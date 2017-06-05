// smtc_PrintTmplSpec.h
//

#ifndef LZZ_smtc_PrintTmplSpec_h
#define LZZ_smtc_PrintTmplSpec_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_SectionKind.h"
#include "smtc_TmplSpecPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printTmplSpec (FilePtr const & file, SectionKind skind, TmplSpecPtr const & tmpl_spec, bool is_decl);
}
namespace smtc
{
  struct PrintTmplSpec
  {
    FilePtr const & file;
    SectionKind skind;
    bool is_decl;
    void operator () (TmplSpecPtr const & tmpl_spec) const;
  public:
    explicit PrintTmplSpec (FilePtr const & file, SectionKind skind, bool is_decl);
    ~ PrintTmplSpec ();
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplSpec.inl"
#endif
#endif
