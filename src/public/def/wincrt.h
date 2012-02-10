#ifndef ELF_DEF_WINCRT_H
#define ELF_DEF_WINCRT_H

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

// Windows ͷ�ļ�
#include <objbase.h>
#include <mmsystem.h>
#include <windows.h>
#include <Commdlg.h>
#include <commctrl.h>

// C ����ʱͷ�ļ�
#include <assert.h>
#include <fcntl.h>
#include <process.h>
#include <malloc.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <time.h>
#include <crtdbg.h>
#include <io.h>

#endif /* !ELF_DEF_WINCRT_H */
