#include "wx/wx.h"
#include "KrtApplication.h"

IMPLEMENT_APP(KumquatRoot2)

bool KumquatRoot2::OnInit()
{
	MainFrame frame( _T("éÙ¸ùÎÄ¼þËÑË÷ - KumquatRoot2") );
	frame.ShowModal();

	return false;
}

