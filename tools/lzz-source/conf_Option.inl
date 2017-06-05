// conf_Option.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace conf
{
  LZZ_INLINE util::String const & StringOption::getValue () const
    {
      return m_value;
    }
}
namespace conf
{
  LZZ_INLINE util::IdentList const & IdentListOption::getValue () const
    {
      return m_value;
    }
}
namespace conf
{
  LZZ_INLINE bool BoolOption::getValue () const
    {
      return m_value;
    }
}
namespace conf
{
  LZZ_INLINE int IntOption::getValue () const
    {
      return m_value;
    }
}
namespace conf
{
  LZZ_INLINE util::StringVector const & StringSetOption::getValue () const
    {
      return m_value_set;
    }
}
#undef LZZ_INLINE
