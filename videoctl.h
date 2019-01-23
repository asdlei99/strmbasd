//------------------------------------------------------------------------------
// File: VideoCtl.h
//
// Desc: DirectShow base classes.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __VIDEOCTL__
#define __VIDEOCTL__

#include "dll.h"

// These help with property page implementations. The first can be used to
// load any string from a resource file. The buffer to load into is passed
// as an input parameter. The same buffer is the return value if the string
// was found otherwise it returns TEXT(""). The GetDialogSize is passed the
// resource ID of a dialog box and returns the size of it in screen pixels

#define STR_MAX_LENGTH 256
LPTSTR WINAPI DLL_EXPORT StringFromResource(__out_ecount(STR_MAX_LENGTH) LPTSTR pBuffer, int iResourceID);

#ifdef UNICODE
#define WideStringFromResource StringFromResource
LPSTR WINAPI DLL_EXPORT StringFromResource(__out_ecount(STR_MAX_LENGTH) LPSTR pBuffer, int iResourceID);
#else
LPWSTR WINAPI DLL_EXPORT WideStringFromResource(__out_ecount(STR_MAX_LENGTH) LPWSTR pBuffer, int iResourceID);
#endif


BOOL WINAPI DLL_EXPORT GetDialogSize(int iResourceID,     // Dialog box resource identifier
                          DLGPROC pDlgProc,    // Pointer to dialog procedure
                          LPARAM lParam,       // Any user data wanted in pDlgProc
                          __out SIZE *pResult);// Returns the size of dialog box

// Class that aggregates an IDirectDraw interface

class DLL_EXPORT CAggDirectDraw : public IDirectDraw, public CUnknown
{
protected:

    LPDIRECTDRAW m_pDirectDraw;

public:

    DECLARE_IUNKNOWN
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid,__deref_out void **ppv);

    // Constructor and destructor

    DLL_EXPORT
    CAggDirectDraw(__in_opt LPCTSTR pName,__inout_opt LPUNKNOWN pUnk) :
        CUnknown(pName,pUnk),
        m_pDirectDraw(NULL) { };

    virtual DLL_EXPORT ~CAggDirectDraw() { };

    // Set the object we should be aggregating
    void DLL_EXPORT SetDirectDraw(__inout LPDIRECTDRAW pDirectDraw) {
        m_pDirectDraw = pDirectDraw;
    }

    // IDirectDraw methods

    STDMETHODIMP DLL_EXPORT Compact();
    STDMETHODIMP DLL_EXPORT CreateClipper(DWORD dwFlags,__deref_out LPDIRECTDRAWCLIPPER *lplpDDClipper,__inout_opt IUnknown *pUnkOuter);
    STDMETHODIMP DLL_EXPORT CreatePalette(DWORD dwFlags,__in LPPALETTEENTRY lpColorTable,__deref_out LPDIRECTDRAWPALETTE *lplpDDPalette,__inout_opt IUnknown *pUnkOuter);
    STDMETHODIMP DLL_EXPORT CreateSurface(__in LPDDSURFACEDESC lpDDSurfaceDesc,__deref_out LPDIRECTDRAWSURFACE *lplpDDSurface,__inout_opt IUnknown *pUnkOuter);
    STDMETHODIMP DLL_EXPORT DuplicateSurface(__in LPDIRECTDRAWSURFACE lpDDSurface,__deref_out LPDIRECTDRAWSURFACE *lplpDupDDSurface);
    STDMETHODIMP DLL_EXPORT EnumDisplayModes(DWORD dwSurfaceDescCount,__in LPDDSURFACEDESC lplpDDSurfaceDescList,__in LPVOID lpContext,__in LPDDENUMMODESCALLBACK lpEnumCallback);
    STDMETHODIMP DLL_EXPORT EnumSurfaces(DWORD dwFlags,__in LPDDSURFACEDESC lpDDSD,__in LPVOID lpContext,__in LPDDENUMSURFACESCALLBACK lpEnumCallback);
    STDMETHODIMP DLL_EXPORT FlipToGDISurface();
    STDMETHODIMP DLL_EXPORT GetCaps(__out LPDDCAPS lpDDDriverCaps,__out LPDDCAPS lpDDHELCaps);
    STDMETHODIMP DLL_EXPORT GetDisplayMode(__out LPDDSURFACEDESC lpDDSurfaceDesc);
    STDMETHODIMP DLL_EXPORT GetFourCCCodes(__inout LPDWORD lpNumCodes,__out_ecount(*lpNumCodes) LPDWORD lpCodes);
    STDMETHODIMP DLL_EXPORT GetGDISurface(__deref_out LPDIRECTDRAWSURFACE *lplpGDIDDSurface);
    STDMETHODIMP DLL_EXPORT GetMonitorFrequency(__out LPDWORD lpdwFrequency);
    STDMETHODIMP DLL_EXPORT GetScanLine(__out LPDWORD lpdwScanLine);
    STDMETHODIMP DLL_EXPORT GetVerticalBlankStatus(__out LPBOOL lpblsInVB);
    STDMETHODIMP DLL_EXPORT Initialize(__in GUID *lpGUID);
    STDMETHODIMP DLL_EXPORT RestoreDisplayMode();
    STDMETHODIMP DLL_EXPORT SetCooperativeLevel(HWND hWnd,DWORD dwFlags);
    STDMETHODIMP DLL_EXPORT SetDisplayMode(DWORD dwWidth,DWORD dwHeight,DWORD dwBpp);
    STDMETHODIMP DLL_EXPORT WaitForVerticalBlank(DWORD dwFlags,HANDLE hEvent);
};


