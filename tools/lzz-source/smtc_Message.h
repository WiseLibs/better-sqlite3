// smtc_Message.h
//

#ifndef LZZ_smtc_Message_h
#define LZZ_smtc_Message_h
// util
#include "util_Ident.h"
#include "util_Loc.h"
#include "util_String.h"
#define LZZ_INLINE inline
namespace smtc
{
  namespace msg
  {
    void fileQualNs (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void templateNs (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidObjSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidNsObjSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidClassObjSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void conflictingObjSpec (util::Loc const & loc, char const * spec1, char const * spec2);
  }
}
namespace smtc
{
  namespace msg
  {
    void nonStaticClassObjWithInit (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void templateObj (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void instantiateObj (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassObj (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidSpecWithLinkageSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void multipleLinkageSpec (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidLinkageSpec (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void nsBitfield (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidBitfieldSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidCatchParamSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidFuncParamSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidNonTypeParamSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualParamName (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void templateTdef (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void instantiateTdef (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualTdef (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassClassDefn (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualEnumDefn (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidFuncSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidNsFuncSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidClassFuncSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void conflictingFuncSpec (util::Loc const & loc, char const * spec1, char const * spec2);
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidFriendFuncSpec (util::Loc const & loc, char const * spec);
  }
}
namespace smtc
{
  namespace msg
  {
    void nsFriendFuncDecl (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void nsFriendFuncDefn (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void friendFuncInst (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassFuncDecl (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassFuncDefn (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void qualFriendFuncDefn (util::Loc const & loc);
  }
}
namespace smtc
{
  namespace msg
  {
    void noFilenames ();
  }
}
namespace smtc
{
  namespace msg
  {
    void fileOpenError (util::String const & filename);
  }
}
namespace smtc
{
  namespace msg
  {
    void tempFileOpenError ();
  }
}
namespace smtc
{
  namespace msg
  {
    void navAlreadyHasReturn (util::Loc const & loc);
  }
}
#undef LZZ_INLINE
#endif
