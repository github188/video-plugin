#pragma once

// VideoPluginPropPage.h : CVideoPluginPropPage ����ҳ���������


// CVideoPluginPropPage : �й�ʵ�ֵ���Ϣ������� VideoPluginPropPage.cpp��

class CVideoPluginPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CVideoPluginPropPage)
	DECLARE_OLECREATE_EX(CVideoPluginPropPage)

// ���캯��
public:
	CVideoPluginPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_VIDEOPLUGIN };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

