#ifndef DLL_H_INCLUDED
#define DLL_H_INCLUDED

#ifndef NO_DLLEXPORT
#   ifdef BUILD_DLL
#       define DLL_EXPORT __declspec(dllexport)
#   else
#       define DLL_EXPORT __declspec(dllimport)
#   endif
#else
#   define DLL_EXPORT
#endif

#define DLL_EXPORT_2 __declspec(dllexport)

#endif // DLL_H_INCLUDED
