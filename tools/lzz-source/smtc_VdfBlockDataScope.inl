// smtc_VdfBlockDataScope.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE VdfDataFuncDefnPtr const & VdfBlockDataScope::getVdfDataFuncDefn () const
    {
      return m_vdf_data_func_defn;
    }
}
#undef LZZ_INLINE
