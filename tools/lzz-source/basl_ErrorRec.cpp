// basl_ErrorRec.cpp
//

#include "basl_ErrorRec.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_ErrorRec.inl"
#endif
// basil
#include "basl_RecCmd.h"
#define LZZ_INLINE inline
namespace basl
{
  void ErrorRec::insertSome (FreeTokenVector const & free_token_set)
    {
      m_rec_cmd_set.push_back (new InsertSomeRecCmd (free_token_set));
    }
}
namespace basl
{
  void ErrorRec::discardSome (int max_discard)
    {
      m_rec_cmd_set.push_back (new DiscardSomeRecCmd (max_discard));
    }
}
namespace basl
{
  void ErrorRec::discardOne (int number)
    {
      m_rec_cmd_set.push_back (new DiscardOneRecCmd (number));
    }
}
namespace basl
{
  void ErrorRec::replaceSome (int max_discard, FreeTokenVector const & free_token_set)
    {
      m_rec_cmd_set.push_back (new ReplaceSomeRecCmd (max_discard, free_token_set));
    }
}
namespace basl
{
  void ErrorRec::replaceOne (int number, FreeTokenVector const & free_token_set)
    {
      m_rec_cmd_set.push_back (new ReplaceOneRecCmd (number, free_token_set));
    }
}
namespace basl
{
  void ErrorRec::moveSome (int max_move, int max_num)
    {
      m_rec_cmd_set.push_back (new MoveSomeRecCmd (max_move, max_num));
    }
}
#undef LZZ_INLINE
