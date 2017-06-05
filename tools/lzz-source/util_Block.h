// util_Block.h
//

#ifndef LZZ_util_Block_h
#define LZZ_util_Block_h
// util
#include "util_BPtr.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  class BlockImpl;
}
namespace util
{
  typedef BPtr <BlockImpl> BlockImplPtr;
}
namespace util
{
  class Block
  {
    BlockImplPtr m_impl;
  public:
    Block ();
    explicit Block (Loc const & loc);
    ~ Block ();
    bool isSet () const;
    void setLoc (Loc const & loc);
    Loc const & getLoc () const;
    void append (char ch) const;
    void append (char const * str) const;
    void append (util::String const & str) const;
    void appendLine (util::String const & str) const;
    char const * toString () const;
    int getNumLines () const;
    int getLength () const;
    void freeze () const;
    void trim () const;
    bool isEmpty () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_Block.inl"
#endif
#endif
