#include "ClientHeader.h"

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
using namespace std;

int senddata(int socket,void *data,int length){
	void *len = &length;
	int sent = send(socket,len,sizeof(int),0);
	int total = 0;
	while(total < length){
		sent = send(socket, data, length,0);
		total += sent;
	}

return total;
}

void* recvdata(int socketfd){
	int total = 0;
	void *buff = operator new (100);
	void *len = operator new (8);
	int recv = read(socketfd,len,sizeof(int));
	int *length = (int *) len;
	while(total < *length){
		recv = read(socketfd,buff,*length);
		total += recv;
	}
return buff;
}

void User::SignUp(){
    cout << "-------Dien cac thong tin de dang ky!-------" << endl;
    username = new char[10];
    city = new (char);
    password = new char;
	extern int sockfd;
	cout << "Nhap vao username: ";

	cin >> username;
	void *data = username;
	senddata(sockfd,data,strlen(username));

	cout << "Nhap password: ";
	cin >> password;
	data = password;
	senddata(sockfd,data,strlen(password));
	//password = sha1(password);
	cout << "Enter city: ";

	cin >> city;
	data = city;
	senddata(sockfd,data,strlen(city));

	char s[100];
	recv(sockfd,s, sizeof(s),0);
	cout << s;

}

void  User::SignIn(){
    username = new (char);
    password = new (char);
    extern int sockfd;
    cout << "Nhap vao username: ";
	cin >> username;
	void *data = username;
	senddata(sockfd,data,strlen(username));
	cout << "Nhap password: ";
	cin >> password;

	//password = sha1(password);
	data = password;
	senddata(sockfd,data,strlen(password));

    char s[100];
	recv(sockfd,s, sizeof(s),0);
	cout << s;
}
