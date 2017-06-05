// basl_ErrorRec.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace basl
{
  LZZ_INLINE ErrorRec::ErrorRec ()
    {}
}
namespace basl
{
  LZZ_INLINE ErrorRec::~ ErrorRec ()
    {}
}
namespace basl
{
  LZZ_INLINE RecCmdPtrDeque const & ErrorRec::getRecCmdSet () const
    {
      return m_rec_cmd_set;
    }
}
#undef LZZ_INLINE
