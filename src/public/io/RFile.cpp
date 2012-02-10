//////////////////////////////////////////////////////////////////////////
//RFile.cpp, ��Դ�ļ���
//Fun:��Դ�ļ�����, �����д����
//Author:Joe
//Create Time:2004.11.26
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "rfile.h"
#include "ClientResource.h"
#include "FilesInfo.h"
#include "Package.h"
#include "../ziplib/lzo1x.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRFile::CRFile(const char* pszFileName, uchar* pData, ulong dwSize)
:m_pData(pData)
, m_dwSize(dwSize)
, m_dwPos(0)
{
	strncpy(m_pszFileName, pszFileName, MAX_PATH);
}

CRFile::CRFile(const char* pszFileName, FILE* pfile)
:m_pData(NULL)
, m_dwSize(0)
, m_dwPos(0)
{
	fseek(pfile, 0, SEEK_END);
	m_dwSize = ftell(pfile);
	fseek(pfile, 0, SEEK_SET);
	m_pData = new uchar[m_dwSize+1];
	memset(m_pData, 0, m_dwSize);
	size_t nNumRead = fread(m_pData, m_dwSize, 1, pfile);
	m_pData[m_dwSize] = '\0';
	if (nNumRead != 1)
	{
		LogWarn(ROOT_MODULE, "��ȡ�ļ�(Name:%s, size:%d)����.", pszFileName, m_dwSize);
	}
	strncpy(m_pszFileName, pszFileName, MAX_PATH);
}

CRFile::~CRFile(void)
{
	if (m_pData)
	{
		delete []m_pData;
	}
}

// ���ļ����ݵ�������
bool CRFile::ReadData(void* pBuf, ulong dwSize)
{
	assert(pBuf);
	// �����ļ�
	if (m_pData)
	{
		if (m_dwPos+dwSize>m_dwSize)
			return false;
		memcpy(pBuf, m_pData+m_dwPos, dwSize);
		m_dwPos +=dwSize;
		return true;
	}
	return false;
}

// �����ݵ�stringstream��
bool CRFile::ReadToStream(stringstream& stream)
{
	// �����ļ�
	if (m_pData)
	{
		stream << m_pData;
		//stream.write((char*)m_pData, m_dwSize);
		//stream.put((char*)m_pData, m_dwSize+1);
		stream.seekg(0, std::ios_base::beg);
		m_dwPos+=m_dwSize;
		return true;
	}
	return false;
}

// ��int��������
bool CRFile::ReadData(int& nValue)
{
	return ReadData(&nValue, sizeof(int));
}

// ��ulong��������
bool CRFile::ReadData(ulong& nValue)
{
	return ReadData(&nValue, sizeof(ulong));
}

bool CRFile::ReadChar(uchar &c)
{
	return ReadData(&c, sizeof(uchar));
}

char * CRFile::ReadLine(char * pszLineBuffer, int iBufferLen)
{
	int  iLineLen = 0;
	bool bCount = false;

	ZeroMemory(pszLineBuffer, iBufferLen);
	// �ӵ�ǰΪֹ��ȡ�ַ�
	while (m_dwPos < m_dwSize && iLineLen < iBufferLen - 1)
	{
		char c = m_pData[m_dwPos++];
		if ('\r' == c)
		{
			if (m_dwPos+1 < m_dwSize)
			{
				c = m_pData[m_dwPos+1];
				if ('\n' == c)
				{
					m_dwPos++;
				}
			}
			break;
		}
		else
			if ('\n' == c)
			{
				break;
			}

			pszLineBuffer[iLineLen++] = c;

	}
	return pszLineBuffer;
}

ulong  CRFile::Seek(int iPosition, int iOrigin)
{
	ulong dwCurPosition = m_dwPos;
	switch (iOrigin)
	{
	case SEEK_CUR:
		m_dwPos +=iPosition;
		break;
	case SEEK_END:
		assert(iPosition<0);
		assert(abs(iPosition)< (int)m_dwSize);
		m_dwPos  = m_dwSize + iPosition;// ����Ϊ����
		break;
	case SEEK_SET:
	default:
		m_dwPos= iPosition;
	}
	return dwCurPosition;
}

////////////////////////////////////////////////
// ���ܣ�ȡ���ļ�·��
///////////////////////////////////////////////
// ����"/" �� "\\"
char *CRFile::GetFilePath(const char *szFileName, char* szOutput)
{
	int iLen=lstrlen(szFileName);
	strcpy(szOutput, szFileName);

	for (int i = iLen-1; i >= 0; i--)
	{
		szOutput[i]=0;

		if (szFileName[i] == '\\' || szFileName[i] == '/')
			break;
	}
	if (szOutput[0] == 0)
	{
		szOutput[0] = '.';
		szOutput[1] = 0;
	}

	return szOutput;
}

