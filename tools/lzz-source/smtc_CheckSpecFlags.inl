// smtc_CheckSpecFlags.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE void checkValidSpecFlags (gram::SpecSel const & spec_sel, int flags, InvalidMsg msg)
  {
    checkInvalidSpecFlags (spec_sel, ~ flags, msg);
  }
}
#undef LZZ_INLINE
