// smtc_ParamToNavCtorParam.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE ParamPtr ParamToNavCtorParam::operator () (ParamPtr const & param) const
  {
    return paramToNavCtorParam (param);
  }
}
namespace smtc
{
  LZZ_INLINE ParamToNavCtorParam::ParamToNavCtorParam ()
                  {}
}
#undef LZZ_INLINE
