// smtc_EntityVisitor.h
//

#ifndef LZZ_smtc_EntityVisitor_h
#define LZZ_smtc_EntityVisitor_h
#define LZZ_INLINE inline
namespace smtc
{
  class NsEntity;
}
namespace smtc
{
  class EnumEntity;
}
namespace smtc
{
  class ObjEntity;
}
namespace smtc
{
  class FuncDeclEntity;
}
namespace smtc
{
  class ClassDeclEntity;
}
namespace smtc
{
  class ClassDefnEntity;
}
namespace smtc
{
  class FuncDefnEntity;
}
namespace smtc
{
  class FrndClassDeclEntity;
}
namespace smtc
{
  class TdefEntity;
}
namespace smtc
{
  class FrndFuncDefnEntity;
}
namespace smtc
{
  class FrndFuncDeclEntity;
}
namespace smtc
{
  class TmplClassDeclEntity;
}
namespace smtc
{
  class FrndTmplClassDeclEntity;
}
namespace smtc
{
  class TmplClassDefnEntity;
}
namespace smtc
{
  class TmplFuncDeclEntity;
}
namespace smtc
{
  class TmplFuncDefnEntity;
}
namespace smtc
{
  class FrndTmplFuncDeclEntity;
}
namespace smtc
{
  class FrndTmplFuncDefnEntity;
}
namespace smtc
{
  class AccessSpecEntity;
}
namespace smtc
{
  class ClassInstEntity;
}
namespace smtc
{
  class FuncInstEntity;
}
namespace smtc
{
  class LazyClassEntity;
}
namespace smtc
{
  class TmplLazyClassEntity;
}
namespace smtc
{
  class UsingDeclEntity;
}
namespace smtc
{
  class UsingDirEntity;
}
namespace smtc
{
  class NavClassEntity;
}
namespace smtc
{
  class VdfClassEntity;
}
namespace smtc
{
  class NavSubmitFuncDefnEntity;
}
namespace smtc
{
  class VdfDataFuncDefnEntity;
}
namespace smtc
{
  struct EntityVisitor
  {
    virtual void visit (NsEntity const & entity) const;
    virtual void visit (ObjEntity const & entity) const;
    virtual void visit (FuncDeclEntity const & entity) const;
    virtual void visit (ClassDeclEntity const & entity) const;
    virtual void visit (ClassDefnEntity const & entity) const;
    virtual void visit (FuncDefnEntity const & entity) const;
    virtual void visit (FrndClassDeclEntity const & entity) const;
    virtual void visit (TdefEntity const & entity) const;
    virtual void visit (FrndFuncDefnEntity const & entity) const;
    virtual void visit (FrndFuncDeclEntity const & entity) const;
    virtual void visit (TmplClassDeclEntity const & entity) const;
    virtual void visit (FrndTmplClassDeclEntity const & entity) const;
    virtual void visit (TmplClassDefnEntity const & entity) const;
    virtual void visit (TmplFuncDeclEntity const & entity) const;
    virtual void visit (TmplFuncDefnEntity const & entity) const;
    virtual void visit (FrndTmplFuncDeclEntity const & entity) const;
    virtual void visit (FrndTmplFuncDefnEntity const & entity) const;
    virtual void visit (AccessSpecEntity const & entity) const;
    virtual void visit (ClassInstEntity const & entity) const;
    virtual void visit (FuncInstEntity const & entity) const;
    virtual void visit (LazyClassEntity const & entity) const;
    virtual void visit (TmplLazyClassEntity const & entity) const;
    virtual void visit (EnumEntity const & entity) const;
    virtual void visit (UsingDeclEntity const & entity) const;
    virtual void visit (UsingDirEntity const & entity) const;
    virtual void visit (NavClassEntity const & entity) const;
    virtual void visit (NavSubmitFuncDefnEntity const & entity) const;
    virtual void visit (VdfClassEntity const & entity) const;
    virtual void visit (VdfDataFuncDefnEntity const & entity) const;
  };
}
#undef LZZ_INLINE
#endif
