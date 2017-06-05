// gram_CharBlock.inl
//

#include "gram_CharBlockImpl.h"
#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE void CharBlock::append (char ch) const
    {
      getCharBlockImpl ().append (ch);
    }
}
namespace gram
{
  LZZ_INLINE void CharBlock::append (char const * str) const
    {
      getCharBlockImpl ().append (str);
    }
}
namespace gram
{
  LZZ_INLINE void CharBlock::append (util::String const & str) const
    {
      append (str.c_str ());
    }
}
namespace gram
{
  LZZ_INLINE void CharBlock::appendLine (util::String const & str) const
    {
      append (str.c_str ());
      append ('\n');
    }
}
namespace gram
{
  LZZ_INLINE char const * CharBlock::c_str () const
    {
      return getCharBlockImpl ().c_str ();
    }
}
namespace gram
{
  LZZ_INLINE int CharBlock::getNumLines () const
    {
      return getCharBlockImpl ().getNumLines ();
    }
}
namespace gram
{
  LZZ_INLINE int CharBlock::getLength () const
    {
      return getCharBlockImpl ().getLength ();
    }
}
namespace gram
{
  LZZ_INLINE void CharBlock::freeze () const
    {
      getCharBlockImpl ().freeze ();
    }
}
namespace gram
{
  LZZ_INLINE void CharBlock::trim () const
    {
      getCharBlockImpl ().trim ();
    }
}
namespace gram
{
  LZZ_INLINE bool CharBlock::isEmpty () const
    {
      return getCharBlockImpl ().isEmpty ();
    }
}
namespace gram
{
  LZZ_INLINE CharBlockImpl & CharBlock::getCharBlockImpl () const
    {
      return static_cast <CharBlockImpl &> (* getImpl ());
    }
}
#undef LZZ_INLINE
