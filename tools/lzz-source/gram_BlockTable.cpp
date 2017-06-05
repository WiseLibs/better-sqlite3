// gram_BlockTable.cpp
//

#include "gram_BlockTable.h"
#include <map>
#include "util_IntToString.h"
#include "util_GetIdent.h"
#define LZZ_INLINE inline
using namespace std;
namespace
{
  using namespace gram;
}
namespace
{
  using namespace util;
}
namespace
{
  struct BlockTable
  {
    typedef std::map <size_t, Block> BlockMap;
    BlockMap block_map;
    int next_id;
    Ident addBlock (Block const & block);
    Block getBlock (Ident const & lexeme);
  public:
    explicit BlockTable ();
    ~ BlockTable ();
  };
}
namespace
{
  BlockTable & getBlockTable ();
}
namespace gram
{
  util::Ident addBlock (Block const & block)
  {
    return getBlockTable ().addBlock (block);
  }
}
namespace gram
{
  Block getBlock (util::Ident const & lexeme)
  {
    return getBlockTable ().getBlock (lexeme);
  }
}
namespace
{
  Ident BlockTable::addBlock (Block const & block)
    {
      string lexeme_str = "BLOCK#";
      lexeme_str += intToString (next_id ++);
      Ident lexeme = getIdent (lexeme_str);
      block_map [lexeme.getHandle ()] = block;
      return lexeme;
    }
}
namespace
{
  Block BlockTable::getBlock (Ident const & lexeme)
    {
      BlockMap::iterator i = block_map.find (lexeme.getHandle ());
      assert (i != block_map.end ());
      Block block = i->second;
      block_map.erase (i);
      return block;
    }
}
namespace
{
  LZZ_INLINE BlockTable::BlockTable ()
    : next_id (1)
         {}
}
namespace
{
  BlockTable::~ BlockTable ()
         {}
}
namespace
{
  BlockTable & getBlockTable ()
  {
    static BlockTable table;
    return table;
  }
}
#undef LZZ_INLINE
