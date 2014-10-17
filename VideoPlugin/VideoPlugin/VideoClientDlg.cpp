
// VideoClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoClientDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include <atlconv.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVideoUtil m_videoUtil;
// CVideoClientDlg �Ի���


CVideoClientDlg::CVideoClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoClientDlg::IDD, pParent)
	, m_bFullScreen(false)
	, m_FullScreenRect(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCSDLPLAYER, m_sdlPlayer);
	DDX_Control(pDX, IDC_CO_CHANNEL, m_nCoChanel);
}

BEGIN_MESSAGE_MAP(CVideoClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCPLAYER, &CVideoClientDlg::OnBnClickedCplayer)
	ON_BN_CLICKED(IDCSTOP, &CVideoClientDlg::OnBnClickedCstop)
	ON_BN_CLICKED(IDCCAPTURE, &CVideoClientDlg::OnBnClickedCcapture)
	ON_BN_CLICKED(IDCRECORD, &CVideoClientDlg::OnBnClickedCrecord)
	ON_BN_CLICKED(IDCFULLSCREEN, &CVideoClientDlg::OnBnClickedCfullscreen)
	ON_BN_CLICKED(IDC_UP, &CVideoClientDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_LEFT, &CVideoClientDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_RIGHT, &CVideoClientDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_DOWN, &CVideoClientDlg::OnBnClickedDown)
	//ON_STN_DBLCLK(IDCSDLPLAYER, &CVideoClientDlg::OnStnDblclickCsdlplayer)
	//ON_STN_CLICKED(IDCSDLPLAYER, &CVideoClientDlg::OnStnClickedCsdlplayer)
	ON_BN_CLICKED(IDC_BTN_AMP, &CVideoClientDlg::OnBnClickedBtnAmp)
	ON_BN_CLICKED(IDC_BTN_SHR, &CVideoClientDlg::OnBnClickedBtnShr)
	ON_BN_CLICKED(IDC_BTN_RFH, &CVideoClientDlg::OnBnClickedBtnRfh)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CVideoClientDlg::OnBnClickedBtnExit)
	ON_CBN_SELCHANGE(IDC_CO_CHANNEL, &CVideoClientDlg::OnCbnSelchangeCoChannel)
END_MESSAGE_MAP()


// CVideoClientDlg ��Ϣ�������

