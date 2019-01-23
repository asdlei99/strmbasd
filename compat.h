#ifndef COMPAT_H_INCLUDED
#define COMPAT_H_INCLUDED

#include "bigger_type.h"
#include <intsafe.h>
#include <windows.h>
//#include <strmif.h>

#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wwrite-strings"

#define ENABLE_IREFERENCE_CLOCK_TIMER_CONTROL_FIX 1

#ifndef _In_
#define _In_
#endif

#ifndef _Out_
#define _Out_
#endif

#define __inout_opt
#define __in_bcount(T)
#define __in
#define __out
//#define _asm asm
#define __out_ecount(T)
#define __deref_out
#define __deref_in
#define __deref_inout_opt
#define __in_opt
#define __inout
#define __out_opt
#define __in_ecount(T)
#define __deref_out_opt
#define __out_ecount_part(T, V)
#define __field_ecount_opt(T)
#define __in_bcount_opt(T)
#define __out_bcount(T)
#define __range(T, V)
#define __inout_ecount_full(T)
#define __out_bcount_part(T, V)
#define __in_ecount_opt(T)
#define _Outptr_
#define __allowed(T)
#define __deref_out_range(T, V)
#define __success(T)
#define __out_range(T, V)

#define __control_entrypoint(category)     __allowed(on_function)

//#define AM_NOVTABLE __declspec(novtable)
#define AM_NOVTABLE

#undef _X86_

#ifdef _I64_MAX
#undef _I64_MAX
#define _I64_MAX LONG_LONG_MAX
#endif

constexpr long long operator "" _I64 (unsigned long long int i)
{
    return i;
}

namespace compat
{
    template <typename T, typename U>
    constexpr auto min (T lhs, U rhs) -> typename BiggerType <T, U>::type
    {
        if (lhs <= rhs)
            return lhs;
        else
            return rhs;
    }

    template <typename T, typename U>
    constexpr auto max (T lhs, U rhs) -> typename BiggerType <T, U>::type
    {
        if (lhs >= rhs)
            return lhs;
        else
            return rhs;
    }
}

/*
HRESULT DWordMult(_In_  DWORD dwMultiplicand,
                  _In_  DWORD dwMultiplier,
                  _Out_ DWORD *pdwResult);

HRESULT DWordAdd(_In_  DWORD dwAugend,
                 _In_  DWORD dwAddend,
                 _Out_ DWORD *pdwResult);
*/

#endif // COMPAT_H_INCLUDED
