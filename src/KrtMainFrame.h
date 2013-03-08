#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/filefn.h"
#include "wx/listctrl.h"
#include "wx/hyperlink.h"

#include "KrtConstant.h"
#include "KrtDirDialog.h"
#include "KrtAboutDialog.h"
#include "KrtSearchingDlg.h"

//////////////////////////////////////////////////////////////////////////
// ������ MainFrame ������

class MainFrame:public wxDialog
{
public:
	MainFrame( const wxString &title = wxT("") );

	//��ť�¼�
	void OnBtnBrowser( wxCommandEvent & );
	void OnBtnStart( wxCommandEvent & );
	void OnShowAboutDlg( wxCommandEvent & );
	void OnDisplayResult( wxArrayString * );

private:
	wxBoxSizer  *topSizer;
	wxBoxSizer	*conSizer;
	//wxListCtrl  *resultList;
	wxStaticBox *boxPar;		//�������þ�̬��
	wxStaticBox *boxRes;		//���ҽ����̬��
	//�������ÿؼ�
	wxTextCtrl *txtRootPath;		//��ʼĿ¼�����
	wxTextCtrl *txtFileNameKey;		//�ļ���ƥ���ı���
	wxCheckBox *chkUseNameKey;		//��ѡ��, ʹ���ļ���ƥ��
	wxTextCtrl *txtFileContKey;		//�ļ�����ƥ���ı���
	wxCheckBox *chkUseContKey;		//��ѡ��, ʹ���ļ�����ƥ��
	wxRadioBox *rdoSearchType;		//ƥ��ģʽ
	wxTextCtrl *txtNamesList;		//�ļ���׺
	wxRadioBox *rdoNamesType;		//ʹ����չ��
	wxButton   *btnStartSearch;		//��ʼ����

	//��������ؼ�
	wxListCtrl *resList;

	//�¼�
	DECLARE_EVENT_TABLE()
};

//////////////////////////////////////////////////////////////////////////

