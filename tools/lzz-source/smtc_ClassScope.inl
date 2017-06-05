// smtc_ClassScope.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ClassDefnPtr const & ClassScope::getClassDefn () const
    {
      return m_class_defn;
    }
}
#undef LZZ_INLINE
