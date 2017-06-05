// smtc_ClassDefnEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ClassDefnEntity::ClassDefnEntity (ClassDefnPtr const & class_defn)
    : ClassDeclEntity (class_defn)
    {}
}
#undef LZZ_INLINE
