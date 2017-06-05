// smtc_Lzz.cpp
//

#include "smtc_Lzz.h"
// std lib
#include <algorithm>

// semantic
#include "smtc_CreateNsScope.h"
#include "smtc_GetGlobalNs.h"
#include "smtc_Output.h"
#include "smtc_PrintNs.h"

// gram
#include "gram_MacroTable.h"
#include "gram_ParseRecoverOpt.h"
#include "gram_Parser.h"
#include "gram_PrepFile.h"
#include "gram_PrintPPTokenSet.h"

// config
#include "conf_Config.h"
#include "conf_PrintHelp.h"

// config
#include "conf_Config.h"
#include "conf_PrintHelp.h"

// message
#include "msg_Recorder.h"

// util
#include "util_Exception.h"
#include "util_FilenameTable.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct CompileFile
  {
    std::ostream & os;
    void operator () (util::String const & filename) const;
  public:
    explicit CompileFile (std::ostream & os);
    ~ CompileFile ();
  };
}
namespace
{
  void CompileFile::operator () (util::String const & filename) const
  {
    // reset config options (may have been changed by pragmas) and reset the macro table
    if (isPreprocessOptionSet ())
    {
      preprocessFile (filename, os);
    }
    else
    {
      Output output (filename);
      translateFile (filename, output);
    }
  }
}
namespace
{
  LZZ_INLINE CompileFile::CompileFile (std::ostream & os)
    : os (os)
       {}
}
namespace
{
  CompileFile::~ CompileFile ()
       {}
}
namespace smtc
{
  bool isHelpOptionSet ()
  {
    return (
      conf::getOptionValue (conf::opt_help) ||
      conf::getOptionValue (conf::opt_version) ||
      conf::getOptionValue (conf::opt_rec_help) ||
      conf::getOptionValue (conf::opt_print_options) ||
      conf::getOptionValue (conf::opt_print_rec_tokens));
  }
}
namespace smtc
{
  bool isPreprocessOptionSet ()
  {
    return (
      conf::getOptionValue (conf::opt_pp_incl) ||
      conf::getOptionValue (conf::opt_pp_all) ||
      conf::getOptionValue (conf::opt_pp));
  }
}
namespace smtc
{
  void printLzzHelp (std::ostream & os)
  {
    if (conf::getOptionValue (conf::opt_help))
    {
      conf::printHelp (os);
    }
    else if (conf::getOptionValue (conf::opt_version))
    {
      conf::printVersion (os);
    }
    else if (conf::getOptionValue (conf::opt_rec_help))
    {
      gram::printRecoverHelp (os);
    }
    else if (conf::getOptionValue (conf::opt_print_options))
    {
      conf::printOptionValues (os);
    }
    else if (conf::getOptionValue (conf::opt_print_rec_tokens))
    {
      gram::printRecoverTokens (os);
    }
  }
}
namespace smtc
{
  void preprocessFile (util::String const & filename, std::ostream & os)
  {
    gram::resetMacroTable ();
    // the parser can throw exceptions
    try
    {
      basl::TokenDeque token_set;
      msg::resetRecorder ();
      if (conf::getOptionValue (conf::opt_pp_incl) || conf::getOptionValue (conf::opt_pp_all))
      {
        gram::prepFile (filename, conf::getOptionValue (conf::opt_pp_incl), token_set);
      }
      else if (conf::getOptionValue (conf::opt_pp))
      {
        gram::ppParse (filename, token_set);
      }
      if (! msg::hasFatalMessage ())
      {
        gram::printPPTokenSet (os, token_set);
      }
    }
    catch (util::Exception const &)
    {
    }
    conf::setInitConfig ();
  }
}
namespace smtc
{
  void translateFile (util::String const & filename, Output & output)
  {
    gram::resetMacroTable ();
    try
    {
      msg::resetRecorder ();
      NsPtr ns = smtc::getGlobalNs ();
      gram::parse (filename, createNsScope (ns), output);
      if (! msg::hasFatalMessage ())
      {
        output.lexDone ();
        printNs (output, ns);
        output.close (true);
      }
      else
      {
        output.close (false);
      }
    }
    catch (util::Exception const &)
    {
      output.close (false);
    }
    conf::setInitConfig ();
  }
}
namespace smtc
{
  void compileFiles (util::StringDeque const & filenames, std::ostream & os)
  {
    if (isHelpOptionSet ())
    {
      printLzzHelp (os);
    }
    else
    {
      std::for_each (filenames.begin (), filenames.end (), CompileFile (os));
    }
  }
}
#undef LZZ_INLINE
