// smtc_ObjEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ObjPtr const & ObjEntity::getObj () const
    {
      return m_obj;
    }
}
#undef LZZ_INLINE
