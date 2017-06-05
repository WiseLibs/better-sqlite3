// util_BlockImpl.h
//

#ifndef LZZ_util_BlockImpl_h
#define LZZ_util_BlockImpl_h
// util
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace util
{
  class BlockImpl
  {
    Loc m_loc;
    char * m_data;
    int m_length;
    int m_size;
    int m_num_lines;
  public:
    BlockImpl (Loc const & loc);
    ~ BlockImpl ();
    void setLoc (Loc const & loc);
    Loc const & getLoc () const;
    void append (char ch);
    void append (char const * str);
    char const * c_str () const;
    int getNumLines () const;
    int getLength () const;
    void freeze ();
    void trim ();
    bool isEmpty () const;
  private:
    BlockImpl (BlockImpl const & impl);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_BlockImpl.inl"
#endif
#endif
