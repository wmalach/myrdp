// socketclint.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "conio.h"
#include "windows.h"
#include "winsock.h"
#pragma comment(lib,"ws2_32.lib")

void TCPClient()
{
	//����socket
	SOCKET sockclient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(INVALID_SOCKET == sockclient)
	{ 
		return;
	}
	//���ӷ��������������������׽��ֵ�ַ
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5678);
//	addr.sin_port = htons(3389);
	//����inet_addr()���������ǰѡ�xxx.xxx.xxx.xxx����ʽ��ʾ��IPV4��ַ��ת��ΪIN_ADDR�ṹ���ܹ�
	//���յ���ʽ��unsigned long�ͣ���ΪIN_ADDR�ṹ���еĸ�����յ�S_addr��Ա������������unsigned long�ͣ�
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//����ip

	//������������������󣬵�Ȼ����Ҳ����ͨ��connet�����ķ���ֵ�жϵ����������ӳɹ���
	int iRetVal = connect(sockclient,(struct sockaddr*)&addr,sizeof(addr));
	if(SOCKET_ERROR == iRetVal)
	{
		printf("����������ʧ�ܣ�");
		closesocket(sockclient);
		return;
	}
	printf("���������ӳɹ���\n");
	//�����շ�
	CHAR szSend[100] = "hello server";   //�ͻ���  �ȷ�����
	send(sockclient,szSend,sizeof(szSend),0);  //���ͺ���������ͨ������ֵ�жϷ��ͳɹ����

	//���շ������ش�������
	CHAR szRecv[100] = {0};
	recv(sockclient,szRecv,100,0); //���պ���
	printf("%s\n",szRecv);//��ʾ���ַ����ĸ�ʽ����������˷��͵����ݡ�

	//  getch();//��ͣһ��
	//�ر�socket
	closesocket(sockclient);
}
void UDPClient()
{
	//����SOCKET ��ipЭ���壬���ݱ���ʽ��udpЭ�顣
	SOCKET sockclient = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(INVALID_SOCKET == sockclient)
	{
		return ;
	}
	//�����շ������������׽��ֵ�ַ
	struct sockaddr_in svraddr = {0};
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(5780);
	svraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//ָ���������˵�IP��˿ڡ�
	CHAR szSend[100] = "hello udp server";
	/*�˺������ǿͻ��˵��׽��֣�Ȼ���Ƿ������˵�ַ*/
	//�����Ϊ:�Ӻ���ǰ��Ŀͻ����׽��ֵķ������ݻ������н������͸��������˵�ַ
	sendto(sockclient,szSend,100,0,(struct sockaddr*)&svraddr,sizeof(svraddr));//����ʱ����ip��ַ�Ͷ˿ڡ�

	//ע���ó���Ҳ���Խ��շ������˻ش������ݡ�
	CHAR szRecv[100];  
	//�����Ϊ���Ӻ�������ķ������˵�ַ��ȡ�����ͻ����׽��ֵĽ��ջ�����szRecv��
	int len = sizeof(svraddr);
	recvfrom(sockclient,szRecv,100,0,(struct sockaddr*)&svraddr,&len);
	printf("%s \n",szRecv);
	//�ر�socket
	closesocket(sockclient);
}

int main(int argc, _TCHAR* argv[])
{
	//��ʼ��socket��
	WSADATA wsa = {0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	//tcp�ͻ���
	TCPClient();
	//UDPClient();
	//�����׽�����Դ
	WSACleanup();
	_getch();


	return 0;
}