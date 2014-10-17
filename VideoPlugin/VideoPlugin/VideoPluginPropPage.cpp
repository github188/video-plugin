// VideoPluginPropPage.cpp : CVideoPluginPropPage 属性页类的实现。

#include "stdafx.h"
#include "VideoPlugin.h"
#include "VideoPluginPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CVideoPluginPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CVideoPluginPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CVideoPluginPropPage, "VIDEOPLUGIN.VideoPluginPropPage.1",
	0xaa622c0f, 0x939f, 0x462e, 0x8d, 0xb0, 0x1f, 0x21, 0x14, 0xbe, 0x2a, 0x82)



// CVideoPluginPropPage::CVideoPluginPropPageFactory::UpdateRegistry -
// 添加或移除 CVideoPluginPropPage 的系统注册表项

BOOL CVideoPluginPropPage::CVideoPluginPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_VIDEOPLUGIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CVideoPluginPropPage::CVideoPluginPropPage - 构造函数

CVideoPluginPropPage::CVideoPluginPropPage() :
	COlePropertyPage(IDD, IDS_VIDEOPLUGIN_PPG_CAPTION)
{
}



// CVideoPluginPropPage::DoDataExchange - 在页和属性间移动数据

void CVideoPluginPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CVideoPluginPropPage 消息处理程序
