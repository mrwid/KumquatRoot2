#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"

#include "KrtConstant.h"

//////////////////////////////////////////////////////////////////////////
// 主界面 MainFrame 类声明

class MainFrame:public wxFrame
{
public:
	MainFrame( const wxString &title = wxT("") );

};

//////////////////////////////////////////////////////////////////////////
// MainFrame 方法的实现

MainFrame::MainFrame( const wxString &title ):wxFrame( NULL, wxID_ANY, title )
{
	//主界面窗口调整
	this->SetSize( wxSize( MAIN_SIZE_X, MAIN_SIZE_Y ) );		//调整窗口大小
	this->Center();												//居中
}