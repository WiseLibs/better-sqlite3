// smtc_DeclareObj.cpp
//

#include "smtc_DeclareObj.h"
// semantic
#include "smtc_CheckSpecFlags.h"
#include "smtc_ClassDefn.h"
#include "smtc_ClassScope.h"
#include "smtc_CreateMbrInit.h"
#include "smtc_CreateNonTypeParam.h"
#include "smtc_CreateObj.h"
#include "smtc_CreateObjEntity.h"
#include "smtc_GetCvTypeAsRef.h"
#include "smtc_GetNameLoc.h"
#include "smtc_Init.h"
#include "smtc_IsNameBitf.h"
#include "smtc_IsNameQual.h"
#include "smtc_LazyClass.h"
#include "smtc_LazyClassScope.h"
#include "smtc_LinkageSpecScope.h"
#include "smtc_Message.h"
#include "smtc_NameToString.h"
#include "smtc_NavClass.h"
#include "smtc_NavClassScope.h"
#include "smtc_Ns.h"
#include "smtc_NsScope.h"
#include "smtc_ScopeVisitor.h"
#include "smtc_SpecFlags.h"
#include "smtc_TranslateVdfDataInit.h"
#include "smtc_VdfBlockDataScope.h"
#include "smtc_VdfDataFuncDefn.h"

// gram
#include "gram_Block.h"

