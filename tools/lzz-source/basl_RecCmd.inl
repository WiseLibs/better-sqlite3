// basl_RecCmd.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE InsertSomeRecCmd::InsertSomeRecCmd (FreeTokenVector const & free_token_set)
    : free_token_set (free_token_set)
    {}
}
namespace basl
{
  LZZ_INLINE DiscardSomeRecCmd::DiscardSomeRecCmd (int max_discard)
    : max_discard (max_discard)
    {}
}
namespace basl
{
  LZZ_INLINE DiscardOneRecCmd::DiscardOneRecCmd (int number)
    : number (number)
    {}
}
namespace basl
{
  LZZ_INLINE ReplaceSomeRecCmd::ReplaceSomeRecCmd (int max_discard, FreeTokenVector const & free_token_set)
    : max_discard (max_discard), free_token_set (free_token_set)
    {}
}
namespace basl
{
  LZZ_INLINE ReplaceOneRecCmd::ReplaceOneRecCmd (int number, FreeTokenVector const & free_token_set)
    : number (number), free_token_set (free_token_set)
    {}
}
namespace basl
{
  LZZ_INLINE MoveSomeRecCmd::MoveSomeRecCmd (int max_move, int max_num)
    : max_move (max_move), max_num (max_num)
    {}
}
#undef LZZ_INLINE
