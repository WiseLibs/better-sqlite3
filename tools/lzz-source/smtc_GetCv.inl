// smtc_GetCv.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE Cv getCv (bool c, bool v)
  {
    return Cv (c, v);
  }
}
#undef LZZ_INLINE
