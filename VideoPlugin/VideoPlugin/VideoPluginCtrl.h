#pragma once

// VideoPluginCtrl.h : CVideoPluginCtrl ActiveX 控件类的声明。


// CVideoPluginCtrl : 有关实现的信息，请参阅 VideoPluginCtrl.cpp。
class CVideoClientDlg;
class CVideoPluginCtrl : public COleControl
{
	DECLARE_DYNCREATE(CVideoPluginCtrl)

// 构造函数
public:
	CVideoPluginCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CVideoPluginCtrl();

	DECLARE_OLECREATE_EX(CVideoPluginCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CVideoPluginCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVideoPluginCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CVideoPluginCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
	CVideoClientDlg* m_app;
public:
	enum {
		dispidOnVideoStart = 2L,
		dispidOnWindowClose = 1L,
		dispidserverIP = 24,
		dispidserverPort = 25,
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	CString m_serverIP;
	CString m_serverPort;

	void OnServerIPChanged(void);
	void OnServerPortChanged(void);

	BSTR GetMsgContext();
	BSTR GetMsgContexta();

	void setIP(LPCTSTR ip);
	void setPort(LPCTSTR port);
protected:
	void OnWindowClose(void);
	void OnVideoStart(void);
};

