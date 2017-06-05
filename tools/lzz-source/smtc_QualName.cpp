// smtc_QualName.cpp
//

#include "smtc_QualName.h"
#include "smtc_NameVisitor.h"
#define LZZ_INLINE inline
namespace smtc
{
  QualName::QualName (NamePtr const & qual_name, NamePtr const & unql_name)
    : m_qual_name (qual_name), m_unql_name (unql_name)
    {}
}
namespace smtc
{
  QualName::~ QualName ()
    {}
}
namespace smtc
{
  NamePtr const & QualName::getQualName () const
    {
      return m_qual_name;
    }
}
namespace smtc
{
  NamePtr const & QualName::getUnqlName () const
    {
      return m_unql_name;
    }
}
namespace smtc
{
  void QualName::accept (NameVisitor const & visitor) const
    {
      visitor.visit (* this);
    }
}
#undef LZZ_INLINE
