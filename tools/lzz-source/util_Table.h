// util_Table.h
//

#ifndef LZZ_util_Table_h
#define LZZ_util_Table_h
// library
#include <stddef.h>
#define LZZ_INLINE inline
namespace util
{
  struct TableNode
  {
    size_t handle;
    size_t bit_mask;
    TableNode * left;
    TableNode * right;
    TableNode (size_t handle, size_t bit_mask);
    ~ TableNode ();
  };
}
namespace util
{
  class Table
  {
    TableNode * m_root;
  public:
    Table ();
    ~ Table ();
    bool addHandle (size_t handle);
  private:
    size_t get_fdb_mask (size_t handle1, size_t handle2);
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "util_Table.inl"
#endif
#endif
