#pragma once

// VideoPlugin.h : VideoPlugin.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CVideoPluginApp : 有关实现的信息，请参阅 VideoPlugin.cpp。

class CVideoPluginApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

// extern const GUID CDECL _tlid;
// 2014-08-18: Jasmine */
extern const  GUID CDECL BASED_CODE _tlid;

extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

extern CString g_szOcxPath;