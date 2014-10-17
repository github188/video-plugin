#pragma once

// VideoPluginCtrl.h : CVideoPluginCtrl ActiveX �ؼ����������


// CVideoPluginCtrl : �й�ʵ�ֵ���Ϣ������� VideoPluginCtrl.cpp��
class CVideoClientDlg;
class CVideoPluginCtrl : public COleControl
{
	DECLARE_DYNCREATE(CVideoPluginCtrl)

// ���캯��
public:
	CVideoPluginCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CVideoPluginCtrl();

	DECLARE_OLECREATE_EX(CVideoPluginCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CVideoPluginCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVideoPluginCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CVideoPluginCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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

