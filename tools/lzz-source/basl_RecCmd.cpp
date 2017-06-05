// basl_RecCmd.cpp
//

#include "basl_RecCmd.h"
#ifndef LZZ_ENABLE_INLINE
#include "basl_RecCmd.inl"
#endif
#define LZZ_INLINE inline
namespace basl
{
  RecCmd::~ RecCmd ()
    {}
}
namespace basl
{
  InsertSomeRecCmd::~ InsertSomeRecCmd ()
    {}
}
namespace basl
{
  bool InsertSomeRecCmd::canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const
    {
      return lrbt_parser.insertSome (start_lr_parser, free_token_set, lr_parser);
    }
}
namespace basl
{
  DiscardSomeRecCmd::~ DiscardSomeRecCmd ()
    {}
}
namespace basl
{
  bool DiscardSomeRecCmd::canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const
    {
      return lrbt_parser.discardSome (start_lr_parser, max_discard, lr_parser);
    }
}
namespace basl
{
  DiscardOneRecCmd::~ DiscardOneRecCmd ()
    {}
}
namespace basl
{
  bool DiscardOneRecCmd::canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const
    {
      return lrbt_parser.discardOne (start_lr_parser, number, lr_parser);
    }
}
namespace basl
{
  ReplaceSomeRecCmd::~ ReplaceSomeRecCmd ()
    {}
}
namespace basl
{
  bool ReplaceSomeRecCmd::canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const
    {
      return lrbt_parser.replaceSome (start_lr_parser, max_discard, free_token_set, lr_parser);
    }
}
namespace basl
{
  ReplaceOneRecCmd::~ ReplaceOneRecCmd ()
    {}
}
namespace basl
{
  bool ReplaceOneRecCmd::canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const
    {
      return lrbt_parser.replaceOne (start_lr_parser, number, free_token_set, lr_parser);
    }
}
namespace basl
{
  MoveSomeRecCmd::~ MoveSomeRecCmd ()
    {}
}
namespace basl
{
  bool MoveSomeRecCmd::canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const
    {
      return lrbt_parser.moveSome (start_lr_parser, max_move, max_num, lr_parser);
    }
}
#undef LZZ_INLINE
