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
	wxArrayString dirItems;					//Ŀ¼����
	dirItems.Add( parItems[0] );			//����������Ŀ¼·����ӵ�Ŀ¼������

	wxString filename;		bool cont;		wxString tempPath;
	while( dirItems.GetCount() )			//��Ŀ¼���в�Ϊ��ʱִ��
	{
		if( (dirItems[0].Find("\\") == -1) && (dirItems[0].Find('/') == -1) )
		{
			dirItems.RemoveAt(0);
			wxMessageBox( _T("·������") );
			continue;
		}
		wxDir dir( dirItems[0] );			//�򿪶���ǰ��Ŀ¼·��
		if( !dir.IsOpened() )
		{
			wxMessageBox( _T("�޷��򿪸�Ŀ¼!"), _T("����"), wxOK | wxICON_INFORMATION );
			return NULL;
		}
		
		cont = dir.GetFirst( &filename );						//��ȡ�׸��ļ�
		while ( cont )
		{
			tempPath = dirItems[0] + "\\" + filename;			//�ϳ� filename ������·��
			if( dir.Exists( tempPath ) )			//�ж� tempPath �Ƿ�ΪĿ¼
				dirItems.Add( tempPath );			//ΪĿ¼ʱ����ӵ�Ŀ¼����
			else
			{
				resultItems.Add( tempPath );
				current = tempPath;
				(*lTotal)++;
			}
			cont = dir.GetNext(&filename);			//��ȡ��һ���ļ�
		}
		dirItems.RemoveAt(0);				//��ǰĿ¼������ɺ����Ŀ¼������ɾ��
	}
	wxMessageBox(
		wxString::Format( "���! �������� %i ���ļ�, %i ���ļ�����������", *lTotal, *lFit ),
		_T("���"), wxOK | wxICON_INFORMATION
	);
	t_mr.Stop();
	return NULL;
}



//////////////////////////////////////////////////////////////////////////

class SearchingDlg: public wxDialog
{
public:
	SearchingDlg( wxArrayString *, const wxArrayString &, const wxString & );
	void OnClose( wxCloseEvent & );		//��ֹ�رնԻ���
	void OnStopExit( wxCommandEvent & );			//�رնԻ���
	void OnSearchFile( wxTimerEvent &t );		//�����ļ�
	void OnRedrawUI( wxTimerEvent & );			//�ػ�UI
	void OnPauseContinue( wxCommandEvent & );

private:
	const wxArrayString parItems;		//���Ҳ���

	wxGauge			*gauge;						//������
	wxStaticText	*lblCurrentFile;			//��ǰɨ����ļ�
	wxStaticText	*lblFileTotal;				//��ɨ����ļ��ܼ�
	wxStaticText	*lblFitTotal;				//���ϵ��ļ��ܼ�
	wxButton		*btnPauseContinue;			//��ͣ/������ť
	wxButton		*btnStopExit;				//ֹͣ/�˳���ť

	//�������
	wxArrayString *resultItems;

	//��ʱ��
	wxTimer tmrRedrawUI;			//UI�ػ涨ʱ��

	//��ǰ�����ļ�·��
	wxString strCurrentFile;

	//ͳ�Ƽ���
	unsigned long iTotalFile;		//��ɨ���ļ�����
	unsigned long iFitTotal;		//������������

	//�����߳�
	ThreadWork *thread;

	//�¼��б�
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

	tmrRedrawUI.Start( 150, wxTIMER_CONTINUOUS );				//����UI�ػ涨ʱ��

	thread = new ThreadWork( parItems, strCurrentFile, &iTotalFile, &iFitTotal, *resultItems, tmrRedrawUI );
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
EVT_CLOSE( SearchingDlg::OnClose )
EVT_BUTTON( BTN_STOPEXIT, SearchingDlg::OnStopExit )
EVT_BUTTON( BTN_PAUSECONTINUE, SearchingDlg::OnPauseContinue )
EVT_TIMER( TMR_REDRAW_UI, SearchingDlg::OnRedrawUI )
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