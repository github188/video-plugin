
// VideoClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "videoutil.h"
#include "VideoPlugin.h"
#include "atltypes.h"


// CVideoClientDlg 对话框
class CVideoClientDlg : public CDialogEx
{
// 构造
public:
	CVideoClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VIDEOCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	
	BOOL            m_bFullScreen;     // 全屏标志  
	CRect           m_FullScreenRect;  // 整个屏幕尺寸
	CRect           m_OldPictureRect;  // 整个屏幕尺寸
	WINDOWPLACEMENT m_OldWndPlacement; // 全屏时对话框的位置属性  
	WINDOWPLACEMENT m_NewWndPlacement; // 全屏后对话框的位置属性

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); 
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void OnLoadPNG(LPCTSTR m_Path, CRect m_Rect);

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCplayer();
	afx_msg void OnBnClickedCstop();
	afx_msg void OnBnClickedCcapture();
	afx_msg void OnBnClickedCrecord();
	afx_msg void OnBnClickedCfullscreen();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedDown();
	CStatic m_sdlPlayer;
	BOOL PreTranslateMessage(MSG *pMsg);
	void NormalShow(void); 
	void OnFullShow(void);
	afx_msg void OnBnClickedBtnAmp();
	afx_msg void OnBnClickedBtnShr();
	afx_msg void OnBnClickedBtnRfh();
	afx_msg void OnBnClickedBtnExit();
	CComboBox m_nCoChanel;
	afx_msg void OnCbnSelchangeCoChannel();
	vector<string> ipvector;
};

extern CVideoUtil m_videoUtil;
