// gram_MacroTable.cpp
//

#include "gram_MacroTable.h"
// std lib
#include <algorithm>
#include <cstdio>
#include <ctime>

// gram
#include "gram_BuildMacro.h"
#include "gram_CheckMacroRepSet.h"
#include "gram_CreateFileMacro.h"
#include "gram_CreateLineMacro.h"
#include "gram_CreateObjMacro.h"
#include "gram_GetIdent.h"
#include "gram_LexDefineLine.h"
#include "gram_Lexer.h"
#include "gram_Macro.h"
#include "gram_TokenNumber.h"

// basil
#include "basl_TokenVector.h"

// config
#include "conf_Config.h"

// util
#include "util_Exception.h"
#include "util_GetIdent.h"
#include "util_IdentVector.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  class MacroTable
  {
    MacroPtrDataTable data_table;
    util::IdentVector persistent_macro_set;
  public:
    MacroTable ();
    void reset ();
    bool isPersistentMacro (util::Ident const & ident);
    void addMacro (MacroPtr const & macro);
    bool isMacro (util::Ident const & name) const;
    bool isMacro (util::Ident const & name, MacroPtr & macro) const;
    void delMacro (util::Ident const & name);
    MacroPtrDataTable const & getDataTable () const;
  private:
    void addCmdMacro (util::String const & str);
    void addCmdMacroSet (util::StringVector const & str_set);
  };
}
namespace
{
  MacroTable & getMacroTable ();
}
namespace
{
  MacroTable::MacroTable ()
    {
      // initialize the persistent macro set since these will not change during parsing of the file
      util::StringVector const & str_set = conf::getOptionValue (conf::opt_persistent_macro_set);
      for (util::StringVectorConstIter beg = str_set.begin (), end = str_set.end (); beg != end; ++ beg)
      {
        persistent_macro_set.push_back (util::getIdent (* beg));
      }
    }
}
namespace
{
  void MacroTable::reset ()
    {
      // clear all entries
      data_table.clear ();

      // get time
      time_t t = time (0);

      // get time string from time, format will be like:
      //
      // 012345678901234567890123
      // Fri Feb  5 16:45:17 1999
      // 
      basl::TokenVector rep_set;
      char * str = ctime (& t);
      util::String lexeme_str;
      // __DATE__
      lexeme_str = '\"';
      lexeme_str.append (str +  4, 6);
      lexeme_str.append (str + 19, 5);
      lexeme_str+= '\"';
      rep_set.push_back (basl::Token (LITERAL_STRING_TOKEN, util::Loc (), getIdent (lexeme_str)));
      addMacro (createObjMacro (util::Loc (), getIdent ("__DATE__"), rep_set));
      rep_set.clear ();

      // __TIME__
      lexeme_str = '\"';
      lexeme_str.append (str + 11, 8);
      lexeme_str+= '\"';
      rep_set.push_back (basl::Token (LITERAL_STRING_TOKEN, util::Loc (), getIdent (lexeme_str)));
      addMacro (createObjMacro (util::Loc (), getIdent ("__TIME__"), rep_set));
      rep_set.clear ();

      // __FILE__
      addMacro (createFileMacro (util::Loc (), getIdent ("__FILE__")));

      // __LINE__
      addMacro (createLineMacro (util::Loc (), getIdent ("__LINE__")));

      // __cplusplus
      rep_set.push_back (basl::Token (LITERAL_INT_TOKEN, util::Loc (), getIdent ("199711L")));
      addMacro (createObjMacro (util::Loc (), getIdent ("__cplusplus"), rep_set));
      rep_set.clear ();

      // add -D macros
      addCmdMacroSet (conf::getOptionValue (conf::opt_macro_set));
    }
}
namespace
{
  bool MacroTable::isPersistentMacro (util::Ident const & ident)
    {
      return std::find (persistent_macro_set.begin (), persistent_macro_set.end (), ident) != persistent_macro_set.end ();
    }
}
namespace
{
  void MacroTable::addMacro (MacroPtr const & macro)
    {
      data_table.addData (macro->getName ().getHandle (), macro);
    }
}
namespace
{
  bool MacroTable::isMacro (util::Ident const & name) const
    {
      MacroPtr macro;
      return isMacro (name, macro);
    }
}
namespace
{
  bool MacroTable::isMacro (util::Ident const & name, MacroPtr & macro) const
    {
      bool found = false;
      MacroPtrDataTableFindResult find_result = data_table.findData (name.getHandle ());
      if (find_result.hasData ())
      {
        found = true;
        macro = find_result.getData ();
      }
      return found;
    }
}
namespace
{
  void MacroTable::delMacro (util::Ident const & name)
    {
      data_table.removeData (name.getHandle ());
    }
}
namespace
{
  MacroPtrDataTable const & MacroTable::getDataTable () const
    {
      return data_table;
    }
}
namespace
{
  void MacroTable::addCmdMacro (util::String const & str)
    {
      // exceptions
      try
      {
        // create lexer to lex string
        util::Loc dir_loc;
        Lexer lexer (str, dir_loc);
        util::Loc name_loc;
        util::Ident name;
        bool is_func = false;
        util::IdentVector param_set;
        bool var = false;
        basl::TokenVector rep_set;
        if (lexDefineLine (lexer, true, dir_loc, name_loc, name, is_func, param_set, var, rep_set))
        {
          // remove macro with same name if exists
          if (isMacro (name))
          {
            delMacro (name);
          }
          if (checkMacroRepSet (is_func, param_set, var, rep_set))
          {
            // use default location to signify that the macro is not from source
            addMacro (buildMacro (dir_loc, name, is_func, param_set, var, rep_set));
          }
        }
      }
      catch (util::Exception const e)
      {
      }
      catch (...)
      {
        throw;
      }
    }
}
namespace
{
  void MacroTable::addCmdMacroSet (util::StringVector const & str_set)
    {
      // add all macros in list
      for (util::StringVectorConstIter beg = str_set.begin (), end = str_set.end (); beg != end; ++ beg)
      {
        addCmdMacro (* beg);
      }
    }
}
namespace
{
  MacroTable & getMacroTable ()
  {
    static MacroTable table;
    return table;
  }
}
namespace gram
{
  void resetMacroTable ()
  {
    getMacroTable ().reset ();
  }
}
namespace gram
{
  MacroPtrDataTable const & getMacroDataTable ()
  {
    return getMacroTable ().getDataTable ();
  }
}
namespace gram
{
  bool isPersistentMacro (util::Ident const & ident)
  {
    return getMacroTable ().isPersistentMacro (ident);
  }
}
namespace gram
{
  void addMacro (MacroPtr const & macro)
  {
    getMacroTable ().addMacro (macro);
  }
}
namespace gram
{
  bool isMacro (util::Ident const & name)
  {
    return getMacroTable ().isMacro (name);
  }
}
namespace gram
{
  bool isMacro (util::Ident const & name, MacroPtr & macro)
  {
    return getMacroTable ().isMacro (name, macro);
  }
}
namespace gram
{
  void delMacro (util::Ident const & name)
  {
    getMacroTable ().delMacro (name);
  }
}
#undef LZZ_INLINE