// util
#include "util_BitOp.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  struct DeclareObj : ScopeVisitor
  {
    Linkage const & linkage;
    gram::SpecSel const & spec_sel;
    CvType const & cv_type;
    NamePtr const & name;
    InitPtr const & init;
    void visit (NsScope const & scope) const;
    void visit (ClassScope const & scope) const;
    void visit (LazyClassScope const & scope) const;
    void visit (NavClassScope const & scope) const;
    void visit (TmplSpecScope const & scope) const;
    void visit (TmplInstScope const & scope) const;
    void visit (LinkageSpecScope const & scope) const;
    void visit (VdfBlockDataScope const & scope) const;
    void checkClassNameAndFlags () const;
    EntityPtr buildEntity () const;
  public:
    explicit DeclareObj (Linkage const & linkage, gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name, InitPtr const & init);
    ~ DeclareObj ();
  };
}
namespace
{
  void DeclareObj::visit (NsScope const & scope) const
    {
      // cannot be a bitfield
      if (isNameBitf (name))
      {
        msg::nsBitfield (getNameLoc (name));
        return;
      }

      // inline, virtual and explict are not valid for any object
      checkInvalidSpecFlags (spec_sel, INLINE_SPEC|VIRTUAL_SPEC|EXPLICIT_SPEC, msg::invalidObjSpec);
      
      // mutable, auto and register are not valid for namespace objects
      checkInvalidSpecFlags (spec_sel, MUTABLE_SPEC|AUTO_SPEC|REGISTER_SPEC, msg::invalidNsObjSpec);

      if (linkage.isSet ())
      {
        // no storage class specifiers permitted (7.5p7)
        checkInvalidSpecFlags (spec_sel, STATIC_SPEC|EXTERN_SPEC, msg::invalidSpecWithLinkageSpec);
      }
      else
      {
        // static and extern not both valid
        checkConflictingSpecFlags (spec_sel, STATIC_SPEC|EXTERN_SPEC, 0, msg::conflictingObjSpec);
      }

      // add entity to ns
      scope.getNs ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareObj::visit (ClassScope const & scope) const
    {
      // check name and flags
      checkClassNameAndFlags ();

      // non static obj can't have initializer
      int flags = spec_sel.getFlags ();
      if (init.isSet () && ! util::hasFlag (flags, STATIC_SPEC))
      {
        msg::nonStaticClassObjWithInit (init->getLoc ());
      }

      // add entity to class
      scope.getClassDefn ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareObj::visit (LazyClassScope const & scope) const
    {
      // check name and flags
      checkClassNameAndFlags ();

      // non-static obj can have initializer
      int flags = spec_sel.getFlags ();
      if (init.isSet () && ! util::hasFlag (flags, STATIC_SPEC))
      {
        scope.getLazyClass ()->addMbrInit (createMbrInit (name, init->toString ()));
      }
      
      // add entity
      scope.getLazyClass ()->addEntity (buildEntity ());
    }
}
namespace
{
  void DeclareObj::visit (NavClassScope const & scope) const
    {
      // check name and flags
      checkClassNameAndFlags ();

      // obj defined as is in submit
      int flags = spec_sel.getFlags ();
      NavClassPtr const & nav_class = scope.getNavClass ();
      nav_class->addSubmitObj (createObj (flags, cv_type, name, init));
      // add ctor param, type is passed and stored in class as a reference
      CvType ref_cv_type = getCvTypeAsRef (cv_type);
      nav_class->addParam (createNonTypeParam (0, ref_cv_type, name, gram::Block ()));
      // add mbr init for obj
      nav_class->addMbrInit (createMbrInit (name, nameToString (name)));
      // and finally declare obj in class
      ObjPtr obj = createObj (0, ref_cv_type, name, InitPtr ());

      // add entity
      nav_class->addEntity (createObjEntity (obj));
    }
}
namespace
{
  void DeclareObj::visit (TmplSpecScope const & scope) const
    {
      // cannot declare a template object
      msg::templateObj (getNameLoc (name));
    }
}
namespace
{
  void DeclareObj::visit (TmplInstScope const & scope) const
    {
      // cannot explicitly instantiate an object
      msg::instantiateObj (getNameLoc (name));
    }
}
namespace
{
  void DeclareObj::visit (LinkageSpecScope const & scope) const
    {
      if (linkage.isSet ())
      {
        // nested linkage spec
        msg::multipleLinkageSpec (scope.getLoc ());
      }
      else
      {
        // declaring object with external linkage
        Linkage const & linkage = scope.getLinkage ();
        scope.getParent ()->accept (DeclareObj (linkage, spec_sel, cv_type, name, init));
      }
    }
}
namespace
{
  void DeclareObj::visit (VdfBlockDataScope const & scope) const
    {
      // add obj as static
      InitPtr vdf_init;
      if (init.isSet ())
      {
        vdf_init = translateVdfDataInit (init);
      }
      ObjPtr obj = createObj (STATIC_SPEC, cv_type, name, vdf_init);
      scope.getVdfDataFuncDefn ()->addObj (obj);
    }
}
namespace
{
  void DeclareObj::checkClassNameAndFlags () const
    {
      // can't be qualified
      if (isNameQual (name))
      {
        msg::qualClassObj (getNameLoc (name));
      }
      // object cannot be inline, virtual or explicit
      checkInvalidSpecFlags (spec_sel, INLINE_SPEC|VIRTUAL_SPEC|EXPLICIT_SPEC, msg::invalidObjSpec);
      // auto, register and extern are not valid class obj specifiers
      checkInvalidSpecFlags (spec_sel, AUTO_SPEC|REGISTER_SPEC|EXTERN_SPEC, msg::invalidClassObjSpec);
      if (isNameBitf (name))
      {
        // bitfield cannot be static
        checkInvalidSpecFlags (spec_sel, STATIC_SPEC, msg::invalidBitfieldSpec);
      }
      else
      {
        // object cannot be both static and mutable
        checkConflictingSpecFlags (spec_sel, STATIC_SPEC|MUTABLE_SPEC, 0, msg::conflictingObjSpec);
      }
      // no need to check linkage since grammar limits linkage specs to namespace declarations
    }
}
namespace
{
  EntityPtr DeclareObj::buildEntity () const
    {
      ObjPtr obj = createObj (linkage, spec_sel.getFlags (), cv_type, name, init);
      return createObjEntity (obj);
    }
}
namespace
{
  LZZ_INLINE DeclareObj::DeclareObj (Linkage const & linkage, gram::SpecSel const & spec_sel, CvType const & cv_type, NamePtr const & name, InitPtr const & init)
    : linkage (linkage), spec_sel (spec_sel), cv_type (cv_type), name (name), init (init)
         {}
}
namespace
{
  DeclareObj::~ DeclareObj ()
         {}
}
namespace smtc
{
  void declareObj (ScopePtr const & scope, gram::SpecSel const & spec, CvType const & cv_type, NamePtr const & name, InitPtr const & init)
  {
    Linkage linkage;
    scope->accept (DeclareObj (linkage, spec, cv_type, name, init));
  }
}
#undef LZZ_INLINE
