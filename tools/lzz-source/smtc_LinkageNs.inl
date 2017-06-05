// smtc_LinkageNs.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Ident const & LinkageNs::getLinkage () const
    {
      return m_linkage;
    }
}
#undef LZZ_INLINE
