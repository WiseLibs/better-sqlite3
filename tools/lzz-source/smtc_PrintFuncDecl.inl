// smtc_PrintFuncDecl.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE PrintFuncDecl::PrintFuncDecl (NamePtr const & qual_name)
    : qual_name (qual_name), is_frnd (false), is_inst (false), is_decl (false), not_inline (false), not_explicit (false), not_static (false), not_virtual (false), not_external (false), not_pure (false), use_alt_ret_type (false)
    {}
}
#undef LZZ_INLINE
