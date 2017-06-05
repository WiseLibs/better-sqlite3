// smtc_AccessSpec.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE AccessSpec::AccessSpec (util::Loc const & loc, Access access)
    : m_loc (loc), m_access (access)
    {}
}
namespace smtc
{
  LZZ_INLINE util::Loc const & AccessSpec::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE Access AccessSpec::getAccess () const
    {
      return m_access;
    }
}
#undef LZZ_INLINE
