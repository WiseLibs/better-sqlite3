// smtc_FrndFuncDefnEntity.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE FuncDefnPtr const & FrndFuncDefnEntity::getFuncDefn () const
    {
      return m_func_defn;
    }
}
#undef LZZ_INLINE
