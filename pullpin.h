//------------------------------------------------------------------------------
// File: PullPin.h
//
// Desc: DirectShow base classes - defines CPullPin class.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __PULLPIN_H__
#define __PULLPIN_H__

#include "dll.h"

//
// CPullPin
//
// object supporting pulling data from an IAsyncReader interface.
// Given a start/stop position, calls a pure Receive method with each
// IMediaSample received.
//
// This is essentially for use in a MemInputPin when it finds itself
// connected to an IAsyncReader pin instead of a pushing pin.
//

class DLL_EXPORT CPullPin : public CAMThread
{
    IAsyncReader*       m_pReader;
    REFERENCE_TIME      m_tStart;
    REFERENCE_TIME      m_tStop;
    REFERENCE_TIME      m_tDuration;
    BOOL                m_bSync;

    enum ThreadMsg {
	TM_Pause,       // stop pulling and wait for next message
	TM_Start,       // start pulling
	TM_Exit,        // stop and exit
    };

    ThreadMsg m_State;

    // override pure thread proc from CAMThread
    DWORD DLL_EXPORT ThreadProc(void);

    // running pull method (check m_bSync)
    void DLL_EXPORT Process(void);

    // clean up any cancelled i/o after a flush
    void DLL_EXPORT CleanupCancelled(void);

    // suspend thread from pulling, eg during seek
    HRESULT DLL_EXPORT PauseThread();

    // start thread pulling - create thread if necy
    HRESULT DLL_EXPORT StartThread();

    // stop and close thread
    HRESULT DLL_EXPORT StopThread();

    // called from ProcessAsync to queue and collect requests
    HRESULT DLL_EXPORT QueueSample(
		__inout REFERENCE_TIME& tCurrent,
		REFERENCE_TIME tAlignStop,
		BOOL bDiscontinuity);

    HRESULT DLL_EXPORT CollectAndDeliver(
		REFERENCE_TIME tStart,
		REFERENCE_TIME tStop);

    HRESULT DLL_EXPORT DeliverSample(
		IMediaSample* pSample,
		REFERENCE_TIME tStart,
		REFERENCE_TIME tStop);

protected:
    IMemAllocator *     m_pAlloc;

public:
    DLL_EXPORT CPullPin();
    virtual DLL_EXPORT ~CPullPin();

    // returns S_OK if successfully connected to an IAsyncReader interface
    // from this object
    // Optional allocator should be proposed as a preferred allocator if
    // necessary
    // bSync is TRUE if we are to use sync reads instead of the
    // async methods.
    HRESULT DLL_EXPORT Connect(IUnknown* pUnk, IMemAllocator* pAlloc, BOOL bSync);

    // disconnect any connection made in Connect
    HRESULT DLL_EXPORT Disconnect();

    // agree an allocator using RequestAllocator - optional
    // props param specifies your requirements (non-zero fields).
    // returns an error code if fail to match requirements.
    // optional IMemAllocator interface is offered as a preferred allocator
    // but no error occurs if it can't be met.
    virtual HRESULT DLL_EXPORT DecideAllocator(
		IMemAllocator* pAlloc,
		__inout_opt ALLOCATOR_PROPERTIES * pProps);

    // set start and stop position. if active, will start immediately at
    // the new position. Default is 0 to duration
    HRESULT DLL_EXPORT Seek(REFERENCE_TIME tStart, REFERENCE_TIME tStop);

    // return the total duration
    HRESULT DLL_EXPORT Duration(__out REFERENCE_TIME* ptDuration);

    // start pulling data
    HRESULT DLL_EXPORT Active(void);

    // stop pulling data
    HRESULT DLL_EXPORT Inactive(void);

    // helper functions
    LONGLONG DLL_EXPORT AlignDown(LONGLONG ll, LONG lAlign) {
	// aligning downwards is just truncation
	return ll & ~(lAlign-1);
    };

    LONGLONG DLL_EXPORT AlignUp(LONGLONG ll, LONG lAlign) {
	// align up: round up to next boundary
	return (ll + (lAlign -1)) & ~(lAlign -1);
    };

    // GetReader returns the (addrefed) IAsyncReader interface
    // for SyncRead etc
    IAsyncReader* DLL_EXPORT GetReader() {
	m_pReader->AddRef();
	return m_pReader;
    };

    // -- pure --

    // override this to handle data arrival
    // return value other than S_OK will stop data
    virtual HRESULT DLL_EXPORT Receive(IMediaSample*) PURE;

    // override this to handle end-of-stream
    virtual HRESULT DLL_EXPORT EndOfStream(void) PURE;

    // called on runtime errors that will have caused pulling
    // to stop
    // these errors are all returned from the upstream filter, who
    // will have already reported any errors to the filtergraph.
    virtual void DLL_EXPORT OnError(HRESULT hr) PURE;

    // flush this pin and all downstream
    virtual HRESULT DLL_EXPORT BeginFlush() PURE;
    virtual HRESULT DLL_EXPORT EndFlush() PURE;

};

#endif //__PULLPIN_H__
