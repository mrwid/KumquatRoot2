#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"

#include "KrtConstant.h"

//////////////////////////////////////////////////////////////////////////
// ������ MainFrame ������

class MainFrame:public wxFrame
{
public:
	MainFrame( const wxString &title = wxT("") );

};

//////////////////////////////////////////////////////////////////////////
// MainFrame ������ʵ��

MainFrame::MainFrame( const wxString &title ):wxFrame( NULL, wxID_ANY, title )
{
	//�����洰�ڵ���
	this->SetSize( wxSize( MAIN_SIZE_X, MAIN_SIZE_Y ) );		//�������ڴ�С
	this->Center();												//����
}