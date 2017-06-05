// gram_FileReader.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE util::Filename const & FileReader::getFilename () const
    {
      return m_filename;
    }
}
#undef LZZ_INLINE
