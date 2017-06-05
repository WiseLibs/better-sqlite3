// smtc_DirectInit.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE DirectInit::DirectInit (util::Loc const & loc, gram::BlockVector const & block_set)
    : Init (loc), m_block_set (block_set)
    {}
}
namespace smtc
{
  LZZ_INLINE gram::BlockVector const & DirectInit::getBlockSet () const
    {
      return m_block_set;
    }
}
#undef LZZ_INLINE
