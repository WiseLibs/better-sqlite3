// smtc_Enum.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace smtc
{
  LZZ_INLINE util::Loc const & Enum::getLoc () const
    {
      return m_loc;
    }
}
namespace smtc
{
  LZZ_INLINE bool Enum::hasName () const
    {
      return m_name.isSet ();
    }
}
namespace smtc
{
  LZZ_INLINE NamePtr const & Enum::getName () const
    {
      return m_name;
    }
}
namespace smtc
{
  LZZ_INLINE EnumtorPtrVector const & Enum::getEnumtorSet () const
    {
      return m_enumtor_set;
    }
}
#undef LZZ_INLINE
