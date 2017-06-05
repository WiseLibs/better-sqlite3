// conf_Config.cpp
//

#include "conf_Config.h"
// std lib
#include <algorithm>
#include <cctype>
#include <iostream>
#include <cstring>

// config
#include "conf_Message.h"
#include "conf_Option.h"

// util
#include "util_GetEnv.h"
#include "util_GetIdent.h"
#include "util_GetNextWord.h"
#include "util_SkipWs.h"
#define LZZ_INLINE inline
using namespace std;
namespace
{
  using namespace conf;
}
namespace
{
  using namespace util;
}
namespace
{
  enum
  {
    NO_VALUE_OPTION = 1 << 0,
    DISABLED_OPTION = 1 << 1
  };
}
namespace
{
  int const disabled_if_cgi =
#ifdef CGI_BUILD
  DISABLED_OPTION
#else
  0
#endif
  ;
}
namespace
{
  struct OptionRec
  {
    char const * name;
    char const * old_name;
    Option * option;
    int flags;
  };
}
namespace
{
  OptionRec (option_rec_set) [] =
  {
    { "i", "inl", & opt_inl, 0 },
    { "t", "tpl", & opt_tpl, 0 },
    { "n", "tnl", & opt_tnl, 0 },

    { "hx", "hdr-ext", & opt_hdr_ext, 0 },
    { "sx", "src-ext", & opt_src_ext, 0 },
    { "ix", "inl-ext", & opt_inl_ext, 0 },
    { "tx", "tpl-ext", & opt_tpl_ext, 0 },
    { "nx", "tnl-ext", & opt_tnl_ext, 0 },
    
    { "hl", "hdr-line", & opt_hdr_line, 0 },
    { "sl", "src-line", & opt_src_line, 0 },
    { "il", "inl-line", & opt_inl_line, 0 },
    { "tl", "tpl-line", & opt_tpl_line, 0 },
    { "nl", "tnl-line", & opt_tnl_line, 0 },

    { "hd", "hdr-smart-write", & opt_hdr_smart_write, 0 },
    { "sd", "src-smart-write", & opt_src_smart_write, 0 },
    { "id", "inl-smart-write", & opt_inl_smart_write, 0 },
    { "td", "tpl-smart-write", & opt_tpl_smart_write, 0 },
    { "nd", "tnl-smart-write", & opt_tnl_smart_write, 0 },

    { "c", "src-if-hdr", & opt_src_if_hdr, 0 },
    { "o", "out-dir", & opt_out_dir, disabled_if_cgi },
    { "da", "dll-api", & opt_dll_api, 0 },
    { "dx", "dll-exports", & opt_dll_exports, 0 },
    { "x", 0, & opt_expand_filename, disabled_if_cgi },
    { "d", "delete-old", & opt_delete_old, disabled_if_cgi },
    { "I", 0, & opt_incl_path_set, disabled_if_cgi },
    { "D", 0, & opt_macro_set, 0 },
    { "a", 0, & opt_ai_filename, disabled_if_cgi },
    { "p", 0, & opt_pp, 0 },
    { "P", 0, & opt_pp_all, 0 },
    { "E", 0, & opt_pp_incl, 0 },
    { "r", 0, & opt_rec, 0 },

    { "e",  0, & opt_prep_block, 0 },
    { "b",  0, & opt_tab_stop, 0 },

    { "k", 0, & opt_package, 0 },

#ifdef PRL_BUILD
    // Dan requested this option, for now keep it prl only
    { "ts", "tpl-src", & opt_tpl_src, 0 },

    // bonnie needs this option
    { "macro", 0, & opt_persistent_macro_set, 0 },

    // and the inl-inl option at the moment is only for prl
    { "ii", "inl-inl", & opt_inl_inl, 0 },
#endif

#ifdef DEBUG_BUILD
    { "tr", 0, & opt_trace, 0 },
#endif

    { "v", 0, & opt_print_options, NO_VALUE_OPTION },
    { "hr", 0, & opt_rec_help, NO_VALUE_OPTION },
    { "T", 0, & opt_print_rec_tokens, NO_VALUE_OPTION },
    { "ver", 0,  & opt_version, NO_VALUE_OPTION },
    { "h", 0, & opt_help, NO_VALUE_OPTION },
    { "help", 0, & opt_help, NO_VALUE_OPTION },
  };
}
namespace
{
  int const num_options = sizeof (option_rec_set) / sizeof (option_rec_set [0]);
}
namespace
{
  Option * getOption (char const * name, int & flags);
}
namespace
{
  bool opt_inl_save;
}
namespace
{
  bool opt_tpl_save;
}
namespace
{
  bool opt_tnl_save;
}
namespace
{
  util::String opt_inl_ext_save;
}
namespace
{
  util::String opt_tpl_ext_save;
}
namespace
{
  util::String opt_tnl_ext_save;
}
namespace
{
  bool opt_tpl_src_save;
}
namespace
{
  bool opt_prep_block_save;
}
namespace
{
  void saveInitValues ();
}
namespace
{
  void resetInitValues ();
}
namespace
{
  bool parseEnvOptions (String const & str);
}
namespace
{
  bool parseEnvOptions ();
}
namespace
{
  bool parseCmdLine (int argc, char * * argv, util::StringDeque & file_set);
}
namespace conf
{
  BoolOption opt_inl (false);
}
namespace conf
{
  BoolOption opt_tpl (false);
}
namespace conf
{
  BoolOption opt_tnl (false);
}
namespace conf
{
  BoolOption opt_inl_inl (false);
}
namespace conf
{
  StringOption opt_hdr_ext ("h");
}
namespace conf
{
  StringOption opt_src_ext ("cpp");
}
namespace conf
{
  StringOption opt_inl_ext ("inl");
}
namespace conf
{
  StringOption opt_tpl_ext ("tpl");
}
namespace conf
{
  StringOption opt_tnl_ext ("tnl");
}
namespace conf
{
  BoolOption opt_hdr_line (false);
}
namespace conf
{
  BoolOption opt_src_line (false);
}
namespace conf
{
  BoolOption opt_inl_line (false);
}
namespace conf
{
  BoolOption opt_tpl_line (false);
}
namespace conf
{
  BoolOption opt_tnl_line (false);
}
namespace conf
{
  BoolOption opt_hdr_smart_write (false);
}
namespace conf
{
  BoolOption opt_src_smart_write (false);
}
namespace conf
{
  BoolOption opt_inl_smart_write (false);
}
namespace conf
{
  BoolOption opt_tpl_smart_write (false);
}
namespace conf
{
  BoolOption opt_tnl_smart_write (false);
}
namespace conf
{
  BoolOption opt_src_if_hdr (false);
}
namespace conf
{
  BoolOption opt_expand_filename (false);
}
namespace conf
{
  StringOption opt_out_dir ("");
}
namespace conf
{
  StringOption opt_dll_api ("");
}
namespace conf
{
  StringOption opt_dll_exports ("");
}
namespace conf
{
  BoolOption opt_delete_old (false);
}
namespace conf
{
  StringSetOption opt_incl_path_set;
}
namespace conf
{
  StringSetOption opt_macro_set;
}
namespace conf
{
  StringSetOption opt_ai_filename;
}
namespace conf
{
  BoolOption opt_pp_all (false);
}
namespace conf
{
  BoolOption opt_pp (false);
}
namespace conf
{
  BoolOption opt_pp_incl (false);
}
namespace conf
{
  StringOption opt_rec ("r:DCOLON:COLON,i:IDENT,i:SEMI,r:SEMI:COMMA,d:30");
}
namespace conf
{
  BoolOption opt_tpl_src (false);
}
namespace conf
{
  BoolOption opt_prep_block (false);
}
namespace conf
{
  IntOption opt_tab_stop (8);
}
namespace conf
{
  StringSetOption opt_persistent_macro_set;
}
namespace conf
{
  BoolOption opt_print_rec_tokens (false);
}
namespace conf
{
  BoolOption opt_print_options (false);
}
namespace conf
{
  BoolOption opt_rec_help (false);
}
namespace conf
{
  BoolOption opt_version (false);
}
namespace conf
{
  BoolOption opt_help (false);
}
namespace conf
{
  StringOption opt_package ("");
}
namespace conf
{
  util::String const & getOptionValue (StringOption const & opt)
  {
    return opt.getValue ();
  }
}
namespace conf
{
  bool isOptionSet (StringOption const & opt)
  {
    return ! opt.getValue ().empty ();
  }
}
namespace conf
{
  int getOptionValue (IntOption const & opt)
  {
    return opt.getValue ();
  }
}
namespace conf
{
  bool getOptionValue (BoolOption const & opt)
  {
    return opt.getValue ();
  }
}
namespace conf
{
  util::StringVector const & getOptionValue (StringSetOption const & opt)
  {
    return opt.getValue ();
  }
}
namespace
{
  Option * getOption (char const * name, int & flags)
  {
    Option * option = 0;
    OptionRec const * beg = option_rec_set;
    OptionRec const * end = option_rec_set + num_options;
    for (; beg != end; ++ beg)
    {
      if ((beg->name != 0 && strcmp (beg->name, name) == 0) || (beg->old_name != 0 && strcmp (beg->old_name, name) == 0))
      {
        option = beg->option;
        flags = beg->flags;
        break;
      }
    }
    return option;
  }
}
namespace
{
  void saveInitValues ()
  {
    opt_inl_save = opt_inl.getValue ();
    opt_tpl_save = opt_tpl.getValue ();
    opt_tnl_save = opt_tnl.getValue ();
    opt_inl_ext_save = opt_inl_ext.getValue ();
    opt_tpl_ext_save = opt_tpl_ext.getValue ();
    opt_tnl_ext_save = opt_tnl_ext.getValue ();
    opt_tpl_src_save = opt_tpl_src.getValue ();
    opt_prep_block_save = opt_prep_block.getValue ();
  }
}
namespace
{
  void resetInitValues ()
  {
    opt_inl.setValue (opt_inl_save);
    opt_tpl.setValue (opt_tpl_save);
    opt_tnl.setValue (opt_tnl_save);
    opt_inl_ext.setValue (opt_inl_ext_save);
    opt_tpl_ext.setValue (opt_tpl_ext_save);
    opt_tnl_ext.setValue (opt_tnl_ext_save);
    opt_tpl_src.setValue (opt_tpl_src_save);
    opt_prep_block.setValue (opt_prep_block_save);
  }
}
namespace
{
  bool parseEnvOptions (String const & str)
  {
    bool env = true;
    StringConstIter str_beg = str.begin ();
    StringConstIter str_end = str.end ();
    char const * ws = " \t";
    for (;;)
    {
      String word = getNextWord (skipWs (str_beg, str_end, ws), str_end, ws, str_beg);
      if (word.empty ())
      {
        break;
      }
      char const * opt = word.c_str ();
      // discard leading dash if present
      if (opt [0] == '-')
      {
        ++ opt;
        if (opt [0] == '\0' || opt [0] == ' ')
        {
          msg::optionExpected (env);
          return false;
        }
      }
      // check if single letter option
      if (isupper (opt [0]) && opt [1] != '\0')
      {
        // search for option
        char opt1 [2];
        opt1 [0] = opt [0];
        opt1 [1] = '\0';
        int flags;
        Option * option = getOption (opt1, flags);
        if (! option)
        {
          msg::invalidOption (opt1, env);
          return false;
        }
        if (flags & DISABLED_OPTION)
        {
          msg::disabledOption (opt, env);
          return false;
        }
        option->setValue (opt + 1);
      }
      else
      {
        // check if preceded with 'no-'
        bool has_no = false;
        if (memcmp (opt, "no-", 3) == 0)
        {
          has_no = true;
          opt += 3;
        }
        // get option
        int flags;
        Option * option = getOption (opt, flags);
        if (! option)
        {
          msg::invalidOption (opt, env);
          return false;
        }
        if (flags & DISABLED_OPTION)
        {
          msg::disabledOption (opt, env);
          return false;
        }
        if (option->isBoolOption ())
        {
          // has_no is the value
          option->setValue (has_no ? "no" : "yes");
        }
        else if (has_no)
        {
          msg::notBoolOption (opt, env);
          return false;
        }
        else
        {
          String value = getNextWord (skipWs (str_beg, str_end, ws), str_end, ws, str_beg);
          if (value.empty ())
          {
            msg::optionValueExpected (opt, env);
            return false;
          }
          option->setValue (value);
        }
      }
    }
    return true;
  }
}
namespace
{
  bool parseEnvOptions ()
  {
    // do nothing if environment variable is not set
    util::String env_options;
    if (! util::getEnv ("LZZ_OPTIONS", env_options))
    {
      return true;
    }
    return parseEnvOptions (env_options);
  }
}
namespace
{
  bool parseCmdLine (int argc, char * * argv, util::StringDeque & file_set)
  {
    for (int i = 1; i < argc; i ++)
    {
      char * opt = argv [i];
      if (* opt != '-')
      {
#ifdef CGI_BUILD
        msg::filenameNotAccepted (argv [i]);
#else
        // must be file name
        file_set.push_back (argv [i]);
#endif
      }
      else
      {
        ++ opt;
        // check if has opt
        if (* opt == '\0')
        {
          msg::optionExpected ();
          msg::typeHelpForUsage ();
          return false;
        }
        // check if single letter option, eg: -D or -I
        if (isupper (opt [0]) && opt [1] != '\0')
        {
          // search for option
          char opt1 [2];
          opt1 [0] = opt [0];
          opt1 [1] = '\0';
          int flags;
          Option * option = getOption (opt1, flags);
          if (! option)
          {
            msg::invalidOption (opt1);
            msg::typeHelpForUsage ();
            return false;
          }
          if (flags & DISABLED_OPTION)
          {
            msg::disabledOption (opt);
            return false;
          }
          option->setValue (opt + 1);
        }
        else
        {
          // check if preceeded with "no-"
          bool has_no = false;
          if (memcmp (opt, "no-", 3) == 0)
          {
            has_no = true;
            opt += 3;
          }
          // search for option
          int flags;
          Option * option = getOption (opt, flags);
          if (! option)
          {
            msg::invalidOption (opt);
            msg::typeHelpForUsage ();
            return false;
          }
          if (flags & DISABLED_OPTION)
          {
            msg::disabledOption (opt);
            return false;
          }
          // bool option has no value
          if (option->isBoolOption ())
          {
            // has_no is the value
            option->setValue (has_no ? "no" : "yes");
          }
          // get value
          else
          {
            if (has_no)
            {
              msg::notBoolOption (opt);
              msg::typeHelpForUsage ();
              return false;
            }
            if (i + 1 == argc)
            {
              msg::optionValueExpected (opt);
              msg::typeHelpForUsage ();
              return false;
            }
            char const * value = argv [++ i];
            option->setValue (value);
          }
        }
      }
    }
    return true;
  }
}
namespace conf
{
  bool parseOptions (int argc, char * * argv, util::StringDeque & file_set)
  {
    // check if LZZ_SYNTAX_RECOVER_COMMANDS is set
    const char * env_str = getenv ("LZZ_SYNTAX_RECOVER_COMMANDS");
    if (env_str)
    {
      opt_rec.setValue (env_str);
    }
    // pre config
    if (! (parseEnvOptions () && parseCmdLine (argc, argv, file_set)))
    {
      return false;
    }
#ifndef CGI_BUILD
    // check if files given
    if (file_set.empty () && ! (opt_help.getValue () || opt_version.getValue () || opt_rec_help.getValue () ||
            opt_print_options.getValue () || opt_print_rec_tokens.getValue ()))
    {
      msg::noFiles ();
      msg::typeHelpForUsage ();
      return false;
    }
#endif
    /* no, don't do this, -inl-inl doesn't use the .inl file
    // if using -inl-inl then also set -inl, just to make checks easier
    if (getOptionValue (opt_inl_inl))
    {
      opt_inl.setValue ("yes");
    }
    */
    // option validation checks
    // if dll-api is set then dll-exports must be set too
    if (! getOptionValue (opt_dll_api).empty () && getOptionValue (opt_dll_exports).empty ())
    {
      msg::dllExportsNotSet ();
      return false;
    }
    saveInitValues ();
    return true;
  }
}
namespace conf
{
  void setInitConfig ()
  {
    resetInitValues ();
  }
}
namespace conf
{
  void setUseFile (util::Ident const & dir, bool on, util::String const & ext)
  {
    if (dir == util::getIdent ("inl"))
    {
      opt_inl.setValue (on);
      if (! ext.empty ())
      {
        opt_inl_ext.setValue (ext);
      }
    }
    else if (dir == util::getIdent ("tpl"))
    {
      opt_tpl.setValue (on);
      if (! ext.empty ())
      {
        opt_tpl_ext.setValue (ext);
      }
    }
    else if (dir == util::getIdent ("tnl"))
    {
      opt_tnl.setValue (on);
      if (! ext.empty ())
      {
        opt_tnl_ext.setValue (ext);
      }
    }
  }
}
namespace conf
{
  void setTplSrc ()
  {
    opt_tpl_src.setValue (true);
  }
}
namespace conf
{
  void setPrepBlock (bool flag)
  {
    opt_prep_block.setValue (flag);
  }
}
namespace conf
{
  void printOptionValues (std::ostream & os)
  {
    os << "Option values:" << '\n';
    OptionRec const * beg = option_rec_set;
    OptionRec const * end = option_rec_set + num_options;
    for (; beg != end; ++ beg)
    {
      if (! (beg->flags & NO_VALUE_OPTION))
      {
        os << " -";
        os.setf (std::ios::left, std::ios::adjustfield);
        os.width (8);
        os << beg->name;
        Option const * option = beg->option;
        if (option->getKind () == STRING_SET_OPTION)
        {
          bool first = true;
          util::StringVector const & str_set = static_cast <StringSetOption const &> (* option).getValue ();
          for (util::StringVectorConstIter set_beg = str_set.begin (), set_end = str_set.end (); set_beg != set_end; ++ set_beg)
          {
            if (first)
            {
              first = false;
            }
            else
            {
              os << "          ";
            }
            os << * set_beg << '\n';
          }
          if (first)
          {
            os << '\n';
          }
        }
        else
        {
          os << option->getValueAsString () << '\n';
        }
      }
    }
  }
}
#undef LZZ_INLINE
