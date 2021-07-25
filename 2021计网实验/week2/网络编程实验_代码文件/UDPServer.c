#include<time.h>
#include<windows.h>
#include<winsock2.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib");

int main() {
    WSADATA data;
    int state = WSAStartup(MAKEWORD(2,2),&data);
    if(state != 0) {
        printf("initial error\n");
        return 0;
    }
    SOCKET word = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);
    if(word == INVALID_SOCKET) {
        printf("socket error\n");
        return 0;
    }
    struct sockaddr_in my_socket;
    struct sockaddr_in from;        //sender address
	int  fromsize = sizeof(from);
    my_socket.sin_family = AF_INET;
    my_socket.sin_port = htons(10000);//开放和客户端一样的端口
    my_socket.sin_addr.s_addr = INADDR_ANY;   
    if(bind(word,(LPSOCKADDR)&my_socket,sizeof(my_socket)) == SOCKET_ERROR) {
        printf("bind error\n");
        return 0;
    }
    char rev[64];
    int size = 0;
    char res[50];
    int result;
 	while(1){
        fflush(stdout);//每次接收前先清空并输出当前缓冲区
	    int cc = recvfrom(word, rev,100, 0, (SOCKADDR *)&from, &fromsize);//接收客户端数据包
	    if (cc == SOCKET_ERROR){
            printf("recvfrom() failed; %d\n", WSAGetLastError());
            break;
        }
        else if (cc == 0)
            break;
		else{
            size ++;
			rev[cc] = '\0';
            printf("The server is receiving......\n");
			printf("The content of the package for this time is: %s\n",rev);
            printf("The number of received packages is %d in total.\n\n",size);
        }
	}
    closesocket(word);
    WSACleanup();
}