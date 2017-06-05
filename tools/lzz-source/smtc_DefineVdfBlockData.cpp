// smtc_DefineVdfBlockData.cpp
//

#include "smtc_DefineVdfBlockData.h"
// semantic
#include "smtc_CreateIdentBaseName.h"
#include "smtc_CreateNonTmplName.h"
#include "smtc_CreateVdfBlockDataScope.h"
#include "smtc_CreateVdfDataFuncDefn.h"
#include "smtc_CreateVdfDataFuncDefnEntity.h"
#include "smtc_GetCvTypeAsRef.h"
#include "smtc_GetUserType.h"
#include "smtc_GetVdfDataId.h"
#include "smtc_NameToString.h"
#include "smtc_Ns.h"
#include "smtc_ScopeVisitor.h"
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
  struct DefineVdfBlockData : ScopeVisitor
  {
    util::Loc const & loc;
    bool has_id;
    util::Ident const & name_id;
    util::String name_str;
    ParamPtrVector const & param_set;
    bool vararg;
    ScopePtr & res_scope;
    void visit (VdfScope const & scope) const;
  public:
    explicit DefineVdfBlockData (util::Loc const & loc, bool has_id, util::Ident const & name_id, util::String name_str, ParamPtrVector const & param_set, bool vararg, ScopePtr & res_scope);
    ~ DefineVdfBlockData ();
  };
}
namespace
{
  void DefineVdfBlockData::visit (VdfScope const & scope) const
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
      // vdf data func saved in block data scope for obj definitions
      res_scope = createVdfBlockDataScope (vdf_data_func_defn);
    }
}
namespace
{
  LZZ_INLINE DefineVdfBlockData::DefineVdfBlockData (util::Loc const & loc, bool has_id, util::Ident const & name_id, util::String name_str, ParamPtrVector const & param_set, bool vararg, ScopePtr & res_scope)
    : loc (loc), has_id (has_id), name_id (name_id), name_str (name_str), param_set (param_set), vararg (vararg), res_scope (res_scope)
         {}
}
namespace
{
  DefineVdfBlockData::~ DefineVdfBlockData ()
         {}
}
namespace smtc
{
  ScopePtr defineVdfBlockData (ScopePtr const & scope, util::Loc const & loc, util::Ident const & ident, ParamPtrVector const & param_set, bool vararg)
  {
    ScopePtr res_scope;
    scope->accept (DefineVdfBlockData (loc, true, ident, util::String (), param_set, vararg, res_scope));
    return res_scope;
  }
}
namespace smtc
{
  ScopePtr defineVdfBlockData (ScopePtr const & scope, util::Loc const & loc, util::String const & str, ParamPtrVector const & param_set, bool vararg)
  {
    ScopePtr res_scope;
    scope->accept (DefineVdfBlockData (loc, false, util::Ident (), str, param_set, vararg, res_scope));
    return res_scope;
  }
}
#undef LZZ_INLINE
