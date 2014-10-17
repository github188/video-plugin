// VideoPluginCtrl.cpp : CVideoPluginCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "VideoPlugin.h"
#include "VideoPluginCtrl.h"
#include "VideoPluginPropPage.h"
#include "afxdialogex.h"
#include "VideoClientDlg.h"
#include "get_data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CVideoPluginCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CVideoPluginCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CVideoPluginCtrl, COleControl)
	DISP_PROPERTY_NOTIFY_ID(CVideoPluginCtrl, "servereIP", dispidserverIP, m_serverIP, OnServerIPChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CVideoPluginCtrl, "serverPort", dispidserverPort, m_serverPort, OnServerPortChanged, VT_BSTR)
	DISP_FUNCTION_ID(CVideoPluginCtrl, "OnWindowClose", dispidOnWindowClose, OnWindowClose, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CVideoPluginCtrl, "OnVideoStart", dispidOnVideoStart, OnVideoStart, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CVideoPluginCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CVideoPluginCtrl, 1)
	PROPPAGEID(CVideoPluginPropPage::guid)
END_PROPPAGEIDS(CVideoPluginCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CVideoPluginCtrl, "VIDEOPLUGIN.VideoPluginCtrl.1",
	0x95452421, 0xc307, 0x4060, 0x95, 0x81, 0x84, 0xc3, 0xf6, 0x27, 0x4d, 0x55)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CVideoPluginCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DVideoPlugin = { 0xC29B30E6, 0xDE9E, 0x4C9D, { 0xA5, 0xBD, 0x33, 0x28, 0xA6, 0xF3, 0xFC, 0x57 } };
const IID IID_DVideoPluginEvents = { 0x512A767A, 0xEBA8, 0x49D6, { 0xAA, 0x9D, 0x1B, 0xFE, 0x34, 0xA0, 0xD7, 0xB4 } };


// 控件类型信息

static const DWORD _dwVideoPluginOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CVideoPluginCtrl, IDS_VIDEOPLUGIN, _dwVideoPluginOleMisc)



// CVideoPluginCtrl::CVideoPluginCtrlFactory::UpdateRegistry -
// 添加或移除 CVideoPluginCtrl 的系统注册表项

BOOL CVideoPluginCtrl::CVideoPluginCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_VIDEOPLUGIN,
			IDB_VIDEOPLUGIN,
			afxRegApartmentThreading,
			_dwVideoPluginOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CVideoPluginCtrl::CVideoPluginCtrl - 构造函数

CVideoPluginCtrl::CVideoPluginCtrl()
{
	InitializeIIDs(&IID_DVideoPlugin, &IID_DVideoPluginEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CVideoPluginCtrl::~CVideoPluginCtrl - 析构函数

CVideoPluginCtrl::~CVideoPluginCtrl()
{
	// TODO: 在此清理控件的实例数据。
	if(m_app)
		delete m_app;
	m_app=0;
}



// CVideoPluginCtrl::OnDraw - 绘图函数

void CVideoPluginCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	//pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//pdc->Ellipse(rcBounds);
	m_app->MoveWindow(rcBounds);
	m_app->ShowWindow(SW_SHOW);

}



// CVideoPluginCtrl::DoPropExchange - 持久性支持

void CVideoPluginCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));

	PX_String(pPX, _T("serverIP"), m_serverIP);
	PX_String(pPX, _T("serverPort"), m_serverPort);

	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。

}



// CVideoPluginCtrl::OnResetState - 将控件重置为默认状态

void CVideoPluginCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CVideoPluginCtrl 消息处理程序
int CVideoPluginCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_app = new CVideoClientDlg;
	m_app->Create(IDD_VIDEOCLIENT_DIALOG, this);
	
	strncpy(ServIP, (LPCTSTR)(this->m_serverIP), 100);
	ServPort = atoi(this->m_serverPort);

	return 0;
}

void CVideoPluginCtrl::OnServerIPChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
}

void CVideoPluginCtrl::OnServerPortChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
}

BSTR CVideoPluginCtrl::GetMsgContext()
{
	return m_serverIP.AllocSysString();
}

BSTR CVideoPluginCtrl::GetMsgContexta()
{
	return m_serverPort.AllocSysString();
}

void CVideoPluginCtrl::setIP(LPCTSTR ip)
{
	m_serverIP = ip;
	strncpy(ServIP, ip, 100);
	SetModifiedFlag();
}

void CVideoPluginCtrl::setPort(LPCTSTR port)
{
	m_serverPort = port;
	ServPort = atoi(m_serverPort);
	SetModifiedFlag();
}


void CVideoPluginCtrl::OnWindowClose(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// TODO: 在此添加调度处理程序代码
	if (m_videoUtil.IsStarted())
	{
		m_videoUtil.StopLiveVideo();
	}
}


void CVideoPluginCtrl::OnVideoStart(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (!m_videoUtil.IsStarted())
	{
		//m_videoUtil.connetToCarmer();
		m_videoUtil.RunLiveVideo();
		// Sleep(1000);
	}
}
