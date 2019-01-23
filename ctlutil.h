//------------------------------------------------------------------------------
// File: CtlUtil.h
//
// Desc: DirectShow base classes.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


// Base classes implementing IDispatch parsing for the basic control dual
// interfaces. Derive from these and implement just the custom method and
// property methods. We also implement CPosPassThru that can be used by
// renderers and transforms to pass by IMediaPosition and IMediaSeeking

#ifndef __CTLUTIL__
#define __CTLUTIL__

#include "compat.h"
#include "dll.h"

// OLE Automation has different ideas of TRUE and FALSE

#define OATRUE (-1)
#define OAFALSE (0)


// It's possible that we could replace this class with CreateStdDispatch

class DLL_EXPORT CBaseDispatch
{
    ITypeInfo * m_pti;

public:

    DLL_EXPORT CBaseDispatch() : m_pti(NULL) {}
    DLL_EXPORT ~CBaseDispatch();

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      REFIID riid,
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);
};


class AM_NOVTABLE DLL_EXPORT CMediaControl :
    public IMediaControl,
    public CUnknown
{
    CBaseDispatch m_basedisp;

public:

    DLL_EXPORT CMediaControl(const TCHAR *, LPUNKNOWN);

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);

    STDMETHODIMP DLL_EXPORT Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      __in DISPPARAMS * pdispparams,
      __out_opt VARIANT * pvarResult,
      __out_opt EXCEPINFO * pexcepinfo,
      __out_opt UINT * puArgErr);
};


class AM_NOVTABLE DLL_EXPORT CMediaEvent :
    public IMediaEventEx,
    public CUnknown
{
    CBaseDispatch m_basedisp;

public:

    DLL_EXPORT CMediaEvent(__in_opt LPCTSTR, __in_opt LPUNKNOWN);

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);

    STDMETHODIMP DLL_EXPORT Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      __in DISPPARAMS * pdispparams,
      __out_opt VARIANT * pvarResult,
      __out_opt EXCEPINFO * pexcepinfo,
      __out_opt UINT * puArgErr);
};


class AM_NOVTABLE DLL_EXPORT CMediaPosition :
    public IMediaPosition,
    public CUnknown
{
    CBaseDispatch m_basedisp;


public:

    DLL_EXPORT CMediaPosition(__in_opt LPCTSTR, __in_opt LPUNKNOWN);
    DLL_EXPORT CMediaPosition(__in_opt LPCTSTR, __in_opt LPUNKNOWN, __inout HRESULT *phr);

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);

    STDMETHODIMP DLL_EXPORT Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      __in DISPPARAMS * pdispparams,
      __out_opt VARIANT * pvarResult,
      __out_opt EXCEPINFO * pexcepinfo,
      __out_opt UINT * puArgErr);

};


// OA-compatibility means that we must use double as the RefTime value,
// and REFERENCE_TIME (essentially a LONGLONG) within filters.
// this class converts between the two

class COARefTime : public CRefTime {
public:

    COARefTime() {
    };

    COARefTime(CRefTime t)
        : CRefTime(t)
    {
    };

    COARefTime(REFERENCE_TIME t)
        : CRefTime(t)
    {
    };

    COARefTime(double d) {
        m_time = (LONGLONG) (d * 10000000);
    };

    operator double() {
        return double(m_time) / 10000000;
    };

    operator REFERENCE_TIME() {
        return m_time;
    };

    COARefTime& operator=(const double& rd)  {
        m_time = (LONGLONG) (rd * 10000000);
        return *this;
    }

    COARefTime& operator=(const REFERENCE_TIME& rt)  {
        m_time = rt;
        return *this;
    }

    inline BOOL operator==(const COARefTime& rt)
    {
        return m_time == rt.m_time;
    };

    inline BOOL operator!=(const COARefTime& rt)
    {
        return m_time != rt.m_time;
    };

    inline BOOL operator < (const COARefTime& rt)
    {
        return m_time < rt.m_time;
    };

    inline BOOL operator > (const COARefTime& rt)
    {
        return m_time > rt.m_time;
    };

    inline BOOL operator >= (const COARefTime& rt)
    {
        return m_time >= rt.m_time;
    };

