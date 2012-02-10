/**
 * @file GUID.h
 * CGUID�� ���� ֱ��ת��GUID�ṹ��
 * ����ĳ������ʱ����ʼΪ0��ͨ������Fill()��Ա��������GUID
 * ������=�� == ��
 * 2006/10/10 by bugs
 * ʹ�ø��� �����ȵ���Initialize��ʼCOM
 * @todo ��װ���ֽӿڼ���, ����ʹ�� C++.
 */

#ifndef ELF_DEF_GUID_H
#define ELF_DEF_GUID_H

#pragma once

#include <hash_map>
#include <string>
#include "type.h"

using namespace stdext;

class CGUID
{
private:
	ulong  Data1;
	ushort Data2;
	ushort Data3;
	uchar  Data4[8];

	friend class hash_guid_compare;

public:
	static void Initialize();
	static void Uninitialize();

	static bool CreateGUID(CGUID &guid);
	static CGUID GUID_INVALID;

	CGUID(void)
	{
		memset(this, 0, sizeof(CGUID));
	}

	explicit CGUID(const char* strGuid);
	~CGUID(void)
	{
	}

	CGUID & operator = (const CGUID & guid)
	{
		if (&guid != this)
			memcpy(this, &guid, sizeof(CGUID));
		return *this;
	}

	inline bool operator == (const CGUID & guid) const
	{
		return (((ulong *) this)[0] == ((ulong *) &guid)[0] &&
			  ((ulong *) this)[1] == ((ulong *) &guid)[1] &&
			  ((ulong *) this)[2] == ((ulong *) &guid)[2] &&
			  ((ulong *) this)[3] == ((ulong *) &guid)[3]);
	}

	bool operator != (const CGUID & guid) const
	{
		return !(operator ==(guid));
	}

	bool operator < (const CGUID& guid) const
	{
		if (((ulong *)this)[0] < ((ulong *)&guid)[0])
			return true;
		else if (((ulong *)this)[0] == ((ulong *)&guid)[0])
		{
			if (((ulong *)this)[1] < ((ulong *)&guid)[1])
				return true;
			else if (((ulong *)this)[1] == ((ulong *)&guid)[1])
			{
				if (((ulong *)this)[2] < ((ulong *)&guid)[2])
					return true;
				else if (((ulong *)this)[2] == ((ulong *)&guid)[2])
					if (((ulong *)this)[3] < ((ulong *)&guid)[3])
						return true;
			}
		}
		return false;
	}

	bool CopyConstrucutureCalFunc(const char* szValue, long& retValue);
	// strGuid at least 36
	bool tostring(char * strGuid) const
	{
		if (strGuid == 0)	return false;
		sprintf(strGuid, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		Data1, Data2, Data3, Data4[0], Data4[1],
		Data4[2], Data4[3], Data4[4], Data4[5], Data4[6], Data4[7]);
		return true;
	}

	const char *tostring() const;

	bool IsInvalid()
	{
		if (memcmp(this, &GUID_INVALID, sizeof(CGUID)))
			return false;
		return true;
	}
};

class guid_compare
{
public:
	inline bool operator()(const CGUID& Key1, const CGUID& Key2) const
	{
		if (Key1 < Key2)
			return true;
		return false;
	}

};

class hash_guid_compare:public hash_compare<CGUID, guid_compare>
{
private:
	guid_compare	comp;
public:
	// calculate hash number
	size_t operator()(const CGUID& Key) const
	{
		return ((ulong *) &Key)[0] + ((ulong *) &Key)[1] +
			((ulong *) &Key)[2] + ((ulong *) &Key)[3];
	}
	//less operator
	bool operator()(const CGUID& _Key1, const CGUID& _Key2) const
	{
		return comp(_Key1, _Key2);
	}
};

const CGUID NULL_GUID = CGUID::GUID_INVALID;

#endif /* !ELF_DEF_GUID_H */
