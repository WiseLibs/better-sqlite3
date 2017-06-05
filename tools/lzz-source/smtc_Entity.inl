// smtc_Entity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE Entity::Entity ()
    {}
}
namespace smtc
{
  LZZ_INLINE Entity::~ Entity ()
    {}
}
#undef LZZ_INLINE
