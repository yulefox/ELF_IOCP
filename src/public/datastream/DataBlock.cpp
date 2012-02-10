// =============================================================================
/**
 *  file: DataBlock.cpp
 *
 *  Brief:�й̶���С���ڴ�죬��̬�������ݿ�Ļ���������
 *
 *  Authtor:wangqiao
 *
 *	Date:2007-6-13
 */
// =============================================================================
#include "DataBlock.h"

CDataBlock::CDataBlock(long maxsize)
:m_nMaxSize(maxsize)
, m_nCurSize(0)
, m_bInitData(false)
{
	m_pBase = new uchar[maxsize];
	if (NULL == m_pBase)
	{
		LogWarn(ROOT_MODULE, "�ں���CDataBlock::CDataBlock(...), �����ڴ����");
	}
}

CDataBlock::~CDataBlock(void)
{
	SAFE_DELETE_ARRAY(m_pBase);
}

void CDataBlock::SetCurSize(long lSize)
{
	m_nCurSize = (lSize > 0 && lSize <= m_nMaxSize) ? lSize : 0;
}

/*
* ʹ���ڴ�ع���Ĵ���

CDataBlock::CDataBlock(long maxsize)
:m_nMaxSize(maxsize)
, m_nCurSize(0)
, m_bInitData(false)
{
m_pBase = (uchar*)M_ALLOC(m_nMaxSize);
if (NULL == m_pBase)
{
LogTrace(ROOT_MODULE, "�ں���CDataBlock::CDataBlock(...), �����ڴ����");
}
}

CDataBlock::CDataBlock(void *maxsize)
:m_nMaxSize((long)maxsize)
, m_nCurSize(0)
, m_bInitData(false)
{
m_pBase = (uchar*)M_ALLOC(m_nMaxSize);
if (NULL == m_pBase)
{
LogTrace(ROOT_MODULE, "�ں���CDataBlock::CDataBlock(...), �����ڴ����");
}
}

CDataBlock::~CDataBlock(void)
{
M_FREE(m_pBase, m_nMaxSize);
}

void CDataBlock::SetCurSize(long lSize)
{
m_nCurSize = (lSize > 0 && lSize <= m_nMaxSize) ? lSize : 0;
}
*/
