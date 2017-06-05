// smtc_Enum.h
//

#ifndef LZZ_smtc_Enum_h
#define LZZ_smtc_Enum_h
// semantic
#include "smtc_EnumtorPtrVector.h"
#include "smtc_NamePtr.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace smtc
{
  class Enum
  {
    util::Loc m_loc;
    NamePtr m_name;
    EnumtorPtrVector m_enumtor_set;
  public:
    Enum (util::Loc const & loc, NamePtr const & name, EnumtorPtrVector const & enumtor_set);
    ~ Enum ();
    util::Loc const & getLoc () const;
    bool hasName () const;
    NamePtr const & getName () const;
    EnumtorPtrVector const & getEnumtorSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_Enum.inl"
#endif
#endif
