// smtc_TmplName.h
//

#ifndef LZZ_smtc_TmplName_h
#define LZZ_smtc_TmplName_h
// semantic
#include "smtc_UnqlName.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class TmplName : public UnqlName
  {
    bool m_has_tmpl;
    util::String m_args;
  public:
    TmplName (BaseNamePtr const & base_name, bool has_tmpl, util::String const & args);
    ~ TmplName ();
    bool hasTemplateKeyword () const;
    util::String const & getArgs () const;
    void accept (NameVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_TmplName.inl"
#endif
#endif
