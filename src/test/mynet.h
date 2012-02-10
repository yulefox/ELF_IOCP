/**
 * ���� socket ����Ϊ���ӵ�Ψһ��ʶ, ���ϲ�ʹ��ʱΪ���� socket ��ӡ��, �����
 * Ϊ id, ��˸�ģ���� socket, id, type �ȱ������Ƹ���, ����Ա�ʶ.
 */
#ifndef LIBDB_MYNET_H
#define LIBDB_MYNET_H

#include "public/net.hpp"

int mynet_init(void);
int mynet_fini(void);

void mynet_server_ready(int type, int id, bool flag);
bool mynet_server_isready(void);

/**
 * ���������¼�
 */
int mynet_proc_event(SOCKET s, int type, int res, void *args);

/**
 * ����������Ϣ.
 */
int mynet_proc_msg(void);

int mynet_send(CMessage &msg, net_type t);

#endif /* !LIBDB_MYNET_H */
