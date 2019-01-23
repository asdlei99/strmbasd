//------------------------------------------------------------------------------
// File: SysClock.h
//
// Desc: DirectShow base classes - defines a system clock implementation of
//       IReferenceClock.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __SYSTEMCLOCK__
#define __SYSTEMCLOCK__

#include "dll.h"

//
// Base clock.  Uses timeGetTime ONLY
// Uses most of the code in the base reference clock.
// Provides GetTime
//

class DLL_EXPORT CSystemClock : public CBaseReferenceClock, public IAMClockAdjust, public IPersist
{
public:
    // We must be able to create an instance of ourselves
    static CUnknown * WINAPI DLL_EXPORT CreateInstance(__inout_opt LPUNKNOWN pUnk, __inout HRESULT *phr);
    DLL_EXPORT CSystemClock(__in_opt LPCTSTR pName, __inout_opt LPUNKNOWN pUnk, __inout HRESULT *phr);

    DECLARE_IUNKNOWN

    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void ** ppv);

    // Yield up our class id so that we can be persisted
    // Implement required Ipersist method
    STDMETHODIMP DLL_EXPORT GetClassID(__out CLSID *pClsID);

    //  IAMClockAdjust methods
    STDMETHODIMP DLL_EXPORT SetClockDelta(REFERENCE_TIME rtDelta);
}; //CSystemClock

#endif /* __SYSTEMCLOCK__ */
