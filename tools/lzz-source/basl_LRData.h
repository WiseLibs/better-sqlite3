// basl_LRData.h
//

#ifndef LZZ_basl_LRData_h
#define LZZ_basl_LRData_h
#define LZZ_INLINE inline
namespace basl
{
  struct NontermInfo;
}
namespace basl
{
  struct LRRule
  {
    char const * str;
    int size;
    NontermInfo const * nonterm_info;
  };
}
namespace basl
{
  enum
  {
    LR_SHIFT,
    LR_REDUCE,
    LR_ACCEPT,
    LR_DONE
  };
}
namespace basl
{
  typedef int const * LRAction;
}
namespace basl
{
  typedef LRAction const * LRActionSeq;
}
namespace basl
{
  struct LRMove
  {
    int token_number;
    LRActionSeq action_seq;
  };
}
namespace basl
{
  typedef LRMove const * LRMoveSel;
}
namespace basl
{
  struct LRState
  {
    LRMoveSel move_sel;
    int lex_state;
    int goto_index;
  };
}
namespace basl
{
  struct LRGoto
  {
    int index;
    int state;
  };
}
namespace basl
{
  typedef LRGoto LRShift;
}
namespace basl
{
  typedef LRShift const * LRShiftSel;
}
namespace basl
{
  struct LRSymbol
  {
    char const * name;
    LRShiftSel goto_sel;
  };
}
namespace basl
{
  struct LRData
  {
    LRRule const * rule_set;
    int num_start_rules;
    LRState const * state_set;
    LRSymbol const * symbol_set;
  };
}
#undef LZZ_INLINE
#endif
