// smtc_CtorInit.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE MbrInitPtrVector const & CtorInit::getMbrInitSet () const
    {
      return m_mbr_init_set;
    }
}
#undef LZZ_INLINE
