#ifndef __YALC_ATTR_H
#define __YALC_ATTR_H

#define __YALC_C89 1989
#define __YALC_C95 1995
#define __YALC_C99 1999
#define __YALC_C11 2011
#define __YALC_C17 2017
#define __YALC_C23 2023

// NOTE:
//   some compilers still report c23 as 202000L
//   the __STDC_VERSION__ is not defined at all before c95
#if !defined(__STDC_VERSION__)
#  define __YALC_CSTD __YALC_C89
#elif __STDC_VERSION__ >= 202000L
#  define __YALC_CSTD __YALC_C23
#elif __STDC_VERSION__ >= 201710L
#  define __YALC_CSTD __YALC_C17
#elif __STDC_VERSION__ >= 201112L
#  define __YALC_CSTD __YALC_C11
#elif __STDC_VERSION__ >= 199901L
#  define __YALC_CSTD __YALC_C99
#elif __STDC_VERSION__ >= 199409L
#  define __YALC_CSTD __YALC_C95
#else
#  define __YALC_CSTD __YALC_C89
#endif

// see https://en.cppreference.com/c/program/exit
#if __YALC_CSTD < __YALC_C11
#define __YALC_NO_RETURN__
#elif __YALC_CSTD < __YALC_C23
#define __YALC_NO_RETURN__ _Noreturn
#elif __YALC_CSTD >= __YALC_C23
#define __YALC_NO_RETURN__ [[noreturn]]
#endif


#endif // __YALC_ATTR_H