BOOL CVideoClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	COLORREF maskColor = RGB(255,255,255);   //������ɫ
	
	DWORD dwStyle = GetStyle();//��ȡ����ʽ  
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;  
	dwNewStyle&=dwStyle;//��λ�뽫����ʽȥ��  
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);//���ó��µ���ʽ  
	DWORD dwExStyle = GetExStyle();//��ȡ����չ��ʽ  
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;  
	dwNewExStyle&=dwExStyle;//��λ�뽫����չ��ʽȥ��  
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);//�����µ���չ��ʽ  
	SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);
	//����windows���ҵ���ʽ�ı��ˣ�����λ�úʹ�С����ԭ�����䣡  

	CRect rect(0,0,960,540);
	CWnd::SetWindowPos(NULL,0,0,rect.Width(),rect.Height(),SWP_NOZORDER|SWP_NOMOVE); 
	
	CWnd *pWnd;
	//double cc; //1920 * 1080��Ϊ1280 * 720
	//cc = 0.6667;
	pWnd = GetDlgItem( IDCPLAYER );    //��ID�Ż�ȡ�ؼ�ָ��
	pWnd->SetWindowPos( NULL,213 ,476,24,24,SWP_NOZORDER );    //�༭�ؼ��Ĵ�С��λ�ö��ı�  
	pWnd = GetDlgItem( IDCSTOP );  
	pWnd->SetWindowPos( NULL,260,479,25,25,SWP_NOZORDER );
	pWnd = GetDlgItem( IDCCAPTURE );  
	pWnd->SetWindowPos( NULL,312,479,31,25,SWP_NOZORDER );
	pWnd = GetDlgItem( IDCRECORD );  
	pWnd->SetWindowPos( NULL,365,481,36,27,SWP_NOZORDER );
	pWnd = GetDlgItem( IDCFULLSCREEN );  
	pWnd->SetWindowPos( NULL,431,482,33,22,SWP_NOZORDER );
	pWnd = GetDlgItem( IDCSDLPLAYER );  
	pWnd->SetWindowPos( NULL,54,43,720,406,SWP_NOZORDER );
	pWnd = GetDlgItem( IDC_UP );  
	pWnd->SetWindowPos( NULL,832,130,25,25,SWP_NOZORDER );
	pWnd = GetDlgItem( IDC_LEFT );  
	pWnd->SetWindowPos( NULL,808,154,25,25,SWP_NOZORDER );
	pWnd = GetDlgItem( IDC_RIGHT );  
	pWnd->SetWindowPos( NULL,854,154,25,25,SWP_NOZORDER );
	pWnd = GetDlgItem( IDC_DOWN );  
	pWnd->SetWindowPos( NULL,832,176,25,25,SWP_NOZORDER );

	pWnd = GetDlgItem( IDC_BTN_AMP ); 
	pWnd->SetWindowPos( NULL,817,326,25,25,SWP_NOZORDER );
	pWnd = GetDlgItem( IDC_BTN_SHR ); 
	pWnd->SetWindowPos( NULL,844,326,25,25,SWP_NOZORDER );

	pWnd = GetDlgItem( IDC_CO_CHANNEL ); 
	pWnd->SetWindowPos( NULL,497,483,117,22,SWP_NOZORDER );
	pWnd->ShowWindow(SW_HIDE);
	pWnd = GetDlgItem( IDC_BTN_RFH ); 
	pWnd->SetWindowPos( NULL, 817,360,25,22, SWP_NOZORDER );
	pWnd->ShowWindow(SW_HIDE);
	pWnd = GetDlgItem( IDC_BTN_EXIT ); 
	pWnd->SetWindowPos( NULL, 844,360,25,22, SWP_NOZORDER );
	pWnd->ShowWindow(SW_HIDE);

	//m_nCoChanel.SetDropDownMenu(IDR_MENUDROPDOWN, 0);

	m_videoUtil.SetSdlPlayer(&m_sdlPlayer);
	//m_videoUtil.SetScreenSize();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVideoClientDlg::OnPaint()
{
	CRect rect;
	m_sdlPlayer.GetWindowRect(&rect);
	OnLoadPNG(_T(g_szOcxPath+"res/ui-mockup-player-bg1.png"), rect);
	CStatic* pWnd = (CStatic*)GetDlgItem(IDCSDLPLAYER); // �õ� Picture Control ���  
	ATL::CImage image;  
	image.Load(_T(g_szOcxPath+"res/ui-mockup-player-inner.png"));  
	HBITMAP hBmp = image.Detach();  
	m_sdlPlayer.SetBitmap(hBmp);
	
}

HBRUSH CVideoClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)   
{  
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);  
	  
	switch(pWnd->GetDlgCtrlID())
	{
	case IDCPLAYER:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCSTOP:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCCAPTURE:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCRECORD:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCFULLSCREEN:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_UP:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_LEFT:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_RIGHT:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_DOWN:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_BTN_AMP:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    case IDC_BTN_SHR:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCCHANNEL:
			   pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
			   pWnd = pWnd->GetParent();
			   hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
			   pDC ->SetBkMode(TRANSPARENT);
	default: break;
	}
	return hbr;
}  

void CVideoClientDlg::OnLoadPNG(LPCTSTR Path, CRect m_Rect)
{
	ATL::CImage img;
	HRESULT ret = img.Load(Path); //Ҫ���ص�ͼƬ���ƣ�����·��
	HBITMAP hbitmap = img.Detach();

	//����� BMP ͼƬһ������ͼƬ ,��������ʾͼƬ�Ĳ���
	CPaintDC dc(this);// ���ڻ��Ƶ��豸������
	CRect rect;    
	GetClientRect(&rect);  
	CBitmap pngBackground;
	BITMAP bitmap;
	CDC memdc;
	pngBackground.Attach(hbitmap);
	memdc.CreateCompatibleDC(&dc);
	pngBackground.GetBitmap(&bitmap);  //�����󶨹�ϵ  
	CBitmap  *pbmpOld=memdc.SelectObject(&pngBackground);   //����ԭ��CDC���󣬲�ѡ����CDC������DC  
	dc.SetStretchBltMode(COLORONCOLOR);//��ֹbmpͼƬʧ��
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	memdc.SelectObject(pbmpOld);  
	pngBackground.DeleteObject();  
	memdc.DeleteDC(); 
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVideoClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVideoClientDlg::OnBnClickedCplayer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_nCoChanel.GetCurSel();

	if (!m_videoUtil.IsStarted())
	{
		//m_videoUtil.connetToCarmer();
		m_videoUtil.RunLiveVideo();
		// Sleep(1000);
	}

	//if (index != CB_ERR)
	//{
	//	
	//}
	//else
	//{
	//	MessageBox("����ѡ��Ƶ����");
	//}

}


