// util_TrimBlock.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE void TrimBlock::operator () (Block const & block) const
  {
    block.trim ();
  }
}
namespace util
{
  LZZ_INLINE TrimBlock::TrimBlock ()
              {}
}
#undef LZZ_INLINE
