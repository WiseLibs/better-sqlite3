// basl_RefStack.h
//

#ifndef LZZ_basl_RefStack_h
#define LZZ_basl_RefStack_h
#define LZZ_INLINE inline
namespace basl
{
  template <typename DATA>
  struct RefStackElem
  {
    RefStackElem <DATA> * prev;
    DATA data;
    int num_ref;
  };
}
namespace basl
{
  template <typename DATA>
  class RefStackPool
  {
    RefStackElem <DATA> * m_recycled_elem;
  public:
    RefStackPool ();
    ~ RefStackPool ();
    RefStackElem <DATA> * getNewElem (RefStackElem <DATA> * prev, DATA const & data);
    void freeElem (RefStackElem <DATA> * elem);
  };
}
namespace basl
{
  template <typename DATA>
  class RefStack
  {
    RefStackElem <DATA> * m_elem;
    static RefStackPool <DATA> m_elem_pool;
  public:
    RefStack ();
    RefStack (RefStack <DATA> const & stack);
    ~ RefStack ();
    RefStack <DATA> const & operator = (RefStack <DATA> const & stack);
    DATA const & back () const;
    void pop_back ();
    void pop_back (int num);
    void push_back (DATA const & data);
  };
}
namespace basl
{
  template <typename DATA>
  LZZ_INLINE DATA const & RefStack <DATA>::back () const
    {
      return m_elem->data;
    }
}
#undef LZZ_INLINE
#endif
