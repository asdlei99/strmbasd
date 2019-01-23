#include "compat.h"
#include <rpc.h>

/*
HRESULT DWordMult(_In_  DWORD dwMultiplicand,
                  _In_  DWORD dwMultiplier,
                  _Out_ DWORD *pdwResult)
{
    *pdwResult = dwMultiplicand * dwMultiplier;
    if (static_cast <unsigned long long> (dwMultiplicand) * static_cast <unsigned long long> (dwMultiplier)
        >= 4294967295ULL)
        return INTSAFE_E_ARITHMETIC_OVERFLOW;
    return S_OK;
}

HRESULT DWordAdd(_In_  DWORD dwAugend,
                 _In_  DWORD dwAddend,
                 _Out_ DWORD *pdwResult)
{
    *pdwResult = dwAugend + dwAddend;
    if (static_cast <unsigned long long> (dwAugend) + static_cast <unsigned long long> (dwAddend)
        >= 4294967295ULL)
        return INTSAFE_E_ARITHMETIC_OVERFLOW;
    return S_OK;
}
*/

#define MAKE_GUID_HACK(NAME, DATA1, DATA2, DATA3, B0, B1, B2, B3, B4, B5, B6, B7) \
auto NAME = GUID { \
    DATA1, \
    DATA2, \
    DATA3, \
    { B0, B1, B2, B3, B4, B5, B6, B7 } \
};

#if ENABLE_IREFERENCE_CLOCK_TIMER_CONTROL_FIX
MAKE_GUID_HACK(IID_IReferenceClockTimerControl, 0xebec459c, 0x2eca, 0x4d42, 0xa8,0xaf, 0x30,0xdf,0x55,0x76,0x14,0xb8)
#endif