    inline BOOL operator <= (const COARefTime& rt)
    {
        return m_time <= rt.m_time;
    };

    inline COARefTime operator+(const COARefTime& rt)
    {
        return COARefTime(m_time + rt.m_time);
    };

    inline COARefTime operator-(const COARefTime& rt)
    {
        return COARefTime(m_time - rt.m_time);
    };

    inline COARefTime operator*(LONG l)
    {
        return COARefTime(m_time * l);
    };

    inline COARefTime operator/(LONG l)
    {
        return COARefTime(m_time / l);
    };

private:
    //  Prevent bugs from constructing from LONG (which gets
    //  converted to double and then multiplied by 10000000
    COARefTime(LONG);
    LONG DLL_EXPORT operator=(LONG);
};


// A utility class that handles IMediaPosition and IMediaSeeking on behalf
// of single-input pin renderers, or transform filters.
//
// Renderers will expose this from the filter; transform filters will
// expose it from the output pin and not the renderer.
//
// Create one of these, giving it your IPin* for your input pin, and delegate
// all IMediaPosition methods to it. It will query the input pin for
// IMediaPosition and respond appropriately.
//
// Call ForceRefresh if the pin connection changes.
//
// This class no longer caches the upstream IMediaPosition or IMediaSeeking
// it acquires it on each method call. This means ForceRefresh is not needed.
// The method is kept for source compatibility and to minimise the changes
// if we need to put it back later for performance reasons.

class DLL_EXPORT CPosPassThru : public IMediaSeeking, public CMediaPosition
{
    IPin *m_pPin;

    HRESULT DLL_EXPORT GetPeer(__deref_out IMediaPosition **ppMP);
    HRESULT DLL_EXPORT GetPeerSeeking(__deref_out IMediaSeeking **ppMS);

public:

    DLL_EXPORT CPosPassThru(__in_opt LPCTSTR, __in_opt LPUNKNOWN, __inout HRESULT*, IPin *);
    DECLARE_IUNKNOWN

    HRESULT DLL_EXPORT ForceRefresh() {
        return S_OK;
    };

    // override to return an accurate current position
    virtual HRESULT DLL_EXPORT GetMediaTime(__out LONGLONG *pStartTime, __out_opt LONGLONG *pEndTime) {
        return E_FAIL;
    }

    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid,__deref_out void **ppv);

    // IMediaSeeking methods
    STDMETHODIMP DLL_EXPORT GetCapabilities( __out DWORD * pCapabilities );
    STDMETHODIMP DLL_EXPORT CheckCapabilities( __inout DWORD * pCapabilities );
    STDMETHODIMP DLL_EXPORT SetTimeFormat(const GUID * pFormat);
    STDMETHODIMP DLL_EXPORT GetTimeFormat(__out GUID *pFormat);
    STDMETHODIMP DLL_EXPORT IsUsingTimeFormat(const GUID * pFormat);
    STDMETHODIMP DLL_EXPORT IsFormatSupported( const GUID * pFormat);
    STDMETHODIMP DLL_EXPORT QueryPreferredFormat( __out GUID *pFormat);
    STDMETHODIMP DLL_EXPORT ConvertTimeFormat(__out LONGLONG * pTarget,
                                   __in_opt const GUID * pTargetFormat,
                                   LONGLONG Source,
                                   __in_opt const GUID * pSourceFormat );
    STDMETHODIMP DLL_EXPORT SetPositions( __inout_opt LONGLONG * pCurrent, DWORD CurrentFlags
                             , __inout_opt LONGLONG * pStop, DWORD StopFlags );

    STDMETHODIMP DLL_EXPORT GetPositions( __out_opt LONGLONG * pCurrent, __out_opt LONGLONG * pStop );
    STDMETHODIMP DLL_EXPORT GetCurrentPosition( __out LONGLONG * pCurrent );
    STDMETHODIMP DLL_EXPORT GetStopPosition( __out LONGLONG * pStop );
    STDMETHODIMP DLL_EXPORT SetRate( double dRate);
    STDMETHODIMP DLL_EXPORT GetRate( __out double * pdRate);
    STDMETHODIMP DLL_EXPORT GetDuration( __out LONGLONG *pDuration);
    STDMETHODIMP DLL_EXPORT GetAvailable( __out_opt LONGLONG *pEarliest, __out_opt LONGLONG *pLatest );
    STDMETHODIMP DLL_EXPORT GetPreroll( __out LONGLONG *pllPreroll );

    // IMediaPosition properties
    STDMETHODIMP DLL_EXPORT get_Duration(__out REFTIME * plength);
    STDMETHODIMP DLL_EXPORT put_CurrentPosition(REFTIME llTime);
    STDMETHODIMP DLL_EXPORT get_StopTime(__out REFTIME * pllTime);
    STDMETHODIMP DLL_EXPORT put_StopTime(REFTIME llTime);
    STDMETHODIMP DLL_EXPORT get_PrerollTime(__out REFTIME * pllTime);
    STDMETHODIMP DLL_EXPORT put_PrerollTime(REFTIME llTime);
    STDMETHODIMP DLL_EXPORT get_Rate(__out double * pdRate);
    STDMETHODIMP DLL_EXPORT put_Rate(double dRate);
    STDMETHODIMP DLL_EXPORT get_CurrentPosition(__out REFTIME * pllTime);
    STDMETHODIMP DLL_EXPORT CanSeekForward(__out LONG *pCanSeekForward);
    STDMETHODIMP DLL_EXPORT CanSeekBackward(__out LONG *pCanSeekBackward);

