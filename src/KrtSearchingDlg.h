

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
	void OnStopExit( wxCommandEvent & );			//关闭对话框
	void OnSearchFile( wxTimerEvent &t );		//搜索文件
	void OnRedrawUI( wxTimerEvent & );			//重绘UI
	void OnPauseContinue( wxCommandEvent & );	//暂停继续
	void OnSearchDone( wxCommandEvent & );

private:
	const wxArrayString parItems;		//查找参数

	wxGauge			*gauge;						//进度条
	wxStaticText	*lblCurrentFile;			//当前扫描的文件
	wxStaticText	*lblFileTotal;				//已扫描的文件总计
	wxStaticText	*lblFitTotal;				//符合的文件总计
	wxButton		*btnPauseContinue;			//暂停/继续按钮
	wxButton		*btnStopExit;				//停止/退出按钮

	//搜索结果
	wxArrayString *resultItems;

	//定时器
	wxTimer tmrRedrawUI;			//UI重绘定时器

	//当前搜索文件路径
	wxString strCurrentFile;

	//统计计数
	unsigned long iTotalFile;		//已扫描文件总量
	unsigned long iFitTotal;		//符合条件数量

	//搜索线程
	ThreadWork *thread;

	//线程控制
	bool therad_stop;

	//事件列表
	DECLARE_EVENT_TABLE()
};

