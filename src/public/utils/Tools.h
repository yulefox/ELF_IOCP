// ********************************************
// 	���ຯ��
// ********************************************
#ifndef ELF_UTILS_TOOLS_H
#define ELF_UTILS_TOOLS_H

#pragma once

#include "public/def.h"
#include "public/def/stl.h"
#include "public/def/type.h"
#include "public/def/wincrt.h"

//#define FLOATEQ(f1, f2) (abs((f1)-(f2)) < 0.001f)
//
/////  ����ģ��ֱ��Hash���ַ�����
//#define QuestRet(QuestID)     QuestID/1000*100
//
//#define PutDebugString    LogDebug
//#define PutTraceString    LogTrace
//#define PutErrorString    LogError
//
//static const float PI = 3.141592654f;
//static const float E = 1.0e-3f;

int random(int nMax);						// �����
//int Round(float f);							// ��������
//int Round(double f);						// ��������
//void Delay(long time);						// ��ʱ
//int GetFileLength(const char *name);		// ȡ�ļ�����
//bool CheckFile(const char *name);			// �ж��ļ��Ƿ����
//void ShowMessage(const char *msg, ...);		// ��ʾ��Ϣ
//void InitialDebugFileName(bool bIsTimed = false, bool bIsClear = true);	// �Ƿ񰴵�ǰʱ�������������ļ�
//const char* GetDebugFileName();
//bool OverloadFile(const char* filename, const char *msg);		// ����һ���ļ�����
//char *GetFilePath(const char *filename, char* out);	// ���ļ�����ȡ�ļ�·��
//char *GetFileName(const char *filename, char* out); // ���ļ�·������ȡ�ļ���
//char *GetFileExtName(const char *filename, char* out);	// ���ļ�����ȡ�ļ���չ��
//char *GetFileNameNoExt(const char* filename, char* out);    //�õ�ȥ���ļ�������չ������ִ�
//WCHAR* WChar(char *str);					//char to wchar
//char* Char(WCHAR* str);						//wchar to char
//void DeleteDirectory(const char* strDir);	// ɾ��Ŀ¼
//bool GetFileDialog(bool Load, const char* currentPath, char*, const char* strFilter="All Files\0*.*\0");	// ��ȡ�ļ�
//bool GetPathDialog(const char* strRoot, char*);					// ��ȡ·��
//void ReplaceLine(char* str);		// �滻STR�е�'\\'Ϊ'/';
//bool GetString(const char* sour, char* dest, int num);	// ��ȡһ�����ַ����еĵ�NUM�������ո�Ϊ���
//
//bool CreateDir(const char* dir);
void FindFile(const char* strFile, const char* strExt, list<string>* plistFileName);	// ��ȡ���е�ָ����չ�����ļ�
//const char *GetCurrentPath();	//��ȡ��ǰ����·��
//
//// ����ļ���Ϣ������ָ����Ŀ¼�±����ļ�, ���һ��������ʾ�Ƿ���ݵ�ǰϵͳʱ�����´����ļ���false�������룩
//void PutStrToFileSaveToDir(const char* dir, const char* filename, const char *msg, bool IsRePut=false);
//
//inline bool IsInRect(long x, long y, RECT& rect)
//{
//	if (x > rect.left && x < rect.right && y > rect.top && y < rect.bottom)
//	{
//		return true;
//	}
//	return false;
//}
//
//// �ж����������Ƿ��ཻ
//// ��Դ���ε�����һ�㱻Ŀ����ΰ����ˣ����ཻ
//inline bool IsInstersect(RECT sRect, RECT dRect)
//{
//	// ���������ν���:
//	// ���󽻼������Ͻ�����, �����������ε����Ͻ�����֮�нϴ��һ��
//	// ���󽻼������½�����, �����������ε����½�����֮�н�С��һ��
//	long  lx, ly, rx, ry;
//	// �ཻ��������Ͻ�����
//	lx = max(sRect.left, dRect.left);
//	ly = max(sRect.top, dRect.top);
//	// �ཻ��������½�����
//	rx = min(sRect.right, dRect.right);
//	ry = min(sRect.bottom, dRect.bottom);
//	// �ཻ����Ŀ�͸߶�����0��ʾ�ཻ
//	return ((rx - lx > 0) && (ry - ly > 0));
//}
//
//bool FormatMoneyNumber(char *str, const int size);// ��ʽ����Ǯ��ʾ, ÿ����֮���һ��", "
//
//template<class T>
//void QuickSort(T* a, int begin, int end);	// ��������
//
//long Distance(long sx, long sy, long dx, long dy);
//float Distance(float sx, float sy, float dx, float dy);
//long GetLineDir(long sx, long sy, long dx, long dy);		// ��ȡ��(sx, sy)��(dx, dy)�ķ���(0-7)
///***********************************************************************/
///*  zhaohang 2010-11-15 add*/
//long GetLineDir(float sx, float sy, float dx, float dy);
///***********************************************************************/
//float GetRadianDir(float sx, float sy, float dx, float dy, float dir = 0);
//// ͨ������õ��߶������е�
//long GetLinePointByDir(list<POINT>& listPos, long lX, long lY, long lDir, long lDistance, float offset = 0);
//// �õ�ͨ��Ŀ���������߶��ϵĵ�
//long GetLinePointToDest(list<POINT>& listPos, long lX, long lY, long lDestX, long lDestY, long lDistance, float offset = 0);
//// �õ�ͨ��Ŀ���������߶��ϵĵ�
//long GetLinePointToDest(list<POINT>& listPos, float fX, float fY, float fDestX, float fDestY, long lDistance, float offset = 0);
//struct fPoint
//{
//    float x;
//    float y;
//};
////��ȡ����Ŀ��������еĸ������꣬lDistace��ʾ����Ŀ���ľ���ΪĿ���
//long GetLinePointToDest(list<fPoint>& listPos, float fStartX, float fStartY, float fDestX, float fDestY, float fDistance = 0);
//
//// �õ�һ��Բ������е�
//long GetCircPoint(list<POINT>& listPos, long lCenterX, long lCenterY, long lRadius);
//// �õ�һ��������������е�
//long GetSquarePoint(list<POINT>& listPos, long lCenterX, long lCenterY, long lOffLen);
//// �õ�Դ��Ŀ��ֱ��һ��Դ��Զͬʱ��Ŀ������ĵ�����
//void GetLineBack(long &x, long &y, long lX, long lY, long lDestX, long lDestY, long lFigure);
//// �õ�Դ��Ŀ��ֱ��һ��Դ���ͬʱ��Ŀ������������
//void GetLineFront(long &x, long &y, long lSrcX, long lSrcY, long lDestX, long lDestY, long lDistance);
//// ȥ���ַ����ұߵĿո�
//char* TrimRight(char* pszStr);
//
//// �߾���ʱ�亯��, ����ϵͳ�Կ��������ĺ�����, ��RDTSCָ���ȡCPU�Կ���������ָ�����ڣ�����CPUƵ�ʵõ�
//ulong GetCurTickCount();
//ulong GetCurTime();
//
//void IniEncoder(const char* pstrIn, char* pstrOut);		// ����
//void IniDecoder(const char* pstrIn, char* pstrOut, int len);		// ����
//
//#ifdef _RUNSTACKINFO_
//// �������ջ��Ϣ
//void StartStackInfo();
//void OutputStackInfo(const char* pszInfo);
//void EmptyStackInfo();
//void EndStackInfo();
//#endif
//
//
//// �ṩ��hashʹ��
//class point_compare
//{
//public:
//	bool operator()(const POINT& Key1, const POINT& Key2) const
//	{
//		if (Key1.x < Key2.x)
//			return true;
//		else if (Key1.x == Key2.x)
//			if (Key1.y < Key2.y)
//				return true;
//		return false;
//	}
//
//};
//extern bool g_bOutPut;	// �Ƿ����
//
/////
///// calculate the rest seconds in this day.
/////
//ulong GetRestSeconds();
//
/////
///// Calculate the elapsed day between two time values.
/////
//ulong GetElapsedDay(time_t time1, time_t time2);
//
//
///*
//*���ܣ����ɼ����ַ���
//*ϸ�������� ��Դ�ַ��� ����ָ�����Ƚضϣ����������� ʡ�Է��ű�ʾ
//*������ szString	Դ�ַ���
//*		iLen		ָ������
//*����ֵ�� std::string
//*��ӣ�����
//*/
////std::string	GetShortString(LPCTSTR szString, int iLen);
//
//#define RUN_TIME_STAT(tag, exp) { \
//    DWORD stime = timeGetTime(); \
//    exp; \
//    DWORD etime = timeGetTime(); \
//    char s[256]; \
//    sprintf(s, "Run Time:%s %u\n", (const char*)tag, etime > stime ? etime-stime:0); \
//    OutputDebugString(s); \
//}
//
//char *CopyConfigStr(char *dest, size_t max, const std::string &src);
//
//inline bool IsNullString(const char *s)
//{
//    return s == NULL || s[0] == '\0';
//}

#endif /* !ELF_UTILS_TOOLS_H */
