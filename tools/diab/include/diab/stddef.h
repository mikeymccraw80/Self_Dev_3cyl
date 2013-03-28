#ifndef __Idiab_stddef
#define __Idiab_stddef
#include <xmacros.h>

_C_LIB_DECL
#ifndef NULL
#define NULL	0
#endif

#if !defined(offsetof)
#define offsetof(s,memb) ((size_t)((char *)&((s *)0)->memb-(char *)0))
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef int ptrdiff_t;
#endif

#if !defined(__size_t) && !defined(_SIZE_T)
#define	__size_t
#define _SIZE_T
#ifdef _TYPE_size_t
_TYPE_size_t;
#else
typedef unsigned int size_t;
#endif
#endif

#ifndef _WCHART
#ifndef	__wchar_t
#define	__wchar_t
#ifdef _TYPE_wchar_t
_TYPE_wchar_t;
#else
typedef long int wchar_t;
#endif
#endif
#define _WCHART
#endif /* _WCHART */

#ifndef _WINTT
#ifndef	__wint_t
#define	__wint_t
#ifdef _TYPE_wint_t
_TYPE_wint_t;
#else
typedef long int wint_t;
#endif
#endif
#define _WINTT
#endif /* _WINTT */

#ifndef __VXWORKS__
#ifndef _OFF_T
#define _OFF_T
typedef long int off_t;
#endif
#endif /* __VXWORKS__ */

_END_C_LIB_DECL

#ifdef _STD_USING
using 	std::ptrdiff_t;
using 	std::size_t;
using 	std::wchar_t;
using 	std::wint_t;
#endif
#endif
