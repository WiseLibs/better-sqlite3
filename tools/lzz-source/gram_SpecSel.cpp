// gram_SpecSel.cpp
//

#include "gram_SpecSel.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_SpecSel.inl"
#endif
// util
#include "util_BitOp.h"
#include <assert.h>
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  struct IsSpecFlag
  {
    int flag;
    bool operator () (SpecLocPair const & spec) const;
  public:
    explicit IsSpecFlag (int flag);
    ~ IsSpecFlag ();
  };
}
namespace
{
  LZZ_INLINE bool IsSpecFlag::operator () (SpecLocPair const & spec) const
  {
    return spec.first == flag;
  }
}
namespace
{
  LZZ_INLINE IsSpecFlag::IsSpecFlag (int flag)
    : flag (flag)
              {}
}
namespace
{
  IsSpecFlag::~ IsSpecFlag ()
              {}
}
namespace gram
{
  void SpecSel::addSpec (int flag, util::Loc const & loc)
    {
      m_flags |= flag;
      m_spec_loc_set.push_back (SpecLocPair (flag, loc));
    }
}
namespace gram
{
  void SpecSel::remSpec (int flag)
    {
      std::deque <SpecLocPair>::iterator i = std::find_if (m_spec_loc_set.begin (), m_spec_loc_set.end (), IsSpecFlag (flag));
      if (i != m_spec_loc_set.end ())
      {
        m_spec_loc_set.erase (i);
      }
    }
}
namespace gram
{
  bool SpecSel::hasSpec (int flag) const
    {
      return util::hasFlag (m_flags, flag);
    }
}
namespace gram
{
  util::Loc const & SpecSel::getSpecLoc (int flag) const
    {
      std::deque <SpecLocPair>::const_iterator i = std::find_if (m_spec_loc_set.begin (), m_spec_loc_set.end (), IsSpecFlag (flag));
      assert (i != m_spec_loc_set.end ());
      return i->second;
    }
}
#undef LZZ_INLINE
