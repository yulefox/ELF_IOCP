// =============================================================================
/**
 *  file: DataBlockAllocator.h
 *
 *  Brief:�̶���С���ڴ�������
 *
 *  Authtor:wangqiao
 *
 *	Date:2007-6-13
 */
// =============================================================================

#ifndef __DATABLOCK_ALLOCATOR__H__
#define __DATABLOCK_ALLOCATOR__H__

#pragma once

#include "public/def/def.h"

class CDataBlock;
class CGUID;

struct tagDBOpParam
{
	// ��ǰ��д���ݿ���
	ulong	nCurNum;
	// ��ǰ��д���ݿ�Ĵ�С
	ulong	nCurDBSize;
	// ��ǰ��д���ݵ�λ��
	ulong	nCurPos;
	// ��ǰ��д���ݿ��ָ��
	uchar	*pDBPtr;
};

class CDataBlockAllocator
{
public:
	CDataBlockAllocator(int nDBNum, int nDBSize, int bIniShareDB = false);
public:
	~CDataBlockAllocator(void);

private:
	typedef list<CDataBlock*>	FreeDataBlocks;
	typedef list<CDataBlock*>::iterator itFreeDB;

	FreeDataBlocks m_FreeDataBlocks;
	CRITICAL_SECTION m_CSFreeDB;
	int	m_nMaxDBNum;
	const int	m_nDBSize;
	// �����߼�����ʱʹ�õ����ݿ�
	// �������࣬ʹ�ýϴ�����ݿ���������ִ�С������
	typedef multimap<long, uchar*>	MMapShareDB;
	typedef pair <long, uchar*> ShareDBPair;
	typedef multimap<long, uchar*>::iterator itShareDB;
	MMapShareDB m_ShareDataBlocks;

	typedef map<uchar*, long>	mapAllocedRecord;
	typedef map<uchar*, long>::iterator itAllocR;
	mapAllocedRecord	m_AllocedShareDB;
	// �������������ݿ����
	map<long, long>	m_MapTest;
private:
	void Initial(int bIniShareDB = false);
	void Release();

public:
	CDataBlock*	AllocDB(long lTestFlag=0);
	void FreeDB(CDataBlock*);

	uchar* AllockShareDB(long lSize);
	void FreeShareDB(uchar* pData);

	void PutAllocInfo(const char* pszFileName);
};

#endif
