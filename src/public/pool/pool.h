/**
 * @file pool.h
 * @date 2011-09-02
 * @author Fox (yulefox at gmail.com)
 * ����ԭ DataBlock ʵ�ֵ��ڴ��, �� C �ӿڷ�װ�ڴ��ķ������ͷ�.
 * @todo Ԥ�������.
 * @todo Ŀǰʵ��Ϊ���߳�, Ч���Ե�, �ɿ���ʵ�ֵ��߳��ڴ��, �����ͨ����.
 */

#ifndef ELF_POOL_POOL_H
#define ELF_POOL_POOL_H

#pragma once

#include "public/def.h"

BEGIN_C_DECLS

/**
 * @return 0
 */
int pool_init(void);

/**
 * @return 0
 */
int pool_fini(void);
void *pool_alloc(size_t size);
void pool_free(void *block);

END_C_DECLS

#endif /* !ELF_POOL_POOL_H */