// gram_CharBlockImpl.h
//

#ifndef LZZ_gram_CharBlockImpl_h
#define LZZ_gram_CharBlockImpl_h
// gram
#include "gram_BlockImpl.h"
#define LZZ_INLINE inline
namespace gram
{
  class CharBlockImpl : public BlockImpl
  {
    char * m_data;
    int m_length;
    int m_size;
    int m_num_lines;
    enum
    {
      INITSIZE = 32
    };
  public:
    CharBlockImpl (util::Loc const & loc);
    ~ CharBlockImpl ();
    bool isCharBlock () const;
    util::String toString () const;
    void append (char ch);
    void append (char const * str);
    char const * c_str () const;
    int getNumLines () const;
    int getLength () const;
    void freeze ();
    void trim ();
    bool isEmpty () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_CharBlockImpl.inl"
#endif
#endif
