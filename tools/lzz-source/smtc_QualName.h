// smtc_QualName.h
//

#ifndef LZZ_smtc_QualName_h
#define LZZ_smtc_QualName_h
#include "smtc_Name.h"
#include "smtc_NamePtr.h"
#define LZZ_INLINE inline
namespace smtc
{
  class QualName : public Name
  {
    NamePtr m_qual_name;
    NamePtr m_unql_name;
  public:
    QualName (NamePtr const & qual_name, NamePtr const & unql_name);
    ~ QualName ();
    NamePtr const & getQualName () const;
    NamePtr const & getUnqlName () const;
    void accept (NameVisitor const & visitor) const;
  };
}
#undef LZZ_INLINE
#endif
