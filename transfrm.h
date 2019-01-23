//------------------------------------------------------------------------------
// File: Transfrm.h
//
// Desc: DirectShow base classes - defines classes from which simple
//       transform codecs may be derived.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


// It assumes the codec has one input and one output stream, and has no
// interest in memory management, interface negotiation or anything else.
//
// derive your class from this, and supply Transform and the media type/format
// negotiation functions. Implement that class, compile and link and
// you're done.


#ifndef __TRANSFRM__
#define __TRANSFRM__

#include "dll.h"

// ======================================================================
// This is the com object that represents a simple transform filter. It
// supports IBaseFilter, IMediaFilter and two pins through nested interfaces
// ======================================================================

class DLL_EXPORT CTransformFilter;

// ==================================================
// Implements the input pin
// ==================================================

class DLL_EXPORT CTransformInputPin : public CBaseInputPin
{
    friend class CTransformFilter;

protected:
    CTransformFilter *m_pTransformFilter;


public:

    DLL_EXPORT
    CTransformInputPin(
        __in_opt LPCTSTR pObjectName,
        __inout CTransformFilter *pTransformFilter,
        __inout HRESULT * phr,
        __in_opt LPCWSTR pName);
#ifdef UNICODE
    DLL_EXPORT
    CTransformInputPin(
        __in_opt LPCSTR pObjectName,
        __inout CTransformFilter *pTransformFilter,
        __inout HRESULT * phr,
        __in_opt LPCWSTR pName);
#endif

    STDMETHODIMP QueryId(__deref_out LPWSTR * Id)
    {
        return AMGetWideString(L"In", Id);
    }

    // Grab and release extra interfaces if required

    HRESULT DLL_EXPORT CheckConnect(IPin *pPin);
    HRESULT DLL_EXPORT BreakConnect();
    HRESULT DLL_EXPORT CompleteConnect(IPin *pReceivePin);

    // check that we can support this output type
    HRESULT DLL_EXPORT CheckMediaType(const CMediaType* mtIn);

    // set the connection media type
    HRESULT DLL_EXPORT SetMediaType(const CMediaType* mt);

    // --- IMemInputPin -----

    // here's the next block of data from the stream.
    // AddRef it yourself if you need to hold it beyond the end
    // of this call.
    STDMETHODIMP DLL_EXPORT Receive(IMediaSample * pSample);

    // provide EndOfStream that passes straight downstream
    // (there is no queued data)
    STDMETHODIMP DLL_EXPORT EndOfStream(void);

    // passes it to CTransformFilter::BeginFlush
    STDMETHODIMP DLL_EXPORT BeginFlush(void);

    // passes it to CTransformFilter::EndFlush
    STDMETHODIMP DLL_EXPORT EndFlush(void);

    STDMETHODIMP DLL_EXPORT NewSegment(
                        REFERENCE_TIME tStart,
                        REFERENCE_TIME tStop,
                        double dRate);

    // Check if it's OK to process samples
    virtual HRESULT DLL_EXPORT CheckStreaming();

    // Media type
public:
    CMediaType& CurrentMediaType() { return m_mt; };

};

// ==================================================
// Implements the output pin
// ==================================================

class DLL_EXPORT CTransformOutputPin : public CBaseOutputPin
{
    friend class CTransformFilter;

protected:
    CTransformFilter *m_pTransformFilter;

public:

    // implement IMediaPosition by passing upstream
    IUnknown * m_pPosition;

    DLL_EXPORT
    CTransformOutputPin(
        __in_opt LPCTSTR pObjectName,
        __inout CTransformFilter *pTransformFilter,
        __inout HRESULT * phr,
        __in_opt LPCWSTR pName);
#ifdef UNICODE
    DLL_EXPORT
    CTransformOutputPin(
        __in_opt LPCSTR pObjectName,
        __inout CTransformFilter *pTransformFilter,
        __inout HRESULT * phr,
        __in_opt LPCWSTR pName);
#endif
    DLL_EXPORT ~CTransformOutputPin();

    // override to expose IMediaPosition
    STDMETHODIMP DLL_EXPORT NonDelegatingQueryInterface(REFIID riid, __deref_out void **ppv);

    // --- CBaseOutputPin ------------

    STDMETHODIMP DLL_EXPORT QueryId(__deref_out LPWSTR * Id)
    {
        return AMGetWideString(L"Out", Id);
    }

    // Grab and release extra interfaces if required

    HRESULT DLL_EXPORT CheckConnect(IPin *pPin);
    HRESULT DLL_EXPORT BreakConnect();
    HRESULT DLL_EXPORT CompleteConnect(IPin *pReceivePin);

    // check that we can support this output type
    HRESULT DLL_EXPORT CheckMediaType(const CMediaType* mtOut);

    // set the connection media type
    HRESULT DLL_EXPORT SetMediaType(const CMediaType *pmt);

    // called from CBaseOutputPin during connection to ask for
    // the count and size of buffers we need.
    HRESULT DLL_EXPORT DecideBufferSize(
                IMemAllocator * pAlloc,
                __inout ALLOCATOR_PROPERTIES *pProp);

    // returns the preferred formats for a pin
    HRESULT DLL_EXPORT GetMediaType(int iPosition, __inout CMediaType *pMediaType);

