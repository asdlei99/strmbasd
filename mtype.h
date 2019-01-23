//------------------------------------------------------------------------------
// File: MtType.h
//
// Desc: DirectShow base classes - defines a class that holds and manages
//       media type information.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef __MTYPE__
#define __MTYPE__

#include "dll.h"

/* Helper class that derived pin objects can use to compare media
   types etc. Has same data members as the struct AM_MEDIA_TYPE defined
   in the streams IDL file, but also has (non-virtual) functions */

class DLL_EXPORT CMediaType : public _AMMediaType {

public:

    DLL_EXPORT ~CMediaType();
    DLL_EXPORT CMediaType();
    DLL_EXPORT CMediaType(const GUID * majortype);
    DLL_EXPORT CMediaType(const AM_MEDIA_TYPE&, __out_opt HRESULT* phr = NULL);
    DLL_EXPORT CMediaType(const CMediaType&, __out_opt HRESULT* phr = NULL);

    CMediaType& DLL_EXPORT operator=(const CMediaType&);
    CMediaType& DLL_EXPORT operator=(const AM_MEDIA_TYPE&);

    BOOL DLL_EXPORT operator == (const CMediaType&) const;
    BOOL DLL_EXPORT operator != (const CMediaType&) const;

    HRESULT DLL_EXPORT Set(const CMediaType& rt);
    HRESULT DLL_EXPORT Set(const AM_MEDIA_TYPE& rt);

    BOOL DLL_EXPORT IsValid() const;

    const GUID* DLL_EXPORT Type() const { return &majortype;} ;
    void DLL_EXPORT SetType(const GUID *);
    const GUID* DLL_EXPORT Subtype() const { return &subtype;} ;
    void DLL_EXPORT SetSubtype(const GUID *);

    BOOL DLL_EXPORT IsFixedSize() const {return bFixedSizeSamples; };
    BOOL DLL_EXPORT IsTemporalCompressed() const {return bTemporalCompression; };
    ULONG DLL_EXPORT GetSampleSize() const;

    void DLL_EXPORT SetSampleSize(ULONG sz);
    void DLL_EXPORT SetVariableSize();
    void DLL_EXPORT SetTemporalCompression(BOOL bCompressed);

    // read/write pointer to format - can't change length without
    // calling SetFormat, AllocFormatBuffer or ReallocFormatBuffer

    BYTE*   DLL_EXPORT Format() const {return pbFormat; };
    ULONG   DLL_EXPORT FormatLength() const { return cbFormat; };

    void DLL_EXPORT SetFormatType(const GUID *);
    const GUID* DLL_EXPORT FormatType() const {return &formattype; };
    BOOL DLL_EXPORT SetFormat(__in_bcount(length) BYTE *pFormat, ULONG length);
    void DLL_EXPORT ResetFormatBuffer();
    BYTE* DLL_EXPORT AllocFormatBuffer(ULONG length);
    BYTE* DLL_EXPORT ReallocFormatBuffer(ULONG length);

    void DLL_EXPORT InitMediaType();

    BOOL DLL_EXPORT MatchesPartial(const CMediaType* ppartial) const;
    BOOL DLL_EXPORT IsPartiallySpecified(void) const;
};


/* General purpose functions to copy and delete a task allocated AM_MEDIA_TYPE
   structure which is useful when using the IEnumMediaFormats interface as
   the implementation allocates the structures which you must later delete */

void WINAPI DLL_EXPORT DeleteMediaType(__inout_opt AM_MEDIA_TYPE *pmt);
AM_MEDIA_TYPE * WINAPI DLL_EXPORT CreateMediaType(AM_MEDIA_TYPE const *pSrc);
HRESULT WINAPI DLL_EXPORT CopyMediaType(__out AM_MEDIA_TYPE *pmtTarget, const AM_MEDIA_TYPE *pmtSource);
void WINAPI DLL_EXPORT FreeMediaType(__inout AM_MEDIA_TYPE& mt);

//  Initialize a media type from a WAVEFORMATEX

STDAPI DLL_EXPORT CreateAudioMediaType(
    const WAVEFORMATEX *pwfx,
    __out AM_MEDIA_TYPE *pmt,
    BOOL bSetFormat);

#endif /* __MTYPE__ */

