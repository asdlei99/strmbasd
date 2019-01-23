//------------------------------------------------------------------------------
// File: AMExtra.h
//
// Desc: DirectShow base classes.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __AMEXTRA__
#define __AMEXTRA__

#include "dll.h"

// Simple rendered input pin
//
// NOTE if your filter queues stuff before rendering then it may not be
// appropriate to use this class
//
// In that case queue the end of stream condition until the last sample
// is actually rendered and flush the condition appropriately

class DLL_EXPORT CRenderedInputPin : public CBaseInputPin
{
public:

    DLL_EXPORT
    CRenderedInputPin(__in_opt LPCTSTR pObjectName,
                      __in CBaseFilter *pFilter,
                      __in CCritSec *pLock,
                      __inout HRESULT *phr,
                      __in_opt LPCWSTR pName);
#ifdef UNICODE
    DLL_EXPORT
    CRenderedInputPin(__in_opt LPCSTR pObjectName,
                      __in CBaseFilter *pFilter,
                      __in CCritSec *pLock,
                      __inout HRESULT *phr,
                      __in_opt LPCWSTR pName);
#endif

    // Override methods to track end of stream state
    STDMETHODIMP DLL_EXPORT EndOfStream();
    STDMETHODIMP DLL_EXPORT EndFlush();

    HRESULT DLL_EXPORT Active();
    HRESULT DLL_EXPORT Run(REFERENCE_TIME tStart);

protected:

    // Member variables to track state
    BOOL m_bAtEndOfStream;      // Set by EndOfStream
    BOOL m_bCompleteNotified;   // Set when we notify for EC_COMPLETE

private:
    void DLL_EXPORT DoCompleteHandling();
};

#endif // __AMEXTRA__

