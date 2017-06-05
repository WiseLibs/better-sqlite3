// smtc_Init.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE Init::Init (util::Loc const & loc)
    : m_loc (loc)
    {}
}
namespace smtc
{
  LZZ_INLINE util::Loc const & Init::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE bool Init::isDirect () const
    {
      return ! isCopy ();
    }
}
#undef LZZ_INLINE
