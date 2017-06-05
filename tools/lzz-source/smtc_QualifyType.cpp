// smtc_QualifyType.cpp
//

#include "smtc_QualifyType.h"
// semantic
#include "smtc_ArrayType.h"
#include "smtc_FuncType.h"
#include "smtc_GetArrayType.h"
#include "smtc_GetElabType.h"
#include "smtc_GetFuncType.h"
#include "smtc_GetMbrPtrType.h"
#include "smtc_GetPtrType.h"
#include "smtc_GetRefType.h"
#include "smtc_GetUserType.h"
#include "smtc_MbrPtrType.h"
#include "smtc_PtrType.h"
#include "smtc_QualifyTypeName.h"
#include "smtc_RefType.h"
#include "smtc_UserType.h"

#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct QualifyType
  {
    util::IdentSet const & type_name_set;
    NamePtr const & qual_name;
    bool dpdt;
    CvType & res_cv_type;
    bool qualify (CvType const & cv_type);
  public:
    explicit QualifyType (util::IdentSet const & type_name_set, NamePtr const & qual_name, bool dpdt, CvType & res_cv_type);
    ~ QualifyType ();
  };
}
namespace
{
  bool QualifyType::qualify (CvType const & cv_type)
    {
      bool result = false;
      Cv const & cv = cv_type.getCv ();
      TypePtr const & type = cv_type.getType ();
      TypeKind kind = type->getKind ();
      if (kind == REF_TYPE)
      {
        RefType const & ref_type = static_cast <RefType const &> (* type);
        if (qualify (ref_type.getToCvType ()))
        {
          res_cv_type = CvType (getRefType (res_cv_type), cv);
          result = true;
        }
      }
      else if (kind == PTR_TYPE)
      {
        PtrType const & ptr_type = static_cast <PtrType const &> (* type);
        if (qualify (ptr_type.getToCvType ()))
        {
          res_cv_type = CvType (getPtrType (res_cv_type), cv);
          result = true;
        }
      }
      else if (kind == MBR_PTR_TYPE)
      {
        MbrPtrType const & mbr_ptr_type = static_cast <MbrPtrType const &> (* type);
        NamePtr res_mbr_name = mbr_ptr_type.getMbrName ();
        result = qualifyTypeName (res_mbr_name, type_name_set, qual_name, res_mbr_name);
        if (qualify (mbr_ptr_type.getToCvType ()) || result)
        {
          if (! res_cv_type.isSet ())
          {
            res_cv_type = mbr_ptr_type.getToCvType ();
          }
          res_cv_type = CvType (getMbrPtrType (res_mbr_name, res_cv_type), cv);
          result = true;
        }
      }
      else if (kind == ARRAY_TYPE)
      {
        ArrayType const & array_type = static_cast <ArrayType const &> (* type);
        if (qualify (array_type.getElementCvType ()))
        {
          res_cv_type = CvType (getArrayType (res_cv_type, array_type.getSize ()), cv);
          result = true;
        }
      }
      else if (kind == FUNC_TYPE)
      {
        FuncType const & func_type = static_cast <FuncType const &> (* type);
        if (qualify (func_type.getReturnCvType ()))
        {
          res_cv_type = getFuncType (res_cv_type, func_type.getParamTypeSet (), func_type.hasVarArgs (), func_type.getCv (),
              func_type.getThrowSpec ());
          result = true;
        }
      }
      else if (kind == USER_TYPE)
      {
        UserType const & user_type = static_cast <UserType const &> (* type);
        NamePtr res_name;
        if (qualifyTypeName (user_type.getName (), type_name_set, qual_name, res_name))
        {
          // if dependent then add 'typename'
          if (dpdt)
          {
            res_cv_type = CvType (getElabType (TYPENAME_KEY, res_name), cv);
          }
          else
          {
            res_cv_type = CvType (getUserType (res_name), cv);
          }
          result = true;
        }
      }
      return result;
    }
}
namespace
{
  LZZ_INLINE QualifyType::QualifyType (util::IdentSet const & type_name_set, NamePtr const & qual_name, bool dpdt, CvType & res_cv_type)
    : type_name_set (type_name_set), qual_name (qual_name), dpdt (dpdt), res_cv_type (res_cv_type)
         {}
}
namespace
{
  QualifyType::~ QualifyType ()
         {}
}
namespace smtc
{
  bool qualifyType (CvType const & cv_type, util::IdentSet const & type_name_set, NamePtr const & qual_name, bool dpdt, CvType & res_cv_type)
  {
    QualifyType qualifier (type_name_set, qual_name, dpdt, res_cv_type);
    return qualifier.qualify (cv_type);
  }
}
#undef LZZ_INLINE
