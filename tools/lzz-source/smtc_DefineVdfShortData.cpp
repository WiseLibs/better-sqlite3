// smtc_DefineVdfShortData.cpp
//

#include "smtc_DefineVdfShortData.h"
// semantic
#include "smtc_CreateFuncDefn.h"
#include "smtc_CreateFuncDefnEntity.h"
#include "smtc_CreateIdentBaseName.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateObj.h"
#include "smtc_CreateVdfDataFuncDefn.h"
#include "smtc_CreateVdfDataFuncDefnEntity.h"
#include "smtc_GetCvTypeAsRef.h"
#include "smtc_GetUserType.h"
#include "smtc_GetVdfDataId.h"
#include "smtc_NameToString.h"
#include "smtc_Ns.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#include "smtc_TranslateVdfDataInit.h"
#include "smtc_VdfDataFuncDefn.h"
#include "smtc_VdfScope.h"

// util
#include "util_GetIdent.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DefineVdfShortData : ScopeVisitor
  {
    CvType const & type;
    util::Loc const & loc;
    bool has_id;
    util::Ident const & name_id;
    util::String name_str;
    ParamPtrVector const & param_set;
    bool vararg;
    InitPtr const & init;
    void visit (VdfScope const & scope) const;
  public:
    explicit DefineVdfShortData (CvType const & type, util::Loc const & loc, bool has_id, util::Ident const & name_id, util::String name_str, ParamPtrVector const & param_set, bool vararg, InitPtr const & init);
    ~ DefineVdfShortData ();
  };
}
namespace
{
  void DefineVdfShortData::visit (VdfScope const & scope) const
    {
      // definition goes in outer ns
      NsPtr const & ns = scope.getOuterNs ();
      // return type is ref to const base type
      CvType ret_type = getCvTypeAsRef (CvType (getUserType (scope.getBaseTypeName ()), Cv (true, false)));
      // get encoded function name and comment
      util::String base_type_str = nameToString (scope.getBaseTypeName ());
      util::String cmt = base_type_str;
      cmt += ": ";
      util::Ident enc_name_id;
      if (has_id)
      {
        // name_id is encoded id, and that's all we have for a comment too
        enc_name_id = name_id;
        cmt += name_id.c_str ();
      }
      else
      {
        enc_name_id = util::getIdent (getVdfDataId (base_type_str, name_str));
        cmt += name_str;
      }
      NamePtr name = createNonTmplName (createIdentBaseName (loc, enc_name_id));
      VdfDataFuncDefnPtr vdf_data_func_defn = createVdfDataFuncDefn (0, ret_type, name, param_set, vararg, cmt);
      ns->addEntity (createVdfDataFuncDefnEntity (vdf_data_func_defn));
      // add obj, as static
      NamePtr obj_name = createNonTmplName (createIdentBaseName (loc, util::getIdent ("_node")));
      InitPtr vdf_init;
      if (init.isSet ())
      {
        vdf_init = translateVdfDataInit (init);
      }
      ObjPtr obj = createObj (STATIC_SPEC, type, obj_name, vdf_init);
      vdf_data_func_defn->addObj (obj);
      // no return stmt (will generate one automatically) 
    }
}
namespace
{
  LZZ_INLINE DefineVdfShortData::DefineVdfShortData (CvType const & type, util::Loc const & loc, bool has_id, util::Ident const & name_id, util::String name_str, ParamPtrVector const & param_set, bool vararg, InitPtr const & init)
    : type (type), loc (loc), has_id (has_id), name_id (name_id), name_str (name_str), param_set (param_set), vararg (vararg), init (init)
         {}
}
namespace
{
  DefineVdfShortData::~ DefineVdfShortData ()
         {}
}
namespace smtc
{
  void defineVdfShortData (ScopePtr const & scope, CvType const & type, util::Loc const & loc, util::Ident const & ident, ParamPtrVector const & param_set, bool vararg, InitPtr const & init)
  {
    scope->accept (DefineVdfShortData (type, loc, true, ident, util::String (), param_set, vararg, init));
  }
}
namespace smtc
{
  void defineVdfShortData (ScopePtr const & scope, CvType const & type, util::Loc const & loc, util::String const & str, ParamPtrVector const & param_set, bool vararg, InitPtr const & init)
  {
    scope->accept (DefineVdfShortData (type, loc, false, util::Ident (), str, param_set, vararg, init));
  }
}
#undef LZZ_INLINE