void CVideoClientDlg::OnBnClickedCstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_videoUtil.IsStarted())
	{
		m_videoUtil.StopLiveVideo();
	}
}


void CVideoClientDlg::OnBnClickedCcapture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"Capture");

	m_videoUtil.CaptureBmp();
}


void CVideoClientDlg::OnBnClickedCrecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_videoUtil.RecordVideo();
}


void CVideoClientDlg::OnBnClickedCfullscreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (FALSE == m_bFullScreen)  
	{  
		OnFullShow(); //ȫ����ʾ  
	}  
	else  
	{  
		NormalShow();  //�ָ�Ĭ����ʾ  
	} 
	//m_videoUtil.StartThread();

}

void CVideoClientDlg::OnBnClickedUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"UP");
	m_videoUtil.MoveTurner(TURN_UP);
}


void CVideoClientDlg::OnBnClickedLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"Left");
	m_videoUtil.MoveTurner(TURN_LEFT);
}


void CVideoClientDlg::OnBnClickedRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"Right");
	m_videoUtil.MoveTurner(TURN_RIGHT);
}


void CVideoClientDlg::OnBnClickedDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"Down");
	m_videoUtil.MoveTurner(TURN_DOWN);
}

void CVideoClientDlg::OnFullShow(void)  
{  
	// TODO: Add your command handler code here  
	/*
	if (FALSE == m_bFullScreen)  
	{  
		m_bFullScreen = TRUE; 

		//��ȡ�Ի���ԭʼλ��  
		GetWindowPlacement(&m_OldWndPlacement);  
		CRect WindowRect;  
		GetWindowRect(&WindowRect);  
		CRect ClientRect; 
		GetClientRect(&ClientRect);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);  
		ClientToScreen(&ClientRect);  

		//��ȡ��Ļ�ķֱ���  
		int nFullWidth  = GetSystemMetrics(SM_CXSCREEN);  
		int nFullHeight = GetSystemMetrics(SM_CYSCREEN);  

		//�Ի���ȫ����ʾ  
		m_FullScreenRect.left = WindowRect.left - ClientRect.left;  
		m_FullScreenRect.top = WindowRect.top - ClientRect.top;  
		m_FullScreenRect.right  = WindowRect.right - ClientRect.right + nFullWidth;  
		m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;  

		m_NewWndPlacement.length           = sizeof(WINDOWPLACEMENT);  
		m_NewWndPlacement.flags            = 0;  
		m_NewWndPlacement.showCmd          = SW_SHOWNORMAL;  
		m_NewWndPlacement.rcNormalPosition = m_FullScreenRect;  
		SetWindowPlacement(&m_NewWndPlacement);  

		//Picture�ؼ�ȫ����ʾ  
		CRect rect;
		m_sdlPlayer.GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_OldPictureRect = rect;

		m_sdlPlayer.SetWindowPos( NULL,0 ,0,m_FullScreenRect.Width(),m_FullScreenRect.Height(),SWP_NOZORDER ); 
		m_sdlPlayer.GetWindowRect(&rect);
		ScreenToClient(&rect);
		OnLoadPNG(_T("res/ui-mockup-player-inner.png"),rect);
		UpdateWindow();

		m_videoUtil.SetSdlPlayer(&m_sdlPlayer);
		m_videoUtil.SetFullScreen(true);
	}
	*/
}  

