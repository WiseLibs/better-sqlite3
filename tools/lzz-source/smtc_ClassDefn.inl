// smtc_ClassDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE BaseSpecPtrVector const & ClassDefn::getBaseSpecSet () const
    {
      return m_base_spec_set;
    }
}
namespace smtc
{
  LZZ_INLINE EntityPtrDeque const & ClassDefn::getEntitySet () const
    {
      return m_entity_set;
    }
}
#undef LZZ_INLINE
