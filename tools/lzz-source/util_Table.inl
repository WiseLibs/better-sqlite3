// util_Table.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE TableNode::TableNode (size_t handle, size_t bit_mask)
    : handle (handle), bit_mask (bit_mask)
    {}
}
namespace util
{
  LZZ_INLINE size_t Table::get_fdb_mask (size_t handle1, size_t handle2)
    {
      int i, k;
      for (i = 1, k = handle1 ^ handle2; ! (k & i); i <<= 1);
      return i;
    }
}
#undef LZZ_INLINE
