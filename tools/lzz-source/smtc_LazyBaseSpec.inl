// smtc_LazyBaseSpec.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE gram::BlockVector const & LazyBaseSpec::getArgSet () const
    {
      return m_arg_set;
    }
}
#undef LZZ_INLINE
