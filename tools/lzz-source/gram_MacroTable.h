// gram_MacroTable.h
//

#ifndef LZZ_gram_MacroTable_h
#define LZZ_gram_MacroTable_h
// gram
#include "gram_MacroPtrDataTable.h"

// util
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace gram
{
  void resetMacroTable ();
}
namespace gram
{
  MacroPtrDataTable const & getMacroDataTable ();
}
namespace gram
{
  bool isPersistentMacro (util::Ident const & ident);
}
namespace gram
{
  void addMacro (MacroPtr const & macro);
}
namespace gram
{
  bool isMacro (util::Ident const & name);
}
namespace gram
{
  bool isMacro (util::Ident const & name, MacroPtr & macro);
}
namespace gram
{
  void delMacro (util::Ident const & name);
}
#undef LZZ_INLINE
#endif
