// basl_SyntaxTree.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE bool SyntaxTree::isEmpty () const
    {
      return m_node == 0;
    }
}
namespace basl
{
  LZZ_INLINE Node & SyntaxTree::getNode () const
    {
      return * m_node;
    }
}
namespace basl
{
  LZZ_INLINE Node * SyntaxTree::pointer () const
    {
      return m_node;
    }
}
#undef LZZ_INLINE