private:
    HRESULT DLL_EXPORT GetSeekingLongLong( HRESULT (__stdcall IMediaSeeking::*pMethod)( LONGLONG * ),
                                __out LONGLONG * pll );
};


// Adds the ability to return a current position

class DLL_EXPORT CRendererPosPassThru : public CPosPassThru
{
    CCritSec m_PositionLock;    // Locks access to our position
    LONGLONG m_StartMedia;      // Start media time last seen
    LONGLONG m_EndMedia;        // And likewise the end media
    BOOL m_bReset;              // Have media times been set

public:

    // Used to help with passing media times through graph

    DLL_EXPORT CRendererPosPassThru(__in_opt LPCTSTR, __in_opt LPUNKNOWN, __inout HRESULT*, IPin *);
    HRESULT DLL_EXPORT RegisterMediaTime(IMediaSample *pMediaSample);
    HRESULT DLL_EXPORT RegisterMediaTime(LONGLONG StartTime,LONGLONG EndTime);
    HRESULT DLL_EXPORT GetMediaTime(__out LONGLONG *pStartTime,__out_opt LONGLONG *pEndTime);
    HRESULT DLL_EXPORT ResetMediaTime();
    HRESULT DLL_EXPORT EOS();
};

STDAPI DLL_EXPORT CreatePosPassThru(
    __in_opt LPUNKNOWN pAgg,
    BOOL bRenderer,
    IPin *pPin,
    __deref_out IUnknown **ppPassThru
);

// A class that handles the IDispatch part of IBasicAudio and leaves the
// properties and methods themselves pure virtual.

class AM_NOVTABLE DLL_EXPORT CBasicAudio : public IBasicAudio, public CUnknown
{
    CBaseDispatch m_basedisp;

public:

    DLL_EXPORT CBasicAudio(__in_opt LPCTSTR, __in_opt LPUNKNOWN);

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);

    STDMETHODIMP DLL_EXPORT Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      __in DISPPARAMS * pdispparams,
      __out_opt VARIANT * pvarResult,
      __out_opt EXCEPINFO * pexcepinfo,
      __out_opt UINT * puArgErr);
};


// A class that handles the IDispatch part of IBasicVideo and leaves the
// properties and methods themselves pure virtual.

class AM_NOVTABLE DLL_EXPORT CBaseBasicVideo : public IBasicVideo2, public CUnknown
{
    CBaseDispatch m_basedisp;

public:

    DLL_EXPORT CBaseBasicVideo(__in_opt LPCTSTR, __in_opt LPUNKNOWN);

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);

    STDMETHODIMP DLL_EXPORT Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      __in DISPPARAMS * pdispparams,
      __out_opt VARIANT * pvarResult,
      __out_opt EXCEPINFO * pexcepinfo,
      __out_opt UINT * puArgErr);

    STDMETHODIMP DLL_EXPORT GetPreferredAspectRatio(
      __out long *plAspectX,
      __out long *plAspectY)
    {
        return E_NOTIMPL;
    }
};


