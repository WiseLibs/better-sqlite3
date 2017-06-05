// smtc_NavSubmitFuncDefnEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE NavSubmitFuncDefnPtr NavSubmitFuncDefnEntity::getNavSubmitFuncDefn () const
    {
      return getFuncDecl ();
    }
}
#undef LZZ_INLINE
