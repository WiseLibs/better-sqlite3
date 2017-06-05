// smtc_LazyClassScope.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE LazyClassPtr LazyClassScope::getLazyClass () const
    {
      return getClassDefn ();
    }
}
#undef LZZ_INLINE
