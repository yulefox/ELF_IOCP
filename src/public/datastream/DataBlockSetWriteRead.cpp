
// =============================================================================
/**
 *  file: DataBlockWriteRead.cpp
 *
 *  Brief:������һ�����ݿ��д����
 *
 *  Authtor:wangqiao
 *
 *	Date:2008-11-21
 */
// =============================================================================


#include "DataBlockSetWriteRead.h"

#include "DataBlock.h"
#include "DataBlockAllocator.h"

	// �������
void tagDataBlockWriteSet::AddToByteArray(void* pSource, long n)
{
	//AddBuff((uchar*)&n, sizeof(long));
	AddBuff((uchar*)pSource, n);
}

void tagDataBlockWriteSet::AddToByteArray(const char* pStr)
{
	long size = lstrlen(pStr);
	AddBuff((uchar*)&size, sizeof(long));
	AddBuff((uchar*)pStr, size);
}

void tagDataBlockWriteSet::AddToByteArray(const CGUID& guid)
{
	long size = sizeof(CGUID);
	if (guid == CGUID::GUID_INVALID)
	{
		size = 0;
	}
	AddBuff((uchar*)&size, 1);
	AddBuff((uchar*)&guid, size);
}

void tagDataBlockWriteSet::AddBuff(uchar* pBuf, long size)
{
	long lTempSize = size;
	while (pDBWriteParam->pDBPtr != NULL && size > 0)
	{
		long minsize = min(size, (long)pDBWriteParam->nCurDBSize-(long)pDBWriteParam->nCurPos);
		memcpy(pDBWriteParam->pDBPtr+pDBWriteParam->nCurPos, pBuf, minsize);
		pDBWriteParam->nCurPos += minsize;
		(*pDataSet)[pDBWriteParam->nCurNum]->SetCurSize(pDBWriteParam->nCurPos);

		size -= minsize;
		pBuf += minsize;
		if (pDBWriteParam->nCurPos >= pDBWriteParam->nCurDBSize && size > 0)
		{
			AddWrDataBlock();
		}
	}
	(*pToltalSize) += lTempSize;
}
void tagDataBlockWriteSet::AddWrDataBlock()
{
	pDBWriteParam->nCurNum++;
	pDBWriteParam->nCurPos = 0;
	pDBWriteParam->nCurDBSize = 0;
	pDBWriteParam->pDBPtr = NULL;

	CDataBlock* pDB = pDBAllocator->AllocDB(2000);
	if (pDB == NULL)
	{
        LogWarn(ROOT_MODULE, "�ں���tagDataBlockWriteSet::AddWrDataBlock()�У� �������ݿ����");
		return;
	}
	pDataSet->push_back(pDB);
	pDBWriteParam->nCurDBSize = (*pDataSet)[pDBWriteParam->nCurNum]->GetMaxSize();
	pDBWriteParam->pDBPtr = (*pDataSet)[pDBWriteParam->nCurNum]->Base();
}



void* tagDataBlockReadSet::GetBufferFromByteArray(void* pBuf, long lLen)
{
	GetBuff((uchar*)pBuf, lLen);
	return pBuf;
}
char* tagDataBlockReadSet::GetStringFromByteArray(char* pStr, long lMaxLen)
{
	if (lMaxLen <= 1)	return NULL;
	long len = GetLongFromByteArray();
	if (len < 0)	len = 0;
	len = min(len, lMaxLen-1);
	GetBuff((uchar*)pStr, len);
	pStr[len] = '\0';
	return pStr;
}
bool  tagDataBlockReadSet::GetBufferFromByteArray(CGUID& guid)
{
	long size = 0;
	GetBuff((uchar*)&size, 1);
	if (size == 0)
	{
		guid = CGUID::GUID_INVALID;
		return false;
	}
	else
	{
		GetBuff((uchar*)&guid, sizeof(CGUID));
		return true;
	}
	return true;
}

void* tagDataBlockReadSet::GetBuff(uchar* pByte, long size)
{
	/*char str[1024];
	sprintf(str, "Get(...) ��ʼ!size:%d, ", size);
	PutStringToFile("Net", str);*/

	while (pDBReadParam->pDBPtr != NULL && size > 0)
	{
		if (pDBReadParam->nCurDBSize >= pDBReadParam->nCurPos)
		{
			long minsize = min(size, (long)pDBReadParam->nCurDBSize-(long)pDBReadParam->nCurPos);
			/*sprintf(str, "memcpy:Dest:%u, Source:%u, size:%d, m_nCurRdDBSize:%d, m_nCurRdPos:%d", pBuf, m_pRdDBPtr+m_nCurRdPos, minsize, m_nCurRdDBSize, m_nCurRdPos);
			PutStringToFile("Net", str);*/

			memcpy(pByte, pDBReadParam->pDBPtr+pDBReadParam->nCurPos, minsize);
			size -= minsize;
			pDBReadParam->nCurPos += minsize;
			pByte += minsize;
			if (pDBReadParam->nCurPos >= pDBReadParam->nCurDBSize)
				AddRdDataBlock();
		}
		else
		{
			size = 0;

            LogError(ROOT_MODULE, "�ں���tagDataBlockReadSet::GetBuff(()�У� �����ݳ���");
		}
	}
	/*PutStringToFile("Net", "Get(...) ����!");*/
	return pByte;
}
void tagDataBlockReadSet::AddRdDataBlock()
{
	pDBReadParam->nCurNum++;
	pDBReadParam->nCurPos = 0;
	pDBReadParam->nCurDBSize = 0;
	pDBReadParam->pDBPtr = NULL;
	if (pDBReadParam->nCurNum < pDataSet->size())
	{
		pDBReadParam->nCurDBSize = (*pDataSet)[pDBReadParam->nCurNum]->GetCurSize();
		pDBReadParam->pDBPtr = (*pDataSet)[pDBReadParam->nCurNum]->Base();
	}
}
