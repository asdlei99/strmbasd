//------------------------------------------------------------------------------
// File: WinCtrl.h
//
// Desc: DirectShow base classes - defines classes for video control
//       interfaces.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __WINCTRL__
#define __WINCTRL__

#include "dll.h"

#define ABSOL(x) (x < 0 ? -x : x)
#define NEGAT(x) (x > 0 ? -x : x)

//  Helper
BOOL WINAPI DLL_EXPORT PossiblyEatMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class DLL_EXPORT CBaseControlWindow : public CBaseVideoWindow, public CBaseWindow
{
protected:

    CBaseFilter *m_pFilter;            // Pointer to owning media filter
    CBasePin *m_pPin;                  // Controls media types for connection
    CCritSec *m_pInterfaceLock;        // Externally defined critical section
    COLORREF m_BorderColour;           // Current window border colour
    BOOL m_bAutoShow;                  // What happens when the state changes
    HWND m_hwndOwner;                  // Owner window that we optionally have
    HWND m_hwndDrain;                  // HWND to post any messages received
    BOOL m_bCursorHidden;              // Should we hide the window cursor

public:

    // Internal methods for other objects to get information out

    HRESULT DLL_EXPORT DoSetWindowStyle(long Style,long WindowLong);
    HRESULT DLL_EXPORT DoGetWindowStyle(__out long *pStyle,long WindowLong);
    BOOL DLL_EXPORT IsAutoShowEnabled() { return m_bAutoShow; };
    COLORREF DLL_EXPORT GetBorderColour() { return m_BorderColour; };
    HWND DLL_EXPORT GetOwnerWindow() { return m_hwndOwner; };
    BOOL DLL_EXPORT IsCursorHidden() { return m_bCursorHidden; };

    inline BOOL DLL_EXPORT PossiblyEatMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        return ::PossiblyEatMessage(m_hwndDrain, uMsg, wParam, lParam);
    }

    // Derived classes must call this to set the pin the filter is using
    // We don't have the pin passed in to the constructor (as we do with
    // the CBaseFilter object) because filters typically create the
    // pins dynamically when requested in CBaseFilter::GetPin. This can
    // not be called from our constructor because is is a virtual method

    void DLL_EXPORT SetControlWindowPin(CBasePin *pPin) {
        m_pPin = pPin;
    }

public:

    DLL_EXPORT
    CBaseControlWindow(__inout CBaseFilter *pFilter,   // Owning media filter
                       __in CCritSec *pInterfaceLock,  // Locking object
                       __in_opt LPCTSTR pName,         // Object description
                       __inout_opt LPUNKNOWN pUnk,     // Normal COM ownership
                       __inout HRESULT *phr);          // OLE return code

    // These are the properties we support

    STDMETHODIMP DLL_EXPORT put_Caption(__in BSTR strCaption);
    STDMETHODIMP DLL_EXPORT get_Caption(__out BSTR *pstrCaption);
    STDMETHODIMP DLL_EXPORT put_AutoShow(long AutoShow);
    STDMETHODIMP DLL_EXPORT get_AutoShow(__out long *AutoShow);
    STDMETHODIMP DLL_EXPORT put_WindowStyle(long WindowStyle);
    STDMETHODIMP DLL_EXPORT get_WindowStyle(__out long *pWindowStyle);
    STDMETHODIMP DLL_EXPORT put_WindowStyleEx(long WindowStyleEx);
    STDMETHODIMP DLL_EXPORT get_WindowStyleEx(__out long *pWindowStyleEx);
    STDMETHODIMP DLL_EXPORT put_WindowState(long WindowState);
    STDMETHODIMP DLL_EXPORT get_WindowState(__out long *pWindowState);
    STDMETHODIMP DLL_EXPORT put_BackgroundPalette(long BackgroundPalette);
    STDMETHODIMP DLL_EXPORT get_BackgroundPalette(__out long *pBackgroundPalette);
    STDMETHODIMP DLL_EXPORT put_Visible(long Visible);
    STDMETHODIMP DLL_EXPORT get_Visible(__out long *pVisible);
    STDMETHODIMP DLL_EXPORT put_Left(long Left);
    STDMETHODIMP DLL_EXPORT get_Left(__out long *pLeft);
    STDMETHODIMP DLL_EXPORT put_Width(long Width);
    STDMETHODIMP DLL_EXPORT get_Width(__out long *pWidth);
    STDMETHODIMP DLL_EXPORT put_Top(long Top);
    STDMETHODIMP DLL_EXPORT get_Top(__out long *pTop);
    STDMETHODIMP DLL_EXPORT put_Height(long Height);
    STDMETHODIMP DLL_EXPORT get_Height(__out long *pHeight);
    STDMETHODIMP DLL_EXPORT put_Owner(OAHWND Owner);
    STDMETHODIMP DLL_EXPORT get_Owner(__out OAHWND *Owner);
    STDMETHODIMP DLL_EXPORT put_MessageDrain(OAHWND Drain);
    STDMETHODIMP DLL_EXPORT get_MessageDrain(__out OAHWND *Drain);
    STDMETHODIMP DLL_EXPORT get_BorderColor(__out long *Color);
    STDMETHODIMP DLL_EXPORT put_BorderColor(long Color);
    STDMETHODIMP DLL_EXPORT get_FullScreenMode(__out long *FullScreenMode);
    STDMETHODIMP DLL_EXPORT put_FullScreenMode(long FullScreenMode);

    // And these are the methods

    STDMETHODIMP DLL_EXPORT SetWindowForeground(long Focus);
    STDMETHODIMP DLL_EXPORT NotifyOwnerMessage(OAHWND hwnd,long uMsg,LONG_PTR wParam,LONG_PTR lParam);
    STDMETHODIMP DLL_EXPORT GetMinIdealImageSize(__out long *pWidth,__out long *pHeight);
    STDMETHODIMP DLL_EXPORT GetMaxIdealImageSize(__out long *pWidth,__out long *pHeight);
    STDMETHODIMP DLL_EXPORT SetWindowPosition(long Left,long Top,long Width,long Height);
    STDMETHODIMP DLL_EXPORT GetWindowPosition(__out long *pLeft,__out long *pTop,__out long *pWidth,__out long *pHeight);
    STDMETHODIMP DLL_EXPORT GetRestorePosition(__out long *pLeft,__out long *pTop,__out long *pWidth,__out long *pHeight);
	STDMETHODIMP DLL_EXPORT HideCursor(long HideCursor);
    STDMETHODIMP DLL_EXPORT IsCursorHidden(__out long *CursorHidden);
};

