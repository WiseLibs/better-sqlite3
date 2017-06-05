// gram_CharReader.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE CharReader::Char::Char ()
                     {}
}
namespace gram
{
  LZZ_INLINE CharReader::Char::Char (char c, int cols)
    : c (c), cols (cols)
                                                          {}
}
namespace gram
{
  LZZ_INLINE void CharReader::pause ()
    {
      m_file_reader.pause ();
    }
}
#undef LZZ_INLINE
