// =============================================================================
/**
 *  file: DataBlock.h
 *
 *  Brief:�й̶���С���ڴ�죬��̬�������ݿ�Ļ���������
 *
 *  Authtor:wangqiao
 *
 *	Date:2007-6-13
 */
// =============================================================================
#ifndef __DATABLOCK__H__
#define __DATABLOCK__H__
#pragma once

class CDataBlock
{
public:
	CDataBlock(long maxsize);
	CDataBlock(void *maxsize);

	long m_lTestFlag;
public:
	virtual ~CDataBlock(void);

private:
	// �Ƿ��ǳ�ʼ������
	bool m_bInitData;
	// ������ʼ��ַ
	uchar *m_pBase;

	// ��ǰ���ݿ��С
	long m_nCurSize;
	// �����ݿ��С
	const long m_nMaxSize;
public:
	uchar *Base()	{return m_pBase;}

	long GetCurSize()	{return m_nCurSize;}
	void SetCurSize(long lSize);

	long GetMaxSize()	{return m_nMaxSize;}

	void SetIsInitData(bool b)	{m_bInitData=b;}
	bool GetIsInitData()	{return m_bInitData;}
private:
  // ������Щ����
  CDataBlock &operator= (const CDataBlock &);
  CDataBlock (const CDataBlock &);
};

#endif
