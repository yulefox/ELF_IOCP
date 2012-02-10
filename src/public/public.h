/**
 * @file public.h
 * @date 2011-08-29
 * @author Fox (yulefox at gmail.com)
 * ����ģ�� (public) �ṩ�ⲿ������ͷ�ļ�.
 * ����ģ���ṩ����־д�뼰���ݿ���书��.
 */

#ifndef ELF_PUBLIC_H
#define ELF_PUBLIC_H

#pragma once

#include "def.h"
#include "def/GUID.h"
#include "def/stl.h"
#include "def/type.h"
#include "def/wincrt.h"

#include "log/log.h"

#include "pool/pool.h"
#include "pool/chunk.h"

#include "utils/Tools.h"

#ifdef _DEBUG
#pragma comment(lib, "libpublic_d.lib")
#else
#pragma comment(lib, "libpublic.lib")
#endif /* _DEBUG */

BEGIN_C_DECLS

/**
 * ��ʼ������ģ��
 * - ��־
 * - �ڴ��
 * @return 0
 */
int public_init(void);

/**
 * @return 0
 */
int public_fini(void);

END_C_DECLS

#endif /* !ELF_PUBLIC_H */