    // inherited from IQualityControl via CBasePin
    STDMETHODIMP DLL_EXPORT Notify(IBaseFilter * pSender, Quality q);

    // Media type
public:
    CMediaType& CurrentMediaType() { return m_mt; };
};


class AM_NOVTABLE DLL_EXPORT CTransformFilter : public CBaseFilter
{

public:

    // map getpin/getpincount for base enum of pins to owner
    // override this to return more specialised pin objects

    virtual int DLL_EXPORT GetPinCount();
    virtual CBasePin * DLL_EXPORT GetPin(int n);
    STDMETHODIMP DLL_EXPORT FindPin(LPCWSTR Id, __deref_out IPin **ppPin);

    // override state changes to allow derived transform filter
    // to control streaming start/stop
    STDMETHODIMP DLL_EXPORT Stop();
    STDMETHODIMP DLL_EXPORT Pause();

public:

    DLL_EXPORT CTransformFilter(__in_opt LPCTSTR , __inout_opt LPUNKNOWN, REFCLSID clsid);
#ifdef UNICODE
    DLL_EXPORT CTransformFilter(__in_opt LPCSTR , __inout_opt LPUNKNOWN, REFCLSID clsid);
#endif
    DLL_EXPORT ~CTransformFilter();

    // =================================================================
    // ----- override these bits ---------------------------------------
    // =================================================================

    // These must be supplied in a derived class

    virtual HRESULT DLL_EXPORT Transform(IMediaSample * pIn, IMediaSample *pOut);

    // check if you can support mtIn
    virtual HRESULT DLL_EXPORT CheckInputType(const CMediaType* mtIn) PURE;

    // check if you can support the transform from this input to this output
    virtual HRESULT DLL_EXPORT CheckTransform(const CMediaType* mtIn, const CMediaType* mtOut) PURE;

    // this goes in the factory template table to create new instances
    // static CCOMObject * CreateInstance(__inout_opt LPUNKNOWN, HRESULT *);

    // call the SetProperties function with appropriate arguments
    virtual HRESULT DLL_EXPORT DecideBufferSize(
                        IMemAllocator * pAllocator,
                        __inout ALLOCATOR_PROPERTIES *pprop) PURE;

    // override to suggest OUTPUT pin media types
    virtual HRESULT DLL_EXPORT GetMediaType(int iPosition, __inout CMediaType *pMediaType) PURE;



    // =================================================================
    // ----- Optional Override Methods           -----------------------
    // =================================================================

    // you can also override these if you want to know about streaming
    virtual HRESULT DLL_EXPORT StartStreaming();
    virtual HRESULT DLL_EXPORT StopStreaming();

    // override if you can do anything constructive with quality notifications
    virtual HRESULT DLL_EXPORT AlterQuality(Quality q);

    // override this to know when the media type is actually set
    virtual HRESULT DLL_EXPORT SetMediaType(PIN_DIRECTION direction,const CMediaType *pmt);

    // chance to grab extra interfaces on connection
    virtual HRESULT DLL_EXPORT CheckConnect(PIN_DIRECTION dir,IPin *pPin);
    virtual HRESULT DLL_EXPORT BreakConnect(PIN_DIRECTION dir);
    virtual HRESULT DLL_EXPORT CompleteConnect(PIN_DIRECTION direction,IPin *pReceivePin);

    // chance to customize the transform process
    virtual HRESULT DLL_EXPORT Receive(IMediaSample *pSample);

    // Standard setup for output sample
    HRESULT DLL_EXPORT InitializeOutputSample(IMediaSample *pSample, __deref_out IMediaSample **ppOutSample);

    // if you override Receive, you may need to override these three too
    virtual HRESULT DLL_EXPORT EndOfStream(void);
    virtual HRESULT DLL_EXPORT BeginFlush(void);
    virtual HRESULT DLL_EXPORT EndFlush(void);
    virtual HRESULT DLL_EXPORT NewSegment(
                        REFERENCE_TIME tStart,
                        REFERENCE_TIME tStop,
                        double dRate);

#ifdef PERF
    // Override to register performance measurement with a less generic string
    // You should do this to avoid confusion with other filters
    virtual void DLL_EXPORT RegisterPerfId()
         {m_idTransform = MSR_REGISTER(TEXT("Transform"));}
#endif // PERF


// implementation details

protected:

#ifdef PERF
    int m_idTransform;                 // performance measuring id
#endif
    BOOL m_bEOSDelivered;              // have we sent EndOfStream
    BOOL m_bSampleSkipped;             // Did we just skip a frame
    BOOL m_bQualityChanged;            // Have we degraded?

    // critical section protecting filter state.

    CCritSec m_csFilter;

    // critical section stopping state changes (ie Stop) while we're
    // processing a sample.
    //
    // This critical section is held when processing
    // events that occur on the receive thread - Receive() and EndOfStream().
    //
    // If you want to hold both m_csReceive and m_csFilter then grab
    // m_csFilter FIRST - like CTransformFilter::Stop() does.

    CCritSec m_csReceive;

    // these hold our input and output pins

    friend class CTransformInputPin;
    friend class CTransformOutputPin;
    CTransformInputPin *m_pInput;
    CTransformOutputPin *m_pOutput;
};

#endif /* __TRANSFRM__ */