// Class that aggregates an IDirectDrawSurface interface

class DLL_EXPORT CAggDrawSurface : public IDirectDrawSurface, public CUnknown
{
protected:

    LPDIRECTDRAWSURFACE m_pDirectDrawSurface;

public:

    DECLARE_IUNKNOWN
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid,__deref_out void **ppv);

    // Constructor and destructor

    DLL_EXPORT
    CAggDrawSurface(__in_opt LPCTSTR pName,__inout_opt LPUNKNOWN pUnk) :
        CUnknown(pName,pUnk),
        m_pDirectDrawSurface(NULL) { };

    virtual DLL_EXPORT ~CAggDrawSurface() { };

    // Set the object we should be aggregating
    void DLL_EXPORT SetDirectDrawSurface(__inout LPDIRECTDRAWSURFACE pDirectDrawSurface) {
        m_pDirectDrawSurface = pDirectDrawSurface;
    }

    // IDirectDrawSurface methods

    STDMETHODIMP DLL_EXPORT AddAttachedSurface(__in LPDIRECTDRAWSURFACE lpDDSAttachedSurface);
    STDMETHODIMP DLL_EXPORT AddOverlayDirtyRect(__in LPRECT lpRect);
    STDMETHODIMP DLL_EXPORT Blt(__in LPRECT lpDestRect,__in LPDIRECTDRAWSURFACE lpDDSrcSurface,__in LPRECT lpSrcRect,DWORD dwFlags,__in LPDDBLTFX lpDDBltFx);
    STDMETHODIMP DLL_EXPORT BltBatch(__in_ecount(dwCount) LPDDBLTBATCH lpDDBltBatch,DWORD dwCount,DWORD dwFlags);
    STDMETHODIMP DLL_EXPORT BltFast(DWORD dwX,DWORD dwY,__in LPDIRECTDRAWSURFACE lpDDSrcSurface,__in LPRECT lpSrcRect,DWORD dwTrans);
    STDMETHODIMP DLL_EXPORT DeleteAttachedSurface(DWORD dwFlags,__in LPDIRECTDRAWSURFACE lpDDSAttachedSurface);
    STDMETHODIMP DLL_EXPORT EnumAttachedSurfaces(__in LPVOID lpContext,__in LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback);
    STDMETHODIMP DLL_EXPORT EnumOverlayZOrders(DWORD dwFlags,__in LPVOID lpContext,__in LPDDENUMSURFACESCALLBACK lpfnCallback);
    STDMETHODIMP DLL_EXPORT Flip(__in LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride,DWORD dwFlags);
    STDMETHODIMP DLL_EXPORT GetAttachedSurface(__in LPDDSCAPS lpDDSCaps,__deref_out LPDIRECTDRAWSURFACE *lplpDDAttachedSurface);
    STDMETHODIMP DLL_EXPORT GetBltStatus(DWORD dwFlags);
    STDMETHODIMP DLL_EXPORT GetCaps(__out LPDDSCAPS lpDDSCaps);
    STDMETHODIMP DLL_EXPORT GetClipper(__deref_out LPDIRECTDRAWCLIPPER *lplpDDClipper);
    STDMETHODIMP DLL_EXPORT GetColorKey(DWORD dwFlags,__out LPDDCOLORKEY lpDDColorKey);
    STDMETHODIMP DLL_EXPORT GetDC(__out HDC *lphDC);
    STDMETHODIMP DLL_EXPORT GetFlipStatus(DWORD dwFlags);
    STDMETHODIMP DLL_EXPORT GetOverlayPosition(__out LPLONG lpdwX,__out LPLONG lpdwY);
    STDMETHODIMP DLL_EXPORT GetPalette(__deref_out LPDIRECTDRAWPALETTE *lplpDDPalette);
    STDMETHODIMP DLL_EXPORT GetPixelFormat(__out LPDDPIXELFORMAT lpDDPixelFormat);
    STDMETHODIMP DLL_EXPORT GetSurfaceDesc(__out LPDDSURFACEDESC lpDDSurfaceDesc);
    STDMETHODIMP DLL_EXPORT Initialize(__in LPDIRECTDRAW lpDD,__in LPDDSURFACEDESC lpDDSurfaceDesc);
    STDMETHODIMP DLL_EXPORT IsLost();
    STDMETHODIMP DLL_EXPORT Lock(__in LPRECT lpDestRect,__inout LPDDSURFACEDESC lpDDSurfaceDesc,DWORD dwFlags,HANDLE hEvent);
    STDMETHODIMP DLL_EXPORT ReleaseDC(HDC hDC);
    STDMETHODIMP DLL_EXPORT Restore();
    STDMETHODIMP DLL_EXPORT SetClipper(__in LPDIRECTDRAWCLIPPER lpDDClipper);
    STDMETHODIMP DLL_EXPORT SetColorKey(DWORD dwFlags,__in LPDDCOLORKEY lpDDColorKey);
    STDMETHODIMP DLL_EXPORT SetOverlayPosition(LONG dwX,LONG dwY);
    STDMETHODIMP DLL_EXPORT SetPalette(__in LPDIRECTDRAWPALETTE lpDDPalette);
    STDMETHODIMP DLL_EXPORT Unlock(__in LPVOID lpSurfaceData);
    STDMETHODIMP DLL_EXPORT UpdateOverlay(__in LPRECT lpSrcRect,__in LPDIRECTDRAWSURFACE lpDDDestSurface,__in LPRECT lpDestRect,DWORD dwFlags,__in LPDDOVERLAYFX lpDDOverlayFX);
    STDMETHODIMP DLL_EXPORT UpdateOverlayDisplay(DWORD dwFlags);
    STDMETHODIMP DLL_EXPORT UpdateOverlayZOrder(DWORD dwFlags,__in LPDIRECTDRAWSURFACE lpDDSReference);
};


class DLL_EXPORT CLoadDirectDraw
{
    LPDIRECTDRAW m_pDirectDraw;     // The DirectDraw driver instance
    HINSTANCE m_hDirectDraw;        // Handle to the loaded library

public:

    DLL_EXPORT CLoadDirectDraw();
    DLL_EXPORT ~CLoadDirectDraw();

    HRESULT DLL_EXPORT LoadDirectDraw(__in LPSTR szDevice);
    void DLL_EXPORT ReleaseDirectDraw();
    HRESULT DLL_EXPORT IsDirectDrawLoaded();
    LPDIRECTDRAW DLL_EXPORT GetDirectDraw();
    BOOL DLL_EXPORT IsDirectDrawVersion1();
};

#endif // __VIDEOCTL__

