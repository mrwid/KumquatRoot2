

#pragma once

#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/timer.h"

#include "KrtThreadWork.h"
#include "KrtConstant.h"
#include "KrtMainFrame.h"


//////////////////////////////////////////////////////////////////////////

class SearchingDlg: public wxDialog
{
public:
	SearchingDlg( wxArrayString *, const wxArrayString &, const wxString & );
	void OnStopExit( wxCommandEvent & );			//�رնԻ���
	void OnSearchFile( wxTimerEvent &t );		//�����ļ�
	void OnRedrawUI( wxTimerEvent & );			//�ػ�UI
	void OnPauseContinue( wxCommandEvent & );	//��ͣ����
	void OnSearchDone( wxCommandEvent & );

private:
	const wxArrayString parItems;		//���Ҳ���

	wxGauge			*gauge;						//������
	wxStaticText	*lblCurrentFile;			//��ǰɨ����ļ�
	wxStaticText	*lblFileTotal;				//��ɨ����ļ��ܼ�
	wxStaticText	*lblFitTotal;				//���ϵ��ļ��ܼ�
	wxButton		*btnPauseContinue;			//��ͣ/������ť
	wxButton		*btnStopExit;				//ֹͣ/�˳���ť

	//�������
	wxArrayString *resultItems;

	//��ʱ��
	wxTimer tmrRedrawUI;			//UI�ػ涨ʱ��

	//��ǰ�����ļ�·��
	wxString strCurrentFile;

	//ͳ�Ƽ���
	unsigned long iTotalFile;		//��ɨ���ļ�����
	unsigned long iFitTotal;		//������������

	//�����߳�
	ThreadWork *thread;

	//�߳̿���
	bool therad_stop;

	//�¼��б�
	DECLARE_EVENT_TABLE()
};

