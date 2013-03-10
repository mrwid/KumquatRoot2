#pragma once

//////////////////////////////////////////////////////////////////////////

// MainFrame
#define		BTN_GETROOT			10000			//选择起始目录
#define		BTN_START_SEARCH	10001			//开始搜索按钮
#define		LIST_RESULT			10002			//搜索结果列表

// SearchingDlg
#define		DLG_SEARCHDLG		10003			//搜索对话框
#define		BTN_PAUSECONTINUE	10004			//暂停/继续按钮
#define		BTN_STOPEXIT		10005			//停止/退出

// SearchingDlg - wxTimer
#define		TMR_REDRAW_UI		10006			//定时重绘UI


// ThreadWork
#define		VIR_BTN_DONE		10007			//通知UI线程完成


// wxMenu
#define		MENU_OPEN			10008			//打开文件
#define		MENU_PLACE			10009			//打开所在目录
#define		MENU_SAVEAS			10010			//另存为...
#define		MENU_DELETE			10011			//删除文件
#define		MENU_ABOUT			10012			//关于软件