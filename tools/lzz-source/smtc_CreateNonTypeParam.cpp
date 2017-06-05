// smtc_CreateNonTypeParam.cpp
//

#include "smtc_CreateNonTypeParam.h"
// semantic
#include "smtc_NonTypeParam.h"
#define LZZ_INLINE inline
namespace smtc
{
  NonTypeParamPtr createNonTypeParam (int flags, CvType const & cv_type, NamePtr const & name, gram::Block const & def_arg)
  {
    if (def_arg.isSet ())
    {
      def_arg.trim ();
    }
    return new NonTypeParam (flags, cv_type, name, def_arg);
  }
}
#undef LZZ_INLINE
