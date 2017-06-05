// smtc_PrintHandler.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE void PrintHandler::operator () (HandlerPtr const & handler) const
  {
    printHandler (file, skind, handler);
  }
}
namespace smtc
{
  LZZ_INLINE PrintHandler::PrintHandler (FilePtr const & file, SectionKind skind)
    : file (file), skind (skind)
              {}
}
#undef LZZ_INLINE
