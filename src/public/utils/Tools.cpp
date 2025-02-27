// ********************************************
// 	杂相函数
// ********************************************

#include "Tools.h"
//#include <shlobj.h>
//#include <SYS/TIMEB.H>
//
//#ifdef _WIN32
//#define wcsset _wcsset
//#define stricmp _stricmp
//#define strlwr _strlwr
//#endif /* !_WIN32 */
//

bool g_bOutPut = true;		// 输出功能开关

int random(int nMax)
{
	if (nMax > RAND_MAX)
	{
		float ret = (float)rand() * ((float)nMax / (float)RAND_MAX);
		ret += (float)rand() * ((float)nMax/(float)RAND_MAX) / (float)RAND_MAX;
		while ((int)ret == nMax && ret > 0)
		{
			ret = (float)rand() * ((float)nMax / (float)RAND_MAX);
			ret += (float)rand() * ((float)nMax/(float)RAND_MAX) / (float)RAND_MAX;
		}
		return (int)ret;
	}
	else
	{
		int ret = rand()*nMax/RAND_MAX;
		while (ret == nMax && ret > 0)
		{
			ret = rand()*nMax/RAND_MAX;
		}
		return ret;
	}
}

//// 四舍五入
//int Round(float f)
//{
//	if (f<0)
//		return (long)(f-0.5);
//	return (long)(f+0.5);
//}
//
//// 四舍五入
//int Round(double f)
//{
//	if (f<0)
//		return (long)(f-0.5);
//	return (long)(f+0.5);
//}
//
//// *************************
//// 延时
//void Delay(long time)
//{
//	static long old_clock, new_clock; // 延时变量
//	new_clock=old_clock=GetCurTickCount();
//
//	MSG msg;
//	while (new_clock < old_clock + time)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
//		{
//            if (!GetMessage(&msg, NULL, 0, 0)) return;
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//		}
//		else if (1)
//		{
//			new_clock=GetCurTickCount();
//			if (GetAsyncKeyState(VK_F4))
//			{
//				return;
//			}
//		}
//		else WaitMessage();	// 等待消息
//	}
//}
//
//// ***************************
//// 获取文件长度
//int GetFileLength(const char *name)
//{
//	if (name == NULL)	return 0;
//	int fh, nbytes = 0;
//	fh = _open(name, _O_RDONLY);
//	if (fh== -1)
//	{
//		//char s[32];
//		//sprintf(s, "file %s not found!", name);
//		//LogError(s);
//		return -1;
//	}
//
//	nbytes=_filelength(fh);
//	_close(fh);
//
//
//	/*CRFile* prfile = rfOpen(name):
//	if (prfile)
//	{
//		nbytes = prfile->GetDatalen();
//		rfClose(prfile);
//	}*/
//	return nbytes;
//}
//
//
//// **************************
//// 判断文件是否存在
//bool CheckFile(const char *name)
//{
//	WIN32_FIND_DATA fdt;
//	if (FindFirstFile(name, &fdt)==INVALID_HANDLE_VALUE)
//		return false;
//	else
//		return true;
//}
//
//// **************************
//// 显示调试信息
//void ShowMessage(const char *msg, ...)
//{
//	va_list va;
//	char str[256];
//
//	va_start(va, msg);
//	sprintf_s(str, 256, msg, va);
//	va_end(va);
//
//	LOG_ERROR("", str);
//
//}
//
//static char szDebugFileName[_MAX_PATH] = "debug.txt";
//void InitialDebugFileName(bool bIsTimed, bool bIsClear)
//{
//	// 初始化debugfilename名字
//	SYSTEMTIME st;
//	GetLocalTime(&st);
//
//	if (bIsTimed)
//		_snprintf(szDebugFileName, 256, "log\\debug%d_%d_%d[%2.2d_%2.2d_%2.2d].txt", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
//	else
//		_snprintf(szDebugFileName, 256, "log\\debug.txt");
//
//	struct _finddata_t c_file;
//	intptr_t hFile;
//	bool bExist = ((hFile = _findfirst("log", &c_file)) != -1L);
//	if (!bExist)
//		CreateDirectory("log", NULL);
//	// 清空文件
//	if (bIsClear)
//	{
//		FILE *fp;
//		if ((fp=fopen(szDebugFileName, "w+")) == NULL)
//		{
//            static char errorInfo[512] = " ";
//            sprintf_s<512>(errorInfo, "%s Open failed!!", szDebugFileName);
//			assert(errorInfo);
//			return;
//		}
//		fclose(fp);
//	}
//}
//
//const char* GetDebugFileName()
//{
//	return szDebugFileName;
//}
//// *************************
//// 输出调试信息
////void PutDebugString(const char *fmt, ...)
//// {
////    char msg[4096];
////    va_list va;
//// 	va_start(va, fmt);
//// 	vsprintf(msg, fmt, va);
//// 	va_end(va);
////
//// 	int iInfoLen = lstrlen(msg);
//// 	if (0 >= iInfoLen)
//// 		return;
//// 	//static string filenam
//// 	static int num=0;
//// 	char t[128];
////
//// 	FILE *fp;
//// 	if ((fp=fopen(szDebugFileName, "a+")) == NULL)
//// 	{
//// 		//assert(0);
//// 		return;
//// 	}
////
//// 	num++;
//// 	SYSTEMTIME stTime;
//// 	GetLocalTime(&stTime);
//// 	_snprintf(t, 128, "\n%d(%02d-%02d %02d:%02d:%02d.%03d):", num, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);
//// 	fseek(fp, 0, SEEK_END);
//// 	fwrite(t, lstrlen(t), 1, fp);
//// 	fwrite(msg, iInfoLen, 1, fp);
//// 	fclose(fp);
//// }
//
//// *************************
//// 输出城战调试信息
////void PutWarDebugString(const char *msg)
//// {
//// 	static int num=0;
//// 	char t[128];
////
//// 	FILE *fp;
//// 	if ((fp=fopen("WarDebug.txt", "a+")) == NULL)
//// 	{
//// 		//ShowMessage("Can't open Debug.txt (%s)", msg);
//// 		assert(0);
//// 		return;
//// 	}
////
//// 	num++;
//// 	SYSTEMTIME stTime;
//// 	GetLocalTime(&stTime);
//// 	_snprintf(t, 128, "\n%d(%02d-%02d %02d:%02d:%02d.%03d):", num, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);
//// 	fseek(fp, 0, SEEK_END);
//// 	fwrite(t, lstrlen(t), 1, fp);
//// 	fwrite(msg, lstrlen(msg), 1, fp);
//// 	fclose(fp);
//// }
//
//// *************************
//// 输出文件信息
////void PutStringToFile(const char* filename, const char *msg)
//// {
//// 	if (!g_bOutPut)
//// 		return;
//// 	char strFile[MAX_PATH];
//// 	SYSTEMTIME stTime;
//// 	GetLocalTime(&stTime);
//// 	_snprintf(strFile, MAX_PATH, "log/%s_%04d-%02d-%02d.log", filename, stTime.wYear, stTime.wMonth, stTime.wDay);
////
//// 	FILE *fp;
//// 	if ((fp=fopen(strFile, "a+")) == NULL)
//// 	{
//// 	// 	assert(0);
//// 		return;
//// 	}
////
//// 	static int num=0;
//// 	num++;
////
//// 	char t[128];
//// 	_snprintf(t, 128, "\n%d(%02d-%02d %02d:%02d:%02d.%03d)",
//// 		num, stTime.wMonth, stTime.wDay, stTime.wHour,
//// 		stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);
//// 	fseek(fp, 0, SEEK_END);
//// 	fwrite(t, lstrlen(t), 1, fp);
//// 	fwrite(msg, lstrlen(msg), 1, fp);
//// 	fclose(fp);
//// }
//// *************************
//// 更新一个文件内容
//bool OverloadFile(const char* filename, const char *msg)
//{
//	if (NULL == msg)
//		return false;
//	HANDLE hFile;
//	// 	CreateDirectory(pDirPath, NULL);
//	hFile = ::CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (INVALID_HANDLE_VALUE == hFile)
//	{
//		return false;
//	}
//
//	// 	这里开始写文件
//	ulong dwWritenSize = 0;
//	WriteFile(hFile, msg, (DWORD)strlen(msg), &dwWritenSize, NULL);
//	FlushFileBuffers(hFile);
//
//	// 	关闭句柄
//	CloseHandle(hFile);
//
//	return true;
//}
//// *************************
//// 输出log信息
//// void PutLogInfo(const char *msg)
//// {
//// 	char strFile[MAX_PATH];
//// 	SYSTEMTIME stTime;
//// 	GetLocalTime(&stTime);
//// 	_snprintf(strFile, MAX_PATH, "log/%04d-%02d-%02d.txt", stTime.wYear, stTime.wMonth, stTime.wDay);
////
//// 	FILE *fp;
//// 	if ((fp=fopen(strFile, "a+")) == NULL)
//// 	{
//// 		return;
//// 	}
////
//// 	fseek(fp, 0, SEEK_END);
//// 	fwrite(msg, lstrlen(msg), 1, fp);
//// 	fclose(fp);
//// }

