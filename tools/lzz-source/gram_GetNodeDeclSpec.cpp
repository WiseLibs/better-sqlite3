// gram_GetNodeDeclSpec.cpp
//

#include "gram_GetNodeDeclSpec.h"
// gram
#include "gram_DclSpecFlags.h"
#include "gram_DclSpecToString.h"
#include "gram_DeclSpecFlags.h"
#include "gram_DeclSpecToString.h"
#include "gram_GetClassKey.h"
#include "gram_GetNodeName.h"
#include "gram_Message.h"
#include "gram_Nonterm.h"
#include "gram_TokenNumber.h"
#include "gram_Visitor.h"

// semantic
#include "smtc_GetBuiltInType.h"
#include "smtc_GetCvType.h"
#include "smtc_GetElabType.h"
#include "smtc_GetUserType.h"

// util
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace
{
  using namespace gram;
}
namespace
{
  enum
  {
    BOOL_SPEC = 1 << 0,
    CHAR_SPEC = 1 << 1,
    DOUBLE_SPEC = 1 << 2,
    FLOAT_SPEC = 1 << 3,
    INT_SPEC = 1 << 4,
    LONG_SPEC = 1 << 5,
    SHORT_SPEC = 1 << 6,
    SIGNED_SPEC = 1 << 7,
    UNSIGNED_SPEC = 1 << 8,
    VOID_SPEC = 1 << 9,
    WCHAR_SPEC = 1 << 10,
    LONG_LONG_SPEC = 1 << 11
  };
}
namespace
{
  char const * builtInSpecToString (int flag);
}
namespace
{
  enum
  {
    CONST_SPEC = 1 << 0,
    VOLATILE_SPEC = 1 << 1
  };
}
namespace
{
  char const * cvSpecToString (int flag);
}
namespace
{
  int firstFlag (int flags);
}
namespace
{
  struct GetNodeDeclSpec : Visitor
  {
    SpecSel & decl_spec_sel;
    SpecSel & dcl_spec_sel;
    SpecSel & bltn_spec_sel;
    SpecSel & cv_spec_sel;
    smtc::TypePtr & type;
    void visit (DeclSpecNode & node) const;
    void visit (FtorSpecNode & node) const;
    void visit (CVSpecNode & node) const;
    void visit (BuiltInTypeNode & node) const;
    void visit (UserTypeNode & node) const;
    void visit (ElabTypeNode & node) const;
  public:
    explicit GetNodeDeclSpec (SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, SpecSel & bltn_spec_sel, SpecSel & cv_spec_sel, smtc::TypePtr & type);
    ~ GetNodeDeclSpec ();
  };
}
namespace
{
  smtc::TypePtr getBuiltInType (SpecSel const & spec_sel);
}
namespace
{
  char const * builtInSpecToString (int flag)
  {
    char const * str;
    switch (flag)
    {
      case BOOL_SPEC:
      {
        str = "bool";
        break;
      }
      case CHAR_SPEC:
      {
        str = "char";
        break;
      }
      case DOUBLE_SPEC:
      {
        str = "double";
        break;
      }
      case FLOAT_SPEC:
      {
        str = "float";
        break;
      }
      case INT_SPEC:
      {
        str = "int";
        break;
      }
      case LONG_SPEC:
      {
        str = "long";
        break;
      }
      case LONG_LONG_SPEC:
      {
        str = "long long";
        break;
      }
      case SHORT_SPEC:
      {
        str = "short";
        break;
      }
      case SIGNED_SPEC:
      {
        str = "signed";
        break;
      }
      case UNSIGNED_SPEC:
      {
        str = "unsigned";
        break;
      }
      case VOID_SPEC:
      {
        str = "void";
        break;
      }
      case WCHAR_SPEC:
      {
        str = "wchar";
        break;
      }
    }
    return str;
  }
}
namespace
{
  char const * cvSpecToString (int flag)
  {
    char const * str;
    if (flag == CONST_SPEC)
    {
      str = "const";
    }
    else
    {
      str = "volatile";
    }
    return str;
  }
}
namespace
{
  int firstFlag (int flags)
  {
    assert (flags != 0);
    int flag = 1;
    while (! util::hasFlag (flags, flag))
    {
      flag <<= 1;
    }
    return flag;
  }
}
namespace
{
  void GetNodeDeclSpec::visit (DeclSpecNode & node) const
    {
      int flag = 0;
      if (node.getTYPEDEF_TOKEN ().getNumber () == TYPEDEF_TOKEN)
      {
        flag = TYPEDEF_SPEC;
      }
      else
      {
        flag = FRIEND_SPEC;
      }
      // can never have duplicate or both since not permitted by grammar
      decl_spec_sel.addSpec (flag, node.getTYPEDEF_TOKEN ().getLoc ());
    }
}
namespace
{
  void GetNodeDeclSpec::visit (FtorSpecNode & node) const
    {
      int flag = 0;
      switch (node.getFtorToken ().getNumber ())
      {
        case INLINE_TOKEN:
        {
          flag = INLINE_SPEC;
          break;
        }
        case VIRTUAL_TOKEN:
        {
          flag = VIRTUAL_SPEC;
          break;
        }
        case EXPLICIT_TOKEN:
        {
          flag = EXPLICIT_SPEC;
          break;
        }
        case STATIC_TOKEN:
        {
          flag = STATIC_SPEC;
          break;
        }
        case EXTERN_TOKEN:
        {
          flag = EXTERN_SPEC;
          break;
        }
        case MUTABLE_TOKEN:
        {
          flag = MUTABLE_SPEC;
          break;
        }
        case AUTO_TOKEN:
        {
          flag = AUTO_SPEC;
          break;
        }
        case REGISTER_TOKEN:
        {
          flag = REGISTER_SPEC;
          break;
        }
        case DLL_API_TOKEN:
        {
          flag = DLL_API_SPEC;
          break;
        }
      }
      util::Loc const & loc = node.getFtorToken ().getLoc ();
      if (dcl_spec_sel.hasSpec (flag))
      { 
        msg::duplicateSpecifier (loc, dclSpecToString (flag));
      }
      else
      {
        dcl_spec_sel.addSpec (flag, loc);
      }
    }
}
namespace
{
  void GetNodeDeclSpec::visit (CVSpecNode & node) const
    {
      int flag = 0;
      if (node.getCvToken ().getNumber () == CONST_TOKEN)
      {
        flag = CONST_SPEC;
      }
      else
      {
        flag = VOLATILE_SPEC;
      }
      util::Loc const & loc = node.getCvToken ().getLoc ();
      if (cv_spec_sel.hasSpec (flag))
      { 
        msg::duplicateSpecifier (loc, cvSpecToString (flag));
      }
      else
      {
        cv_spec_sel.addSpec (flag, loc);
      }
    }
}
namespace
{
  void GetNodeDeclSpec::visit (BuiltInTypeNode & node) const
    {
      int flag = 0, alt_flags = 0;
      switch (node.getBuiltInTypeToken ().getNumber ())
      {
        case BOOL_TOKEN:
        {
          flag = BOOL_SPEC;
          alt_flags = 0;
          break;
        }
        case CHAR_TOKEN:
        {
          flag = CHAR_SPEC;
          alt_flags = SIGNED_SPEC | UNSIGNED_SPEC;
          break;
        }
        case DOUBLE_TOKEN:
        {
          flag = DOUBLE_SPEC;
          alt_flags = LONG_SPEC;
          break;
        }
        case FLOAT_TOKEN:
        {
          flag = FLOAT_SPEC;
          alt_flags = 0;
          break;
        }
        case INT_TOKEN:
        {
          flag = INT_SPEC;
          alt_flags = LONG_SPEC | LONG_LONG_SPEC | SHORT_SPEC | SIGNED_SPEC | UNSIGNED_SPEC;
          break;
        }
        case LONG_TOKEN:
        {
          int cur_flags = bltn_spec_sel.getFlags ();
          if (cur_flags & LONG_SPEC && ! (cur_flags & LONG_LONG_SPEC))
          {
            flag = LONG_LONG_SPEC;
            alt_flags = INT_SPEC | SIGNED_SPEC | UNSIGNED_SPEC | LONG_SPEC;
          }
          else
          {
            flag = LONG_SPEC;
            alt_flags = DOUBLE_SPEC | INT_SPEC | SIGNED_SPEC | UNSIGNED_SPEC;
          }
          break;
        }
        case SHORT_TOKEN:
        {
          flag = SHORT_SPEC;
          alt_flags = INT_SPEC | SIGNED_SPEC | UNSIGNED_SPEC;
          break;
        }
        case SIGNED_TOKEN:
        {
          flag = SIGNED_SPEC;
          alt_flags = INT_SPEC | SHORT_SPEC | LONG_SPEC | LONG_LONG_SPEC | CHAR_SPEC;
          break;
        }
        case UNSIGNED_TOKEN:
        {
          flag = UNSIGNED_SPEC;
          alt_flags = INT_SPEC | SHORT_SPEC | LONG_SPEC | LONG_LONG_SPEC | CHAR_SPEC;
          break;
        }
        case VOID_TOKEN:
        {
          flag = VOID_SPEC;
          alt_flags = 0;
          break;
        }
        case WCHAR_TOKEN:
        {
          flag = WCHAR_SPEC;
          alt_flags = 0;
          break;
        }
      }
      int flags = bltn_spec_sel.getFlags ();
      util::Loc const & loc = node.getBuiltInTypeToken ().getLoc ();
      if (util::hasFlag (flags, flag))
      {
        msg::duplicateSpecifier (loc, builtInSpecToString (flag));
      }
      else if ((flags &= ~ alt_flags) != 0)
      {
        msg::conflictingSpecifier (loc, builtInSpecToString (firstFlag (flags)), builtInSpecToString (flag));
      }
      else
      {
        bltn_spec_sel.addSpec (flag, loc);
      }
    }
}
namespace
{
  void GetNodeDeclSpec::visit (UserTypeNode & node) const
    {
      smtc::NamePtr name = getNodeName (node.getObjName ());
      type = smtc::getUserType (name);
    }
}
namespace
{
  void GetNodeDeclSpec::visit (ElabTypeNode & node) const
    {
      smtc::ClassKey key = getClassKey (node.getClassKey ().getNumber ());
      smtc::NamePtr name = getNodeName (node.getObjName ());
      type = smtc::getElabType (key, name);
    }
}
namespace
{
  LZZ_INLINE GetNodeDeclSpec::GetNodeDeclSpec (SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, SpecSel & bltn_spec_sel, SpecSel & cv_spec_sel, smtc::TypePtr & type)
    : decl_spec_sel (decl_spec_sel), dcl_spec_sel (dcl_spec_sel), bltn_spec_sel (bltn_spec_sel), cv_spec_sel (cv_spec_sel), type (type)
         {}
}
namespace
{
  GetNodeDeclSpec::~ GetNodeDeclSpec ()
         {}
}
namespace
{
  smtc::TypePtr getBuiltInType (SpecSel const & spec_sel)
  {
    smtc::TypePtr type;
    switch (spec_sel.getFlags ())
    {
      // char
      case CHAR_SPEC:
      {
        type = smtc::getCharType ();
        break;
      }
      // unsigned char
      case UNSIGNED_SPEC | CHAR_SPEC:
      {
        type = smtc::getUnsignedCharType ();
        break;
      }
      // signed char
      case SIGNED_SPEC | CHAR_SPEC:
      {
        type = smtc::getSignedCharType ();
        break;
      }
      // bool
      case BOOL_SPEC:
      {
        type = smtc::getBoolType ();
        break;
      }
      // int
      case INT_SPEC:
      case SIGNED_SPEC:
      case SIGNED_SPEC | INT_SPEC:
      {
        type = smtc::getIntType ();
        break;
      }
      // unsigned int
      case UNSIGNED_SPEC:
      case UNSIGNED_SPEC | INT_SPEC:
      {
        type = smtc::getUnsignedIntType ();
        break;
      }
      // short int
      case SHORT_SPEC:
      case SHORT_SPEC | INT_SPEC:
      case SHORT_SPEC | SIGNED_SPEC | INT_SPEC:
      case SHORT_SPEC | SIGNED_SPEC:
      {
        type = smtc::getShortIntType ();
        break;
      }
      // unsigned short int
      case SHORT_SPEC | UNSIGNED_SPEC | INT_SPEC:
      case SHORT_SPEC | UNSIGNED_SPEC:
      {
        type = smtc::getUnsignedShortIntType ();
        break;
      }
      // long int
      case LONG_SPEC:
      case LONG_SPEC | INT_SPEC:
      case LONG_SPEC | SIGNED_SPEC | INT_SPEC:
      case LONG_SPEC | SIGNED_SPEC:
      {
        type = smtc::getLongIntType ();
        break;
      }
      // unsigned long int
      case LONG_SPEC | UNSIGNED_SPEC | INT_SPEC:
      case LONG_SPEC | UNSIGNED_SPEC:
      {
        type = smtc::getUnsignedLongIntType ();
        break;
      }
      // long long int
      case LONG_SPEC | LONG_LONG_SPEC:
      case LONG_SPEC | LONG_LONG_SPEC | INT_SPEC:
      case LONG_SPEC | LONG_LONG_SPEC | SIGNED_SPEC | INT_SPEC:
      case LONG_SPEC | LONG_LONG_SPEC | SIGNED_SPEC:
      {
        type = smtc::getLongLongIntType ();
        break;
      }
      // unsigned long long int
      case LONG_SPEC | LONG_LONG_SPEC | UNSIGNED_SPEC | INT_SPEC:
      case LONG_SPEC | LONG_LONG_SPEC | UNSIGNED_SPEC:
      {
        type = smtc::getUnsignedLongLongIntType ();
        break;
      }
      // float
      case FLOAT_SPEC:
      {
        type = smtc::getFloatType ();
        break;
      }
      // double
      case DOUBLE_SPEC:
      {
        type = smtc::getDoubleType ();
        break;
      }
      // long double
      case DOUBLE_SPEC | LONG_SPEC:
      {
        type = smtc::getLongDoubleType ();
        break;
      }
      // wchar_t
      case WCHAR_SPEC:
      {
        type = smtc::getWideCharType ();
        break;
      }
      // void
      case VOID_SPEC:
      {
        type = smtc::getVoidType ();
        break;
      }
    }
    return type;
  }
}
namespace gram
{
  void getNodeDeclSpec (basl::Nonterm & nonterm, SpecSel & decl_spec_sel, SpecSel & dcl_spec_sel, smtc::CvType & cv_type)
  {
    SpecSel bltn_spec_sel, cv_spec_sel;
    smtc::TypePtr type;
    nonterm.accept (GetNodeDeclSpec (decl_spec_sel, dcl_spec_sel, bltn_spec_sel, cv_spec_sel, type));
    // set cv type 
    if (bltn_spec_sel.anySet ())
    {
      type = getBuiltInType (bltn_spec_sel);
    }
    if (type.isSet ())
    {
      int cv_flags = cv_spec_sel.getFlags ();
      cv_type = smtc::getCvType (type, util::hasFlag (cv_flags, CONST_SPEC), util::hasFlag (cv_flags, VOLATILE_SPEC));
    }
  }
}
namespace gram
{
  void getNodeDeclSpec (basl::Nonterm & nonterm, smtc::CvType & cv_type)
  {
    SpecSel decl_spec_sel, dcl_spec_sel;
    getNodeDeclSpec (nonterm, decl_spec_sel, dcl_spec_sel, cv_type);
  }
}
namespace gram
{
  void getNodeLazyCtorSpec (basl::Nonterm & nonterm, SpecSel & dcl_spec_sel, smtc::Cv & cv)
  {
    SpecSel decl_spec_sel, bltn_spec_sel, cv_spec_sel;
    smtc::TypePtr type;
    nonterm.accept (GetNodeDeclSpec (decl_spec_sel, dcl_spec_sel, bltn_spec_sel, cv_spec_sel, type));
    int cv_flags = cv_spec_sel.getFlags ();
    cv = smtc::Cv (util::hasFlag (cv_flags, CONST_SPEC), util::hasFlag (cv_flags, VOLATILE_SPEC));
  }
}
#undef LZZ_INLINE
