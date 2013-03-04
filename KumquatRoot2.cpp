#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"

class KumquatRoot2:public wxApp
{
	virtual bool OnInit();
};

bool KumquatRoot2::OnInit()
{
	wxFrame *frame = new wxFrame(NULL, wxID_ANY, wxT("éÙ¸ùÎÄ¼þËÑË÷ - KumquatRoot2"));
	frame->Show(true);

	return true;
}

DECLARE_APP(KumquatRoot2)
IMPLEMENT_APP(KumquatRoot2)