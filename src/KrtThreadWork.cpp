#include "KrtApplication.h"
#include "KrtThreadWork.h"
#include "KrtConstant.h"

//////////////////////////////////////////////////////////////////////////

ThreadWork::ThreadWork(
	const wxArrayString &par,
	wxString &currentFile,
	unsigned long &totalNum,
	unsigned long &fitNum,
	wxArrayString &res,
	wxWindow *parent,
	bool &thread_stop
):	parItems(par),
	current(currentFile),
	lTotal(totalNum),
	lFit(fitNum),
	resultItems(res),
	wnd(parent),
	threadstop( thread_stop )
{
	;
}

void *ThreadWork::Entry()
{
	wxArrayString dirItems;					//目录队列
	dirItems.Add( parItems[0] );			//将待遍历的目录路径添加到目录队列中

	wxString filename;		bool cont;		wxString tempPath;
	while( dirItems.GetCount() && ( !threadstop ) )			//当目录队列不为空时执行
	{
		if( (dirItems[0].Find("\\") == -1) && (dirItems[0].Find('/') == -1) )
		{
			dirItems.RemoveAt(0);
			wxMessageBox( _T("路径问题") );
			continue;
		}
		wxDir dir( dirItems[0] );			//打开队列前端目录路径
		if( !dir.IsOpened() )
		{
			wxMessageBox( _T("无法打开该目录!"), _T("错误"), wxOK | wxICON_INFORMATION );
			return NULL;
		}
		
		cont = dir.GetFirst( &filename );						//获取首个文件
		while ( cont )
		{
			tempPath = dirItems[0] + "\\" + filename;			//合成 filename 的完整路径
			if( dir.Exists( tempPath ) )			//判断 tempPath 是否为目录
				dirItems.Add( tempPath );			//为目录时则添加到目录队列
			else
			{
				resultItems.Add( tempPath );
				current = tempPath;
				lTotal++;
			}
			cont = dir.GetNext(&filename);			//获取下一个文件
		}
		dirItems.RemoveAt(0);				//当前目录遍历完成后将其从目录队列中删除
	}

	if( !threadstop )
	{
		wxCommandEvent event( wxEVT_COMMAND_BUTTON_CLICKED, VIR_BTN_DONE );
		wxPostEvent( wnd->GetEventHandler(), event );
	}
	return NULL;
}
