// smtc_Ns.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE EntityPtrDeque const & Ns::getEntitySet () const
    {
      return m_entity_set;
    }
}
#undef LZZ_INLINE
