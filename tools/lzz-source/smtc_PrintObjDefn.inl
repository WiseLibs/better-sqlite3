// smtc_PrintObjDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintObjDefn::PrintObjDefn (NamePtr const & qual_name)
    : PrintObjDecl (qual_name)
    {
      with_init = true;
    }
}
#undef LZZ_INLINE
