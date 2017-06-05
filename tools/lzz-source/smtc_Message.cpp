// smtc_Message.cpp
//

#include "smtc_Message.h"
// semantic
#include "msg_Message.h"
#include "msg_Output.h"
#define LZZ_INLINE inline
namespace smtc
{
  namespace msg
  {
    using namespace ::msg;
  }
}
namespace smtc
{
  namespace msg
  {
    void fileQualNs (util::Loc const & loc)
  {
    static char const str [] = "Cannot define a globally qualified namespace.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void templateNs (util::Loc const & loc)
  {
    static char const str [] = "Cannot define a namespace with a template-id.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidObjSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid object specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidNsObjSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid namespace object specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidClassObjSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid class object specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void conflictingObjSpec (util::Loc const & loc, char const * spec1, char const * spec2)
  {
    static char const str [] = "Conflicting object specifiers: '%1' and '%2'.";
    print (loc, Message (ERROR_MSG, str) << spec1 << spec2);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void nonStaticClassObjWithInit (util::Loc const & loc)
  {
    static char const str [] = "A non static class object cannot have an initializer.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void templateObj (util::Loc const & loc)
  {
    static char const str [] = "Cannot declare a template object.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void instantiateObj (util::Loc const & loc)
  {
    static char const str [] = "Cannot explicitly instantiate an object.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassObj (util::Loc const & loc)
  {
    static char const str [] = "A class object cannot be qualified.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidSpecWithLinkageSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid in a declaration with a linkage specification.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void multipleLinkageSpec (util::Loc const & loc)
  {
    static char const str [] = "Multiple linkage specifications.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidLinkageSpec (util::Loc const & loc)
  {
    static char const str [] = "A linkage specifictaion is not valid in this context.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void nsBitfield (util::Loc const & loc)
  {
    static char const str [] = "A bitfield cannot be declared in a namespace.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidBitfieldSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid bitfield specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidCatchParamSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid catch parameter specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidFuncParamSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid function parameter specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidNonTypeParamSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid non-type parameter specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualParamName (util::Loc const & loc)
  {
    static char const str [] = "Cannot declare a qualified parameter.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void templateTdef (util::Loc const & loc)
  {
    static char const str [] = "Cannot declare a template typedef.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void instantiateTdef (util::Loc const & loc)
  {
    static char const str [] = "Cannot explicitly instantiate a typedef.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualTdef (util::Loc const & loc)
  {
    static char const str [] = "Cannot declare a qualified typedef.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassClassDefn (util::Loc const & loc)
  {
    static char const str [] = "Cannot define a qualified class inside a class.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualEnumDefn (util::Loc const & loc)
  {
    static char const str [] = "Cannot define a qualified enum.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidFuncSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid function specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidNsFuncSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid namespace function specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidClassFuncSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid class function specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void conflictingFuncSpec (util::Loc const & loc, char const * spec1, char const * spec2)
  {
    static char const str [] = "Conflicting function specifiers: '%1' and '%2'.";
    print (loc, Message (ERROR_MSG, str) << spec1 << spec2);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void invalidFriendFuncSpec (util::Loc const & loc, char const * spec)
  {
    static char const str [] = "'%1' is not a valid friend function specifier.";
    print (loc, Message (ERROR_MSG, str) << spec);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void nsFriendFuncDecl (util::Loc const & loc)
  {
    static char const str [] = "A friend function cannot be declared in a namespace.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void nsFriendFuncDefn (util::Loc const & loc)
  {
    static char const str [] = "A friend function cannot be defined in a namespace.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void friendFuncInst (util::Loc const & loc)
  {
    static char const str [] = "A friend function cannot be explicitly instantiated.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassFuncDecl (util::Loc const & loc)
  {
    static char const str [] = "A class function declaration cannot be qualified.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualClassFuncDefn (util::Loc const & loc)
  {
    static char const str [] = "A class function definition cannot be qualified.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void qualFriendFuncDefn (util::Loc const & loc)
  {
    static char const str [] = "A friend function definition cannot be qualified.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void noFilenames ()
  {
    static char const str [] = "No files specified.";
    print (Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void fileOpenError (util::String const & filename)
  {
    static char const str [] = "Error opening file '%1'.";
    print (Message (ERROR_MSG, str) << filename);
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void tempFileOpenError ()
  {
    static char const str [] = "Unable to open temporary files.";
    print (Message (ERROR_MSG, str));
  }
  }
}
namespace smtc
{
  namespace msg
  {
    void navAlreadyHasReturn (util::Loc const & loc)
  {
    static char const str [] = "Navigator already has a return statement.";
    print (loc, Message (ERROR_MSG, str));
  }
  }
}
#undef LZZ_INLINE
