// smtc_Cv.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE Cv::Cv ()
    : m_c (false), m_v (false)
    {}
}
namespace smtc
{
  LZZ_INLINE Cv::Cv (bool c, bool v)
    : m_c (c), m_v (v)
    {}
}
namespace smtc
{
  LZZ_INLINE bool Cv::isSet () const
    {
      return m_c || m_v;
    }
}
namespace smtc
{
  LZZ_INLINE bool Cv::isConstOnly () const
    {
      return m_c && ! m_v;
    }
}
namespace smtc
{
  LZZ_INLINE bool Cv::isVolatileOnly () const
    {
      return m_v && ! m_c;
    }
}
namespace smtc
{
  LZZ_INLINE bool Cv::isConst () const
    {
      return m_c;
    }
}
namespace smtc
{
  LZZ_INLINE bool Cv::isVolatile () const
    {
      return m_v;
    }
}
#undef LZZ_INLINE
