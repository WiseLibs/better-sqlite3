// smtc_CopyInit.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE CopyInit::CopyInit (util::Loc const & loc, gram::Block const & block)
    : Init (loc), m_block (block)
    {}
}
namespace smtc
{
  LZZ_INLINE gram::Block const & CopyInit::getBlock () const
    {
      return m_block;
    }
}
#undef LZZ_INLINE
