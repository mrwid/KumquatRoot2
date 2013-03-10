#pragma once
//////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "wx/app.h"
#include "wx/menu.h"
#include "wx/sizer.h"
#include "wx/filefn.h"
#include "wx/listctrl.h"

#include "KrtConstant.h"
#include "KrtDirDialog.h"
#include "KrtAboutDialog.h"
#include "KrtSearchingDlg.h"

//////////////////////////////////////////////////////////////////////////
// ������ MainFrame ������

class MainFrame:public wxDialog
{
public:
	MainFrame( const wxString &title = wxT("") );

	//��ť�¼�
	void OnBtnBrowser( wxCommandEvent & );
	void OnBtnStart( wxCommandEvent & );
	void OnShowAboutDlg( wxCommandEvent & );
	void OnDisplayResult( wxArrayString * );
	void OnShowPopMenu( wxListEvent & );

private:
	wxBoxSizer  *topSizer;
	wxBoxSizer	*conSizer;
	//wxListCtrl  *resultList;
	wxStaticBox *boxPar;		//�������þ�̬��
	wxStaticBox *boxRes;		//���ҽ����̬��
	//�������ÿؼ�
	wxTextCtrl *txtRootPath;		//��ʼĿ¼�����
	wxTextCtrl *txtFileNameKey;		//�ļ���ƥ���ı���
	wxCheckBox *chkUseNameKey;		//��ѡ��, ʹ���ļ���ƥ��
	wxTextCtrl *txtFileContKey;		//�ļ�����ƥ���ı���
	wxCheckBox *chkUseContKey;		//��ѡ��, ʹ���ļ�����ƥ��
	wxRadioBox *rdoSearchType;		//ƥ��ģʽ
	wxTextCtrl *txtNamesList;		//�ļ���׺
	wxRadioBox *rdoNamesType;		//ʹ����չ��
	wxButton   *btnStartSearch;		//��ʼ����

	//��������ؼ�
	wxListCtrl *resList;

	//��������Ҽ��˵�
	wxMenu *popMenu;

	//�¼�
	DECLARE_EVENT_TABLE()
};
