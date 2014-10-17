
// VideoClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "videoutil.h"
#include "VideoPlugin.h"
#include "atltypes.h"


// CVideoClientDlg �Ի���
class CVideoClientDlg : public CDialogEx
{
// ����
public:
	CVideoClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIDEOCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	
	BOOL            m_bFullScreen;     // ȫ����־  
	CRect           m_FullScreenRect;  // ������Ļ�ߴ�
	CRect           m_OldPictureRect;  // ������Ļ�ߴ�
	WINDOWPLACEMENT m_OldWndPlacement; // ȫ��ʱ�Ի����λ������  
	WINDOWPLACEMENT m_NewWndPlacement; // ȫ����Ի����λ������

	// ���ɵ���Ϣӳ�亯��
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
