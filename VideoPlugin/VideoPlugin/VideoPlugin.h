#pragma once

// VideoPlugin.h : VideoPlugin.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CVideoPluginApp : �й�ʵ�ֵ���Ϣ������� VideoPlugin.cpp��

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