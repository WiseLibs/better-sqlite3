// smtc_VdfClassEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE VdfClassEntity::VdfClassEntity (ClassDefnPtr const & class_defn)
    : ClassDefnEntity (class_defn)
    {}
}
#undef LZZ_INLINE
