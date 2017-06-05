// smtc_PrintTmplObjDefn.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintTmplObjDefn::PrintTmplObjDefn (NamePtr const & qual_name)
    : PrintObjDefn (qual_name)
    {}
}
#undef LZZ_INLINE
