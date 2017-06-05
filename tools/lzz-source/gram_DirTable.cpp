// gram_DirTable.cpp
//

#include "gram_DirTable.h"
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
  struct DirTable
  {
    util::IntDataTable data_table;
    DirTable ();
    bool isDir (util::Ident const & name, DirKind & kind);
  };
}
namespace
{
  DirTable::DirTable ()
    {
      // populate database
      struct
      {
        char const * name;
        int kind;
      }
      database [] =
      {
        { "define", DEFINE_DIR },
        { "include", INCLUDE_DIR },
        { "insert", INSERT_DIR },
        { "if", IF_DIR },
        { "ifdef", IFDEF_DIR },
        { "ifndef", IFNDEF_DIR },
        { "elif", ELIF_DIR },
        { "else", ELSE_DIR },
        { "endif", ENDIF_DIR },
        { "undef", UNDEF_DIR },
        { "line", LINE_DIR },
        { "error", ERROR_DIR },
        { "pragma", PRAGMA_DIR },
        { "warning", WARNING_DIR },
        { "hdr", HDR_DIR },
        { "src", SRC_DIR },
        { "inl", INL_DIR },
        { "tpl", TPL_DIR },
        { "tnl", TNL_DIR },
        { "header", HDR_DIR },
        { "source", SRC_DIR },
        { "inline", INL_DIR },
        { "template", TPL_DIR },
        { "template_inline", TNL_DIR },
      };
      for (int i = 0; i < sizeof (database) / sizeof (database [0]); ++ i)
      {
        data_table.addData (util::getIdent (database [i].name).getHandle (), database [i].kind);
      }
    }
}
namespace
{
  bool DirTable::isDir (util::Ident const & name, DirKind & kind)
    {
      bool result = false;
      util::IntDataTableFindResult find_result = data_table.findData (name.getHandle ());
      if (find_result.hasData ())
      {
        kind = (DirKind) find_result.getData ();
        result = true;
      }
      return result;
    }
}
namespace gram
{
  bool isDir (util::Ident const & name, DirKind & kind)
  {
    static DirTable table;
    return table.isDir (name, kind);
  }
}
#undef LZZ_INLINE
