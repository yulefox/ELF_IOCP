//////////////////////////////////////////////////////////////////////////
//RFile.h, ��Դ�ļ���
//Fun:��Դ�ļ�����, �����д����
//Author:Joe
//Create Time:2004.11.26
//////////////////////////////////////////////////////////////////////////
#pragma once

class CClientResource;
#include "../DefType.h"
class CRFile
{
public:
	CRFile(const char* pszFileName, uchar* pData, ulong dwSize);
	CRFile(const char* pszFileName, FILE* pfile);
	~CRFile(void);
private:
	uchar*		m_pData;			// ����
	ulong		m_dwSize;
	ulong		m_dwPos;

	// �ļ���
	char m_pszFileName[MAX_PATH];

public:
	const char* GetFileName()	{return m_pszFileName;}
	ulong GetPosition()	{return m_dwPos;}
	void SetPosition(ulong dwPosition) { m_dwPos = dwPosition;}

	uchar* GetData()	{return m_pData;}
	long GetDatalen()	{return m_dwSize;}					// �������ݳ���
	bool ReadData(void* pBuf, ulong dwSize);				// �����ݵ�������
	bool ReadData(int& nValue);								// ��ini��������
	bool ReadData(ulong& nValue);							// ��ulong��������
	bool ReadChar(uchar &c);
	char * ReadLine(char * pszLineBuffer, int iBufferLen);
	bool ReadToStream(stringstream& stream);				// �����ݵ�stringstream��

	ulong  Seek(int iPosition, int iOrigin = 0);

	static char *GetFilePath(const char *szFileName, char* szOutput);// ����"/" �� "\\"
};

//// ����Դ�ļ���ȫ�ֺ���
//CRFile* rfOpen(const char* strFileName, CClientResource* pClientResource=NULL);	// ���ļ�����, ����rfClose�ر�
//void rfClose(CRFile* rfile);						// �ر�CRFile�ļ����

// ʹ�ú�����ļ�·�����
void CheckRFileStr(string& strFileName);


// ȱʡ�Ŀͻ�����Դ
extern CClientResource* g_pDefaultClientResource;
CClientResource* GetDefaultClientResource();
void SetDefaultClientResource(CClientResource* p);
