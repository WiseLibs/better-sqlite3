// util_IdentTable.h
//

#ifndef LZZ_util_IdentTable_h
#define LZZ_util_IdentTable_h
// util
#include "util_CharKeyTable.h"
#include "util_Ident.h"
#define LZZ_INLINE inline
namespace util
{
  class IdentTable
  {
    KeyTable <char> m_table;
  public:
    IdentTable ();
    ~ IdentTable ();
    void push (char ch);
    void push (char const * str);
    Ident getIdent ();
    Ident getIdent (char const * str);
  private:
    IdentTable (IdentTable const & id_table);
  };
}
#undef LZZ_INLINE
#endif
