// util_KeyTable.tpl
//

#include "util_KeyTable.h"
namespace util
{
  template <typename T>
  int Key <T>::getDiffBit (T const * data, int len)
    {
      unsigned int i, j, x;
      // get first diff int
      for (i = 0; m_data [i] == data [i]; i ++);
      // get first diff bit
      for (x = m_data [i] ^ data [i], j = 0; ! (x & (1 << j)); j ++);
      return (i * NUM_BITS) + j;
    }
}
namespace util
{
  template <typename T>
  bool Key <T>::compare (T const * data, int len)
    {
      return (m_len == len) && (memcmp (m_data, data, sizeof (T) * len) == 0);
    }
}
namespace util
{
  template <typename T>
  KeyBlock <T>::KeyBlock ()
    {
      int size = BLOCKSIZE;
      m_data = new T [size];
      m_cur = m_data;
      m_end = m_data + size;
      m_beg = m_data;
    }
}
namespace util
{
  template <typename T>
  KeyBlock <T>::KeyBlock (T const * beg, int len)
    {
      int size = (len >= BLOCKSIZE) ? (len + BLOCKSIZE / 2) : (BLOCKSIZE);
      m_data = new T [size];
      memcpy (m_data, beg, len * sizeof (T));
      m_cur = m_data + len;
      m_end = m_data + size;
      m_beg = m_data;
    }
}
namespace util
{
  template <typename T>
  KeyBlock <T>::~ KeyBlock ()
    {
      delete [] m_data;
    }
}
namespace util
{
  template <typename T>
  KeyStorage <T>::KeyStorage ()
    {
      m_key_block_list.push_back (new KeyBlock <T> ());
    }
}
namespace util
{
  template <typename T>
  KeyStorage <T>::~ KeyStorage ()
    {
      // delete blocks
      for (typename std::list <KeyBlock <T> *>::iterator i = m_key_block_list.begin (); i != m_key_block_list.end (); ++ i)
      {
        delete * i;
      }
    }
}
namespace util
{
  template <typename T>
  void KeyStorage <T>::push (T t)
    {
      KeyBlock <T> & key_block = * m_key_block_list.back ();
      if (! key_block.push (t))
      {
        int len;
        T const * beg = key_block.getBeg (len);
        m_key_block_list.push_back (new KeyBlock <T> (beg, len));
        m_key_block_list.back ()->push (t);
      }
    }
}
namespace util
{
  template <typename T>
  Key <T> KeyStorage <T>::getKey ()
    {
      // terminate key with 0
      push (0);
      int len;
      T const * beg = m_key_block_list.back ()->getBeg (len);
      return Key <T> (beg, len);
    }
}
namespace util
{
  template <typename T>
  KeyNode <T>::KeyNode (Key <T> const & key, int bit)
    : key (key), bit (bit)
    {}
}
namespace util
{
  template <typename T>
  KeyNode <T>::~ KeyNode ()
    {
      if (left->bit > bit)
      {
        delete left;
      }
      if (right->bit > bit)
      {
        delete right;
      }
    }
}
namespace util
{
  template <typename T>
  KeyTable <T>::KeyTable ()
    {
      // create null key
      Key <T> key = m_key_stor.getKey ();
      m_key_stor.commit ();
      // create root node with max bit
      m_root = new KeyNode <T> (key, 0x7FFFFFFF);
      m_root->left = m_root;
      m_root->right = m_root;
    }
}
namespace util
{
  template <typename T>
  KeyTable <T>::~ KeyTable ()
    {
      delete m_root;
    }
}
namespace util
{
  template <typename T>
  void KeyTable <T>::push (T item)
    {
      m_key_stor.push (item);
    }
}
namespace util
{
  template <typename T>
  void KeyTable <T>::discard ()
    {
      m_key_stor.discard ();
    }
}
namespace util
{
  template <typename T>
  Key <T> const * KeyTable <T>::getKey ()
    {
      KeyNode <T> * n, * m, ** p;
      int bit, dif;
      Key <T> key = m_key_stor.getKey ();
      // find closest match
      n = m_root;
      do
      {
        bit = n->bit;
        if (key.isBitSet (bit))
        {
          n = n->right;
        }
        else
        {
          n = n->left;
        }
      }
      while (bit < n->bit);
      // is equal
      if (key.compare (n->key.getData (), n->key.getLength ()))
      {
        // discard data
        m_key_stor.discard ();
        // save node
        m = n;
      }
      else
      {
        // commit data
        m_key_stor.commit ();
        // get first different bit
        dif = key.getDiffBit (n->key.getData (), n->key.getLength ());
        // where to insert it?
        p = & m_root;
        for (bit = -1; dif > (n = * p)->bit && bit < n->bit;)
        {
          bit = n->bit;
          if (key.isBitSet (bit))
          {
            p = & n->right;
          }
          else
          {
            p = & n->left;
          }
        }
        // create new node
        m = new KeyNode <T> (key, dif);
        if (key.isBitSet (dif))
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
      // return pointer to new key
      return & m->key;
    }
}
namespace util
{
  template <typename T>
  size_t KeyTable <T>::getHandle ()
    {
      return (size_t) getKey ();
    }
}
