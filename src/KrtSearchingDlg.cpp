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
		
    SetSizer( topSizer );					// �󶨶Ի���Ͳ��ֿؼ�
	topSizer->Fit( this );					// ���öԻ����С
    topSizer->SetSizeHints( this );			// ���öԻ�����С��С

	//////////////////////////////////////////////////////////////////////////
	
	tmrRedrawUI.Start( 150, wxTIMER_CONTINUOUS );				//����UI�ػ涨ʱ��

	thread = new ThreadWork(
		parItems,				//���Ҳ���
		strCurrentFile,			//��ǰ�ļ�
		iTotalFile,				//��ɨ���ļ�����
		iFitTotal,				//���Ͻ���ļ�����
		*resultItems,			//���Ͻ�����ļ�·��
		this,					//����������ָ��
		therad_stop				//�߳̿���
	);
	if ( thread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError(wxT("Can't create thread!"));
	}
	thread->Run();

	Center();
}

//////////////////////////////////////////////////////////////////////////
//�¼���

BEGIN_EVENT_TABLE( SearchingDlg, wxDialog )
EVT_BUTTON( BTN_STOPEXIT, SearchingDlg::OnStopExit )
EVT_BUTTON( BTN_PAUSECONTINUE, SearchingDlg::OnPauseContinue )
EVT_BUTTON( VIR_BTN_DONE, SearchingDlg::OnSearchDone )
EVT_TIMER( TMR_REDRAW_UI, SearchingDlg::OnRedrawUI )
END_EVENT_TABLE()


//////////////////////////////////////////////////////////////////////////
//�¼���Ӧ

void SearchingDlg::OnStopExit( wxCommandEvent &event )
{
	if( btnStopExit->GetLabel() == _T("ֹͣ") )
	{
		therad_stop = true;
		wxMessageBox(
			wxString::Format( "������ֹ! �������ļ�: %i, ��������: %i", iTotalFile, iFitTotal),
			_T("���"),
			wxOK|wxICON_INFORMATION
		);
	}

	Close();
}

//////////////////////////////////////////////////////////////////////////
//�ػ�UI

void SearchingDlg::OnRedrawUI( wxTimerEvent &event )
{
	gauge->Pulse();
	lblCurrentFile->SetLabel( _T("��ǰ�ļ�: ") + strCurrentFile );
	lblFileTotal->SetLabel( wxString::Format( "�Ѳ���: %i", iTotalFile ) );
	lblFitTotal->SetLabel( wxString::Format( "��������: %i", iFitTotal ) );
}

//��������ͣ�����
void SearchingDlg::OnPauseContinue( wxCommandEvent &event )
{
	if( btnPauseContinue->GetLabel() == _T("��ͣ") )
	{
		tmrRedrawUI.Stop();
		thread -> Pause();
		btnPauseContinue->SetLabel( _T("����") );
	}
	else
	{
		tmrRedrawUI.Start(-1);
		thread -> Resume();
		btnPauseContinue->SetLabel( _T("��ͣ") );
	}
}

//�������
void SearchingDlg::OnSearchDone( wxCommandEvent &event )
{
	tmrRedrawUI.Stop();
	btnStopExit->SetLabel( _T("���!") );
	
	gauge->SetValue(100);
	lblCurrentFile->SetLabel( _T("��ǰ�ļ�: ") + strCurrentFile );
	lblFileTotal->SetLabel( wxString::Format( "�Ѳ���: %i", iTotalFile ) );
	lblFitTotal->SetLabel( wxString::Format( "��������: %i", iFitTotal ) );

	wxMessageBox(
		wxString::Format( "���! �������ļ�: %i, ��������: %i", iTotalFile, iFitTotal),
		_T("���"),
		wxOK|wxICON_INFORMATION
	);
}