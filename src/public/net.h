/**
 * @file net.h
 * @date 2011-09-01
 * @author Fox (yulefox at gmail.com)
 * ����ģ��.
 * ����ײ��׽��ֹ���ԭ��:
 * - ����ײ�ʹ�� entity_t ��Ϊ�������ӵ�ʵ��;
 * - �߼���ʹ�� peer_t ��Ϊ��Ϣ�շ���ʵ��;
 * - �����������׽����� entity_t ����ر�;
 * - �ͻ������Ӽ��߼���ʹ��ͬһ�׽���, ���ӳɹ���󶨵� IOCP, ���׽����� iocp_t
 *   ����ر�;
 * a. �ͻ����߼���ͨ��ʵ������ԭ��:
 * - ���߼���������� ID ����ά��������ʵ������, ��ͻ���ʱ, 
 * ���۷��������ǿͻ���, ���� peer_t ��������ײ��ڽ�������ʱ����, ���ظ��߼���.
 */

#ifndef PUBLIC_NET_H
#define PUBLIC_NET_H

#pragma once

#include "public.h"
#include <winsock2.h>
#include "net/entity.h"
#include "net/message.h"
#include "net/raw.h"

#ifdef _DEBUG
#pragma comment(lib, "libnet_d.lib")
#else
#pragma comment(lib, "libnet.lib")
#endif /* _DEBUG */

BEGIN_C_DECLS

/**
 * Initialize with configure.
 * - log
 * - memory
 */
int net_init(void);
int net_fini(void);
int net_load(void);
int net_start(void);
void net_register(net_func func);
int net_callback(SOCKET s, int type, int res, void *args);
int net_onnotify(SOCKET s, int type, int res, void *args);

END_C_DECLS

#endif /* !PUBLIC_NET_H */