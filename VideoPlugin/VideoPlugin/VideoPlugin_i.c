

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Sep 05 16:22:33 2014
 */
/* Compiler settings for VideoPlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_VideoPluginLib,0x55EABC41,0xEF6C,0x498C,0xB9,0x68,0x66,0x99,0x38,0x11,0xFF,0x2B);


MIDL_DEFINE_GUID(IID, DIID__DVideoPlugin,0xC29B30E6,0xDE9E,0x4C9D,0xA5,0xBD,0x33,0x28,0xA6,0xF3,0xFC,0x57);


MIDL_DEFINE_GUID(IID, DIID__DVideoPluginEvents,0x512A767A,0xEBA8,0x49D6,0xAA,0x9D,0x1B,0xFE,0x34,0xA0,0xD7,0xB4);


MIDL_DEFINE_GUID(CLSID, CLSID_VideoPlugin,0x95452421,0xC307,0x4060,0x95,0x81,0x84,0xC3,0xF6,0x27,0x4D,0x55);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



