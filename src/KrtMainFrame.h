#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "wx/app.h"
#include "wx/menu.h"
#include "wx/sizer.h"
#include "wx/utils.h"
#include "wx/filefn.h"
#include "wx/listctrl.h"

#include <windows.h>

#include "KrtConstant.h"
#include "KrtDirDialog.h"
#include "KrtAboutDialog.h"
#include "KrtSearchingDlg.h"

//////////////////////////////////////////////////////////////////////////
// 主界面 MainFrame 类声明

class MainFrame:public wxDialog
{
public:
	MainFrame( const wxString &title = wxT("") );

	//按钮事件
	void OnBtnBrowser( wxCommandEvent & );
	void OnBtnStart( wxCommandEvent & );
	void OnDisplayResult( wxArrayString * );
	void OnShowPopMenu( wxListEvent & );

	//响应菜单
	void OnOpenTheFile( wxCommandEvent & );
	void OnShowAboutDlg( wxCommandEvent & );
	void OnOpenFileDir( wxCommandEvent & );
	void OnSaveAsFile( wxCommandEvent & );
	void OnDeleteFile( wxCommandEvent & );

	//获取列表结果选择的路径
	wxString getListSelectedPtah();

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

	//搜索结果右键菜单
	wxMenu *popMenu;

	//事件
	DECLARE_EVENT_TABLE()
};
