#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/listctrl.h"

#include "KrtConstant.h"
#include "KrtDirDialog.h"

//////////////////////////////////////////////////////////////////////////
// 主界面 MainFrame 类声明

class MainFrame:public wxDialog
{
public:
	MainFrame( const wxString &title = wxT("") );

private:
	wxBoxSizer  *topSizer;
	wxBoxSizer	*conSizer;
	//wxListCtrl  *resultList;
	wxStaticBox *boxPar;		//参数设置静态框
	wxStaticBox *boxRes;		//查找结果静态框
	//参数设置控件
	wxTextCtrl *txtRootPath;		//起始目录输入框
	wxTextCtrl *txtFileNameKey;		//文件名匹配文本框
	wxCheckBox *chkUseNameKey;		//复选框, 使用文件名匹配
	wxTextCtrl *txtFileContKey;		//文件内容匹配文本框
	wxCheckBox *chkUseContKey;		//复选框, 使用文件内容匹配
	wxRadioBox *rdoSearchType;		//匹配模式
	wxTextCtrl *txtNamesList;		//文件后缀
	wxRadioBox *rdoNamesType;		//使用扩展名
	wxButton   *btnStartSearch;		//开始搜索

	//搜索结果控件
	wxListCtrl *resList;
};

//////////////////////////////////////////////////////////////////////////

// MainFrame 构造函数的实现
MainFrame::MainFrame( const wxString &title ):wxDialog(
	NULL,
	wxID_ANY,
	title,
	wxPoint(-1, -1),
	wxSize(-1, -1),
	wxDEFAULT_FRAME_STYLE)
{
	SetIcon( wxICON(ICON_APP) );			//设置软件图标
	
	//////////////////////////////////////////////////////////////////////////
	// 参数设置静态框与查找结果静态框布局
	boxPar =  new wxStaticBox(this, wxID_ANY, wxT("查找参数设置") );
	boxRes = new wxStaticBox(this, wxID_ANY, wxT("查找结果") );

	wxStaticBoxSizer *parBoxSizer = new wxStaticBoxSizer( boxPar, wxVERTICAL );
		wxBoxSizer *boxPath = new wxBoxSizer( wxHORIZONTAL );
			boxPath->Add( new wxStaticText( this, wxID_ANY, _T("起始目录:")), 0, wxALIGN_CENTER| wxALL, 5 );
			txtRootPath = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(160, -1) );
			boxPath->Add( txtRootPath, 0, wxALIGN_CENTER|wxALL, 5 );
			boxPath->Add( new wxButton( this, BTN_GETROOT, _T("浏览..(&B)")), 0, wxALIGN_CENTER|wxALL, 5 );

		wxBoxSizer *nameKey = new wxBoxSizer( wxHORIZONTAL );
			nameKey->Add( new wxStaticText( this, wxID_ANY, _T("匹配文件名称:")), 0, wxALIGN_CENTER|wxALL, 5 );
			txtFileNameKey = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(170, -1) );
			nameKey->Add( txtFileNameKey,  0, wxALIGN_CENTER|wxALL, 5 );
			chkUseNameKey = new wxCheckBox( this, wxID_ANY, _T("启用") );
			nameKey->Add( chkUseNameKey,  0, wxALIGN_CENTER|wxALL, 5 );

		wxBoxSizer *contKey = new wxBoxSizer( wxHORIZONTAL );
			contKey->Add( new wxStaticText( this, wxID_ANY, _T("匹配文件内容:")), 0, wxALIGN_CENTER|wxALL, 5 );
			txtFileContKey = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(170, -1) );
			contKey->Add( txtFileContKey,  0, wxALIGN_CENTER|wxALL, 5 );
			chkUseContKey = new wxCheckBox( this, wxID_ANY, _T("启用") );
			contKey->Add( chkUseContKey,  0, wxALIGN_CENTER|wxALL, 5 );
		
		wxBoxSizer *boxSearchType = new wxBoxSizer( wxHORIZONTAL );
			boxSearchType->Add( new wxStaticText(this, wxID_ANY, _T("选择匹配模式:")), 1, wxALIGN_CENTER|wxALL, 5 );
			wxArrayString items;
			items.Add( _T("普通精确匹配") );	items.Add( _T("正则表达式匹配") );
			rdoSearchType = new wxRadioBox( this, wxID_ANY, _T(""),wxPoint(-1, -1), wxSize(-1, -1), items );
			boxSearchType->Add( rdoSearchType,  0, wxALIGN_CENTER|wxALL, 5 );
		//////////////////////////////////////////////////////////////////////////

		wxStaticBox *boxNames = new wxStaticBox( this, wxID_ANY, _T("按扩展名过滤") );
		wxStaticBoxSizer *boxNamesSizer = new wxStaticBoxSizer( boxNames, wxVERTICAL );
			txtNamesList = new wxTextCtrl( this, wxID_ANY, _T(""), wxPoint(-1, -1), wxSize(200, -1) );
			boxNamesSizer->Add( txtNamesList, 0, wxALIGN_LEFT|wxALL|wxGROW, 5 );
			wxArrayString namesList;
			namesList.Add( _T("过滤以上扩展名") );	namesList.Add( _T("仅搜索以上扩展名") );
			rdoNamesType = new wxRadioBox(this, wxID_ANY, _T(""),wxPoint(-1, -1), wxSize(-1, -1), namesList );
			boxNamesSizer->Add( rdoNamesType, 0, wxALIGN_CENTER|wxALL, 0 );

	parBoxSizer->Add( boxPath, 1, wxALL|wxALIGN_LEFT, 0 );
	parBoxSizer->Add( nameKey, 1, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->Add( contKey, 1, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->Add( boxSearchType, 1, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->AddSpacer( 15 );
	parBoxSizer->Add( boxNamesSizer, 0, wxALL|wxALIGN_LEFT|wxGROW, 0 );
	parBoxSizer->AddSpacer( 20 );
	btnStartSearch = new wxButton( this, BTN_START_SEARCH, _T("开始搜索(&S)"), wxPoint(-1, -1), wxSize(100, 40) );
	parBoxSizer->Add( btnStartSearch, 0, wxALL|wxALIGN_CENTER, 0 );

	wxStaticBoxSizer *resBoxSizer = new wxStaticBoxSizer( boxRes, wxVERTICAL );
		resList = new wxListCtrl( this, wxID_ANY, wxPoint(-1, -1), wxSize(380, 300), wxLC_REPORT );
		resList->InsertColumn( 0, _T("文件名"), wxLIST_FIND_LEFT, 150 );
		resList->InsertColumn( 1, _T("文件路径"), wxLIST_FIND_LEFT, 200 );
		//resList->InsertItem(0, _T("文本文件.txt"));
		//resList->SetItem(0, 1, _T("D:\\Develop\\a.txt"));
	resBoxSizer->Add( resList, 1, wxALL|wxGROW, 10 );

	topSizer = new wxBoxSizer( wxHORIZONTAL );
	    topSizer->Add( parBoxSizer, 0, wxEXPAND | wxALL, 20 );
	    topSizer->Add( resBoxSizer, 1, wxEXPAND | wxALL, 20 );

    SetSizer( topSizer );					// 绑定对话框和布局控件
	topSizer->Fit( this );					// 调用对话框大小
    topSizer->SetSizeHints( this );			// 设置对话框最小大小

	//////////////////////////////////////////////////////////////////////////
	
	Center();
}