//// �����·�����ļ�, ������rfClose�ر�
//CRFile* rfOpen(const char* strFileName, CClientResource* pClientResource)
// {
// 	CRFile* rfile=NULL;
// 	ulong dwSize = 0;
//
// 	if (pClientResource == NULL)
// 		pClientResource = GetDefaultClientResource();
//
// 	if (pClientResource)
// 	{
// 		string strName(strFileName);
// 		CheckRFileStr(strName);
// 		// ��Դ��Ϣ�б����и��ļ�
// 		tagFileInfo* ptagFileInfo =
// 			pClientResource->GetFilesInfo()->GetFileInfoByText(strName);
// 		if (ptagFileInfo)
// 		{
// 			// �ڰ���
// 			if (!ENABLEBIT(ptagFileInfo->dwPackageType, NOPACK))
// 			{
// 				CPackage *pPackage = pClientResource->GetPackage(ptagFileInfo->dwPackageType);
// 				if (pPackage)
// 				{
// 					dwSize = pPackage->GetFileSize(strName.c_str());
// 					if (dwSize>0)
// 					{
// 						uchar* pBuf = new uchar[dwSize+1];
// 						ulong dwCrc32, dwCompress, dwOrginSize, dwValidSize;
// 						pPackage->ExtractToBuf(strName.c_str(),
// 							pBuf, dwSize, dwCrc32, dwCompress, dwOrginSize, dwValidSize);
//
// 						// ��ѹ
// 						if (!ENABLEBIT(dwCompress, NOCOMPRESS))
// 						{
// 							ulong dwOutSize = ptagFileInfo->dwOrginSize+1;
// 							uchar* pOutBuf = new uchar[dwOutSize];
// 							if (ENABLEBIT(dwCompress, 0x4))
// 								DeCompress(pBuf, dwSize, pOutBuf, &dwOutSize);
// 							else
// 								DeCompressData(pBuf, dwSize, pOutBuf, &dwOutSize);
//
// 							pOutBuf[dwOutSize]='\0';
// 							rfile = new CRFile(pOutBuf, dwOutSize);
// 							delete[] pBuf;
// 						}
// 						else
// 						{
// 							pBuf[dwSize]='\0';
// 							rfile = new CRFile(pBuf, dwSize);
// 						}
// 					}
// 				}
// 			}
// 			// û���ڰ��е�����
// 			else
// 			{
// 				string strTempt(pClientResource->GetCurFolder());
// 				strTempt +=strName;
//
// 				FILE* pf = fopen(strTempt.c_str(), "rb");
// 				if (pf)
// 				{
// 					fseek(pf, 0, SEEK_END);
// 					dwSize = ftell(pf);
// 					fseek(pf, 0, SEEK_SET);
// 					rfile = new CRFile(pf, dwSize);
// 				}
// 			}
// 		}
// 		// ���ⲿ���ļ�
// 		else
// 		{
// 			string strTempt(pClientResource->GetCurFolder());
// 			strTempt +=strName;
//
// 			FILE* pf = fopen(strTempt.c_str(), "rb");
// 			if (pf)
// 			{
// 				fseek(pf, 0, SEEK_END);
// 				dwSize = ftell(pf);
// 				fseek(pf, 0, SEEK_SET);
// 				rfile = new CRFile(pf, dwSize);
// 			}
// 		}
// 	}
// 	return rfile;
// }
//
//// �ر��ļ����
//void rfClose(CRFile* rfile)
// {
// 	if (rfile)
// 	{
// 		delete rfile;
// 	}
// }

void CheckRFileStr(string& strFileName)
{
	static string strReplace("\\");
	static string strEmpty("");
	char *newstring = _strlwr(_strdup(strFileName.c_str()));
	strFileName = newstring;
	free(newstring);

    basic_string <char>::size_type   IRes1, IRes2;
    const basic_string <char>::size_type nPos = -1;
	IRes1  = strFileName.find_first_of("/");
	while (nPos!= IRes1)
	{
		strFileName.replace(IRes1, 1, strReplace);
		IRes2 = strFileName.find_first_of("/");
		if (IRes1 == IRes2-1)
		{
			strFileName.replace(IRes2, 1, strEmpty);
			IRes2 = strFileName.find_first_of("/");
		}
		else
			IRes1 = IRes2;
	}

	if (strFileName.find_first_of("\\") != 0)
	{
		strFileName="\\"+strFileName;
	}
}


// ȱʡ�Ŀͻ�����Դ
CClientResource* g_pDefaultClientResource = NULL;

CClientResource* GetDefaultClientResource()
{
	return g_pDefaultClientResource;
}

void SetDefaultClientResource(CClientResource* p)
{
	g_pDefaultClientResource = p;
}
