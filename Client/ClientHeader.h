#include <iostream>
#include <sqlite3.h>
#include<bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
//#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;
class User{
	public:
		int  id;
		char *username;
		char *password;
		char *city;
		int flag ; //danh dau dang nhap

	public :
        User(){};
		void SignUp();
        void SignIn();
        bool isSignIn(); // kiem tra da dang nhap chua
        void SignOut();
        bool Check(User u);
        void ShowMess(int);
        void ShowMessDetail(int);
        void SendMess(int);
        void AddFriend(int);
        void ShowFriend(int);
        void ShowFriend(int,string s[]);
        void ShowFriendByCity(int);
        void ShowMessRec(int);
        void ShowMessSen(int);
        void BlockFriend(int);
        void EditInfoFriend(User u);
        void (*signal(int sig, void (*func)(int)))(int);

};
int senddata(int socket,void *data,int length);

void* recvdata(int socketfd);
