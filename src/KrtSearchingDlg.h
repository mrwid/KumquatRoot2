#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"

#include "KrtMainFrame.h"
#include "KrtConstant.h"


class SearchingDlg: public wxDialog
{
public:
	SearchingDlg( const wxArrayString &, const wxString & );
	void OnClose( wxCloseEvent & );		//��ֹ�رնԻ���
	void OnStopExit( wxCommandEvent & );		//�رնԻ���

private:
	const wxArrayString parItems;		//���Ҳ���

	wxGauge			*gauge;						//������
	wxStaticText	*lblCurrentFile;			//��ǰɨ����ļ�
	wxStaticText	*lblFileTotal;				//��ɨ����ļ��ܼ�
	wxStaticText	*lblFitTotal;				//���ϵ��ļ��ܼ�
	wxButton		*btnPauseContinue;			//��ͣ/������ť
	wxButton		*btnStopExit;				//ֹͣ/�˳���ť

	//�¼��б�
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
			btnPauseContinue = new wxButton( this, BTN_PAUSECONTINUE, _T("��ͣ"), wxPoint(-1, -1), wxSize(40, 25) );
			boxBtn->Add( btnPauseContinue, 0, wxALIGN_CENTER|wxLEFT|wxTOP, 15 );
			btnStopExit		 = new wxButton( this, BTN_STOPEXIT, _T("ֹͣ"), wxPoint(-1, -1), wxSize(40, 25) );
			boxBtn->Add( btnStopExit, 0, wxALIGN_CENTER|wxLEFT|wxTOP|wxRIGHT, 15 );
	topSizer->Add( boxBtn, 0, wxALIGN_RIGHT );
	
		lblCurrentFile = new wxStaticText( this, wxID_ANY, _T("��ǰ�ļ�:") );
		topSizer->Add( lblCurrentFile, 0, wxLEFT|wxTOP|wxBOTTOM, 15 );

		wxBoxSizer *boxTotal = new wxBoxSizer( wxHORIZONTAL );
			lblFileTotal = new wxStaticText( this, wxID_ANY, _T("�Ѳ���:") );
			boxTotal->Add( lblFileTotal, 0, wxLEFT|wxBOTTOM, 15 );
			lblFitTotal = new wxStaticText( this, wxID_ANY, _T("��������:") );
			boxTotal->Add( lblFitTotal, 0, wxLEFT, 130 );
	topSizer->Add( boxTotal );

	//btnPauseContinue = new wxButton( this, wxID_ANY, _T("��ͣ"), wxPoint() )
		
    SetSizer( topSizer );					// �󶨶Ի���Ͳ��ֿؼ�
	topSizer->Fit( this );					// ���öԻ����С
    topSizer->SetSizeHints( this );			// ���öԻ�����С��С

	Center();
}

//////////////////////////////////////////////////////////////////////////
//�¼���

BEGIN_EVENT_TABLE( SearchingDlg, wxDialog )
EVT_CLOSE( SearchingDlg::OnClose )
EVT_BUTTON( BTN_STOPEXIT, SearchingDlg::OnStopExit )
END_EVENT_TABLE()


//////////////////////////////////////////////////////////////////////////
//�¼���Ӧ
void SearchingDlg::OnClose( wxCloseEvent &event )
{
	;
}

void SearchingDlg::OnStopExit( wxCommandEvent &event )
{
	Destroy();
}