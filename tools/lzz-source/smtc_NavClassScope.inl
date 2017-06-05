// smtc_NavClassScope.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NavClassPtr NavClassScope::getNavClass () const
    {
      return getClassDefn ();
    }
}
#undef LZZ_INLINE
