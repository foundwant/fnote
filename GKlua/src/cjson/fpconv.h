/* Lua CJSON floating point conversion routines */

/* Buffer required to store the largest string representation of a double.
 *
 * Longest double printed with %.14g is 21 characters long:
 * -1.7976931348623e+308 */
# define FPCONV_G_FMT_BUFSIZE   32

#ifdef _WIN32
#define USE_INTERNAL_FPCONV
//#define isnan(x)	_isnan(x)
//#define isinf(x)	(!_finite(x))
#define snprintf(s,sz,f,...)	_snprintf_s(s,sz,_TRUNCATE,f,__VA_ARGS__)
#define strncasecmp(x,y,l) _strnicmp(x,y,l)
#define INLINE __inline
#endif

#ifdef USE_INTERNAL_FPCONV
static INLINE void fpconv_init()
{
    /* Do nothing - not required */
}
#else
extern INLINE void fpconv_init();
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int fpconv_g_fmt(char*, double, int);
extern double fpconv_strtod(const char*, char**);
#ifdef __cplusplus
}
#endif

/* vi:ai et sw=4 ts=4:
 */



