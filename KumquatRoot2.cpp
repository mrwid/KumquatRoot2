#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "src/KrtMainFrame.h"

class KumquatRoot2:public wxApp
{
	virtual bool OnInit();
};

bool KumquatRoot2::OnInit()
{
	MainFrame *frame = new MainFrame( _T("éÙ¸ùÎÄ¼þËÑË÷ - KumquatRoot2") );
	frame->ShowModal();
	frame->Destroy();

	return true;
}

DECLARE_APP(KumquatRoot2)
IMPLEMENT_APP(KumquatRoot2)