
// VideoClientDlg.cpp : 实现文件
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
// CVideoClientDlg 对话框


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


// CVideoClientDlg 消息处理程序

BOOL CVideoClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	COLORREF maskColor = RGB(255,255,255);   //掩码颜色
	
	DWORD dwStyle = GetStyle();//获取旧样式  
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;  
	dwNewStyle&=dwStyle;//按位与将旧样式去掉  
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);//设置成新的样式  
	DWORD dwExStyle = GetExStyle();//获取旧扩展样式  
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;  
	dwNewExStyle&=dwExStyle;//按位与将旧扩展样式去掉  
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);//设置新的扩展样式  
	SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);
	//告诉windows：我的样式改变了，窗口位置和大小保持原来不变！  

	CRect rect(0,0,960,540);
	CWnd::SetWindowPos(NULL,0,0,rect.Width(),rect.Height(),SWP_NOZORDER|SWP_NOMOVE); 
	
	CWnd *pWnd;
	//double cc; //1920 * 1080变为1280 * 720
	//cc = 0.6667;
	pWnd = GetDlgItem( IDCPLAYER );    //从ID号获取控件指针
	pWnd->SetWindowPos( NULL,213 ,476,24,24,SWP_NOZORDER );    //编辑控件的大小和位置都改变  
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVideoClientDlg::OnPaint()
{
	CRect rect;
	m_sdlPlayer.GetWindowRect(&rect);
	OnLoadPNG(_T(g_szOcxPath+"res/ui-mockup-player-bg1.png"), rect);
	CStatic* pWnd = (CStatic*)GetDlgItem(IDCSDLPLAYER); // 得到 Picture Control 句柄  
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
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCSTOP:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCCAPTURE:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCRECORD:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCFULLSCREEN:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_UP:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_LEFT:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_RIGHT:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_DOWN:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDC_BTN_AMP:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    case IDC_BTN_SHR:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
			   return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	case IDCCHANNEL:
			   pDC->SetBkMode(TRANSPARENT);   //设置背景透明
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
	HRESULT ret = img.Load(Path); //要加载的图片名称，包含路径
	HBITMAP hbitmap = img.Detach();

	//像操作 BMP 图片一样处理图片 ,下面是显示图片的操作
	CPaintDC dc(this);// 用于绘制的设备上下文
	CRect rect;    
	GetClientRect(&rect);  
	CBitmap pngBackground;
	BITMAP bitmap;
	CDC memdc;
	pngBackground.Attach(hbitmap);
	memdc.CreateCompatibleDC(&dc);
	pngBackground.GetBitmap(&bitmap);  //建立绑定关系  
	CBitmap  *pbmpOld=memdc.SelectObject(&pngBackground);   //保存原有CDC对象，并选入新CDC对象入DC  
	dc.SetStretchBltMode(COLORONCOLOR);//防止bmp图片失真
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	memdc.SelectObject(pbmpOld);  
	pngBackground.DeleteObject();  
	memdc.DeleteDC(); 
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVideoClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVideoClientDlg::OnBnClickedCplayer()
{
	// TODO: 在此添加控件通知处理程序代码
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
	//	MessageBox("请先选择频道！");
	//}

}


void CVideoClientDlg::OnBnClickedCstop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_videoUtil.IsStarted())
	{
		m_videoUtil.StopLiveVideo();
	}
}


void CVideoClientDlg::OnBnClickedCcapture()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"Capture");

	m_videoUtil.CaptureBmp();
}


void CVideoClientDlg::OnBnClickedCrecord()
{
	// TODO: 在此添加控件通知处理程序代码
	m_videoUtil.RecordVideo();
}


void CVideoClientDlg::OnBnClickedCfullscreen()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FALSE == m_bFullScreen)  
	{  
		OnFullShow(); //全屏显示  
	}  
	else  
	{  
		NormalShow();  //恢复默认显示  
	} 
	//m_videoUtil.StartThread();

}

void CVideoClientDlg::OnBnClickedUp()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"UP");
	m_videoUtil.MoveTurner(TURN_UP);
}


void CVideoClientDlg::OnBnClickedLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"Left");
	m_videoUtil.MoveTurner(TURN_LEFT);
}


void CVideoClientDlg::OnBnClickedRight()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"Right");
	m_videoUtil.MoveTurner(TURN_RIGHT);
}


