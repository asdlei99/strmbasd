//------------------------------------------------------------------------------
// File: perflog.h
//
// Desc: Performance logging framework.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "dll.h"

typedef struct DLL_EXPORT _PERFLOG_LOGGING_PARAMS {
    GUID ControlGuid;
    void (*OnStateChanged)(void);
    ULONG NumberOfTraceGuids;
    TRACE_GUID_REGISTRATION TraceGuids[ANYSIZE_ARRAY];
} PERFLOG_LOGGING_PARAMS, *PPERFLOG_LOGGING_PARAMS;

BOOL DLL_EXPORT
PerflogInitIfEnabled(
    IN HINSTANCE hInstance,
    __in PPERFLOG_LOGGING_PARAMS LogParams
    );

BOOL DLL_EXPORT
PerflogInitialize (
    __in PPERFLOG_LOGGING_PARAMS LogParams
    );

VOID DLL_EXPORT
PerflogShutdown (
    VOID
    );

VOID DLL_EXPORT
PerflogTraceEvent (
    __in PEVENT_TRACE_HEADER Event
    );

extern ULONG PerflogEnableFlags;
extern UCHAR PerflogEnableLevel;
extern ULONG PerflogModuleLevel;
extern TRACEHANDLE PerflogTraceHandle;
extern TRACEHANDLE PerflogRegHandle;

#define PerflogTracingEnabled() (PerflogTraceHandle != 0)

#define PerflogEvent( _x_ ) PerflogTraceEventLevel _x_

VOID DLL_EXPORT
PerflogTraceEventLevel(
    ULONG Level,
    __in PEVENT_TRACE_HEADER Event
    );

VOID DLL_EXPORT
PerflogTraceEvent (
    __in PEVENT_TRACE_HEADER Event
    );
