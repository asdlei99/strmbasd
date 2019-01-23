//------------------------------------------------------------------------------
// File: SeekPT.h
//
// Desc: DirectShow base classes.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __seekpt_h__
#define __seekpt_h__

#include "dll.h"

class DLL_EXPORT CSeekingPassThru : public ISeekingPassThru, public CUnknown
{
public:
    static CUnknown * DLL_EXPORT CreateInstance(__inout_opt LPUNKNOWN pUnk, __inout HRESULT *phr);
    DLL_EXPORT CSeekingPassThru(__in_opt LPCTSTR pName, __inout_opt LPUNKNOWN pUnk, __inout HRESULT *phr);
    DLL_EXPORT ~CSeekingPassThru();

    DECLARE_IUNKNOWN;
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void ** ppv);

    STDMETHODIMP DLL_EXPORT Init(BOOL bSupportRendering, IPin *pPin);

private:
    CPosPassThru              *m_pPosPassThru;
};

#endif