// A class that handles the IDispatch part of IVideoWindow and leaves the
// properties and methods themselves pure virtual.

class AM_NOVTABLE DLL_EXPORT CBaseVideoWindow : public IVideoWindow, public CUnknown
{
    CBaseDispatch m_basedisp;

public:

    DLL_EXPORT CBaseVideoWindow(__in_opt LPCTSTR, __in_opt LPUNKNOWN);

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    /* IDispatch methods */
    STDMETHODIMP DLL_EXPORT GetTypeInfoCount(__out UINT * pctinfo);

    STDMETHODIMP DLL_EXPORT GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      __deref_out ITypeInfo ** pptinfo);

    STDMETHODIMP DLL_EXPORT GetIDsOfNames(
      REFIID riid,
      __in_ecount(cNames) LPOLESTR * rgszNames,
      UINT cNames,
      LCID lcid,
      __out_ecount(cNames) DISPID * rgdispid);

    STDMETHODIMP DLL_EXPORT Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      __in DISPPARAMS * pdispparams,
      __out_opt VARIANT * pvarResult,
      __out_opt EXCEPINFO * pexcepinfo,
      __out_opt UINT * puArgErr);
};


// abstract class to help source filters with their implementation
// of IMediaPosition. Derive from this and set the duration (and stop
// position). Also override NotifyChange to do something when the properties
// change.

class AM_NOVTABLE DLL_EXPORT CSourcePosition : public CMediaPosition
{

public:
    DLL_EXPORT CSourcePosition(__in_opt LPCTSTR, __in_opt LPUNKNOWN, __inout HRESULT*, __in CCritSec *);

    // IMediaPosition methods
    STDMETHODIMP DLL_EXPORT get_Duration(__out REFTIME * plength);
    STDMETHODIMP DLL_EXPORT put_CurrentPosition(REFTIME llTime);
    STDMETHODIMP DLL_EXPORT get_StopTime(__out REFTIME * pllTime);
    STDMETHODIMP DLL_EXPORT put_StopTime(REFTIME llTime);
    STDMETHODIMP DLL_EXPORT get_PrerollTime(__out REFTIME * pllTime);
    STDMETHODIMP DLL_EXPORT put_PrerollTime(REFTIME llTime);
    STDMETHODIMP DLL_EXPORT get_Rate(__out double * pdRate);
    STDMETHODIMP DLL_EXPORT put_Rate(double dRate);
    STDMETHODIMP DLL_EXPORT CanSeekForward(__out LONG *pCanSeekForward);
    STDMETHODIMP DLL_EXPORT CanSeekBackward(__out LONG *pCanSeekBackward);

    // override if you can return the data you are actually working on
    STDMETHODIMP DLL_EXPORT get_CurrentPosition(__out REFTIME * pllTime) {
        return E_NOTIMPL;
    };

protected:

    // we call this to notify changes. Override to handle them
    virtual HRESULT DLL_EXPORT ChangeStart() PURE;
    virtual HRESULT DLL_EXPORT ChangeStop() PURE;
    virtual HRESULT DLL_EXPORT ChangeRate() PURE;

    COARefTime m_Duration;
    COARefTime m_Start;
    COARefTime m_Stop;
    double m_Rate;

    CCritSec * m_pLock;
};

