// smtc_BitfName.h
//

#ifndef LZZ_smtc_BitfName_h
#define LZZ_smtc_BitfName_h
// semantic
#include "smtc_Name.h"

// util
#include "util_Ident.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  class BitfName : public Name
  {
    util::Loc m_loc;
    util::Ident m_ident;
    util::String m_size;
  public:
    BitfName (util::Loc const & loc, util::Ident const & ident, util::String const & size);
    ~ BitfName ();
    util::Loc const & getLoc () const;
    bool hasIdent () const;
    util::Ident const & getIdent () const;
    util::String const & getSize () const;
    void accept (NameVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_BitfName.inl"
#endif
#endif
