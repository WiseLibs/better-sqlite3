// gram_CheckMacroRepSet.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE bool checkMacroRepSet (bool is_func, util::IdentVector const & param_set, bool var, basl::TokenVector & rep_set)
  {
    return is_func ? checkFuncMacroRepSet (param_set, var, rep_set) : checkObjMacroRepSet (rep_set);
  }
}
#undef LZZ_INLINE
