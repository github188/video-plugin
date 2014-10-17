#pragma once

// VideoPluginPropPage.h : CVideoPluginPropPage 属性页类的声明。


// CVideoPluginPropPage : 有关实现的信息，请参阅 VideoPluginPropPage.cpp。

class CVideoPluginPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CVideoPluginPropPage)
	DECLARE_OLECREATE_EX(CVideoPluginPropPage)

// 构造函数
public:
	CVideoPluginPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_VIDEOPLUGIN };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

