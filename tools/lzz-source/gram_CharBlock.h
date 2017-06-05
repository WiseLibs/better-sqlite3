// gram_CharBlock.h
//

#ifndef LZZ_gram_CharBlock_h
#define LZZ_gram_CharBlock_h
// gram
#include "gram_Block.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  class CharBlockImpl;
}
namespace gram
{
  class CharBlock : public Block
  {
  public:
    CharBlock (util::Loc const & loc);
    CharBlock (Block const & block);
    void append (char ch) const;
    void append (char const * str) const;
    void append (util::String const & str) const;
    void appendLine (util::String const & str) const;
    char const * c_str () const;
    int getNumLines () const;
    int getLength () const;
    void freeze () const;
    void trim () const;
    bool isEmpty () const;
  private:
    CharBlockImpl & getCharBlockImpl () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_CharBlock.inl"
#endif
#endif
