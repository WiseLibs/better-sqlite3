// util_GetIdent.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE util::Ident getIdent (util::String const & str)
  {
    return getIdent (str.c_str ());
  }
}
#undef LZZ_INLINE