// MainFrame ���캯����ʵ��
MainFrame::MainFrame( const wxString &title ):wxDialog(
	NULL,
	wxID_ANY,
	title,
	wxPoint(-1, -1),
	wxSize(-1, -1),
	wxDEFAULT_FRAME_STYLE)
{
	SetIcon( wxICON(ICON_APP) );			//�������ͼ��
	
	//////////////////////////////////////////////////////////////////////////
	// �������þ�̬������ҽ����̬�򲼾�
	boxPar =  new wxStaticBox(this, wxID_ANY, wxT("���Ҳ�������") );
	boxRes = new wxStaticBox(this, wxID_ANY, wxT("���ҽ��") );

	//������������
	wxStaticBoxSizer *parBoxSizer = new wxStaticBoxSizer( boxPar, wxVERTICAL );
		//��һ��
		wxBoxSizer *boxPath = new wxBoxSizer( wxHORIZONTAL );
			boxPath->Add( new wxStaticText( this, wxID_ANY, _T("��ʼĿ¼:")), 0, wxALIGN_CENTER| wxALL, 5 );
			txtRootPath = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(160, -1) );
			boxPath->Add( txtRootPath, 0, wxALIGN_CENTER|wxALL, 5 );
			boxPath->Add( new wxButton( this, BTN_GETROOT, _T("���..(&B)")), 0, wxALIGN_CENTER|wxALL, 5 );

		//�ڶ���
		wxBoxSizer *nameKey = new wxBoxSizer( wxHORIZONTAL );
			nameKey->Add( new wxStaticText( this, wxID_ANY, _T("ƥ���ļ�����:")), 0, wxALIGN_CENTER|wxALL, 5 );
			txtFileNameKey = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(170, -1) );
			nameKey->Add( txtFileNameKey,  0, wxALIGN_CENTER|wxALL, 5 );
			chkUseNameKey = new wxCheckBox( this, wxID_ANY, _T("����") );
			nameKey->Add( chkUseNameKey,  0, wxALIGN_CENTER|wxALL, 5 );
		//������
		wxBoxSizer *contKey = new wxBoxSizer( wxHORIZONTAL );
			contKey->Add( new wxStaticText( this, wxID_ANY, _T("ƥ���ļ�����:")), 0, wxALIGN_CENTER|wxALL, 5 );
			txtFileContKey = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(170, -1) );
			contKey->Add( txtFileContKey,  0, wxALIGN_CENTER|wxALL, 5 );
			chkUseContKey = new wxCheckBox( this, wxID_ANY, _T("����") );
			contKey->Add( chkUseContKey,  0, wxALIGN_CENTER|wxALL, 5 );
		
		//���Ĳ�
		wxBoxSizer *boxSearchType = new wxBoxSizer( wxHORIZONTAL );
			boxSearchType->Add( new wxStaticText(this, wxID_ANY, _T("ѡ��ƥ��ģʽ:")), 1, wxALIGN_CENTER|wxALL, 5 );
			wxArrayString items;
			items.Add( _T("��ͨ��ȷƥ��") );	items.Add( _T("������ʽƥ��") );
			rdoSearchType = new wxRadioBox( this, wxID_ANY, _T(""),wxPoint(-1, -1), wxSize(-1, -1), items );
			boxSearchType->Add( rdoSearchType,  0, wxALIGN_CENTER|wxALL, 5 );
		//////////////////////////////////////////////////////////////////////////

		//�����
		wxStaticBox *boxNames = new wxStaticBox( this, wxID_ANY, _T("����չ������") );
		wxStaticBoxSizer *boxNamesSizer = new wxStaticBoxSizer( boxNames, wxVERTICAL );
			txtNamesList = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(200, -1) );
			boxNamesSizer->Add( txtNamesList, 0, wxALIGN_LEFT|wxALL|wxGROW, 5 );
			wxArrayString namesList;
			namesList.Add( _T("����������չ��") );	namesList.Add( _T("������������չ��") );
			rdoNamesType = new wxRadioBox(this, wxID_ANY, _T(""),wxPoint(-1, -1), wxSize(-1, -1), namesList );
			boxNamesSizer->Add( rdoNamesType, 0, wxALIGN_CENTER|wxALL, 0 );

	parBoxSizer->Add( boxPath, 1, wxALL|wxALIGN_LEFT, 0 );
	parBoxSizer->Add( nameKey, 1, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->Add( contKey, 1, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->Add( boxSearchType, 1, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->AddSpacer( 15 );
	parBoxSizer->Add( boxNamesSizer, 0, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->AddSpacer( 20 );
	btnStartSearch = new wxButton( this, BTN_START_SEARCH, _T("��ʼ����(&S)"), wxPoint(-1, -1), wxSize(100, 40) );
	parBoxSizer->Add( btnStartSearch, 0, wxALL|wxALIGN_CENTER, 0 );

	//�Ҳ����������
	wxStaticBoxSizer *resBoxSizer = new wxStaticBoxSizer( boxRes, wxVERTICAL );
		resList = new wxListCtrl( this, wxID_ANY, wxPoint(-1, -1), wxSize(380, 300), wxLC_REPORT );
		resList->InsertColumn( 0, _T("�ļ���"), wxLC_REPORT, 150 );
		resList->InsertColumn( 1, _T("�ļ�·��"), wxLC_REPORT, 200 );
		//resList->InsertItem(0, _T("�ı��ļ�.txt"));
		//resList->SetItem(0, 1, _T("D:\\Develop\\a.txt"));
	resBoxSizer->Add( resList, 1, wxALL|wxGROW, 10 );

	topSizer = new wxBoxSizer( wxHORIZONTAL );
	    topSizer->Add( parBoxSizer, 0, wxEXPAND | wxALL, 20 );
	    topSizer->Add( resBoxSizer, 1, wxEXPAND | wxALL, 20 );

    SetSizer( topSizer );					// �󶨶Ի���Ͳ��ֿؼ�
	topSizer->Fit( this );					// ���öԻ����С
    topSizer->SetSizeHints( this );			// ���öԻ�����С��С

	//////////////////////////////////////////////////////////////////////////
	
	Center();
}

//////////////////////////////////////////////////////////////////////////
//�¼���
BEGIN_EVENT_TABLE(MainFrame, wxDialog)
EVT_BUTTON( BTN_GETROOT, MainFrame::OnBtnBrowser )
EVT_BUTTON( BTN_START_SEARCH, MainFrame::OnBtnStart )
END_EVENT_TABLE()


//////////////////////////////////////////////////////////////////////////

void MainFrame::OnBtnBrowser( wxCommandEvent &event )
{
	KrtDirDlg *dlg = new KrtDirDlg;
	if( dlg->ShowModal() == wxID_OK )
		txtRootPath->SetValue( dlg->getDirPath() );
	dlg->Destroy();
}

void MainFrame::OnBtnStart( wxCommandEvent &event )
{
	wxArrayString parItems;
	wxArrayString *resultItems = new wxArrayString;				//�������
	parItems.Add( txtRootPath->GetValue() );									//��ʼ·��
	parItems.Add( txtFileNameKey->GetValue() );									//�ļ���
	parItems.Add( wxString::Format( "%i", chkUseNameKey->GetValue() ) );		//�Ƿ������ļ���ƥ��
	parItems.Add( txtFileContKey->GetValue() );									//�ļ�����
	parItems.Add( wxString::Format( "%i", chkUseContKey ->GetValue() ) );		//�Ƿ������ļ�����ƥ��
	parItems.Add( wxString::Format( "%i", rdoSearchType->GetSelection() ) );	//��������
	parItems.Add( txtNamesList->GetValue() );									//�ļ���չ��
	parItems.Add( wxString::Format( "%i", rdoNamesType->GetSelection() ) );		//��չ����������
	
	SearchingDlg *dlg = new SearchingDlg( resultItems, parItems, _T("��������...") );
	dlg->ShowModal();
	dlg->Destroy();
	OnDisplayResult( resultItems );
}

void MainFrame::OnDisplayResult( wxArrayString *items )
{
	boxRes->SetLabel( wxString::Format( "���ҽ��(%i)", items->GetCount() ) );
	resList->DeleteAllItems();
	unsigned long i = 0;
	for( i; i < items -> GetCount(); i++ )
	{
		resList->InsertItem( 0, wxFileNameFromPath( (*items)[i]) );
		resList->SetItem( 0, 1, (*items)[i] );
	}
	delete items;
}

//��ʾ���ڶԻ���
void MainFrame::OnShowAboutDlg( wxCommandEvent &event )
{
	AboutDlg *dlg = new AboutDlg( _T("���� KumquatRoot2") );
	dlg->ShowModal();
	dlg->Destroy();
}
