// smtc_TryBlock.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Loc const & TryBlock::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE HandlerPtrVector const & TryBlock::getHandlerSeq () const
    {
      return m_handler_seq;
    }
}
#undef LZZ_INLINE