void CVideoClientDlg::NormalShow(void)  
{  
	if (TRUE == m_bFullScreen)  
	{  
		//�ָ�Ĭ�ϴ���  
		SetWindowPlacement(&m_OldWndPlacement);
		//�ָ�Picture�ؼ�
		int oWidth = m_OldPictureRect.Width();
		int oHight = m_OldPictureRect.Height();
		m_sdlPlayer.MoveWindow(CRect(m_OldPictureRect.left, m_OldPictureRect.top, oWidth, oHight));
		m_bFullScreen = FALSE;  

		m_videoUtil.SetSdlPlayer(&m_sdlPlayer);
		m_videoUtil.SetFullScreen(false);

		//OnPaint();
	}  
}  


BOOL CVideoClientDlg::PreTranslateMessage(MSG *pMsg)  
{  

	if (WM_LBUTTONDBLCLK == pMsg->message) // 1 ���˫����Ӧ  
	{  
		//��ȡ���λ��  
		CPoint ptCursor;  
		GetCursorPos(&ptCursor);  

		CRect rc;  
		m_sdlPlayer.GetWindowRect(&rc);  

		//1.1 ˫��ʱ���λ��Picture�ؼ���Χ�ڲ���Ӧ  
		if (rc.PtInRect(ptCursor))  
		{
			if (FALSE == m_bFullScreen)  
			{  
				OnFullShow(); //ȫ����ʾ  
			}  
			else  
			{  
				NormalShow();  //�ָ�Ĭ����ʾ  
			} 
		}  
	} //end of if (WM_LBUTTONDBLCLK == pMsg->message)  
	else if (WM_KEYDOWN == pMsg->message) // 2 ����������Ӧ  
	{  
		// 2.1��������Esc  
		if (VK_ESCAPE == pMsg->wParam)  
		{  
			if (TRUE == m_bFullScreen)  
			{  
				NormalShow();  //�ָ�Ĭ����ʾ  
			}
		}  

		// 2.2��������Enter  
		if (VK_RETURN == pMsg->wParam)  
		{  
			//m_videoUtil.StopThread();
			if (FALSE == m_bFullScreen)  
			{  
				OnFullShow(); //ȫ����ʾ  
			}  
			else  
			{  
				NormalShow();  //�ָ�Ĭ����ʾ  
			}
			//m_videoUtil.StartThread();
		}  
	} //end of if (WM_KEYDOWN == pMsg->message)  


	return 0;  
}  

void CVideoClientDlg::OnBnClickedBtnAmp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CString str("amp");
	MessageBox(str);*/
	//MessageBox("amp��ť��");
	m_videoUtil.ZoomScene(SCENE_AMPLIFY);
}


void CVideoClientDlg::OnBnClickedBtnShr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("shr��ť��");
	m_videoUtil.ZoomScene(SCENE_SHRINK);
}



void CVideoClientDlg::OnBnClickedBtnRfh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ӷ�������ȡ�ķ�����ip�ַ����б��ԡ�,��Ϊ�ָ�������һ���ַ�����ʾ������ip�ĸ�����֮��ÿ���ַ�������һ��ip��ַ+�˿ںţ�
	char ipList[500] = "2,192.168.1.104:35000,116.228.186.78:35000";

	m_videoUtil.GetServerIPList(ipList, ipvector);
	for (int i=1; i<=ipvector.size(); i++)
	{
		string strChannel = "����ͷ ";
		char buffer[20];
		strChannel.append(itoa(i,buffer,10));
		//memcpy(strChannel.c_str()+strlen(strChannel.c_str()), &i, sizeof(int));
		m_nCoChanel.AddString(ATL::CA2T(strChannel.c_str()));
	}
}


void CVideoClientDlg::OnBnClickedBtnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_videoUtil.StopThread();
	//AfxGetMainWnd()->PostMessage(WM_COMMAND,ID_APP_EXIT);
	exit(0);
}


void CVideoClientDlg::OnCbnSelchangeCoChannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox("aaa");
	int index = m_nCoChanel.GetCurSel();
	string strIp = ipvector.at(index);

	//strIp="192.168.1.169:35000";            //11-11 test
	m_videoUtil.connetToCarmer(strIp);
}