class AM_NOVTABLE DLL_EXPORT CSourceSeeking :
    public IMediaSeeking,
    public CUnknown
{

public:

    DECLARE_IUNKNOWN;
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    // IMediaSeeking methods

    STDMETHODIMP DLL_EXPORT IsFormatSupported(const GUID * pFormat);
    STDMETHODIMP DLL_EXPORT QueryPreferredFormat(__out GUID *pFormat);
    STDMETHODIMP DLL_EXPORT SetTimeFormat(const GUID * pFormat);
    STDMETHODIMP DLL_EXPORT IsUsingTimeFormat(const GUID * pFormat);
    STDMETHODIMP DLL_EXPORT GetTimeFormat(__out GUID *pFormat);
    STDMETHODIMP DLL_EXPORT GetDuration(__out LONGLONG *pDuration);
    STDMETHODIMP DLL_EXPORT GetStopPosition(__out LONGLONG *pStop);
    STDMETHODIMP DLL_EXPORT GetCurrentPosition(__out LONGLONG *pCurrent);
    STDMETHODIMP DLL_EXPORT GetCapabilities( __out DWORD * pCapabilities );
    STDMETHODIMP DLL_EXPORT CheckCapabilities( __inout DWORD * pCapabilities );
    STDMETHODIMP DLL_EXPORT ConvertTimeFormat( __out LONGLONG * pTarget,
                                    __in_opt const GUID * pTargetFormat,
                                    LONGLONG Source,
                                    __in_opt const GUID * pSourceFormat );

    STDMETHODIMP DLL_EXPORT SetPositions( __inout_opt LONGLONG * pCurrent,  DWORD CurrentFlags
			     , __inout_opt LONGLONG * pStop,  DWORD StopFlags );

    STDMETHODIMP DLL_EXPORT GetPositions( __out_opt LONGLONG * pCurrent, __out_opt LONGLONG * pStop );

    STDMETHODIMP DLL_EXPORT GetAvailable( __out_opt LONGLONG * pEarliest, __out_opt LONGLONG * pLatest );
    STDMETHODIMP DLL_EXPORT SetRate( double dRate);
    STDMETHODIMP DLL_EXPORT GetRate( __out double * pdRate);
    STDMETHODIMP DLL_EXPORT GetPreroll(__out LONGLONG *pPreroll);


protected:

    // ctor
    DLL_EXPORT CSourceSeeking(__in_opt LPCTSTR, __in_opt LPUNKNOWN, __inout HRESULT*, __in CCritSec *);

    // we call this to notify changes. Override to handle them
    virtual HRESULT DLL_EXPORT ChangeStart() PURE;
    virtual HRESULT DLL_EXPORT ChangeStop() PURE;
    virtual HRESULT DLL_EXPORT ChangeRate() PURE;

    CRefTime m_rtDuration;      // length of stream
    CRefTime m_rtStart;         // source will start here
    CRefTime m_rtStop;          // source will stop here
    double m_dRateSeeking;

    // seeking capabilities
    DWORD m_dwSeekingCaps;

    CCritSec * m_pLock;
};


// Base classes supporting Deferred commands.

// Deferred commands are queued by calls to methods on the IQueueCommand
// interface, exposed by the filtergraph and by some filters. A successful
// call to one of these methods will return an IDeferredCommand interface
// representing the queued command.
//
// A CDeferredCommand object represents a single deferred command, and exposes
// the IDeferredCommand interface as well as other methods permitting time
// checks and actual execution. It contains a reference to the CCommandQueue
// object on which it is queued.
//
// CCommandQueue is a base class providing a queue of CDeferredCommand
// objects, and methods to add, remove, check status and invoke the queued
// commands. A CCommandQueue object would be part of an object that
// implemented IQueueCommand.

class DLL_EXPORT CCmdQueue;

// take a copy of the params and store them. Release any allocated
// memory in destructor

class DLL_EXPORT CDispParams : public DISPPARAMS
{
public:
    DLL_EXPORT CDispParams(UINT nArgs, __in_ecount(nArgs) VARIANT* pArgs, __inout_opt HRESULT *phr = NULL);
    DLL_EXPORT ~CDispParams();
};


// CDeferredCommand lifetime is controlled by refcounts. Caller of
// InvokeAt.. gets a refcounted interface pointer, and the CCmdQueue
// object also holds a refcount on us. Calling Cancel or Invoke takes
// us off the CCmdQueue and thus reduces the refcount by 1. Once taken
// off the queue we cannot be put back on the queue.

