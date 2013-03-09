#include "KrtApplication.h"
#include "KrtThreadWork.h"
#include "KrtConstant.h"

#include "wx/regex.h"

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
			wxMessageBox( _T("目录路径错误!") );
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
				if( MatchTheFile( tempPath ) )			//按参数匹配该文件
				{
					resultItems.Add( tempPath );
					lFit++;
				}
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


//////////////////////////////////////////////////////////////////////////
//检索入口

bool ThreadWork::MatchTheFile( wxString &path )
{
	if( parItems[5] == _T("0") )	//普通匹配
	{
		if( parItems[2] == _T("1") )			//普通方式匹配文件名
			if( !matchFileName( path ) )
				return false;
	}

	if( parItems[5] == _T("1") )	//正则匹配
	{
		if( parItems[2] == _T("1") )			//正则方式匹配文件名
			if( !regexMatchFileName( path ) )
				return false;
	}

	if( parItems[7] == _T("0") )			//过滤以上扩展名
		if( !unfitExtendName( path ) )
			return false;

	if( parItems[7] == _T("1") )			//仅搜索以上扩展名
		if( !fitExtendName( path ) )
			return false;

	return true;
}

//普通匹配文件名
bool ThreadWork::matchFileName( wxString &path )
{
	if( wxFileNameFromPath( path ).Find(parItems[1]) != wxNOT_FOUND )
		return true;
	
	return false;
}

///正则方式匹配文件名
bool ThreadWork::regexMatchFileName( wxString &path )
{
	
	wxRegEx re( parItems[1], wxRE_ADVANCED );
	if(  !re.IsValid() )
		return false;
	if( re.Matches( wxFileNameFromPath( path ) ) )
		return true;
	
	return false;
}

//仅过滤扩展名
bool ThreadWork::unfitExtendName( wxString &path )
{
	wxString extName;	wxString ret;	wxString par = parItems[6];
	wxSplitPath( path, NULL, NULL, &extName );

	wxRegEx re( "\\w\\S*", wxRE_ADVANCED  );
	while( re.Matches( par ) )
	{
		ret = re.GetMatch( par );
		if( ret == extName )
			return false;
		par.Replace( ret, _T(""), false );
	}

	return true;
}

//仅搜索扩展名
bool ThreadWork::fitExtendName( wxString &path )
{
	wxString extName;	wxString ret;	wxString par = parItems[6];
	wxSplitPath( path, NULL, NULL, &extName );

	wxRegEx re( "\\w\\S*", wxRE_ADVANCED  );
	while( re.Matches( par ) )
	{
		ret = re.GetMatch( par );
		if( ret == extName )
			return true;
		par.Replace( ret, _T(""), false );
	}

	return false;
}