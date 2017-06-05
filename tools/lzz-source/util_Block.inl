// util_Block.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace util
{
  LZZ_INLINE void Block::append (util::String const & str) const
    {
      append (str.c_str ());
    }
}
namespace util
{
  LZZ_INLINE void Block::appendLine (util::String const & str) const
    {
      append (str.c_str ());
      append ('\n');
    }
}
#undef LZZ_INLINE