char *GetFilePath(const char *filename, char* out)
{
	int Len=lstrlen(filename);
	strcpy(out, filename);

	for (int i=Len-1; i>=0; i--)
	{
		if (out[i] == '\\' || out[i] == '/')
			break;
		out[i]=0;
	}

	return out;
}

// 由文件名获取文件扩展名
char *GetFileExtName(const char *filename, char* out)
{
	int Len=lstrlen(filename);
	out[0] = 0;

	for (int i=Len-1; i>=0; i--)
	{
		if (filename[i] == '.')
		{
			strcpy(out, &filename[i]);
			return out;
		}

	}
	return out;
}

// // 由文件路径名获取文件名
//char *GetFileName(const char *filename, char* out)
//{
//    int Len = lstrlen(filename);
//    out[0] = 0;
//    int pos = 0;
//    for (int i=0;i<Len;i++)
//    {
//        if (filename[i] == '/' || filename[i] == '\\')
//        {
//            pos = i;
//        }
//    }
//    if (pos != 0)
//    {
//       strcpy(out, &filename[pos+1]);
//       return out;
//    }
//    return out;
//}
//
//char *GetFileNameNoExt(const char* filename, char* out)
//{
//    int Len=lstrlen(filename);
//    strcpy(out, filename);
//    for (int i=0; i<Len; i++)
//    {
//        if (filename[i] == '.')
//        {
//            out[i] = 0;
//            return out;
//        }
//
//    }
//    return out;
//}
//// *************************
////char to wchar
//WCHAR* WChar(char *string)
//{
//	WCHAR *wchr;
//	int wsize = MultiByteToWideChar(CP_ACP, NULL, string, lstrlen(string), NULL, 0);
//
//	wchr=new WCHAR[wsize+1];
//	wcsset(reinterpret_cast<wchar_t*>(wchr), 0);
//	MultiByteToWideChar(CP_ACP, NULL, string, lstrlen(string), (LPWSTR)wchr, wsize);
//	wchr[wsize]=0;
//	return wchr;
//}
//
//// *************************
////wchar to char
//char* Char(WCHAR *string)
//{
//	char *chr;
//	size_t len = wcslen(reinterpret_cast<wchar_t*>(string));
//	chr=new char[len+1];
//	memset(chr, 0, len+1);
//	for (unsigned int i=0; i<len; i++)
//	{
//		chr[i]=(uchar)string[i];
//	}
//	return chr;
//}
//
//// 删除目录
//void DeleteDirectory(const char* strDir)
//{
//	char strFile[MAX_PATH];
//	_snprintf(strFile, MAX_PATH, "%s\\*.*", strDir);
//
//	// 删除目录中的所有文件
//	BOOL result;
//	WIN32_FIND_DATA FindFileData;
//	HANDLE hFind;
//	hFind = FindFirstFile(strFile, &FindFileData);
//	if (hFind)
//	{
//		if (strcmp(FindFileData.cFileName, "..") != 0 &&
//			strcmp(FindFileData.cFileName, ".") != 0)
//		{
//			_snprintf(strFile, MAX_PATH, "%s\\%s", strDir, FindFileData.cFileName);
//			DeleteFile(strFile);
//		}
//		do
//		{
//			result = FindNextFile(hFind, &FindFileData);
//			if (strcmp(FindFileData.cFileName, "..") != 0 &&
//				strcmp(FindFileData.cFileName, ".") != 0 && result == TRUE)
//			{
//				_snprintf(strFile, MAX_PATH, "%s\\%s", strDir, FindFileData.cFileName);
//
//				BOOL IsDel  = DeleteFile(strFile);
//				if (IsDel == 0)
//				{
//					LPVOID lpMsgBuf;
//					if (!FormatMessage(
//						FORMAT_MESSAGE_ALLOCATE_BUFFER |
//						FORMAT_MESSAGE_FROM_SYSTEM |
//						FORMAT_MESSAGE_IGNORE_INSERTS,
//						NULL,
//						GetLastError(),
//						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
//						(LPTSTR) &lpMsgBuf,
//						0,
//						NULL))
//					{
//						// Handle the error.
//						return;
//					}
//
//					// Process any inserts in lpMsgBuf.
//					// …
//
//					// Display the string.
//					LOG_ERROR("", "FILE:[%s]  %s", strFile, (LPTSTR)lpMsgBuf);
//
//					// Free the buffer.
//					LocalFree(lpMsgBuf);
//				}
//
//			}
//		}while (result);
//	}
//    FindClose(hFind);
//
//	// 删除目录
//	RemoveDirectory(strDir);
//}
//
//// 获取路径
//bool GetFileDialog(bool Load, const char* currentPath, char* strFile, const char* strFilter)
//{
//	OPENFILENAME ofn;
//	memset(&ofn, 0, sizeof(ofn));
//	ofn.lStructSize = sizeof(ofn);
//	ofn.hwndOwner = NULL;	//AfxGetMainWnd()->GetSafeHwnd();
//	ofn.hInstance = NULL;	//AfxGetInstanceHandle ();
//	ofn.lpstrFilter = strFilter;	// file types
//	ofn.lpstrCustomFilter = NULL;
//	ofn.nFilterIndex = 0;		// index of first one
//	ofn.nMaxCustFilter = 0;
//	ofn.lpstrFile = NULL;	// initial file suggested
//	ofn.nMaxFile = 1024;
//	ofn.lpstrTitle = NULL;		// dlg title
//	ofn.lpstrFileTitle = NULL;
//	ofn.lpstrInitialDir = currentPath;   // initial path
//	ofn.Flags = OFN_SHOWHELP | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_SHAREAWARE;
//	ofn.lpstrDefExt = "*";		// default extension
//	ofn.lpfnHook = NULL;
//
//	if (Load)	// ??
//	{
//		if (GetOpenFileName((LPOPENFILENAME)&ofn))
//		{
//			strcpy(strFile, ofn.lpstrFile);
//			return true;
//		}
//	}
//	else	// ??
//	{
//		if (GetSaveFileName((LPOPENFILENAME)&ofn))
//		{
//			strcpy(strFile, ofn.lpstrFile);
//			return true;
//		}
//	}
//	return false;
//}
//
//bool GetPathDialog(const char* strRoot, char* strPath)
//{
//	BROWSEINFO bi;
//	char diskname[MAX_PATH];
//	char path[MAX_PATH];
//
//	ITEMIDLIST *pidl;
//	bi.hwndOwner=NULL;	//AfxGetMainWnd()->GetSafeHwnd();
//	bi.pidlRoot=0;
//	bi.pszDisplayName=diskname;
//	bi.lpszTitle="select a path";
//	bi.ulFlags=BIF_RETURNONLYFSDIRS;
//	bi.lpfn=0;
//	bi.lParam=0;
//	bi.iImage=0;
//
//	if (pidl = SHBrowseForFolder(&bi))
//	{
//		SHGetPathFromIDList(pidl, path);
//
//		strcpy(strPath, path);
//		return true;
//	}
//	return false;
//}
//
//// 替换STR中的'\\'为'/';
//void ReplaceLine(char* str)
//{
//	long l = lstrlen(str);
//	for (int i=0; i<l; i++)
//	{
//		if (str[i] == '\\')
//		{
//			str[i] = '/';
//		}
//	}
//}
//
//// 获取一个长字符串中的第NUM个串，空格为间隔
//bool GetString(const char* sour, char* dest, int num)
//{
//	long len = lstrlen(sour);
//	long n = 0, j = 0;;
//	for (int i=0; i<len+1; i++)
//	{
//		char chr = sour[i];
//
//		if (chr == ' ' || chr == 0)
//		{
//			n++;
//			if (n > num)
//			{
//				dest[j] = 0;
//				return true;
//			}
//			continue;
//		}
//
//		if (num == n)
//		{
//			dest[j] = sour[i];
//			j++;
//		}
//	}
//
//	return false;
//}
//
//// 快速排序
////
//// 快速排序的思路是不难理解的，首先在头尾设置两个指针然后向中间移动，
//// 发现两指针所指的数交换会改善排序状况则交换，如两指针到达或越过了对
//// 方那么就表明已经把数分成了两组，再递归调用自己对这两组分别实施同一
//// 过程即可。
////
//// 对数组a排序，start为开始排序的位置，end为排
//// 序结束位置，例如a[10]则start=0，end=9。
//template<class T>
//void QuickSort(T* a, int begin, int end)
//{
//	int p=begin;
//	int q=end;
//	T mid=a[p]; // 标准数
//	T temp;
//
//	while (p<q)
//	{
//		// 让数组左边的数大于等于标准数
//		while (a[p]<mid)
//		{
//			p++;
//		}
//
//		// 让数组右边的数小于等于标准数
//		while (a[q]>mid)
//		{
//			q--;
//		}
//
//		if (p<=q)
//		{
//			// 交换a[p]、a[q]。
//			temp=a[p];
//			a[p]=a[q];
//			a[q]=temp;
//
//			p++;
//			q--;
//		}
//	}
//
//	if (q>begin) QuickSort(a, begin, q);	// 继续对前半部分排序
//	if (p<end) QuickSort(a, p, end); 	// 继续对后半部分排序
//}
//
//// 获取从(sx, sy)到(dx, dy)的方向(0-7)
//long GetLineDir(long sx, long sy, long dx, long dy)
//{
//	long dir = 0;
//	float fx = (float)(dx - sx);
//	float fy = (float)(dy - sy);
//	if (fx || fy)
//	{
//		float tag = fabs((float)fy/(float)fx);
//		if (tag < tan(0.3926f))	// 22.5
//		{
//			dir = (fx>0)?(2):(6);
//		}
//		else if (tag < tan(1.178f))	// 67.5
//		{
//			if (fx > 0)
//			{
//				dir = (fy>0)?(3):(1);
//			}
//			else
//			{
//				dir = (fy>0)?(5):(7);
//			}
//		}
//		else
//		{
//			dir = (fy>0)?(4):(0);
//		}
//	}
//	return dir;
//}
///***********************************************************************/
///*  zhaohang 2010-11-15 add*/
//long GetLineDir(float sx, float sy, float dx, float dy)
//{
//	long dir = 0;
//	float fx = (dx - sx);
//	float fy = (dy - sy);
//	if (fx || fy)
//	{
//		float tag = fabs(fy/fx);
//		if (tag < tan(0.3926f))	// 22.5
//		{
//			dir = (fx>0)?(2):(6);
//		}
//		else if (tag < tan(1.178f))	// 67.5
//		{
//			if (fx > 0)
//			{
//				dir = (fy>0)?(3):(1);
//			}
//			else
//			{
//				dir = (fy>0)?(5):(7);
//			}
//		}
//		else
//		{
//			dir = (fy>0)?(4):(0);
//		}
//	}
//	return dir;
//}
///***********************************************************************/
//
//float GetRadianDir(float sx, float sy, float dx, float dy, float dir)
//{
//    float x = dx - sx;
//    float y = dy - sy;
//
//    if (fabs(x) > E) {
//        dir = atanf(y/x);
//        if (x < 0) dir += PI;
//    } else if (fabs(y) > E) {
//        dir = (y/(float)fabs(y)) * PI/2;
//    }
//    if (dir < 0) {
//        dir += 2 * PI;
//    }
//    return dir;
//}
//
//bool CreateDir(const char* dir)
//{
//	/*
//	CFileFind f;
//	if (f.FindFile(dir))
//	{
//		return true;
//	}
//	else
//	{
//		bool done = CreateDirectory(dir, NULL);
//		if (done)
//		{
//			return true;
//		}
//	}
//
//	int n = 0;
//	do
//	{
//		n = dir.Find('\\', n);
//		if (n == -1)
//		{
//			bool done = CreateDirectory(dir, NULL);
//			if (!done)
//			{
//			// 	AfxMessageBox("can not create dir " + dir) ;
//				assert(0);
//				return false;
//			}
//			return true;
//		}
//
//		char s[MAX_PATH];
//		memset(s, 0, MAX_PATH);
//		memcpy(s, dir, n);
//		if (f.FindFile(s))
//		{
//		}
//		else
//		{
//			bool done = CreateDirectory(s, NULL);
//			if (!done)
//			{
//			// 	AfxMessageBox("can not create dir " + dir) ;
//				assert(0);
//				return false;
//			}
//		}
//		n++;
//	}while (1);
//*/
//	return true;
//}
//
// 读取所有的指定文件
void FindFile(const char* strFile, const char* strExt, list<string>* plistFileName)
{
	char strPath[MAX_PATH];
	GetFilePath(strFile, strPath);

	WIN32_FIND_DATA stFindData;
	HANDLE hFind = FindFirstFile(strFile, &stFindData);
	if (hFind==INVALID_HANDLE_VALUE)
	{
		return;
	}

	BOOL bNext = TRUE;
	while (1)
	{
		// 是目录
		if (stFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp(stFindData.cFileName, "..") != 0)
			{
				char str[MAX_PATH];
				_snprintf(str, MAX_PATH, "%s%s/*.*", strPath, stFindData.cFileName);
				FindFile(str, strExt, plistFileName);
			}
		}
		else	// 文件
		{
			char strExtName[MAX_PATH];
			GetFileExtName(stFindData.cFileName, strExtName);
			if (stricmp(strExtName, strExt) == 0)
			{
				char str[MAX_PATH];
				_snprintf(str, MAX_PATH, "%s%s", strPath, stFindData.cFileName);
				strlwr(str);	//  转换成小写
				plistFileName->push_back(str);
			}
		}

		bNext = FindNextFile(hFind, &stFindData);
		if (bNext==0)
		{
			break;
		}
	}

	FindClose(hFind);
}

