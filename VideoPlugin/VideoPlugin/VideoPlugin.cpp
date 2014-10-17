// VideoPlugin.cpp : CVideoPluginApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "VideoPlugin.h"

/* 2014-07-24 Jasmine */
#include "Cathelp.h"
#include "objsafe.h"
////////////////////////


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CVideoPluginApp theApp;

const GUID CDECL _tlid = { 0x55EABC41, 0xEF6C, 0x498C, { 0xB9, 0x68, 0x66, 0x99, 0x38, 0x11, 0xFF, 0x2B } };

/* 2014-08-18 Jasmine */
/* change to this, or delete it */
// const GUID CDECL BASED_CODE _tlid = {0x95452421, 0xc307, 0x4060, {0x95, 0x81, 0x84, 0xc3, 0xf6, 0x27, 0x4d, 0x55}};

/* 2014-07-24 Jasmine */
const CATID CLSID_SafeItem = {0x95452421, 0xc307, 0x4060, {0x95, 0x81, 0x84, 0xc3, 0xf6, 0x27, 0x4d, 0x55}};
////////////////////////

const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

CString g_szOcxPath;
CString g_szOcxName;

// CVideoPluginApp::InitInstance - DLL 初始化

BOOL CVideoPluginApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
		g_szOcxPath = this->m_pszHelpFilePath;
        g_szOcxName = this->m_pszExeName;
 
        g_szOcxName += ".HLP";
        int nTmp = g_szOcxName.GetLength();
        nTmp = g_szOcxPath.GetLength() - nTmp;
        g_szOcxPath = g_szOcxPath.Left(nTmp);
	}

	return bInit;
}



// CVideoPluginApp::ExitInstance - DLL 终止

int CVideoPluginApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	/* 2014-07-24 Jasmine */
	// Mark the control as safe for initializing
	HRESULT hr;
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"VideoPlugin:Controls safely initializable from persistent data!");
	if(FAILED(hr))
		return hr;

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if(FAILED(hr))
		return hr;

	hr = CreateComponentCategory(CATID_SafeForScripting, L"VideoPlugin:Controls safely scriptable!");
	if(FAILED(hr))
		return hr;

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if(FAILED(hr))
		return hr;
	////////////////////////

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	/* 2014-07-24 Jasmine */
	// Remove entries from the registry
	HRESULT hr;
	hr = UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if(FAILED(hr))
		return hr;

	hr = UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if(FAILED(hr))
		return hr;

	//////////////////////////


	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	

	return NOERROR;
}
