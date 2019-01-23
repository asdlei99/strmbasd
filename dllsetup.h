//------------------------------------------------------------------------------
// File: DllSetup.h
//
// Desc: DirectShow base classes.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


// To be self registering, OLE servers must
// export functions named DllRegisterServer
// and DllUnregisterServer.  To allow use of
// custom and default implementations the
// defaults are named AMovieDllRegisterServer
// and AMovieDllUnregisterServer.
//
// To the use the default implementation you
// must provide stub functions.
//
// i.e. STDAPI DllRegisterServer()
//      {
//        return AMovieDllRegisterServer();
//      }
//
//      STDAPI DllUnregisterServer()
//      {
//        return AMovieDllUnregisterServer();
//      }
//
//
// AMovieDllRegisterServer   calls IAMovieSetup.Register(), and
// AMovieDllUnregisterServer calls IAMovieSetup.Unregister().

#include "dll.h"


STDAPI DLL_EXPORT AMovieDllRegisterServer2( BOOL );
STDAPI DLL_EXPORT AMovieDllRegisterServer();
STDAPI DLL_EXPORT AMovieDllUnregisterServer();

// helper functions
STDAPI DLL_EXPORT EliminateSubKey( HKEY, LPCTSTR );


STDAPI DLL_EXPORT
AMovieSetupRegisterFilter2( const AMOVIESETUP_FILTER * const psetupdata
                          , IFilterMapper2 *         pIFM2
                          , BOOL                             bRegister  );

