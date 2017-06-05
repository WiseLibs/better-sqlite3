// gram_LineReader.h
//

#ifndef LZZ_gram_LineReader_h
#define LZZ_gram_LineReader_h
// gram
#include "gram_CharReader.h"
#define LZZ_INLINE inline
namespace gram
{
  class LineReader
  {
    struct Char
    {
      char c;
      int lines;
      int cols;
      Char ();
      Char (char c, int lines, int cols);
    };
    enum
    {
      MAX_PEEK = 16
    };
    CharReader m_char_reader;
    Char (m_peek_buf) [MAX_PEEK];
    int m_peek_beg;
    int m_peek_end;
    util::Filename m_filename;
    int m_line;
    int m_column;
    bool m_newline;
  public:
    LineReader (util::Filename const & filename);
    LineReader (util::String const & str, util::Loc const & loc);
    bool peekChar (char & c, int n = 0);
    bool readChar (char & c);
    util::Loc getLocation () const;
    util::Filename const & getFilename () const;
    void setLine (int line);
    void setLine (int line, util::Filename const & filename);
    void pause ();
  private:
    bool readDirectChar (Char & ch);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_LineReader.inl"
#endif
#endif
