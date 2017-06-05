// basl_Node.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE Node::Node ()
    {}
}
namespace basl
{
  LZZ_INLINE Token & Node::getToken ()
    {
      return token;
    }
}
namespace basl
{
  LZZ_INLINE Nonterm & Node::getNonterm ()
    {
      return nonterm;
    }
}
#undef LZZ_INLINE
