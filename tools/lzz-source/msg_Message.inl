// msg_Message.inl
//

#ifdef LZZ_ENABLE_INLINE
#define LZZ_INLINE inline
#else
#define LZZ_INLINE
#endif
namespace msg
{
  LZZ_INLINE Severity Message::getSeverity () const
    {
      return m_severity;
    }
}
namespace msg
{
  LZZ_INLINE util::String const & Message::getString () const
    {
      return m_str;
    }
}
#undef LZZ_INLINE
