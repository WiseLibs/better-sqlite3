// conf_LzzVersion.h
//

#ifndef LZZ_conf_LzzVersion_h
#define LZZ_conf_LzzVersion_h
#if   defined (PRL_BUILD)
#define LZZ_VERSION "2.7.1 PRL"
#elif defined (CGI_BUILD)
#define LZZ_VERSION "2.6.0 CGI"
#else
#define LZZ_VERSION "2.8.2"
#endif
#define LZZ_INLINE inline
#undef LZZ_INLINE
#endif
