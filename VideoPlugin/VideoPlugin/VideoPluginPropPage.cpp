// VideoPluginPropPage.cpp : CVideoPluginPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "VideoPlugin.h"
#include "VideoPluginPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CVideoPluginPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CVideoPluginPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CVideoPluginPropPage, "VIDEOPLUGIN.VideoPluginPropPage.1",
	0xaa622c0f, 0x939f, 0x462e, 0x8d, 0xb0, 0x1f, 0x21, 0x14, 0xbe, 0x2a, 0x82)



// CVideoPluginPropPage::CVideoPluginPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CVideoPluginPropPage ��ϵͳע�����

BOOL CVideoPluginPropPage::CVideoPluginPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_VIDEOPLUGIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CVideoPluginPropPage::CVideoPluginPropPage - ���캯��

CVideoPluginPropPage::CVideoPluginPropPage() :
	COlePropertyPage(IDD, IDS_VIDEOPLUGIN_PPG_CAPTION)
{
}



// CVideoPluginPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CVideoPluginPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CVideoPluginPropPage ��Ϣ�������
