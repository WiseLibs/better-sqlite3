// gram_FileReader.h
//

#ifndef LZZ_gram_FileReader_h
#define LZZ_gram_FileReader_h
// library
#include <cstdio>

// util
#include "util_Filename.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace gram
{
  class FileReader
  {
    enum
    {
      MAX_PEEK = 16
    };
    util::Filename m_filename;
    FILE * m_fp;
    int m_state;
    fpos_t m_file_pos;
    char * m_buf;
    char * m_buf_beg;
    char * m_buf_end;
    char (m_peek_buf) [MAX_PEEK];
    int m_peek_beg;
    int m_peek_end;
  public:
    FileReader (util::Filename const & filename);
    FileReader (util::String const & str, util::Loc const & loc);
    ~ FileReader ();
    util::Filename const & getFilename () const;
    bool peekChar (char & ch, int n = 0);
    bool readChar (char & ch);
    void pause ();
  private:
    bool readDirectChar (char & ch);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "gram_FileReader.inl"
#endif
#endif
