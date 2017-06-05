// smtc_PrintObjDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintObjDecl::PrintObjDecl (NamePtr const & qual_name)
    : qual_name (qual_name), is_extern (false), not_extern (false), not_static (false), with_init (false)
    {}
}
#undef LZZ_INLINE
