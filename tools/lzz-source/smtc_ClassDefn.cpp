// smtc_ClassDefn.cpp
//

#include "smtc_ClassDefn.h"
#ifndef LZZ_ENABLE_INLINE
#include "smtc_ClassDefn.inl"
#endif
#define LZZ_INLINE inline
namespace smtc
{
  ClassDefn::ClassDefn (ClassKey key, NamePtr const & name, bool is_dll_api, BaseSpecPtrVector const & base_spec_set)
    : ClassDecl (key, name, is_dll_api), m_base_spec_set (base_spec_set), m_dpdt (false)
    {}
}
namespace smtc
{
  ClassDefn::~ ClassDefn ()
    {}
}
namespace smtc
{
  void ClassDefn::addEntity (EntityPtr const & entity)
    {
      m_entity_set.push_back (entity);
    }
}
namespace smtc
{
  void ClassDefn::addTypeName (util::Ident const & type_name)
    {
      m_type_name_set.insert (type_name);
    }
}
namespace smtc
{
  util::IdentSet const & ClassDefn::getTypeNameSet () const
    {
      return m_type_name_set;
    }
}
namespace smtc
{
  void ClassDefn::setDependent ()
    {
      m_dpdt = true;
    }
}
namespace smtc
{
  bool ClassDefn::isDependent () const
    {
      return m_dpdt;
    }
}
namespace smtc
{
  void ClassDefn::setQualName (NamePtr const & qual_name)
    {
      m_qual_name = qual_name;
    }
}
namespace smtc
{
  NamePtr const & ClassDefn::getQualName () const
    {
      return m_qual_name;
    }
}
#undef LZZ_INLINE
