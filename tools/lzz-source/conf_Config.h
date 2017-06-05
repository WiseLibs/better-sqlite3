// conf_Config.h
//

#ifndef LZZ_conf_Config_h
#define LZZ_conf_Config_h
// util
#include "util_Ident.h"
#include "util_StringDeque.h"
#include "util_StringVector.h"
#define LZZ_INLINE inline
namespace conf
{
  class BoolOption;
}
namespace conf
{
  class StringOption;
}
namespace conf
{
  class StringSetOption;
}
namespace conf
{
  class IntOption;
}
namespace conf
{
  extern BoolOption opt_inl;
}
namespace conf
{
  extern BoolOption opt_tpl;
}
namespace conf
{
  extern BoolOption opt_tnl;
}
namespace conf
{
  extern BoolOption opt_inl_inl;
}
namespace conf
{
  extern StringOption opt_hdr_ext;
}
namespace conf
{
  extern StringOption opt_src_ext;
}
namespace conf
{
  extern StringOption opt_inl_ext;
}
namespace conf
{
  extern StringOption opt_tpl_ext;
}
namespace conf
{
  extern StringOption opt_tnl_ext;
}
namespace conf
{
  extern BoolOption opt_hdr_line;
}
namespace conf
{
  extern BoolOption opt_src_line;
}
namespace conf
{
  extern BoolOption opt_inl_line;
}
namespace conf
{
  extern BoolOption opt_tpl_line;
}
namespace conf
{
  extern BoolOption opt_tnl_line;
}
namespace conf
{
  extern BoolOption opt_hdr_smart_write;
}
namespace conf
{
  extern BoolOption opt_src_smart_write;
}
namespace conf
{
  extern BoolOption opt_inl_smart_write;
}
namespace conf
{
  extern BoolOption opt_tpl_smart_write;
}
namespace conf
{
  extern BoolOption opt_tnl_smart_write;
}
namespace conf
{
  extern BoolOption opt_src_if_hdr;
}
namespace conf
{
  extern BoolOption opt_expand_filename;
}
namespace conf
{
  extern StringOption opt_out_dir;
}
namespace conf
{
  extern StringOption opt_dll_api;
}
namespace conf
{
  extern StringOption opt_dll_exports;
}
namespace conf
{
  extern BoolOption opt_delete_old;
}
namespace conf
{
  extern StringSetOption opt_incl_path_set;
}
namespace conf
{
  extern StringSetOption opt_macro_set;
}
namespace conf
{
  extern StringSetOption opt_ai_filename;
}
namespace conf
{
  extern BoolOption opt_pp_all;
}
namespace conf
{
  extern BoolOption opt_pp;
}
namespace conf
{
  extern BoolOption opt_pp_incl;
}
namespace conf
{
  extern StringOption opt_rec;
}
namespace conf
{
  extern BoolOption opt_tpl_src;
}
namespace conf
{
  extern BoolOption opt_prep_block;
}
namespace conf
{
  extern IntOption opt_tab_stop;
}
namespace conf
{
  extern StringSetOption opt_persistent_macro_set;
}
namespace conf
{
  extern BoolOption opt_print_rec_tokens;
}
namespace conf
{
  extern BoolOption opt_print_options;
}
namespace conf
{
  extern BoolOption opt_rec_help;
}
namespace conf
{
  extern BoolOption opt_version;
}
namespace conf
{
  extern BoolOption opt_help;
}
namespace conf
{
  extern StringOption opt_package;
}
namespace conf
{
  util::String const & getOptionValue (StringOption const & opt);
}
namespace conf
{
  bool isOptionSet (StringOption const & opt);
}
namespace conf
{
  int getOptionValue (IntOption const & opt);
}
namespace conf
{
  bool getOptionValue (BoolOption const & opt);
}
namespace conf
{
  util::StringVector const & getOptionValue (StringSetOption const & opt);
}
namespace conf
{
  bool parseOptions (int argc, char * * argv, util::StringDeque & file_set);
}
namespace conf
{
  void setInitConfig ();
}
namespace conf
{
  void setUseFile (util::Ident const & dir, bool on, util::String const & ext);
}
namespace conf
{
  void setTplSrc ();
}
namespace conf
{
  void setPrepBlock (bool flag);
}
namespace conf
{
  void printOptionValues (std::ostream & os);
}
#undef LZZ_INLINE
#endif
