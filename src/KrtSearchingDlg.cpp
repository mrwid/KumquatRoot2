#include "KrtSearchingDlg.h"

//////////////////////////////////////////////////////////////////////////

SearchingDlg::SearchingDlg(
	wxArrayString *resItems,
	const wxArrayString &items,
	const wxString &title
):wxDialog( 
	NULL, DLG_SEARCHDLG,
	title, wxPoint(-1, -1), wxSize(400, 150), wxCAPTION ),
	parItems(items),
	tmrRedrawUI( this, TMR_REDRAW_UI ),
	iTotalFile(0),
	iFitTotal(0),
	therad_stop(false)
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

	//////////////////////////////////////////////////////////////////////////
	
	tmrRedrawUI.Start( 150, wxTIMER_CONTINUOUS );				//启动UI重绘定时器

	thread = new ThreadWork(
		parItems,				//查找参数
		strCurrentFile,			//当前文件
		iTotalFile,				//已扫描文件总数
		iFitTotal,				//符合结果文件总数
		*resultItems,			//符合结果的文件路径
		this,					//本搜索窗口指针
		therad_stop				//线程控制
	);
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
EVT_BUTTON( BTN_STOPEXIT, SearchingDlg::OnStopExit )
EVT_BUTTON( BTN_PAUSECONTINUE, SearchingDlg::OnPauseContinue )
EVT_BUTTON( VIR_BTN_DONE, SearchingDlg::OnSearchDone )
EVT_TIMER( TMR_REDRAW_UI, SearchingDlg::OnRedrawUI )
END_EVENT_TABLE()


//////////////////////////////////////////////////////////////////////////
//事件响应

void SearchingDlg::OnStopExit( wxCommandEvent &event )
{
	if( btnStopExit->GetLabel() == _T("停止") )
	{
		therad_stop = true;
		wxMessageBox(
			wxString::Format( "搜索终止! 共搜索文件: %i, 符合条件: %i", iTotalFile, iFitTotal),
			_T("完成"),
			wxOK|wxICON_INFORMATION
		);
	}

	Close();
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

//搜索完成
void SearchingDlg::OnSearchDone( wxCommandEvent &event )
{
	tmrRedrawUI.Stop();
	btnStopExit->SetLabel( _T("完成!") );
	
	gauge->SetValue(100);
	lblCurrentFile->SetLabel( _T("当前文件: ") + strCurrentFile );
	lblFileTotal->SetLabel( wxString::Format( "已查找: %i", iTotalFile ) );
	lblFitTotal->SetLabel( wxString::Format( "符合条件: %i", iFitTotal ) );

	wxMessageBox(
		wxString::Format( "完成! 共搜索文件: %i, 符合条件: %i", iTotalFile, iFitTotal),
		_T("完成"),
		wxOK|wxICON_INFORMATION
	);
}