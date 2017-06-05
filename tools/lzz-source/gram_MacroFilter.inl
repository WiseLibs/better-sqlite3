// gram_MacroFilter.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE MacroFilter::MacroFilter (bool is_final, bool is_if, util::IdentVector & history, basl::TokenDeque & out_set)
    : is_final (is_final), is_if (is_if), history (history), out_set (out_set), state (START_STATE), nest (0), is_sub (false)
        {}
}
namespace gram
{
  LZZ_INLINE FileMacroFilter::FileMacroFilter (basl::TokenDeque & out_set)
    : MacroFilter (true, false, history, out_set)
        {}
}
namespace gram
{
  LZZ_INLINE HashIfMacroFilter::HashIfMacroFilter (basl::TokenDeque & out_set)
    : MacroFilter (true, true, history, out_set)
        {}
}
#undef LZZ_INLINE
