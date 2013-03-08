#pragma once

#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/sizer.h"
#include "wx/timer.h"
#include "wx/filefn.h"
#include "wx/thread.h"

#include "KrtConstant.h"
#include "KrtMainFrame.h"


//////////////////////////////////////////////////////////////////////////

class ThreadWork: public wxThread
{
public:
	ThreadWork(
		const wxArrayString &,
		wxString &,
		unsigned long *,
		unsigned long *,
		wxArrayString &,
		wxTimer &
	);
	virtual void *Entry();

private:
	const wxArrayString parItems;
	wxString &current;
	unsigned long *lTotal;
	unsigned long *lFit;
	wxArrayString &resultItems;
	wxTimer &t_mr;
};


ThreadWork::ThreadWork(
	const wxArrayString &par,
	wxString &currentFile,
	unsigned long *totalNum,
	unsigned long *fitNum,
	wxArrayString &res,
	wxTimer &tm
):	parItems(par),
	current(currentFile),
	lTotal(totalNum),
	lFit(fitNum),
	resultItems(res),
	t_mr(tm)
{
	;
}

void *ThreadWork::Entry()
{
	wxArrayString dirItems;					//目录队列
	dirItems.Add( parItems[0] );			//将待遍历的目录路径添加到目录队列中

	wxString filename;		bool cont;		wxString tempPath;
	while( dirItems.GetCount() )			//当目录队列不为空时执行
	{
		if( (dirItems[0].Find("\\") == -1) && (dirItems[0].Find('/') == -1) )
		{
			dirItems.RemoveAt(0);
			wxMessageBox( _T("路径问题") );
			continue;
		}
		wxDir dir( dirItems[0] );			//打开队列前端目录路径
		if( !dir.IsOpened() )
		{
			wxMessageBox( _T("无法打开该目录!"), _T("错误"), wxOK | wxICON_INFORMATION );
			return NULL;
		}
		
		cont = dir.GetFirst( &filename );						//获取首个文件
		while ( cont )
		{
			tempPath = dirItems[0] + "\\" + filename;			//合成 filename 的完整路径
			if( dir.Exists( tempPath ) )			//判断 tempPath 是否为目录
				dirItems.Add( tempPath );			//为目录时则添加到目录队列
			else
			{
				resultItems.Add( tempPath );
				current = tempPath;
				(*lTotal)++;
			}
			cont = dir.GetNext(&filename);			//获取下一个文件
		}
		dirItems.RemoveAt(0);				//当前目录遍历完成后将其从目录队列中删除
	}
	wxMessageBox(
		wxString::Format( "完成! 共查找了 %i 个文件, %i 个文件符合条件。", *lTotal, *lFit ),
		_T("完成"), wxOK | wxICON_INFORMATION
	);
	t_mr.Stop();
	return NULL;
}



//////////////////////////////////////////////////////////////////////////

class SearchingDlg: public wxDialog
{
public:
	SearchingDlg( wxArrayString *, const wxArrayString &, const wxString & );
	void OnClose( wxCloseEvent & );		//阻止关闭对话框
	void OnStopExit( wxCommandEvent & );			//关闭对话框
	void OnSearchFile( wxTimerEvent &t );		//搜索文件
	void OnRedrawUI( wxTimerEvent & );			//重绘UI
	void OnPauseContinue( wxCommandEvent & );

private:
	const wxArrayString parItems;		//查找参数

	wxGauge			*gauge;						//进度条
	wxStaticText	*lblCurrentFile;			//当前扫描的文件
	wxStaticText	*lblFileTotal;				//已扫描的文件总计
	wxStaticText	*lblFitTotal;				//符合的文件总计
	wxButton		*btnPauseContinue;			//暂停/继续按钮
	wxButton		*btnStopExit;				//停止/退出按钮

	//搜索结果
	wxArrayString *resultItems;

	//定时器
	wxTimer tmrRedrawUI;			//UI重绘定时器

	//当前搜索文件路径
	wxString strCurrentFile;

	//统计计数
	unsigned long iTotalFile;		//已扫描文件总量
	unsigned long iFitTotal;		//符合条件数量

	//搜索线程
	ThreadWork *thread;

	//事件列表
	DECLARE_EVENT_TABLE()
};

//////////////////////////////////////////////////////////////////////////

