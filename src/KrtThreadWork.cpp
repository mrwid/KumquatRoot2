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
	wxArrayString dirItems;					//Ŀ¼����
	dirItems.Add( parItems[0] );			//����������Ŀ¼·����ӵ�Ŀ¼������

	wxString filename;		bool cont;		wxString tempPath;
	while( dirItems.GetCount() && ( !threadstop ) )			//��Ŀ¼���в�Ϊ��ʱִ��
	{
		if( (dirItems[0].Find("\\") == -1) && (dirItems[0].Find('/') == -1) )
		{
			dirItems.RemoveAt(0);
			wxMessageBox( _T("·������") );
			continue;
		}
		wxDir dir( dirItems[0] );			//�򿪶���ǰ��Ŀ¼·��
		if( !dir.IsOpened() )
		{
			wxMessageBox( _T("�޷��򿪸�Ŀ¼!"), _T("����"), wxOK | wxICON_INFORMATION );
			return NULL;
		}
		
		cont = dir.GetFirst( &filename );						//��ȡ�׸��ļ�
		while ( cont )
		{
			tempPath = dirItems[0] + "\\" + filename;			//�ϳ� filename ������·��
			if( dir.Exists( tempPath ) )			//�ж� tempPath �Ƿ�ΪĿ¼
				dirItems.Add( tempPath );			//ΪĿ¼ʱ����ӵ�Ŀ¼����
			else
			{
				resultItems.Add( tempPath );
				current = tempPath;
				lTotal++;
			}
			cont = dir.GetNext(&filename);			//��ȡ��һ���ļ�
		}
		dirItems.RemoveAt(0);				//��ǰĿ¼������ɺ����Ŀ¼������ɾ��
	}

	if( !threadstop )
	{
		wxCommandEvent event( wxEVT_COMMAND_BUTTON_CLICKED, VIR_BTN_DONE );
		wxPostEvent( wnd->GetEventHandler(), event );
	}
	return NULL;
}
