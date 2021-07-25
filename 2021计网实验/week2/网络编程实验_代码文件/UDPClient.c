#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
    WSADATA data;
    int state = WSAStartup(MAKEWORD(2,2),&data);//初始化
    if(state != 0) {
        printf("initial error\n");
        return 0;
    }
    SOCKET word = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);//初始化套接字
    if(word == INVALID_SOCKET) {
        printf("socket error\n");
        return 0;
    }
    struct sockaddr_in my_socket;

    my_socket.sin_family = AF_INET;
    my_socket.sin_port = htons(10000);
    //my_socket.sin_addr.s_addr = inet_addr("49.232.4.77"); //互联网IP
    //my_socket.sin_addr.s_addr = inet_addr("192.168.43.66");//局域网IP
    my_socket.sin_addr.s_addr = inet_addr("172.19.20.150");//局域网IP

    int size;
    printf("Please enter the number of packages you are ready to send:\n");
    scanf("%d",&size);//选择要发送的包的数量
    for(int i=1;i<=size;i++){
        char buf[30];
        char num[10];
        strcpy(buf,"Package ");
        itoa(i,num,10);
        strcat(buf,num);//此时buf的内容为最终发送内容："Package X"
        int cc = sendto(word, buf, strlen(buf), 0,(SOCKADDR *)&my_socket, sizeof(my_socket));//发送包到服务端
        if (cc == SOCKET_ERROR){
            printf("send error\n");
            return 0;
        }
        //Sleep(1)//使每个包之间的发送时间间隔1ms，达到缓冲的效果，减少因数据发送太快而导致的丢包
    }
    closesocket(word);
    WSACleanup();
}