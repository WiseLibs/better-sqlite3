// smtc_PrintTmplClassDefn.h
//

#ifndef LZZ_smtc_PrintTmplClassDefn_h
#define LZZ_smtc_PrintTmplClassDefn_h
// semantic
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_PrintClassDefn.h"
#include "smtc_TmplClassDefnPtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintTmplClassDefn : PrintClassDefn
  {
    void print (FilePtr const & file, TmplClassDefnPtr const & tmpl_class_defn, NsPtr const & ns) const;
    void print (FilePtr const & file, TmplClassDefnPtr const & tmpl_class_defn) const;
  };
}
#undef LZZ_INLINE
#endif