void CVideoClientDlg::OnBnClickedDown()
{
	// TODO: 在此添加控件通知处理程序代码
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

		//获取对话框原始位置  
		GetWindowPlacement(&m_OldWndPlacement);  
		CRect WindowRect;  
		GetWindowRect(&WindowRect);  
		CRect ClientRect; 
		GetClientRect(&ClientRect);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);  
		ClientToScreen(&ClientRect);  

		//获取屏幕的分辨率  
		int nFullWidth  = GetSystemMetrics(SM_CXSCREEN);  
		int nFullHeight = GetSystemMetrics(SM_CYSCREEN);  

		//对话框全屏显示  
		m_FullScreenRect.left = WindowRect.left - ClientRect.left;  
		m_FullScreenRect.top = WindowRect.top - ClientRect.top;  
		m_FullScreenRect.right  = WindowRect.right - ClientRect.right + nFullWidth;  
		m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;  

		m_NewWndPlacement.length           = sizeof(WINDOWPLACEMENT);  
		m_NewWndPlacement.flags            = 0;  
		m_NewWndPlacement.showCmd          = SW_SHOWNORMAL;  
		m_NewWndPlacement.rcNormalPosition = m_FullScreenRect;  
		SetWindowPlacement(&m_NewWndPlacement);  

		//Picture控件全屏显示  
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
		//恢复默认窗口  
		SetWindowPlacement(&m_OldWndPlacement);
		//恢复Picture控件
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

	if (WM_LBUTTONDBLCLK == pMsg->message) // 1 鼠标双击响应  
	{  
		//获取鼠标位置  
		CPoint ptCursor;  
		GetCursorPos(&ptCursor);  

		CRect rc;  
		m_sdlPlayer.GetWindowRect(&rc);  

		//1.1 双击时鼠标位于Picture控件范围内才响应  
		if (rc.PtInRect(ptCursor))  
		{
			if (FALSE == m_bFullScreen)  
			{  
				OnFullShow(); //全屏显示  
			}  
			else  
			{  
				NormalShow();  //恢复默认显示  
			} 
		}  
	} //end of if (WM_LBUTTONDBLCLK == pMsg->message)  
	else if (WM_KEYDOWN == pMsg->message) // 2 键盘输入响应  
	{  
		// 2.1键盘输入Esc  
		if (VK_ESCAPE == pMsg->wParam)  
		{  
			if (TRUE == m_bFullScreen)  
			{  
				NormalShow();  //恢复默认显示  
			}
		}  

		// 2.2键盘输入Enter  
		if (VK_RETURN == pMsg->wParam)  
		{  
			//m_videoUtil.StopThread();
			if (FALSE == m_bFullScreen)  
			{  
				OnFullShow(); //全屏显示  
			}  
			else  
			{  
				NormalShow();  //恢复默认显示  
			}
			//m_videoUtil.StartThread();
		}  
	} //end of if (WM_KEYDOWN == pMsg->message)  


	return 0;  
}  

void CVideoClientDlg::OnBnClickedBtnAmp()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CString str("amp");
	MessageBox(str);*/
	//MessageBox("amp按钮！");
	m_videoUtil.ZoomScene(SCENE_AMPLIFY);
}


void CVideoClientDlg::OnBnClickedBtnShr()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("shr按钮！");
	m_videoUtil.ZoomScene(SCENE_SHRINK);
}



void CVideoClientDlg::OnBnClickedBtnRfh()
{
	// TODO: 在此添加控件通知处理程序代码
	//从服务器获取的服务器ip字符串列表（以“,”为分隔符，第一个字符串表示服务器ip的个数，之后每个字符串都是一个ip地址+端口号）
	char ipList[500] = "2,192.168.1.104:35000,116.228.186.78:35000";

	m_videoUtil.GetServerIPList(ipList, ipvector);
	for (int i=1; i<=ipvector.size(); i++)
	{
		string strChannel = "摄像头 ";
		char buffer[20];
		strChannel.append(itoa(i,buffer,10));
		//memcpy(strChannel.c_str()+strlen(strChannel.c_str()), &i, sizeof(int));
		m_nCoChanel.AddString(ATL::CA2T(strChannel.c_str()));
	}
}


void CVideoClientDlg::OnBnClickedBtnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_videoUtil.StopThread();
	//AfxGetMainWnd()->PostMessage(WM_COMMAND,ID_APP_EXIT);
	exit(0);
}


void CVideoClientDlg::OnCbnSelchangeCoChannel()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("aaa");
	int index = m_nCoChanel.GetCurSel();
	string strIp = ipvector.at(index);

	//strIp="192.168.1.169:35000";            //11-11 test
	m_videoUtil.connetToCarmer(strIp);
}
