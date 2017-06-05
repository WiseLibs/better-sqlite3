// util_Loc.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE bool Loc::isSet () const
    {
      return m_filename.isSet ();
    }
}
namespace util
{
  LZZ_INLINE Filename const & Loc::getFilename () const
    {
      return m_filename;
    }
}
namespace util
{
  LZZ_INLINE int Loc::getLine () const
    {
      return m_line;
    }
}
namespace util
{
  LZZ_INLINE int Loc::getColumn () const
    {
      return m_column;
    }
}
#undef LZZ_INLINE