SearchingDlg::SearchingDlg(
	wxArrayString *resItems,
	const wxArrayString &items,
	const wxString &title
):wxDialog( 
	NULL, wxID_ANY,
	title, wxPoint(-1, -1), wxSize(400, 150), wxCAPTION ),
	parItems(items),
	tmrRedrawUI( this, TMR_REDRAW_UI ),
	iTotalFile(0),
	iFitTotal(0)
{
	resultItems = resItems;
	/*
	unsigned int i = 0;
	int y = 10;
	for( i; i < parItems.GetCount(); i++ )
	{
		new wxStaticText( this, -1, parItems[i], wxPoint(10, y) );
		y += 20;
	}
	*/
	wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL ) ;
		wxBoxSizer *boxBtn = new wxBoxSizer( wxHORIZONTAL );
			gauge = new wxGauge( this, wxID_ANY, 100, wxPoint(15, 20), wxSize(300, 25) );
			boxBtn->Add( gauge, 0, wxALIGN_CENTER|wxLEFT|wxTOP, 15 );
			btnPauseContinue = new wxButton( this, BTN_PAUSECONTINUE, _T("暂停"), wxPoint(-1, -1), wxSize(40, 25) );
			boxBtn->Add( btnPauseContinue, 0, wxALIGN_CENTER|wxLEFT|wxTOP, 15 );
			btnStopExit		 = new wxButton( this, BTN_STOPEXIT, _T("停止"), wxPoint(-1, -1), wxSize(40, 25) );
			boxBtn->Add( btnStopExit, 0, wxALIGN_CENTER|wxLEFT|wxTOP|wxRIGHT, 15 );
	topSizer->Add( boxBtn, 0, wxALIGN_RIGHT );
	
		lblCurrentFile = new wxStaticText( this, wxID_ANY, _T("当前文件:") );
		topSizer->Add( lblCurrentFile, 0, wxLEFT|wxTOP|wxBOTTOM, 15 );

		wxBoxSizer *boxTotal = new wxBoxSizer( wxHORIZONTAL );
			lblFileTotal = new wxStaticText( this, wxID_ANY, _T("已查找:") );
			boxTotal->Add( lblFileTotal, 0, wxLEFT|wxBOTTOM, 15 );
			lblFitTotal = new wxStaticText( this, wxID_ANY, _T("符合条件:") );
			boxTotal->Add( lblFitTotal, 0, wxLEFT, 130 );
	topSizer->Add( boxTotal );

		
    SetSizer( topSizer );					// 绑定对话框和布局控件
	topSizer->Fit( this );					// 调用对话框大小
    topSizer->SetSizeHints( this );			// 设置对话框最小大小

	tmrRedrawUI.Start( 150, wxTIMER_CONTINUOUS );				//启动UI重绘定时器

	thread = new ThreadWork( parItems, strCurrentFile, &iTotalFile, &iFitTotal, *resultItems, tmrRedrawUI );
	if ( thread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError(wxT("Can't create thread!"));
	}
	thread->Run();

	Center();
}

//////////////////////////////////////////////////////////////////////////
//事件绑定

BEGIN_EVENT_TABLE( SearchingDlg, wxDialog )
EVT_CLOSE( SearchingDlg::OnClose )
EVT_BUTTON( BTN_STOPEXIT, SearchingDlg::OnStopExit )
EVT_BUTTON( BTN_PAUSECONTINUE, SearchingDlg::OnPauseContinue )
EVT_TIMER( TMR_REDRAW_UI, SearchingDlg::OnRedrawUI )
END_EVENT_TABLE()


//////////////////////////////////////////////////////////////////////////
//事件响应
void SearchingDlg::OnClose( wxCloseEvent &event )
{
	;
}

void SearchingDlg::OnStopExit( wxCommandEvent &event )
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
//重绘UI

void SearchingDlg::OnRedrawUI( wxTimerEvent &event )
{
	gauge->Pulse();
	lblCurrentFile->SetLabel( _T("当前文件: ") + strCurrentFile );
	lblFileTotal->SetLabel( wxString::Format( "已查找: %i", iTotalFile ) );
	lblFitTotal->SetLabel( wxString::Format( "符合条件: %i", iFitTotal ) );
}


//搜索的暂停与继续
void SearchingDlg::OnPauseContinue( wxCommandEvent &event )
{
	if( btnPauseContinue->GetLabel() == _T("暂停") )
	{
		tmrRedrawUI.Stop();
		thread -> Pause();
		btnPauseContinue->SetLabel( _T("继续") );
	}
	else
	{
		tmrRedrawUI.Start(-1);
		thread -> Resume();
		btnPauseContinue->SetLabel( _T("暂停") );
	}
}