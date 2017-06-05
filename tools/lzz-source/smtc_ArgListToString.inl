// smtc_ArgListToString.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::String argListToString (gram::BlockVector const & arg_list)
  {
    int num_lines = 0;
    return argListToString (arg_list, num_lines);
  }
}
#undef LZZ_INLINE
