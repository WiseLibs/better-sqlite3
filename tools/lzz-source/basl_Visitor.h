// basl_Visitor.h
//

#ifndef LZZ_basl_Visitor_h
#define LZZ_basl_Visitor_h
#define LZZ_INLINE inline
namespace basl
{
  struct Visitor
  {
    Visitor ();
    virtual ~ Visitor ();
  };
}
#undef LZZ_INLINE
#endif
