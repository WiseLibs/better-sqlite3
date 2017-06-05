// smtc_HasLazyBaseSpecArg.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE bool HasLazyBaseSpecArg::operator () (BaseSpecPtr const & base_spec) const
  {
    return hasLazyBaseSpecArg (base_spec, arg);
  }
}
namespace smtc
{
  LZZ_INLINE HasLazyBaseSpecArg::HasLazyBaseSpecArg (util::String const & arg)
    : arg (arg)
              {}
}
#undef LZZ_INLINE
