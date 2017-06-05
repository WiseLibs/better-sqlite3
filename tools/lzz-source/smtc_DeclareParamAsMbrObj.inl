// smtc_DeclareParamAsMbrObj.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE void DeclareParamAsMbrObj::operator () (ParamPtr const & param) const
  {
    declareParamAsMbrObj (lazy_class, param, as_ref);
  }
}
namespace smtc
{
  LZZ_INLINE DeclareParamAsMbrObj::DeclareParamAsMbrObj (LazyClassPtr const & lazy_class, bool as_ref)
    : lazy_class (lazy_class), as_ref (as_ref)
              {}
}
#undef LZZ_INLINE
