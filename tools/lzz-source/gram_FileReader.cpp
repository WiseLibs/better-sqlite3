// gram_FileReader.cpp
//

#include "gram_FileReader.h"
#ifndef LZZ_ENABLE_INLINE
#include "gram_FileReader.inl"
#endif
// gram
#include "gram_Message.h"

// util
#include "util_Exception.h"
#define LZZ_INLINE inline
namespace
{
  enum
  {
    FILE_BUF_SIZE = 4096
  };
}
namespace
{
  enum
  {
    FILE_START,
    FILE_CLOSED,
    FILE_OPEN,
    FILE_EOF
  };
}
namespace gram
{
  using namespace util;
}
namespace gram
{
  using namespace msg;
}
namespace gram
{
  FileReader::FileReader (util::Filename const & filename)
    : m_filename (filename), m_state (FILE_START), m_buf_beg (0), m_buf_end (0), m_peek_beg (0), m_peek_end (0)
    {
      // allocate file buffer
      m_buf = new char [FILE_BUF_SIZE];
    }
}
namespace gram
{
  FileReader::FileReader (util::String const & str, util::Loc const & loc)
    : m_filename (loc.getFilename ()), m_state (FILE_EOF), m_peek_beg (0), m_peek_end (0)
    {
      // save string in buffer
      int len = str.length ();
      m_buf = new char [len + 1];
      m_buf_beg = m_buf;
      m_buf_end = m_buf_beg + len;
      str.copy (m_buf, len);
    }
}
namespace gram
{
  FileReader::~ FileReader ()
    {
      // free buffer
      delete [] m_buf;
    }
}
namespace gram
{
  bool FileReader::peekChar (char & ch, int n)
    {
      int i = (m_peek_beg + n) % MAX_PEEK;
      if (i == m_peek_end)
      {
        if (! readDirectChar (m_peek_buf [m_peek_end]))
        {
          return false;
        }
        m_peek_end = (m_peek_end + 1) % MAX_PEEK;
      }
      ch = m_peek_buf [i]; 
      return true;
    }
}
namespace gram
{
  bool FileReader::readChar (char & ch)
    {
      // check in peek buffer first
      if (m_peek_beg == m_peek_end)
      {
        if (! readDirectChar (ch))
        {
          return false;
        }
      }
      else
      {
        ch = m_peek_buf [m_peek_beg];
        m_peek_beg = (m_peek_beg + 1) % MAX_PEEK;
      }
      return true;
    }
}
namespace gram
{
  void FileReader::pause ()
    {
      if (m_state == FILE_OPEN)
      {
        // save file position
        if (fgetpos (m_fp, & m_file_pos) != 0)
        {
          // file access error
          msg::fileAccessError (util::Loc (), m_filename.getName ());
          throw util::Exception ();
        }
        fclose (m_fp);
        m_state = FILE_CLOSED;
      }
    }
}
namespace gram
{
  bool FileReader::readDirectChar (char & ch)
    {
      // otherwise read from file
      if (m_buf_beg == m_buf_end && m_state != FILE_EOF)
      {
        if (m_state == FILE_CLOSED || m_state == FILE_START)
        {
          m_fp = fopen (m_filename.getName (), "r");
          if (! m_fp)
          {
            msg::fileOpenError (util::Loc (), m_filename.getName ());
            throw util::Exception ();
          }
          // advance file pointer if closed
          if (m_state == FILE_CLOSED)
          {
            // set file position
            if (fsetpos (m_fp, & m_file_pos) != 0)
            {
              // file access error
              msg::fileAccessError (util::Loc (), m_filename.getName ());
              throw util::Exception ();
            }
          }
        }
        // read characters into buffer
        int num_read = fread (m_buf, sizeof (char), FILE_BUF_SIZE, m_fp);
        // check if end of file
        if (feof (m_fp))
        {
          // close file
          fclose (m_fp);
          m_state = FILE_EOF;
        }
        else
        {
          // otherwise make sure some characters were read
          if (num_read == 0)
          {
            // file access error
            msg::fileAccessError (util::Loc (), m_filename.getName ());
            throw util::Exception ();
          }
          // file is now open
          m_state = FILE_OPEN;
        }
        // set buf bounds
        m_buf_beg = m_buf;
        m_buf_end = m_buf_beg + num_read;
      }
      // get next char
      if (m_buf_beg == m_buf_end)
      {
        return false;
      }
      ch = * m_buf_beg ++;
      return true;
    }
}
#undef LZZ_INLINE
