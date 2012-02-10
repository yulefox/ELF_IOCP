
// =============================================================================
/**
 *  file: DataBlockWriteRead.h
 *
 *  Brief:������һ�����ݿ��д����
 *
 *  Authtor:wangqiao
 *
 *	Date:2008-11-21
 */
// =============================================================================

#ifndef __DATABLOCKSET_WRITEREAD__H__
#define __DATABLOCKSET_WRITEREAD__H__

#pragma once

class CDataBlock;
class CDataBlockAllocator;
class CGUID;
struct tagDBOpParam;

// ������һ��д���ݿ�ļ���
typedef struct tagDataBlockWriteSet
{
	typedef vector<CDataBlock*>::iterator itDataSet;
	vector<CDataBlock*>* pDataSet;

	// ���ݿ������
	CDataBlockAllocator* pDBAllocator;
	// ��ǰ���ݿ鼯�ϲ�������
	tagDBOpParam* pDBWriteParam;
	ulong *pToltalSize;

	tagDataBlockWriteSet()
		:pDBAllocator(NULL)
		, pDBWriteParam(NULL)
		, pDataSet(NULL)
		, pToltalSize(NULL)
	{
	}

	void Initial(CDataBlockAllocator* pAllocator,
							tagDBOpParam* pWriteParam,
							vector<CDataBlock*>* pSet,
							ulong* pSize)
	{
		pDBAllocator = pAllocator;
		pDBWriteParam = pWriteParam;
		pDataSet = pSet;
		pToltalSize =pSize;
	}

	void AddToByteArray(void* pSource, long n);	// �������
	void AddToByteArray(const char* pStr);
	void AddToByteArray(const CGUID& guid);
	inline void AddToByteArray(long l)
	{
		AddBuff((uchar*)&l, sizeof(long));
	}
	inline void AddToByteArray(short l)
	{
		AddBuff((uchar*)&l, sizeof(short));
	}
	inline void AddToByteArray(char l)
	{
		AddBuff((uchar*)&l, sizeof(char));
	}
	inline void AddToByteArray(float l)
	{
		AddBuff((uchar*)&l, sizeof(float));
	}
	inline void AddToByteArray(double l)
	{
		AddBuff((uchar*)&l, sizeof(double));
	}
	inline void AddToByteArray(uchar l)
	{
		AddBuff((uchar*)&l, sizeof(uchar));
	}
	inline void AddToByteArray(ushort l)
	{
		AddBuff((uchar*)&l, sizeof(ushort));
	}
	inline void AddToByteArray(ulong l)
	{
		AddBuff((uchar*)&l, sizeof(ulong));
	}
private:
	void AddBuff(uchar* pBuf, long size);
	void AddWrDataBlock();
}DBWriteSet;


typedef struct tagDataBlockReadSet
{
	typedef vector<CDataBlock*>::iterator itDataSet;
	vector<CDataBlock*>* pDataSet;

	// ��ǰ���ݿ鼯�ϲ�������
	tagDBOpParam* pDBReadParam;

	tagDataBlockReadSet()
		:pDBReadParam(NULL)
		, pDataSet(NULL)
	{
	}
	void Initial(tagDBOpParam* pReadParam,
						vector<CDataBlock*>* pSet)
	{
		pDBReadParam = pReadParam;
		pDataSet = pSet;
	}

	void* GetBufferFromByteArray(void* pBuf, long lLen);
	char* GetStringFromByteArray(char* pStr, long lMaxLen);
	bool  GetBufferFromByteArray(CGUID& guid);

	// ��CByteArray��ȡlong
	inline long GetLongFromByteArray()
	{
		long l = 0;
		GetBuff((uchar*)&l, sizeof(long));
		return l;
	}

	// ��CByteArray��ȡshort
	inline short GetShortFromByteArray()
	{
		short l = 0;
		GetBuff((uchar*)&l, sizeof(short));
		return l;
	}

	// ��CByteArray��ȡchar
	inline char GetCharFromByteArray()
	{
		char l  = 0;
		GetBuff((uchar*)&l, sizeof(char));
		return l;
	}

	inline float GetFloatFromByteArray()
	{
		float l = 0;
		GetBuff((uchar*)&l, sizeof(float));
		return l;
	}

	inline double GetDoubleFromByteArray()
	{
		double l = 0;
		GetBuff((uchar*)&l, sizeof(double));
		return l;
	}

	inline uchar GetByteFromByteArray()
	{
		uchar l = 0;
		GetBuff((uchar*)&l, sizeof(uchar));
		return l;
	}

	inline ushort GetWordFromByteArray()
	{
		ushort l= 0;
		GetBuff((uchar*)&l, sizeof(ushort));
		return l;
	}

	inline ulong GetDwordFromByteArray()
	{
		ulong l = 0;
		GetBuff((uchar*)&l, sizeof(ulong));
		return l;
	}

private:
	void* GetBuff(uchar* pByte, long size);
	void AddRdDataBlock();

}DBReadSet;

#endif