//bool FormatMoneyNumber(char *str, const int size)
//{
//	int len=lstrlen(str);
//
//	if (len<=3 || len/3 + len > size)
//		return false;
//
//	int end=len;
//	for (int i=len-3; i>0; i-=3)
//	{
//		int l=lstrlen(str);
//		for (int j=l;j>i;--j)
//		{
//			str[j]=str[j-1];
//		}
//		str[i]=',';
//		str[++end]='\0';
//	}
//	// 加个0在最后头
//	if (end<size)
//		str[end]='\0';
//	return true;
//}
//
//// 获取CPU自开机以来的时钟周期数
//inline unsigned __int64 GetCPUCycleCount()
//{
//	__asm _emit 0x0F
//	__asm _emit 0x31
//	//__asm
//	// {
//	// 	RDTSC
//	// }
//	//if (IsProcessorFeaturePresent(PF_RDTSC_INSTRUCTION_AVAILABLE))
//	// {
//	// 	return RDTSC();
//	// }
//	//else
//	// {
//	// 	return 0;
//	// }
//}
//
//// 获取CPU的频率
//inline ulong GetCPUFrequency()
//{
//	static BOOL bRDTSCSupported=IsProcessorFeaturePresent(PF_RDTSC_INSTRUCTION_AVAILABLE);
//	if (bRDTSCSupported == FALSE)
//	{
//		return timeGetTime();
//	}
//	static ulong dwFrequency=0;
//	if (dwFrequency>0)return dwFrequency;
//	HKEY hKey=0;
//	ulong dwSize;
//	if (RegOpenKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", &hKey)==ERROR_SUCCESS)
//	{
//		RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE)&dwFrequency, &dwSize);
//		RegCloseKey(hKey);
//		dwFrequency*=1000;
//	}
//	return dwFrequency;
//}
//
//
//// 高精度时间函数, 返回系统自开机以来的毫秒数, 用RDTSC指令获取CPU自开机以来的指令周期，除以CPU频率得到
//ulong GetCurTickCount()
//{
//	return timeGetTime();
//
//	static BOOL bSupported=IsProcessorFeaturePresent(PF_RDTSC_INSTRUCTION_AVAILABLE);
//
//	if (FALSE == bSupported)
//	{
//		return timeGetTime();
//	}
//
//	unsigned __int64 cpuCount=GetCPUCycleCount();
//	ulong cpuFrequency=GetCPUFrequency();
//	return (ulong)(cpuCount/cpuFrequency);
//}
//
//ulong GetCurTime()
//{
//	struct _timeb stCostTime;
//	_ftime(&stCostTime);
//	return (ulong)stCostTime.time-stCostTime.timezone*60;
//}
//
//// 加密
//void IniEncoder(const char* pstrIn, char* pstrOut)
//{
//	size_t len = strlen(pstrIn);
//	for (size_t i=0; i<len; i++)
//	{
//		pstrOut[i] = ~pstrIn[i];
//		pstrOut[i] += 12;
//	}
//}
//
//// 解密
//void IniDecoder(const char* pstrIn, char* pstrOut, int len)
//{
//	for (int i=0; i<len; i++)
//	{
//		pstrOut[i] = pstrIn[i];
//		pstrOut[i] -= 12;
//		pstrOut[i] = ~pstrOut[i];
//	}
//}
//
//long Distance(long sx, long sy, long dx, long dy)
//{
//	double fXOffset = sx - dx;
//	double fYOffset = sy - dy;
//	return (long)sqrt(fYOffset * fYOffset + fXOffset * fXOffset);
//}
//
//float Distance(float sx, float sy, float dx, float dy)
//{
//	float fXOffset = sx - dx;
//	float fYOffset = sy - dy;
//	return sqrt(fYOffset * fYOffset + fXOffset * fXOffset);
//}
//
//// 得到该方向上最大数量的格子
//long GetLinePointByDir(list<POINT>& listPos, long lX, long lY, long lDir, long lDistance, float offset)
//{
//	static int pos[8][2] = {0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1};
//	listPos.clear();
//	if (lDistance>0)
//	{
//		long lSourX=lX + Round(pos[lDir][0] * offset);
//		long lSourY=lY + Round(pos[lDir][1] * offset);
//		for (float i = 0; i < lDistance; i++)
//		{
//			lSourX = lSourX + pos[lDir][0];
//			lSourY = lSourY + pos[lDir][1];
//			POINT point ={lSourX, lSourY};
//			listPos.push_back(point);
//		}
//	}
//	return (long)listPos.size();
//}
//// 得到源与目标直线一离源最近同时离目标最近的坐标点
//void GetLineFront(long &x, long &y, long lSrcX, long lSrcY, long lDestX, long lDestY, long lDistance)
//{
//	double lX = (lDestX-lSrcX);
//	double lY = (lDestY-lSrcY);
//	//long lDistance = sqrt(lX*lX + lY*lY);
//
//	list<POINT> listPos;
//
//	GetLinePointToDest(listPos, lSrcX, lSrcY, lDestX, lDestY, lDistance);
//
//
//	list<POINT>::iterator it = listPos.begin();
//	for (;it!=listPos.end();++it)
//	{
//		POINT& pos = (*it);
//		if (lDestX==pos.x && lDestY==pos.y)
//			continue;
//		x = pos.x;
//		y = pos.y;
//	}
//
//}
//// 得到源与目标直线一离源最远同时离目标最近的点坐标
//void GetLineBack(long &x, long &y, long lX, long lY, long lDestX, long lDestY, long lFigure)
//{
//
//	if (lDestX-lX==0)
//	{
//		// y轴
//		if (lY>lDestY)
//		{
//			x = lX;
//			y = lDestY - lFigure - 1 ;
//		}
//		else
//		{
//			x = lX;
//			y = lDestY + lFigure + 1;
//		}
//	}
//	else
//	{
//		if (lDestY-lY==0)
//		{
//			// x轴
//			if (lX>lDestX)
//			{
//				x = lDestX - lFigure - 1;
//				y = lDestY;
//			}
//			else
//			{
//				x = lDestX  + lFigure + 1;
//				y = lDestY;
//			}
//		}
//		else
//		{
//			// 斜线
//			if (lY>lDestY)
//			{
//				y = lDestY - lFigure - 1;
//			}
//			else
//			{
//				y = lDestY + lFigure + 1;
//			}
//			if (lX>lDestX)
//			{
//				x = lDestX - lFigure - 1;
//			}
//			else
//			{
//				x = lDestX + lFigure + 1;
//			}
//		}
//	}
//}
//
//long GetLinePointToDest(list<fPoint>& listPos, float fStartX, float fStartY, float fDestX, float fDestY,float fDistance)
//{
//    float loffX = (float)fDestX - fStartX;
//    float loffY = (float)fDestY - fStartY;
//
//    float fdis = sqrtf(loffX*loffX+loffY*loffY);
//    float fsin = loffX/fdis;
//    float fcos = loffY/fdis;
//    if(fDistance && fDistance < fdis)
//        fdis -= static_cast<long>(fDistance);
//    for (float i = 0.5f; i <= fdis ;)
//    {
//        float fX = fStartX+fsin*i;
//        float fY = fStartY+fcos*i;
//        fPoint pos = {fX, fY};
//        listPos.push_back(pos);
//         i+=0.5;
//    }
//    return (long)listPos.size();
//}
//// 得到穿过目标点直线的所有点
//long GetLinePointToDest(list<POINT>& listPos, long lX, long lY, long lDestX, long lDestY, long lDistance, float offset)
//{
//	long	lStartX		= lX;
//	long	lStartY		= lY;
//
//	float loffX = (float)lDestX-lStartX;
//	float loffY = (float)lDestY-lStartY;
//
//	long fdis = (long)sqrt(loffX*loffX+loffY*loffY);
//	float fsin = loffX/fdis;
//	float fcos = loffY/fdis;
//	for (float i = 1 + offset; i <= lDistance + offset; i++)
//	{
//		long lDestX = lStartX+Round(fsin*i);
//		long lDestY = lStartY+Round(fcos*i);
//		POINT pos = {lDestX, lDestY};
//		listPos.push_back(pos);
//	}
//
//	return (long)listPos.size();
//}
//
//// 得到通过目标点的所有线段上的点
//long GetLinePointToDest(list<POINT>& listPos, float fX, float fY, float fDestX, float fDestY, long lDistance, float offset)
//{
//    float	lStartX		= fX;
//    float	lStartY		= fY;
//
//    float loffX = fDestX-lStartX;
//    float loffY = fDestY-lStartY;
//
//    float fdis = sqrt(loffX*loffX+loffY*loffY);
//    float fsin = loffX/fdis;
//    float fcos = loffY/fdis;
//    for (float i = 1 + offset; i <= lDistance + offset; i++)
//    {
//        long lDestX = Round(lStartX+(fsin*i));
//        long lDestY = Round(lStartY+(fcos*i));
//        POINT pos = {lDestX, lDestY};
//        listPos.push_back(pos);
//    }
//
//    return (long)listPos.size();
//}
//
//// 得到一个圆里的所有点
//long GetCircPoint(list<POINT>& listPos, long lCenterX, long lCenterY, long lRadius)
//{
//	static long pos[4][2] = {-1, -1, 1, -1, 1, 1, -1, 1};
//	listPos.clear();
//	POINT point = {lCenterX, lCenterY};
//	listPos.push_back(point);
//	long lX = 0;
//	long lY = 0;
//	// 当半径每增加1的时候, 向外扩展一层
//	for (int i=1;i<=lRadius;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			lX = lCenterX+pos[j][0];
//			lY = lCenterY+pos[j][1];
//			int count = (int)pow((double)2, i);
//			for (int n=0;n<count;n++)
//			{
//				POINT pos = {lX, lY};
//				if (lX == lCenterX || lY==lCenterY || Distance(lCenterX, lCenterY, lX, lY) < lRadius)
//					listPos.push_back(pos);
//				if (j == 0)
//					lX++;
//				else if (j == 1)
//					lY++;
//				else if (j == 2)
//					lX--;
//				else if (j == 3)
//					lY--;
//			}
//		}
//	}
//	return (long)listPos.size();
//}
//
//
//// 得到一个正方形里的所有点
//long GetSquarePoint(list<POINT>& listPos, long lCenterX, long lCenterY, long lOffLen)
//{
//	static long pos[4][2] = {-1, -1, 1, -1, 1, 1, -1, 1};
//	listPos.clear();
//	POINT point = {lCenterX, lCenterY};
//	listPos.push_back(point);
//	long lX = 0;
//	long lY = 0;
//	// 当半径每增加1的时候, 向外扩展一层
//	for (int i=1;i<=lOffLen;i++)
//	{
//		for (int j=0;j<4;j++)
//		{
//			lX = lCenterX+pos[j][0];
//			lY = lCenterY+pos[j][1];
//			int count = (int)pow((float)2, i);
//			for (int n=0;n<count;n++)
//			{
//				POINT pos = {lX, lY};
//				listPos.push_back(pos);
//				if (j == 0)
//					lX++;
//				else if (j == 1)
//					lY++;
//				else if (j == 2)
//					lX--;
//				else if (j == 3)
//					lY--;
//			}
//		}
//	}
//	return (long)listPos.size();
//}
//
//// 去掉字符串右边的空格
//char* TrimRight(char* pszStr)
//{
//	char *pszTemptStr = pszStr;
//	size_t len = strlen(pszTemptStr);
//	for (size_t i=len-1;i>=0;i--)
//	{
//		if (pszTemptStr[i] == ' ')
//			pszTemptStr[i] ='\0';
//		else
//			break;
//	}
//	return pszTemptStr;
//}
//
//// 输出文件信息，并在指定的目录下保存文件, 最后一个参数表示是否根据当前系统时间重新创建文件（false继续输入）
//void PutStrToFileSaveToDir(const char* dir, const char* filename, const char *msg, bool IsRePut)
//{
//	if (dir && filename && msg)
//	{
//		// 查看文件夹是否存在，不存在加载
//		struct _finddata_t c_file;
//		intptr_t hFile;
//		bool bExist = ((hFile = _findfirst(dir, &c_file)) != -1L);
//		if (!bExist)
//			CreateDirectory(dir, NULL);
//		static char strFileName[_MAX_PATH] = "";
//		// 根据当前系统时间来重新创建文件保存信息
//		if (IsRePut || lstrlen(strFileName) <= 0)
//		{
//			// 初始化strFileName名字
//			SYSTEMTIME st;
//			GetLocalTime(&st);
//			_snprintf(strFileName, 256, "%s\\%s %d_%d_%d[%2.2d_%2.2d_%2.2d].txt", dir, filename, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
//		}
//		// 写入文件
//		//static string filenam
//		static int num=0;
//		FILE *fp;
//		if ((fp=fopen(strFileName, "a+")) == NULL)
//		{
//			assert(0);
//			return;
//		}
//		num++;
//		SYSTEMTIME stTime;
//		GetLocalTime(&stTime);
//		char t[2048]="";
//		_snprintf(t, 2048, "\n%d(%02d-%02d %02d:%02d:%02d.%03d): %s", num, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute,
//			stTime.wSecond, stTime.wMilliseconds, msg);
//		fseek(fp, 0, SEEK_END);
//		fwrite(t, lstrlen(t), 1, fp);
//		fclose(fp);
//	}
//}
//
//static FILE *fStack = NULL;
//static char pszStackFileName[256]="";
//// 输出运行栈信息
//void StartStackInfo()
//{
//	// 创建一个log的保存目录
//	SYSTEMTIME stTime;
//	GetLocalTime(&stTime);
//	_snprintf(pszStackFileName, 256, "log/RunStackInfo[%02d_%02d_%02d_%02d_%02d].txt", stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
//	if ((fStack = fopen(pszStackFileName, "w")) == NULL)
//		return;
//}
//
//void OutputStackInfo(const char* pszInfo)
//{
//	static char line[5]="\n";
//	if (NULL == fStack || NULL == pszInfo)	return;
//
//	char pszTime[128];
//	SYSTEMTIME stTime;
//	GetLocalTime(&stTime);
//	_snprintf(pszTime, 128, "\n(%02d-%02d %02d:%02d:%02d.%03d):", stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);
//	fseek(fStack, 0, SEEK_END);
//	fwrite(pszTime, lstrlen(pszTime), 1, fStack);
//	fwrite(pszInfo, lstrlen(pszInfo), 1, fStack);
//}
//
//void EmptyStackInfo()
//{
//	if (fStack)
//		fclose(fStack);
//	fStack = fopen(pszStackFileName, "w");
//}
//
//void EndStackInfo()
//{
//	if (NULL == fStack)	return;
//	OutputStackInfo("End");
//	fclose(fStack);
//}
//
//ulong GetRestSeconds()
//{
//	time_t timep;
//	tm *ptm;
//	time(&timep);
//	ptm = localtime(&timep);
//	return (23 - ptm->tm_hour) * 60 * 60 + (59 - ptm->tm_min) * 60 + (59 - ptm->tm_sec) ;
//}
//
//ulong GetElapsedDay(time_t time1, time_t time2)
//{
//    // Since time is based on 1970.1.1 00:00. Thanks for GR, our advanced rencai.
//    // Also we can write more shorter : return time2/DAY - time1/DAY;
//    const int DAY = 60 * 60 * 24;
//    time_t tt1 = time1 - time1 % DAY;
//    time_t tt2 = time2 - time2 % DAY;
//    return (ulong) (tt2 - tt1) / DAY;
//}
//
//
//
//
///*
//*功能：生成简略字符串
//*细节描述： 将源字符串 按照指定长度截断，超出部分以 省略符号表示
//*参数： szString	源字符串
//*		iLen		指定长度
//*返回值： std::string
//*添加：王峰
//*/
//// std::string	GetShortString(LPCTSTR szString, int iLen)
//// {
//// 	const int numDots = 3;
////
//// 	std::string	strShort = szString ? szString : "";
////
//// 	if (-1 == iLen)
//// 		return strShort;
////
//// 	// 处理省略
//// 	if (lstrlen(szString) > iLen + numDots)
//// 	{
//// 		// 处理单双字节
//// 		int lenShort = 0;
////
//// 		while (lenShort < iLen)
//// 		{
//// 			if (IsDBCSLeadByte(szString[ lenShort ]))
//// 			{
//// 				lenShort += 2;
//// 			}
//// 			else
//// 			{
//// 				lenShort++;
//// 			}
//// 		}
////
//// 		// 重新分配内存
//// 		strShort.resize(lenShort + numDots + 1);
////
//// 		//
//// 		for (int c = 0; c < numDots; c++)
//// 			strShort[ lenShort + c ] = '.';
////
//// 		strShort[ lenShort + numDots ] = '\0';
//// 	}
////
//// 	return strShort;
//// }
//
//char *CopyConfigStr(char *dest, size_t max, const std::string &src)
//{
//    assert(dest && max > 0);
//    if (src.length() == 0 ||
//        src == "null" ||
//        src == "NULL" ||
//        src == "0")
//    {
//        dest[0] = '\0';
//    }
//    else
//    {
//        strncpy(dest, src.c_str(), max);
//        dest[max-1] = '\0';
//    }
//    return dest;
//}
//
//const char * GetCurrentPath()
//{
//	static char strPath[MAX_PATH] = "";
//	static bool first = true;
//	if(first)
//	{
//		::GetCurrentDirectoryA(MAX_PATH, strPath);
//		first = false;
//	}
//	return strPath;
//}