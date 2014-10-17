

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __VideoPluginidl_h__
#define __VideoPluginidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DVideoPlugin_FWD_DEFINED__
#define ___DVideoPlugin_FWD_DEFINED__
typedef interface _DVideoPlugin _DVideoPlugin;
#endif 	/* ___DVideoPlugin_FWD_DEFINED__ */


#ifndef ___DVideoPluginEvents_FWD_DEFINED__
#define ___DVideoPluginEvents_FWD_DEFINED__
typedef interface _DVideoPluginEvents _DVideoPluginEvents;
#endif 	/* ___DVideoPluginEvents_FWD_DEFINED__ */


#ifndef __VideoPlugin_FWD_DEFINED__
#define __VideoPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoPlugin VideoPlugin;
#else
typedef struct VideoPlugin VideoPlugin;
#endif /* __cplusplus */

#endif 	/* __VideoPlugin_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __VideoPluginLib_LIBRARY_DEFINED__
#define __VideoPluginLib_LIBRARY_DEFINED__

/* library VideoPluginLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_VideoPluginLib;

#ifndef ___DVideoPlugin_DISPINTERFACE_DEFINED__
#define ___DVideoPlugin_DISPINTERFACE_DEFINED__

/* dispinterface _DVideoPlugin */
/* [uuid] */ 


EXTERN_C const IID DIID__DVideoPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C29B30E6-DE9E-4C9D-A5BD-3328A6F3FC57")
    _DVideoPlugin : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DVideoPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DVideoPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DVideoPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DVideoPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DVideoPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DVideoPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DVideoPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DVideoPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DVideoPluginVtbl;

    interface _DVideoPlugin
    {
        CONST_VTBL struct _DVideoPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DVideoPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DVideoPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DVideoPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DVideoPlugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DVideoPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DVideoPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DVideoPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DVideoPlugin_DISPINTERFACE_DEFINED__ */


#ifndef ___DVideoPluginEvents_DISPINTERFACE_DEFINED__
#define ___DVideoPluginEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DVideoPluginEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DVideoPluginEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("512A767A-EBA8-49D6-AA9D-1BFE34A0D7B4")
    _DVideoPluginEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DVideoPluginEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DVideoPluginEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DVideoPluginEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DVideoPluginEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DVideoPluginEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DVideoPluginEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DVideoPluginEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DVideoPluginEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DVideoPluginEventsVtbl;

    interface _DVideoPluginEvents
    {
        CONST_VTBL struct _DVideoPluginEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DVideoPluginEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DVideoPluginEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DVideoPluginEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DVideoPluginEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DVideoPluginEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DVideoPluginEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DVideoPluginEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DVideoPluginEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_VideoPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("95452421-C307-4060-9581-84C3F6274D55")
VideoPlugin;
#endif
#endif /* __VideoPluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