class DLL_EXPORT CDeferredCommand
    : public CUnknown,
      public IDeferredCommand
{
public:

    DLL_EXPORT CDeferredCommand(
        __inout CCmdQueue * pQ,
        __in_opt LPUNKNOWN   pUnk,               // aggregation outer unk
        __inout HRESULT *   phr,
        __in LPUNKNOWN   pUnkExecutor,       // object that will execute this cmd
        REFTIME     time,
        __in GUID*       iid,
        long        dispidMethod,
        short       wFlags,
        long        cArgs,
        __in_ecount(cArgs) VARIANT*    pDispParams,
        __out VARIANT*    pvarResult,
        __out short*      puArgErr,
        BOOL        bStream
        );

    DECLARE_IUNKNOWN

    // override this to publicise our interfaces
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __out void **ppv);

    // IDeferredCommand methods
    STDMETHODIMP DLL_EXPORT Cancel();
    STDMETHODIMP DLL_EXPORT Confidence(
                    __out LONG* pConfidence);
    STDMETHODIMP DLL_EXPORT Postpone(
                    REFTIME newtime);
    STDMETHODIMP DLL_EXPORT GetHResult(
                    __out HRESULT* phrResult);

    // other public methods

    HRESULT DLL_EXPORT Invoke();

    // access methods

    // returns TRUE if streamtime, FALSE if presentation time
    BOOL DLL_EXPORT IsStreamTime() {
       return m_bStream;
    };

    CRefTime DLL_EXPORT GetTime() {
        return m_time;
    };

    REFIID DLL_EXPORT GetIID() {
        return *m_iid;
    };

    long DLL_EXPORT GetMethod() {
        return m_dispidMethod;
    };

    short DLL_EXPORT GetFlags() {
        return m_wFlags;
    };

    DISPPARAMS* DLL_EXPORT GetParams() {
        return &m_DispParams;
    };

    VARIANT* DLL_EXPORT GetResult() {
        return m_pvarResult;
    };

protected:

    CCmdQueue* m_pQueue;

    // pUnk for the interface that we will execute the command on
    LPUNKNOWN   m_pUnk;

    // stored command data
    REFERENCE_TIME     m_time;
    GUID*       m_iid;
    long        m_dispidMethod;
    short       m_wFlags;
    VARIANT*    m_pvarResult;
    BOOL        m_bStream;
    CDispParams m_DispParams;
    DISPID      m_DispId;         //  For get and put

    // we use this for ITypeInfo access
    CBaseDispatch   m_Dispatch;

    // save retval here
    HRESULT     m_hrResult;
};


// a list of CDeferredCommand objects. this is a base class providing
// the basics of access to the list. If you want to use CDeferredCommand
// objects then your queue needs to be derived from this class.

class AM_NOVTABLE DLL_EXPORT CCmdQueue
{
public:
    DLL_EXPORT CCmdQueue(__inout_opt HRESULT *phr = NULL);
    virtual DLL_EXPORT ~CCmdQueue();

    // returns a new CDeferredCommand object that will be initialised with
    // the parameters and will be added to the queue during construction.
    // returns S_OK if successfully created otherwise an error and
    // no object has been queued.
    virtual HRESULT  DLL_EXPORT New(
        __out CDeferredCommand **ppCmd,
        __in LPUNKNOWN   pUnk,
        REFTIME     time,
        __in GUID*       iid,
        long        dispidMethod,
        short       wFlags,
        long        cArgs,
        __in_ecount(cArgs) VARIANT*    pDispParams,
        __out VARIANT*    pvarResult,
        __out short*      puArgErr,
        BOOL        bStream
    );

    // called by the CDeferredCommand object to add and remove itself
    // from the queue
    virtual HRESULT DLL_EXPORT Insert(__in CDeferredCommand* pCmd);
    virtual HRESULT DLL_EXPORT Remove(__in CDeferredCommand* pCmd);

