// smtc_GetEnumtor.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE EnumtorPtr getEnumtor (NamePtr const & name)
  {
    return getEnumtor (name, gram::Block ());
  }
}
#undef LZZ_INLINE
