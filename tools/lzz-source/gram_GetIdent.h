// gram_GetIdent.h
//

#ifndef LZZ_gram_GetIdent_h
#define LZZ_gram_GetIdent_h
// util
#include "util_Ident.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  util::Ident getIdent (char const * str);
}
namespace gram
{
  util::Ident getIdent (util::String const & str);
}
namespace gram
{
  util::Ident getIdent (char ch);
}
namespace gram
{
  extern util::Ident const defined_ident;
}
namespace gram
{
  extern util::Ident const define_ident;
}
namespace gram
{
  extern util::Ident const include_ident;
}
namespace gram
{
  extern util::Ident const insert_ident;
}
namespace gram
{
  extern util::Ident const if_ident;
}
namespace gram
{
  extern util::Ident const ifdef_ident;
}
namespace gram
{
  extern util::Ident const ifndef_ident;
}
namespace gram
{
  extern util::Ident const elif_ident;
}
namespace gram
{
  extern util::Ident const else_ident;
}
namespace gram
{
  extern util::Ident const endif_ident;
}
namespace gram
{
  extern util::Ident const line_ident;
}
namespace gram
{
  extern util::Ident const undef_ident;
}
namespace gram
{
  extern util::Ident const error_ident;
}
namespace gram
{
  extern util::Ident const pragma_ident;
}
namespace gram
{
  extern util::Ident const hdr_ident;
}
namespace gram
{
  extern util::Ident const src_ident;
}
namespace gram
{
  extern util::Ident const inl_ident;
}
namespace gram
{
  extern util::Ident const tpl_ident;
}
namespace gram
{
  extern util::Ident const tnl_ident;
}
namespace gram
{
  extern util::Ident const header_ident;
}
namespace gram
{
  extern util::Ident const source_ident;
}
namespace gram
{
  extern util::Ident const inline_ident;
}
namespace gram
{
  extern util::Ident const template_ident;
}
namespace gram
{
  extern util::Ident const template_inline_ident;
}
namespace gram
{
  extern util::Ident const use_ident;
}
namespace gram
{
  extern util::Ident const true_ident;
}
namespace gram
{
  extern util::Ident const end_of_line_ident;
}
namespace gram
{
  extern util::Ident const lzz_ident;
}
namespace gram
{
  extern util::Ident const yes_ident;
}
namespace gram
{
  extern util::Ident const no_ident;
}
namespace gram
{
  extern util::Ident const on_ident;
}
namespace gram
{
  extern util::Ident const off_ident;
}
namespace gram
{
  extern util::Ident const once_ident;
}
namespace gram
{
  extern util::Ident const tplsrc_ident;
}
namespace gram
{
  extern util::Ident const prep_block_ident;
}
namespace gram
{
  extern util::Ident const va_args_ident;
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_GetIdent.inl"
#endif
#endif
