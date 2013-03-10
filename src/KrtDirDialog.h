#pragma once

#include "wx/wx.h"
#include "wx/dir.h"
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
