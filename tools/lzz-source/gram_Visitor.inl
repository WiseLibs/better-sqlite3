// gram_Visitor.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace gram
{
  LZZ_INLINE Visitor::Visitor (bool slippery)
    : m_slippery (slippery)
    {}
}
#undef LZZ_INLINE
