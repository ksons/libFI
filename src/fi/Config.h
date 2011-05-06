#ifndef FI_CONFIG_H
#define FI_CONFIG_H


#if defined(_WIN32)
# if defined(fi_EXPORTS)
#  define LIBFI_EXPORT __declspec(dllexport)
# else
#  define LIBFI_EXPORT __declspec(dllimport)
# endif
#else
# define LIBFI_EXPORT
#endif

#if defined(_MSC_VER) 
# pragma warning (disable: 4275) /* non-DLL-interface base class used */
# pragma warning (disable: 4251) /* needs to have dll-interface to be used by clients */
/* No warning for safe windows only functions */
# define _CRT_SECURE_NO_WARNINGS
#endif


#endif // FI_CONFIG_H
