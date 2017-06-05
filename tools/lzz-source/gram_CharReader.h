// gram_CharReader.h
//

#ifndef LZZ_gram_CharReader_h
#define LZZ_gram_CharReader_h
// gram
#include "gram_FileReader.h"

// util
#include "util_Loc.h"
#define LZZ_INLINE inline
namespace gram
{
  class CharReader
  {
    struct Char
    {
      char c;
      int cols;
      Char ();
      Char (char c, int cols);
    };
    enum
    {
      MAX_PEEK = 16
    };
    FileReader m_file_reader;
    int m_column;
    Char (m_peek_buf) [MAX_PEEK];
    int m_peek_beg;
    int m_peek_end;
  public:
    CharReader (util::Filename const & filename);
    CharReader (util::String const & str, util::Loc const & loc);
    bool peekChar (char & c, int n = 0);
    bool readChar (char & c, int & cols);
    void pause ();
  private:
    bool readDirectChar (Char & ch);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_CharReader.inl"
#endif
#endif
