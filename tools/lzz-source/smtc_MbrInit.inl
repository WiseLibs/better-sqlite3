// smtc_MbrInit.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NamePtr const & MbrInit::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  LZZ_INLINE util::String const & MbrInit::getArgSet () const
    {
      return m_arg_set;
    }
}
#undef LZZ_INLINE