    // Command-Due Checking
    //
    // There are two schemes of synchronisation: coarse and accurate. In
    // coarse mode, you wait till the time arrives and then execute the cmd.
    // In accurate mode, you wait until you are processing the sample that
    // will appear at the time, and then execute the command. It's up to the
    // filter which one it will implement. The filtergraph will always
    // implement coarse mode for commands queued at the filtergraph.
    //
    // If you want coarse sync, you probably want to wait until there is a
    // command due, and then execute it. You can do this by calling
    // GetDueCommand. If you have several things to wait for, get the
    // event handle from GetDueHandle() and when this is signalled then call
    // GetDueCommand. Stream time will only advance between calls to Run and
    // EndRun. Note that to avoid an extra thread there is no guarantee that
    // if the handle is set there will be a command ready. Each time the
    // event is signalled, call GetDueCommand (probably with a 0 timeout);
    // This may return E_ABORT.
    //
    // If you want accurate sync, you must call GetCommandDueFor, passing
    // as a parameter the stream time of the samples you are about to process.
    // This will return:
    //   -- a stream-time command due at or before that stream time
    //   -- a presentation-time command due at or before the
    //      time that stream time will be presented (only between Run
    //      and EndRun calls, since outside of this, the mapping from
    //      stream time to presentation time is not known.
    //   -- any presentation-time command due now.
    // This means that if you want accurate synchronisation on samples that
    // might be processed during Paused mode, you need to use
    // stream-time commands.
    //
    // In all cases, commands remain queued until Invoked or Cancelled. The
    // setting and resetting of the event handle is managed entirely by this
    // queue object.

    // set the clock used for timing
    virtual HRESULT DLL_EXPORT SetSyncSource(__in_opt IReferenceClock*);

    // switch to run mode. Streamtime to Presentation time mapping known.
    virtual HRESULT DLL_EXPORT Run(REFERENCE_TIME tStreamTimeOffset);

    // switch to Stopped or Paused mode. Time mapping not known.
    virtual HRESULT DLL_EXPORT EndRun();

    // return a pointer to the next due command. Blocks for msTimeout
    // milliseconds until there is a due command.
    // Stream-time commands will only become due between Run and Endrun calls.
    // The command remains queued until invoked or cancelled.
    // Returns E_ABORT if timeout occurs, otherwise S_OK (or other error).
    // Returns an AddRef-ed object
    virtual HRESULT DLL_EXPORT GetDueCommand(__out CDeferredCommand ** ppCmd, long msTimeout);

    // return the event handle that will be signalled whenever
    // there are deferred commands due for execution (when GetDueCommand
    // will not block).
    HANDLE DLL_EXPORT GetDueHandle() {
        return HANDLE(m_evDue);
    };

    // return a pointer to a command that will be due for a given time.
    // Pass in a stream time here. The stream time offset will be passed
    // in via the Run method.
    // Commands remain queued until invoked or cancelled.
    // This method will not block. It will report VFW_E_NOT_FOUND if there
    // are no commands due yet.
    // Returns an AddRef-ed object
    virtual HRESULT DLL_EXPORT GetCommandDueFor(REFERENCE_TIME tStream, __out CDeferredCommand**ppCmd);

    // check if a given time is due (TRUE if it is due yet)
    BOOL DLL_EXPORT CheckTime(CRefTime time, BOOL bStream) {

        // if no clock, nothing is due!
        if (!m_pClock) {
            return FALSE;
        }

        // stream time
        if (bStream) {

            // not valid if not running
            if (!m_bRunning) {
                return FALSE;
            }
            // add on known stream time offset to get presentation time
            time += m_StreamTimeOffset;
        }

        CRefTime Now;
        m_pClock->GetTime((REFERENCE_TIME*)&Now);
        return (time <= Now);
    };

protected:

    // protect access to lists etc
    CCritSec m_Lock;

    // commands queued in presentation time are stored here
    CGenericList<CDeferredCommand> m_listPresentation;

    // commands queued in stream time are stored here
    CGenericList<CDeferredCommand> m_listStream;

    // set when any commands are due
    CAMEvent m_evDue;

    // creates an advise for the earliest time required, if any
    void SetTimeAdvise(void);

    // advise id from reference clock (0 if no outstanding advise)
    DWORD_PTR m_dwAdvise;

    // advise time is for this presentation time
    CRefTime m_tCurrentAdvise;

    // the reference clock we are using (addrefed)
    IReferenceClock* m_pClock;

    // true when running
    BOOL m_bRunning;

    // contains stream time offset when m_bRunning is true
    CRefTime m_StreamTimeOffset;
};

#endif // __CTLUTIL__
