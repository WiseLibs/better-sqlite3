// smtc_PrintClassDefn.h
//

#ifndef LZZ_smtc_PrintClassDefn_h
#define LZZ_smtc_PrintClassDefn_h
// semantic
#include "smtc_ClassDefnPtr.h"
#include "smtc_FilePtr.h"
#include "smtc_NsPtr.h"
#include "smtc_PrintClassDecl.h"
#define LZZ_INLINE inline
namespace smtc
{
  struct PrintClassDefn : PrintClassDecl
  {
    void print (FilePtr const & file, ClassDefnPtr const & class_defn, NsPtr const & ns) const;
    void print (FilePtr const & file, ClassDefnPtr const & class_defn) const;
  protected:
    void printHead (FilePtr const & file, ClassDefnPtr const & class_defn) const;
  };
}
#undef LZZ_INLINE
#endif
