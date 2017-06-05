// gram_LineMacro.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE LineMacro::LineMacro (util::Loc const & loc, util::Ident const & name)
    : Macro (loc, name)
    {}
}
#undef LZZ_INLINE
