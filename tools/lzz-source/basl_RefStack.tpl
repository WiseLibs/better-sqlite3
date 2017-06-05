// basl_RefStack.tpl
//

#include "basl_RefStack.h"
namespace basl
{
  template <typename DATA>
  RefStackPool <DATA>::RefStackPool ()
    : m_recycled_elem (0)
    {}
}
namespace basl
{
  template <typename DATA>
  RefStackPool <DATA>::~ RefStackPool ()
    {
      // free elems
      while (m_recycled_elem)
      {
        RefStackElem <DATA> * elem = m_recycled_elem;
        m_recycled_elem = elem->prev;
        delete elem;
      }
    }
}
namespace basl
{
  template <typename DATA>
  RefStackElem <DATA> * RefStackPool <DATA>::getNewElem (RefStackElem <DATA> * prev, DATA const & data)
    {
      RefStackElem <DATA> * elem;
      if (m_recycled_elem)
      {
        elem = m_recycled_elem;
        m_recycled_elem = elem->prev;
      }
      else
      {
        elem = new RefStackElem <DATA> ();
      }
      elem->prev = prev;
      elem->data = data;
      elem->num_ref = 1;
      return elem;
    }
}
namespace basl
{
  template <typename DATA>
  void RefStackPool <DATA>::freeElem (RefStackElem <DATA> * elem)
    {
      for (;;)
      {
        RefStackElem <DATA> * next = 0;
        if (elem->prev && -- elem->prev->num_ref == 0)
        {
          next = elem->prev;
        }
        elem->prev = m_recycled_elem;
        m_recycled_elem = elem;
        if (! next)
        {
          break;
        }
        elem = next;
      }
    }
}
namespace basl
{
  template <typename DATA>
  RefStackPool <DATA> RefStack <DATA>::m_elem_pool;
}
namespace basl
{
  template <typename DATA>
  RefStack <DATA>::RefStack ()
    : m_elem (0)
    {}
}
namespace basl
{
  template <typename DATA>
  RefStack <DATA>::RefStack (RefStack <DATA> const & stack)
    : m_elem (stack.m_elem)
    {
      if (m_elem)
      {
        ++ m_elem->num_ref;
      }
    }
}
namespace basl
{
  template <typename DATA>
  RefStack <DATA>::~ RefStack ()
    {
      if (m_elem && -- m_elem->num_ref == 0)
      {
        m_elem_pool.freeElem (m_elem);
      }
    }
}
namespace basl
{
  template <typename DATA>
  RefStack <DATA> const & RefStack <DATA>::operator = (RefStack <DATA> const & stack)
    {
      RefStackElem <DATA> * elem = stack.m_elem;
      if (elem)
      {
        ++ elem->num_ref;
      }
      if (m_elem && -- m_elem->num_ref == 0)
      {
        m_elem_pool.freeElem (m_elem);
      }
      m_elem = elem;
      return * this;
    }
}
namespace basl
{
  template <typename DATA>
  void RefStack <DATA>::pop_back ()
    {
      RefStackElem <DATA> * elem = m_elem->prev;
      if (elem)
      {
        ++ elem->num_ref;
      }
      if (-- m_elem->num_ref == 0)
      {
        m_elem_pool.freeElem (m_elem);
      }
      m_elem = elem;
    }
}
namespace basl
{
  template <typename DATA>
  void RefStack <DATA>::pop_back (int num)
    {
      RefStackElem <DATA> * elem = m_elem;
      for (int i = num; i > 0; -- i)
      {
        elem = elem->prev;
      }
      if (elem)
      {
        ++ elem->num_ref;
      }
      if (-- m_elem->num_ref == 0)
      {
        m_elem_pool.freeElem (m_elem);
      }
      m_elem = elem;
    }
}
namespace basl
{
  template <typename DATA>
  void RefStack <DATA>::push_back (DATA const & data)
    {
      m_elem = m_elem_pool.getNewElem (m_elem, data);
    }
}
