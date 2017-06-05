// util_Table.cpp
//

#include "util_Table.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_Table.inl"
#endif
#define LZZ_INLINE inline
namespace util
{
  TableNode::~ TableNode ()
    {
      if (left->bit_mask > bit_mask)
      {
        delete left;
      }
      if (right->bit_mask > bit_mask)
      {
        delete right;
      }
    }
}
namespace util
{
  Table::Table ()
    {
      m_root = new TableNode (0, 0xFFFFFFFF);
      m_root->left = m_root;
      m_root->right = m_root;
    }
}
namespace util
{
  Table::~ Table ()
    {
      delete m_root;
    }
}
namespace util
{
  bool Table::addHandle (size_t handle)
    {
      // find closest match
      TableNode * n, * m, ** p;
      size_t bit_mask;
      n = m_root;
      do
      {
        bit_mask = n->bit_mask;
        if (handle & bit_mask)
        {
          n = n->right;
        }
        else
        {
          n = n->left;
        }
      }
      while (bit_mask < n->bit_mask);
      // is equal
      if (handle == n->handle)
      {
        return false;
      }
      size_t dif_bit_mask = get_fdb_mask (handle, n->handle);
      // where to insert it?
      p = & m_root;
      for (bit_mask = 0; dif_bit_mask > (n = * p)->bit_mask && bit_mask < n->bit_mask;)
      {
        bit_mask = n->bit_mask;
        if (handle & bit_mask)
        {
          p = & n->right;
        }
        else
        {
          p = & n->left;
        }
      }
      // create a new node
      m = new TableNode (handle, dif_bit_mask);
      // add left and right nodes
      if (handle & dif_bit_mask)
      {
        m->right = m;
        m->left = n;
      }
      else
      {
        m->left = m;
        m->right = n;
      }
      * p = m;
      return true;
    }
}
#undef LZZ_INLINE