// This class implements the IBasicVideo interface

class DLL_EXPORT CBaseControlVideo : public CBaseBasicVideo
{
protected:

    CBaseFilter *m_pFilter;   // Pointer to owning media filter
    CBasePin *m_pPin;                   // Controls media types for connection
    CCritSec *m_pInterfaceLock;         // Externally defined critical section

public:

    // Derived classes must provide these for the implementation

    virtual HRESULT DLL_EXPORT IsDefaultTargetRect() PURE;
    virtual HRESULT DLL_EXPORT SetDefaultTargetRect() PURE;
    virtual HRESULT DLL_EXPORT SetTargetRect(RECT *pTargetRect) PURE;
    virtual HRESULT DLL_EXPORT GetTargetRect(RECT *pTargetRect) PURE;
    virtual HRESULT DLL_EXPORT IsDefaultSourceRect() PURE;
    virtual HRESULT DLL_EXPORT SetDefaultSourceRect() PURE;
    virtual HRESULT DLL_EXPORT SetSourceRect(RECT *pSourceRect) PURE;
    virtual HRESULT DLL_EXPORT GetSourceRect(RECT *pSourceRect) PURE;
    virtual HRESULT DLL_EXPORT GetStaticImage(__inout long *pBufferSize,__out_bcount_part(*pBufferSize, *pBufferSize) long *pDIBImage) PURE;

    // Derived classes must override this to return a VIDEOINFO representing
    // the video format. We cannot call IPin ConnectionMediaType to get this
    // format because various filters dynamically change the type when using
    // DirectDraw such that the format shows the position of the logical
    // bitmap in a frame buffer surface, so the size might be returned as
    // 1024x768 pixels instead of 320x240 which is the real video dimensions

    __out virtual VIDEOINFOHEADER * DLL_EXPORT GetVideoFormat() PURE;

    // Helper functions for creating memory renderings of a DIB image

    HRESULT DLL_EXPORT
            GetImageSize(__in VIDEOINFOHEADER *pVideoInfo,
                         __out LONG *pBufferSize,
                         __in RECT *pSourceRect);

    HRESULT DLL_EXPORT
            CopyImage(IMediaSample *pMediaSample,
                      __in VIDEOINFOHEADER *pVideoInfo,
                      __inout LONG *pBufferSize,
                      __out_bcount_part(*pBufferSize, *pBufferSize) BYTE *pVideoImage,
                      __in RECT *pSourceRect);

    // Override this if you want notifying when the rectangles change
    virtual HRESULT DLL_EXPORT OnUpdateRectangles() { return NOERROR; };
    virtual HRESULT DLL_EXPORT OnVideoSizeChange();

