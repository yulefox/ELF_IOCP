/**
 * @file chunk.h
 * @date 2011-09-09
 * @author Fox (yulefox at gmail.com)
 * �ڴ��ʵ��, ʹ��˫�����. chunk ʹ���Ƿ��̰߳�ȫ��, ���뱣֤ chunk ��ͬһʱ
 * �̲��ᱻ���̷߳���.
 * chunk �����ṩ���ݿ��С��¼, ������ʹ���߸�д����ͷ (��������ʼ��С), ��
 * ʹ�������вþ�.
 */

#ifndef ELF_IO_CHUNKIO_H
#define ELF_IO_CHUNKIO_H

#pragma once

#include "public/def.h"

BEGIN_C_DECLS

struct chunk_t *chunk_create(size_t init_size);
void chunk_destroy(struct chunk_t *c);

/**
 * @return current writen size.
 */
int chunk_append(struct chunk_t *c, void *buf, size_t size);
int chunk_retrive(struct chunk_t *c, void *buf, size_t size);

int chunk_set(struct chunk_t *c, void *buf, size_t size);
int chunk_get(struct chunk_t *c, void *buf, size_t size);

/**
 * WSASend used.
 */
int chunk_buffers(struct chunk_t *c, struct _WSABUF **bufs, size_t *count);

END_C_DECLS

#endif /* !ELF_IO_CHUNKIO_H */