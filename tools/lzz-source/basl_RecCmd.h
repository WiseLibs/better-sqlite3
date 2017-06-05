// basl_RecCmd.h
//

#ifndef LZZ_basl_RecCmd_h
#define LZZ_basl_RecCmd_h
// basil
#include "basl_FreeTokenVector.h"
#include "basl_LRBTParser.h"
#include "basl_RecCmdPtr.h"
#define LZZ_INLINE inline
namespace basl
{
  struct LRParser;
}
namespace basl
{
  struct LRBTParser;
}
namespace basl
{
  class RecCmd
  {
  public:
    virtual ~ RecCmd ();
    virtual bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const = 0;
  };
}
namespace basl
{
  class InsertSomeRecCmd : public RecCmd
  {
    FreeTokenVector free_token_set;
  public:
    InsertSomeRecCmd (FreeTokenVector const & free_token_set);
    ~ InsertSomeRecCmd ();
    bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const;
  };
}
namespace basl
{
  class DiscardSomeRecCmd : public RecCmd
  {
    int max_discard;
  public:
    DiscardSomeRecCmd (int max_discard);
    ~ DiscardSomeRecCmd ();
    bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const;
  };
}
namespace basl
{
  class DiscardOneRecCmd : public RecCmd
  {
    int number;
  public:
    DiscardOneRecCmd (int number);
    ~ DiscardOneRecCmd ();
    bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const;
  };
}
namespace basl
{
  class ReplaceSomeRecCmd : public RecCmd
  {
    int max_discard;
    FreeTokenVector free_token_set;
  public:
    ReplaceSomeRecCmd (int max_discard, FreeTokenVector const & free_token_set);
    ~ ReplaceSomeRecCmd ();
    bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const;
  };
}
namespace basl
{
  class ReplaceOneRecCmd : public RecCmd
  {
    int number;
    FreeTokenVector free_token_set;
  public:
    ReplaceOneRecCmd (int number, FreeTokenVector const & free_token_set);
    ~ ReplaceOneRecCmd ();
    bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const;
  };
}
namespace basl
{
  class MoveSomeRecCmd : public RecCmd
  {
    int max_move;
    int max_num;
  public:
    MoveSomeRecCmd (int max_move, int max_num);
    ~ MoveSomeRecCmd ();
    bool canRecover (LRBTParser & lrbt_parser, LRParser const & start_lr_parser, LRParser & lr_parser) const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_RecCmd.inl"
#endif
#endif
