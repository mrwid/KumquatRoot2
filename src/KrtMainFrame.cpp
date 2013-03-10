#include "KrtMainFrame.h"

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
			items.Add( _T("��ͨģ��ƥ��") );	items.Add( _T("������ʽƥ��") );
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
		resList = new wxListCtrl( this, LIST_RESULT, wxPoint(-1, -1), wxSize(380, 300), wxLC_REPORT );
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
	//��������Ҽ��˵�
	popMenu = new wxMenu;
	popMenu->Append( MENU_OPEN, _T("���ļ�(&O)") );
	popMenu->Append( MENU_PLACE, _T("������Ŀ¼(&P)") );
	popMenu->Append( MENU_SAVEAS, _T("���Ϊ...(&S)") );
	popMenu->Append( MENU_DELETE, _T("ɾ���ļ�(&D)") );
	popMenu->AppendSeparator();
	popMenu->Append( MENU_ABOUT, _T("���� KumquatRoot2") );

	//////////////////////////////////////////////////////////////////////////
	
	Center();
}

//////////////////////////////////////////////////////////////////////////
//�¼���
BEGIN_EVENT_TABLE(MainFrame, wxDialog)
EVT_BUTTON( BTN_GETROOT, MainFrame::OnBtnBrowser )
EVT_BUTTON( BTN_START_SEARCH, MainFrame::OnBtnStart )
EVT_LIST_ITEM_RIGHT_CLICK( LIST_RESULT, MainFrame::OnShowPopMenu )
EVT_MENU( MENU_OPEN, MainFrame::OnOpenTheFile )
EVT_MENU( MENU_PLACE, MainFrame::OnOpenFileDir )
EVT_MENU( MENU_ABOUT, MainFrame::OnShowAboutDlg )
EVT_MENU( MENU_SAVEAS, MainFrame::OnSaveAsFile )
EVT_MENU( MENU_DELETE, MainFrame::OnDeleteFile )
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
	if( txtRootPath->GetValue() == wxEmptyString )
		txtRootPath->SetValue( wxGetCwd() );
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
	OnDisplayResult( resultItems );
}

void MainFrame::OnDisplayResult( wxArrayString *items )
{
	if( items -> GetCount() > 3000 )
	{
		wxMessageDialog dlg( NULL,
			_T("���������Ľ������ 3000, ȷ����Ҫ��ʾ������?"), _T("ѯ��"),
			wxOK|wxCANCEL|wxICON_QUESTION
		);
		if( dlg.ShowModal() == wxID_CANCEL )
			return;
	}
	boxRes->SetLabel( wxString::Format( "���ҽ��(%i)", items->GetCount() ) );
	resList->DeleteAllItems();
	unsigned long i = 0;
	for( i; i < items -> GetCount(); i++ )
	{
		resList->InsertItem( 0, wxFileNameFromPath( (*items)[i]) );
		resList->SetItem( 0, 1, (*items)[i] );
	}
	items->Clear();
}


//////////////////////////////////////////////////////////////////////////

wxString MainFrame::getListSelectedPtah()
{
	unsigned long index = resList->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_FOCUSED );
	wxListItem item;
	item.SetMask(wxLIST_MASK_TEXT);
	item.SetId(index);
	item.SetColumn(1);
	resList->GetItem(item);
	return item.GetText();
}

//�����Ҽ��˵�
void MainFrame::OnShowPopMenu( wxListEvent &event )
{
	PopupMenu( popMenu );
}

//���ļ�
void MainFrame::OnOpenTheFile( wxCommandEvent &event )
{
	if( ShellExecute( NULL, _T("open"), getListSelectedPtah(), "", "", 1 ) <= (HINSTANCE)32 )
		wxMessageBox( _T("δ�ҵ���Ч�Ĵ򿪷�ʽ!"), _T("��ʧ��"), wxOK|wxICON_INFORMATION );
}

//���ļ�����Ŀ¼
void MainFrame::OnOpenFileDir( wxCommandEvent &event )
{
	WinExec( "explorer /select, " + getListSelectedPtah(), SW_NORMAL );
}

//�ļ����Ϊ
void MainFrame::OnSaveAsFile( wxCommandEvent &event )
{
	wxString name, ext, fullPath = getListSelectedPtah();
	
	wxSplitPath( fullPath, NULL, &name, &ext );
	wxFileDialog dlg( NULL, _T("���Ϊ..."), wxGetCwd(), name, _T(".")+ext );
	if( dlg.ShowModal() == wxID_OK )
	{
		if( wxFileExists( fullPath ) )
		{
			wxMessageDialog reDlg( NULL,
				wxString::Format( "���ļ����Ѱ���һ����Ϊ %s.%s ���ļ�, ���Ǹ��ļ�?", name, ext ),
				_T("ȷ���ļ��滻"), wxYES|wxNO|wxICON_QUESTION
			);
			if( reDlg.ShowModal() == wxYES )
				if( !wxCopyFile( getListSelectedPtah(), dlg.GetPath() ) )
					wxMessageBox( _T("���Ϊʧ��!"), _T("ʧ��"), wxOK|wxICON_INFORMATION );
		}
	}
}

//ɾ���ļ�
void MainFrame::OnDeleteFile( wxCommandEvent & )
{
	wxString name, ext, fullPath = getListSelectedPtah();
	wxSplitPath( fullPath, NULL, &name, &ext );
	wxMessageDialog dlg( NULL, wxString::Format("ȷ��ɾ�� %s.%s ?", name, ext), _T("ɾ��ȷ��"), wxOK|wxCANCEL|wxICON_QUESTION );
	if( dlg.ShowModal() == wxID_OK )
	{
		if( !wxRemoveFile( fullPath ) )
		{
			wxMessageBox( _T("ɾ��ʧ��!"), _T("ʧ��"), wxOK|wxICON_INFORMATION );
			return;
		}
		resList->DeleteItem( resList->GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_FOCUSED ) );
	}
}

//��ʾ���ڶԻ���
void MainFrame::OnShowAboutDlg( wxCommandEvent &event )
{
	AboutDlg *dlg = new AboutDlg( _T("���� KumquatRoot2") );
	dlg->ShowModal();
	dlg->Destroy();
}
