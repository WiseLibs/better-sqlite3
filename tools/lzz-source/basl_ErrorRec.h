// basl_ErrorRec.h
//

#ifndef LZZ_basl_ErrorRec_h
#define LZZ_basl_ErrorRec_h
// basil
#include "basl_FreeTokenVector.h"
#include "basl_RecCmdPtrDeque.h"
#define LZZ_INLINE inline
namespace basl
{
  class ErrorRec
  {
    RecCmdPtrDeque m_rec_cmd_set;
  public:
    ErrorRec ();
    ~ ErrorRec ();
    void insertSome (FreeTokenVector const & free_token_set);
    void discardSome (int max_discard);
    void discardOne (int number);
    void replaceSome (int max_discard, FreeTokenVector const & free_token_set);
    void replaceOne (int number, FreeTokenVector const & free_token_set);
    void moveSome (int max_move, int max_num);
    RecCmdPtrDeque const & getRecCmdSet () const;
  };
}
#undef LZZ_INLINE
#ifdef LZZ_ENABLE_INLINE
#include "basl_ErrorRec.inl"
#endif
#endif
