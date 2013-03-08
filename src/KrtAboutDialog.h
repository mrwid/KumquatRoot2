#pragma once

#include "wx/wx.h"


class AboutDlg: public wxDialog
{
public:
	AboutDlg( const wxString & );
};

//////////////////////////////////////////////////////////////////////////

AboutDlg::AboutDlg( const wxString &title ):wxDialog(NULL, wxID_ANY, title)
{

	Center();
}