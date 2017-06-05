// gram_SpecSel.h
//

#ifndef LZZ_gram_SpecSel_h
#define LZZ_gram_SpecSel_h
// std lib
#include <algorithm>
#include <deque>

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  typedef std::pair <int, util::Loc> SpecLocPair;
}
namespace gram
{
  class SpecSel
  {
    int m_flags;
    std::deque <SpecLocPair> m_spec_loc_set;
  public:
    SpecSel ();
    void addSpec (int flag, util::Loc const & loc);
    void remSpec (int flag);
    bool hasSpec (int flag) const;
    bool anySet () const;
    int getFlags () const;
    util::Loc const & getSpecLoc (int flag) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_SpecSel.inl"
#endif
#endif
