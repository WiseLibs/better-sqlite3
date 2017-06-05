// smtc_PrintTmplSpecSet.cpp
//

#include "smtc_PrintTmplSpecSet.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_PrintTmplSpec.h"
#define LZZ_INLINE inline
namespace smtc
{
  void printTmplSpecSet (FilePtr const & file, SectionKind skind, TmplSpecPtrVector const & tmpl_spec_set, bool is_decl)
  {
    // first tmpl spec set is the closest to decl so print in reverse 
    std::for_each (tmpl_spec_set.rbegin (), tmpl_spec_set.rend (), PrintTmplSpec (file, skind, is_decl));
  }
}
#undef LZZ_INLINE
