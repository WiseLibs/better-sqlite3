// smtc_PrintTmplSpec.cpp
//

#include "smtc_PrintTmplSpec.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_PrintTmplSpec.inl"
#endif
// semantic
#include "smtc_ParamSetToString.h"
#include "smtc_PrintCode.h"
#include "smtc_TmplSpec.h"

// util
#include "util_AppendWithSpace.h"
#define LZZ_INLINE inline
namespace smtc
{
  using namespace util;
}
namespace smtc
{
  void printTmplSpec (FilePtr const & file, SectionKind skind, TmplSpecPtr const & tmpl_spec, bool is_decl)
  {
    String str = "template";
    appendWithSpace (str, '<');
    // avoid diagraph '<:'
    String param_str = paramSetToString (tmpl_spec->getParamSet (), is_decl);
    if (! param_str.empty () && param_str [0] == ':')
    {
      str += ' ';
    }
    str += param_str;
    // do not end with '>>'
    if (str [str.length () - 1] == '>')
    {
      str += ' ';
    }
    str += '>';
    printLine (file, skind, tmpl_spec->getLoc (), str);
  }
}
namespace smtc
{
  PrintTmplSpec::~ PrintTmplSpec ()
              {}
}
#undef LZZ_INLINE
