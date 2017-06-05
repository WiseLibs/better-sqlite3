// gram_PrepKeywordTable.cpp
//

#include "gram_PrepKeywordTable.h"
// gram
#include "gram_TokenNumber.h"

// util
#include "util_GetIdent.h"
#include "util_IntDataTable.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct PrepKeywordTable
  {
    util::IntDataTable data_table;
    PrepKeywordTable ();
    bool isKeyword (util::Ident const & name, int & kind);
  };
}
namespace
{
  PrepKeywordTable::PrepKeywordTable ()
    {
      // populate database
      struct
      {
        char const * name;
        int kind;
      }
      database [] =
      {
        // allow new and delete to be used as identifiers  
        /*
        { "new",              NEW },
        { "delete",           DELETE },
        */
        { "and",              AND_TOKEN },
        { "bitor",            BITOR_TOKEN },
        { "or",               OR_TOKEN },
        { "xor",              XOR_TOKEN },
        { "compl",            BITNOT_TOKEN },
        { "bitand",           BITAND_TOKEN },
        { "not",              NOT_TOKEN },
        { "not_eq",           NOTEQ_TOKEN },
        { "and_eq",           BITAND_ASSIGN_TOKEN },
        { "or_eq",            BITOR_ASSIGN_TOKEN },
        { "xor_eq",           XOR_ASSIGN_TOKEN },
      };
      for (int i = 0; i < sizeof (database) / sizeof (database [0]); ++ i)
      {
        data_table.addData (util::getIdent (database [i].name).getHandle (), database [i].kind);
      }
    }
}
namespace
{
  bool PrepKeywordTable::isKeyword (util::Ident const & name, int & kind)
    {
      bool result = false;
      util::IntDataTableFindResult find_result = data_table.findData (name.getHandle ());
      if (find_result.hasData ())
      {
        kind = find_result.getData ();
        result = true;
      }
      return result;
    }
}
namespace gram
{
  bool isPrepKeyword (util::Ident const & name, int & kind)
  {
    static PrepKeywordTable table;
    return table.isKeyword (name, kind);
  }
}
#undef LZZ_INLINE
