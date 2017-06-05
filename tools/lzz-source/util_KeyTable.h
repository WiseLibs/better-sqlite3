// util_KeyTable.h
//

#ifndef LZZ_util_KeyTable_h
#define LZZ_util_KeyTable_h
// std lib
#include <cstddef>
#include <cstring>
#include <list>
#define LZZ_INLINE inline
namespace util
{
  template <typename T>
  class Key
  {
    T const * m_data;
    int m_len;
    enum
    {
      NUM_BITS = sizeof (T) * 8
    };
  public:
    Key (T const * data, int len);
    int isBitSet (int i);
    int getDiffBit (T const * data, int len);
    bool compare (T const * data, int len);
    int getLength () const;
    T const * getData () const;
  };
}
namespace util
{
  template <typename T>
  bool operator == (Key <T> const & a, Key <T> const & b);
}
namespace util
{
  template <typename T>
  class KeyBlock
  {
    T * m_data;
    T * m_cur;
    T * m_end;
    T * m_beg;
    enum
    {
      BLOCKSIZE = 512
    };
  public:
    KeyBlock ();
    KeyBlock (T const * beg, int len);
    ~ KeyBlock ();
    bool push (T t);
    void discard ();
    void commit ();
    T const * getBeg (int & len) const;
  };
}
namespace util
{
  template <typename T>
  class KeyStorage
  {
    std::list <KeyBlock <T> *> m_key_block_list;
  public:
    KeyStorage ();
    ~ KeyStorage ();
    void push (T t);
    void discard ();
    void commit ();
    Key <T> getKey ();
  private:
    KeyStorage (KeyStorage <T> const & ks);
  };
}
namespace util
{
  template <typename T>
  struct KeyNode
  {
    Key <T> key;
    int bit;
    KeyNode <T> * left;
    KeyNode <T> * right;
    KeyNode (Key <T> const & key, int bit);
    ~ KeyNode ();
  };
}
namespace util
{
  template <typename T>
  class KeyTable
  {
    KeyNode <T> * m_root;
    KeyStorage <T> m_key_stor;
  public:
    KeyTable ();
    ~ KeyTable ();
    void push (T item);
    void discard ();
    Key <T> const * getKey ();
    size_t getHandle ();
  };
}
namespace util
{
  template <typename T>
  LZZ_INLINE Key <T>::Key (T const * data, int len)
    : m_data (data), m_len (len)
    {}
}
namespace util
{
  template <typename T>
  LZZ_INLINE int Key <T>::isBitSet (int i)
    {
      return ((i / NUM_BITS) < m_len) && ((m_data [i / NUM_BITS] & (1 << (i % NUM_BITS))) != 0);
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE int Key <T>::getLength () const
    {
      return m_len;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE T const * Key <T>::getData () const
    {
      return m_data;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool operator == (Key <T> const & a, Key <T> const & b)
  {
    return a.getData () == b.getData ();
  }
}
namespace util
{
  template <typename T>
  LZZ_INLINE bool KeyBlock <T>::push (T t)
    {
      if (m_cur != m_end)
      {
        * m_cur ++ = t;
        return true;
      }
      return false;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void KeyBlock <T>::discard ()
    {
      m_cur = m_beg;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void KeyBlock <T>::commit ()
    {
      m_beg = m_cur;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE T const * KeyBlock <T>::getBeg (int & len) const
    {
      len = m_cur - m_beg;
      return m_beg;
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void KeyStorage <T>::discard ()
    {
      m_key_block_list.back ()->discard ();
    }
}
namespace util
{
  template <typename T>
  LZZ_INLINE void KeyStorage <T>::commit ()
    {
      m_key_block_list.back ()->commit ();
    }
}
#undef LZZ_INLINE
#endif