    // Derived classes must call this to set the pin the filter is using
    // We don't have the pin passed in to the constructor (as we do with
    // the CBaseFilter object) because filters typically create the
    // pins dynamically when requested in CBaseFilter::GetPin. This can
    // not be called from our constructor because is is a virtual method

    void DLL_EXPORT SetControlVideoPin(__inout CBasePin *pPin) {
        m_pPin = pPin;
    }

    // Helper methods for checking rectangles
    virtual HRESULT DLL_EXPORT CheckSourceRect(__in RECT *pSourceRect);
    virtual HRESULT DLL_EXPORT CheckTargetRect(__in RECT *pTargetRect);

public:

    DLL_EXPORT
    CBaseControlVideo(__inout CBaseFilter *pFilter,    // Owning media filter
                      __in CCritSec *pInterfaceLock,   // Serialise interface
                      __in_opt LPCTSTR pName,          // Object description
                      __inout_opt LPUNKNOWN pUnk,      // Normal COM ownership
                      __inout HRESULT *phr);           // OLE return code

    // These are the properties we support

    STDMETHODIMP DLL_EXPORT get_AvgTimePerFrame(__out REFTIME *pAvgTimePerFrame);
    STDMETHODIMP DLL_EXPORT get_BitRate(__out long *pBitRate);
    STDMETHODIMP DLL_EXPORT get_BitErrorRate(__out long *pBitErrorRate);
    STDMETHODIMP DLL_EXPORT get_VideoWidth(__out long *pVideoWidth);
    STDMETHODIMP DLL_EXPORT get_VideoHeight(__out long *pVideoHeight);
    STDMETHODIMP DLL_EXPORT put_SourceLeft(long SourceLeft);
    STDMETHODIMP DLL_EXPORT get_SourceLeft(__out long *pSourceLeft);
    STDMETHODIMP DLL_EXPORT put_SourceWidth(long SourceWidth);
    STDMETHODIMP DLL_EXPORT get_SourceWidth(__out long *pSourceWidth);
    STDMETHODIMP DLL_EXPORT put_SourceTop(long SourceTop);
    STDMETHODIMP DLL_EXPORT get_SourceTop(__out long *pSourceTop);
    STDMETHODIMP DLL_EXPORT put_SourceHeight(long SourceHeight);
    STDMETHODIMP DLL_EXPORT get_SourceHeight(__out long *pSourceHeight);
    STDMETHODIMP DLL_EXPORT put_DestinationLeft(long DestinationLeft);
    STDMETHODIMP DLL_EXPORT get_DestinationLeft(__out long *pDestinationLeft);
    STDMETHODIMP DLL_EXPORT put_DestinationWidth(long DestinationWidth);
    STDMETHODIMP DLL_EXPORT get_DestinationWidth(__out long *pDestinationWidth);
    STDMETHODIMP DLL_EXPORT put_DestinationTop(long DestinationTop);
    STDMETHODIMP DLL_EXPORT get_DestinationTop(__out long *pDestinationTop);
    STDMETHODIMP DLL_EXPORT put_DestinationHeight(long DestinationHeight);
    STDMETHODIMP DLL_EXPORT get_DestinationHeight(__out long *pDestinationHeight);

    // And these are the methods

    STDMETHODIMP DLL_EXPORT GetVideoSize(__out long *pWidth,__out long *pHeight);
    STDMETHODIMP DLL_EXPORT SetSourcePosition(long Left,long Top,long Width,long Height);
    STDMETHODIMP DLL_EXPORT GetSourcePosition(__out long *pLeft,__out long *pTop,__out long *pWidth,__out long *pHeight);
    STDMETHODIMP DLL_EXPORT GetVideoPaletteEntries(long StartIndex,long Entries,__out long *pRetrieved,__out_ecount_part(Entries, *pRetrieved) long *pPalette);
    STDMETHODIMP DLL_EXPORT SetDefaultSourcePosition();
    STDMETHODIMP DLL_EXPORT IsUsingDefaultSource();
    STDMETHODIMP DLL_EXPORT SetDestinationPosition(long Left,long Top,long Width,long Height);
    STDMETHODIMP DLL_EXPORT GetDestinationPosition(__out long *pLeft,__out long *pTop,__out long *pWidth,__out long *pHeight);
    STDMETHODIMP DLL_EXPORT SetDefaultDestinationPosition();
    STDMETHODIMP DLL_EXPORT IsUsingDefaultDestination();
    STDMETHODIMP DLL_EXPORT GetCurrentImage(__inout long *pBufferSize,__out_bcount_part(*pBufferSize, *pBufferSize) long *pVideoImage);
};

#endif // __WINCTRL__

