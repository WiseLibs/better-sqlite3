// basl_Message.h
//

#ifndef LZZ_basl_Message_h
#define LZZ_basl_Message_h
// basl
#include "basl_FreeTokenVector.h"

// message
#include "msg_Message.h"
#include "msg_Output.h"
#define LZZ_INLINE inline
namespace basl
{
  namespace msg
  {
    void syntaxError (util::Loc const & loc, util::Ident const & lexeme);
  }
}
namespace basl
{
  namespace msg
  {
    void insertingTokens (util::Loc const & loc, util::Ident const & lexeme, FreeTokenVector const & free_token_set);
  }
}
namespace basl
{
  namespace msg
  {
    void replacingTokens (util::Loc const & loc, util::Ident const & lexeme, int num_discard, FreeTokenVector const & free_token_set);
  }
}
namespace basl
{
  namespace msg
  {
    void discardingTokens (util::Loc const & loc, util::Ident const & lexeme, int num_discard);
  }
}
namespace basl
{
  namespace msg
  {
    void movingTokens (util::Loc const & loc, util::Ident const & lexeme1, int num_move, int num, util::Ident const & lexeme2);
  }
}
namespace basl
{
  namespace msg
  {
    void syntaxErrorLimitReached (util::Loc const & loc);
  }
}
namespace basl
{
  namespace msg
  {
    void unableToRecover (util::Loc const & loc);
  }
}
#undef LZZ_INLINE
#endif
