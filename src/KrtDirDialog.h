#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/dirctrl.h"

class KrtDirDlg: public wxDialog
{
public:
	KrtDirDlg();
	wxString getDirPath();

private:
	wxBoxSizer  *topSizer;
	wxGenericDirCtrl *dirCtrl;
};

//////////////////////////////////////////////////////////////////////////

KrtDirDlg::KrtDirDlg():wxDialog(NULL, wxID_ANY, wxT("请选择起始目录:"), wxPoint(-1, -1), wxSize(-1, -1), wxDEFAULT_FRAME_STYLE)
{

	topSizer = new wxBoxSizer( wxVERTICAL );
	
	dirCtrl = new wxGenericDirCtrl( this, 1001, _T(""), wxPoint(-1, -1), wxSize(300, 300), wxDIRCTRL_DIR_ONLY );

    topSizer->Add( dirCtrl, 1, wxEXPAND| wxALL, 20 );

    wxBoxSizer *buttonSizer = new wxBoxSizer( wxHORIZONTAL );

    buttonSizer->Add( new wxButton( this, wxID_OK, "确定" ), 0, wxALL, 10 );
    buttonSizer->Add( new wxButton(this, wxID_CANCEL, "取消" ), 0, wxALL, 10 );

    topSizer->Add( buttonSizer, 0, wxALIGN_CENTER );

    SetSizer( topSizer );
    topSizer->Fit( this );
    topSizer->SetSizeHints( this );

	Center();
}

//////////////////////////////////////////////////////////////////////////

wxString KrtDirDlg::getDirPath()
{
	return dirCtrl->GetPath();
}
