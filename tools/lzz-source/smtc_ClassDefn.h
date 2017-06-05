// smtc_ClassDefn.h
//

#ifndef LZZ_smtc_ClassDefn_h
#define LZZ_smtc_ClassDefn_h
// semantic
#include "smtc_BaseSpecPtrVector.h"
#include "smtc_ClassDecl.h"
#include "smtc_EntityPtrDeque.h"

// util
#include "util_IdentSet.h"
#define LZZ_INLINE inline
namespace smtc
{
  class ClassDefn : public ClassDecl
  {
    BaseSpecPtrVector m_base_spec_set;
    EntityPtrDeque m_entity_set;
    util::IdentSet m_type_name_set;
    bool m_dpdt;
    NamePtr m_qual_name;
  public:
    ClassDefn (ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set);
    ~ ClassDefn ();
    BaseSpecPtrVector const & getBaseSpecSet () const;
    EntityPtrDeque const & getEntitySet () const;
    void addEntity (EntityPtr const & entity);
    void addTypeName (util::Ident const & type_name);
    util::IdentSet const & getTypeNameSet () const;
    void setDependent ();
    bool isDependent () const;
    void setQualName (NamePtr const & qual_name);
    NamePtr const & getQualName () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "smtc_ClassDefn.inl"
#endif
#endif
