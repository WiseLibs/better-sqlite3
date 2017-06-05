// util_DataTable.tpl
//

#include "util_DataTable.h"
namespace util
{
  template <typename T>
  DataTableNode <T>::DataTableNode (size_t handle, size_t bit_mask, T const & data)
    : handle (handle), bit_mask (bit_mask), data (data)
    {}
}
namespace util
{
  template <typename T>
  DataTableNode <T>::~ DataTableNode ()
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
  template <typename T>
  DataTableFindResult <T>::DataTableFindResult (T & data)
    : m_data (& data)
    {}
}
namespace util
{
  template <typename T>
  DataTableFindResult <T>::DataTableFindResult (size_t handle, size_t dif_bit_mask)
    : m_data (0), m_handle (handle), m_dif_bit_mask (dif_bit_mask)
    {}
}
namespace util
{
  template <typename T>
  DataTableFindResult <T>::~ DataTableFindResult ()
    {}
}
namespace util
{
  template <typename T>
  DataTableIter <T>::DataTableIter (DataTableNode <T> const * m_root)
    : m_next (0)
    {
      if (m_root->handle != 0)
      {
        m_visit [m_next ++] = m_root;
      }
    }
}
namespace util
{
  template <typename T>
  DataTableIter <T>::~ DataTableIter ()
    {}
}
namespace util
{
  template <typename T>
  bool DataTableIter <T>::hasMoreElements () const
    {
      return m_next > 0;
    }
}
namespace util
{
  template <typename T>
  T const & DataTableIter <T>::getNextElement ()
    {
      const DataTableNode <T> * n = m_visit [-- m_next];
      if (n->right->handle != 0 && n->right->bit_mask > n->bit_mask)
      {
        m_visit [m_next ++] = n->right;
      }
      if (n->left->handle  != 0 && n->left->bit_mask  > n->bit_mask)
      {
        m_visit [m_next ++] = n->left;
      }
      return n->data;
    }
}
namespace util
{
  template <typename T>
  DataTable <T>::DataTable ()
    {
      init ();
    }
}
namespace util
{
  template <typename T>
  DataTable <T>::~ DataTable ()
    {
      delete m_root;
    }
}
namespace util
{
  template <typename T>
  void DataTable <T>::init ()
    {
      m_root = new DataTableNode <T> (0, 0xFFFFFFFF, T ());
      m_root->left = m_root;
      m_root->right = m_root;
    }
}
namespace util
{
  template <typename T>
  void DataTable <T>::clear ()
    {
      delete m_root;
      init ();
    }
}
namespace util
{
  template <typename T>
  DataTableFindResult <T> DataTable <T>::findData (size_t handle) const
    {
      DataTableNode <T> * n;
      size_t bit_mask;
      // find closest match
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
        return DataTableFindResult <T> (n->data);
      }
      else
      {
        size_t i = 1;
        for (int k = handle ^ n->handle; ! (k & i); i <<= 1);
        return DataTableFindResult <T> (handle, i);
      }
    }
}
namespace util
{
  template <typename T>
  void DataTable <T>::addData (DataTableFindResult <T> const & find_result, T const & data)
    {
      DataTableNode <T> * n, * m, ** p;
      size_t dif_bit_mask, bit_mask;
      size_t handle;
      // get difference bit and handle from find result
      dif_bit_mask = find_result.getDifBitMask ();
      handle = find_result.getHandle ();
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
      m = new DataTableNode <T> (handle, dif_bit_mask, data);
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
    }
}
namespace util
{
  template <typename T>
  void DataTable <T>::removeData (size_t handle)
    {
      DataTableNode <T> * n, * m, ** p, ** q;
      // find node
      p = & m_root;
      while (handle != (n = * p)->handle)
      {
        if (handle & n->bit_mask)
        {
          p = & n->right;
        }
        else
        {
          p = & n->left;
        }
      }
      // find node pointing to node
      q = p;
      while (n != (m = * q)->left && n != m->right)
      {
        if (handle & m->bit_mask)
        {
          q = & m->right;
        }
        else
        {
          q = & m->left;
        }
      }
      // replace n with m (ok if n == m)
      * p = m;
      if (n == m->right)
      {
        * q = m->left;
      }
      else
      {
        * q = m->right;
      }
      m->left = n->left;
      m->right = n->right;
      m->bit_mask = n->bit_mask;
      // make children of n point to n so deletion doesn't kill any other nodes
      n->left = n;
      n->right = n;
      delete n;
    }
}
namespace util
{
  template <typename T>
  DataTableIter <T> DataTable <T>::getElements () const
    {
      return DataTableIter <T> (m_root);
    }
}
namespace util
{
  template <typename T>
  DataTableNode <T> const * DataTable <T>::getRoot () const
    {
      return m_root;
    }
}
