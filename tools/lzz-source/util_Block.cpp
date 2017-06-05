// util_Block.cpp
//

#include "util_Block.h"
#ifndef LZZ_ENABLE_INLINE
#include "util_Block.inl"
#endif
// util
#include "util_BPtr.tpl"
#include "util_BlockImpl.h"
#define LZZ_INLINE inline
namespace util
{
  template class BPtr <BlockImpl>;
}
namespace util
{
  Block::Block ()
    : m_impl (BlockImplPtr ())
    {}
}
namespace util
{
  Block::Block (Loc const & loc)
    : m_impl (new BlockImpl (loc))
    {}
}
namespace util
{
  Block::~ Block ()
    {}
}
namespace util
{
  bool Block::isSet () const
    {
      return m_impl.isSet ();
    }
}
namespace util
{
  void Block::setLoc (Loc const & loc)
    {
      m_impl->setLoc (loc);
    }
}
namespace util
{
  Loc const & Block::getLoc () const
    {
      return m_impl->getLoc ();
    }
}
namespace util
{
  void Block::append (char ch) const
    {
      m_impl->append (ch);
    }
}
namespace util
{
  void Block::append (char const * str) const
    {
      m_impl->append (str);
    }
}
namespace util
{
  char const * Block::toString () const
    {
      return m_impl->c_str ();
    }
}
namespace util
{
  int Block::getNumLines () const
    {
      return m_impl->getNumLines ();
    }
}
namespace util
{
  int Block::getLength () const
    {
      return m_impl->getLength ();
    }
}
namespace util
{
  void Block::freeze () const
    {
      m_impl->freeze ();
    }
}
namespace util
{
  void Block::trim () const
    {
      m_impl->trim ();
    }
}
namespace util
{
  bool Block::isEmpty () const
    {
      return m_impl->isEmpty ();
    }
}
#undef LZZ_INLINE
