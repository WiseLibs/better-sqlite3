// util_DataTable.h
//

#ifndef LZZ_util_DataTable_h
#define LZZ_util_DataTable_h
// library
#include <stddef.h>
#include <assert.h>
#define LZZ_INLINE inline
namespace util
{
  template <typename T>
  struct DataTableNode
  {
    size_t handle;
    size_t bit_mask;
    T data;
    DataTableNode <T> * left;
    DataTableNode <T> * right;
    DataTableNode (size_t handle, size_t bit_mask, T const & data);
    ~ DataTableNode ();
  };
}
namespace util
{
  template <typename T>
  class DataTableFindResult
  {
    T * m_data;
    size_t m_handle;
    size_t m_dif_bit_mask;
  public:
    DataTableFindResult (T & data);
    DataTableFindResult (size_t handle, size_t dif_bit_mask);
    ~ DataTableFindResult ();
    bool hasData () const;
    T & getData ();
    size_t getDifBitMask () const;
    size_t getHandle () const;
  };
}
namespace util
{
  template <typename T>
  class DataTableIter
  {
    DataTableNode <T> const * (m_visit) [sizeof (size_t) * 8];
    int m_next;
  public:
    DataTableIter (DataTableNode <T> const * m_root);
    ~ DataTableIter ();
    bool hasMoreElements () const;
    T const & getNextElement ();
  };
}
namespace util
{
  template <typename T>
  class DataTable
  {
    DataTableNode <T> * m_root;
  public:
    DataTable ();
    ~ DataTable ();
    void init ();
    void clear ();
    DataTableFindResult <T> findData (size_t handle) const;
    void addData (size_t handle, T const & data);
    void addData (DataTableFindResult <T> const & find_result, T const & data);
    void removeData (size_t handle);
    DataTableIter <T> getElements () const;
    DataTableNode <T> const * getRoot () const;
  private:
    DataTable (DataTable <T> const & data_table);
  };
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool DataTableFindResult <T>::hasData () const
    {
      return m_data != 0;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE T & DataTableFindResult <T>::getData ()
    {
      assert (hasData ());
      return * m_data;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE size_t DataTableFindResult <T>::getDifBitMask () const
    {
      return m_dif_bit_mask;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE size_t DataTableFindResult <T>::getHandle () const
    {
      return m_handle;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void DataTable <T>::addData (size_t handle, T const & data)
    {
      DataTableFindResult <T> find_result = findData (handle);
      assert (! find_result.hasData ());
      addData (find_result, data);
    }
}
#undef LZZ_INLINE
#endif
