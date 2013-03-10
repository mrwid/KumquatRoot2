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
		/* ��·��Ĭ��Ϊ��ǰ�ļ���
		if( (dirItems[0].Find("\\") == -1) && (dirItems[0].Find('/') == -1) )
		{
			dirItems.RemoveAt(0);
			wxMessageBox( _T("��ʼ·������Ϊ��!"), _T("����"), wxOK|wxICON_INFORMATION );
			continue;
		}
		*/
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
				if( MatchTheFile( tempPath ) )			//������ƥ����ļ�
				{
					resultItems.Add( tempPath );
					lFit++;
				}
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


//////////////////////////////////////////////////////////////////////////
//��ȡ�ļ�����
void ThreadWork::readFileData( wxString &path, wxString &data )
{
	wxFFile f( path, "rb" );
	if( !f.IsOpened() )
		return;

	wxChar *chr = new wxChar;
	unsigned long int i = 1;
	unsigned long int fileLength = f.Length();
	for( i; i <= fileLength; i++ )
	{
		f.Read( chr, 1 );
		if( *chr != 0 )
			data.Append( *chr );
		else
			break;
		f.Seek( i );
	}
}

//////////////////////////////////////////////////////////////////////////
//�������
bool ThreadWork::MatchTheFile( wxString &path )
{
	if( parItems[5] == _T("0") )	//��ͨƥ��
	{
		if( parItems[2] == _T("1") )			//��ͨ��ʽƥ���ļ���
			if( !matchFileName( path ) )
				return false;

		if( parItems[4] == _T("1") )			//��ͨ��ʽƥ���ļ�����
			if( ! matchFileCont( path ) )
				return false;
	}

	if( parItems[5] == _T("1") )	//����ƥ��
	{
		if( parItems[2] == _T("1") )			//����ʽƥ���ļ���
			if( !regexMatchFileName( path ) )
				return false;

		if( parItems[4] == _T("1") )			//����ʽƥ���ļ�����
			if( !regexMatchFileCont( path ) )
				return false;
	}

	if( parItems[7] == _T("0") )			//����������չ��
		if( !unfitExtendName( path ) )
			return false;

	if( parItems[7] == _T("1") )			//������������չ��
		if( !fitExtendName( path ) )
			return false;

	return true;
}


//////////////////////////////////////////////////////////////////////////

//��ͨƥ���ļ���
bool ThreadWork::matchFileName( wxString &path )
{
	if( wxFileNameFromPath( path ).Find(parItems[1]) != wxNOT_FOUND )
		return true;
	
	return false;
}

///����ʽƥ���ļ���
bool ThreadWork::regexMatchFileName( wxString &path )
{
	
	wxRegEx re( parItems[1], wxRE_ADVANCED );
	if(  !re.IsValid() )
		return false;
	if( re.Matches( wxFileNameFromPath( path ) ) )
		return true;
	
	return false;
}

//��������չ��
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

//��ͨ��ʽƥ���ļ�����
bool ThreadWork::matchFileCont( wxString &path )
{
	wxString *cont = new wxString;
	readFileData( path, *cont );
	if( cont->Find( parItems[3] ) != wxNOT_FOUND )
	{
		cont->Clear();
		return true;
	}
	cont->Clear();
	return false;
}

//����ʽƥ���ļ�����
bool ThreadWork::regexMatchFileCont( wxString &path )
{
	wxString *cont = new wxString;
	readFileData( path, *cont );
	wxRegEx re( parItems[3], wxRE_ADVANCED );

	if( !re.IsValid() )
		return false;
	
	if( re.Matches( *cont ) )
	{
		cont->Clear();
		return true;
	}
	cont->Clear();
	return false;
}

//��������չ��
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