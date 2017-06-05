// smtc_LinkageSpecScope.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE LinkageSpecScope::LinkageSpecScope (ScopePtr const & parent, util::Loc const & loc, Linkage const & linkage)
    : m_parent (parent), m_loc (loc), m_linkage (linkage)
    {}
}
namespace smtc
{
  LZZ_INLINE ScopePtr const & LinkageSpecScope::getParent () const
    {
      return m_parent;
    }
}
namespace smtc
{
  LZZ_INLINE util::Loc const & LinkageSpecScope::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE Linkage const & LinkageSpecScope::getLinkage () const
    {
      return m_linkage;
    }
}
#undef LZZ_INLINE
