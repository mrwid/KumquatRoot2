#include "KrtAboutDialog.h"

AboutDlg::AboutDlg( const wxString &title ):wxDialog(NULL, wxID_ANY, title)
{
	wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBox *boxInfo = new wxStaticBox( this, wxID_ANY, _T("信息"), wxPoint(-1, -1), wxSize(400, 300) );
	wxStaticBoxSizer *boxSizer = new wxStaticBoxSizer( boxInfo, wxVERTICAL );
		boxSizer->Add( new wxStaticText( this, wxID_ANY, _T("作者: wid") ), 0, wxALL|wxGROW, 15 );

			wxBoxSizer *blog = new wxBoxSizer( wxHORIZONTAL );
				blog->Add( new wxStaticText( this, wxID_ANY, _T("博客: ") ), 0, wxLEFT|wxGROW, 15 );
				blog->Add( new wxHyperlinkCtrl(
					this, wxID_ANY,
					_T("http://www.cnblogs.com/mr-wid"),
					_T("http://www.cnblogs.com/mr-wid/"))
				);
		boxSizer->Add( blog, 0, wxLEFT );
		boxSizer->Add( new wxStaticText( this, wxID_ANY, _T("编码指导: WT") ), 0, wxGROW|wxLEFT|wxTOP, 15 );
		boxSizer->Add( new wxStaticText( this, wxID_ANY, _T("开源协议: GNU GPL v3") ), 0, wxGROW|wxLEFT|wxTOP, 15 );

			wxBoxSizer *license = new wxBoxSizer( wxHORIZONTAL );
				license->Add( new wxStaticText( this, wxID_ANY, _T("项目地址: ") ), 0, wxGROW|wxTOP|wxLEFT|wxBOTTOM, 15 );
				license->Add( new wxHyperlinkCtrl(
					this, wxID_ANY,
					_T("https://github.com/mrwid/KumquatRoot2"),
					_T("https://github.com/mrwid/KumquatRoot2")),
					0, wxBOTTOM|wxRIGHT|wxTOP, 15
				);
		boxSizer->Add( license, 0, wxLEFT );

	topSizer->Add( boxSizer, 0, wxALL, 20 );
	topSizer->Add( new wxButton( this, wxID_OK, _T("确定") ), 0, wxCENTER|wxALL, 10 );

    SetSizer( topSizer );
    topSizer->Fit( this );
    topSizer->SetSizeHints( this );

	Center();
}