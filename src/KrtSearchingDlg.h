#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"

#include "KrtMainFrame.h"
#include "KrtConstant.h"


class SearchingDlg: public wxDialog
{
public:
	SearchingDlg( const wxArrayString &, const wxString & );
	void OnClose( wxCloseEvent & );		//阻止关闭对话框
	void OnStopExit( wxCommandEvent & );		//关闭对话框

private:
	const wxArrayString parItems;		//查找参数

	wxGauge			*gauge;						//进度条
	wxStaticText	*lblCurrentFile;			//当前扫描的文件
	wxStaticText	*lblFileTotal;				//已扫描的文件总计
	wxStaticText	*lblFitTotal;				//符合的文件总计
	wxButton		*btnPauseContinue;			//暂停/继续按钮
	wxButton		*btnStopExit;				//停止/退出按钮

	//事件列表
	DECLARE_EVENT_TABLE()
};

//////////////////////////////////////////////////////////////////////////

SearchingDlg::SearchingDlg( const wxArrayString &items, const wxString &title ):wxDialog( 
		NULL, wxID_ANY, title, wxPoint(-1, -1), wxSize(400, 150), wxCAPTION ), parItems(items)
{
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

	//btnPauseContinue = new wxButton( this, wxID_ANY, _T("暂停"), wxPoint() )
		
    SetSizer( topSizer );					// 绑定对话框和布局控件
	topSizer->Fit( this );					// 调用对话框大小
    topSizer->SetSizeHints( this );			// 设置对话框最小大小

	Center();
}

//////////////////////////////////////////////////////////////////////////
//事件绑定

BEGIN_EVENT_TABLE( SearchingDlg, wxDialog )
EVT_CLOSE( SearchingDlg::OnClose )
EVT_BUTTON( BTN_STOPEXIT, SearchingDlg::OnStopExit )
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