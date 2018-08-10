#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "ClientHeader.h"
#include <arpa/inet.h>
#include <sys/types.h>
using namespace std;
int sockfd; /* số mô tả socket – socket handle */
int len;
struct sockaddr_in address; /* structure sockaddr_in, chứa các thông tin về socket AF_INET */
int result;
int main(){
     
     int  ch = 19;
     /* 2. Tạo socket cho trình khách. Lưu lại số mô tả socket */
     sockfd = socket( AF_INET, SOCK_STREAM, 0 );
     /* 3. Đặt tên và gán địa chỉ kết nối cho socket theo giao thức Internet */
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
     address.sin_port = htons( 9735 );
     len = sizeof( address );
     /* 4. Thực hiện kết nối */

     result = connect( sockfd, (struct sockaddr*)&address, len );
     if ( result == -1 ) {
         perror( "Oops: client1 problem" );
         exit( 1 );
     }
    while(1){
                cout << "-------Chon chuc nang: ------\n"
                    "1.Dang ky\n"
                    "2.Dang nhap\n"
                    "3.Hien thi tin nhan\n"
                    "4.Hien thi chi tiet tin nhan\n"
                    "5.Hien thi  tin nhan nhan duoc\n"
                    "6.Hien thi tin nhan da gui\n"
                    "7.Gui tin nhan\n"
                    "8.Them ban be\n"
                    "9.Hien thi ban be\n"
                    "10.Hien thi ban be theo thanh pho\n"
                    "11.Chinh sua thong tin ban be\n"
                    "12.Dang xuat\n"
                    "-----------------------\n";

            int choose;
            cin >> choose;
	    send(sockfd, &choose, sizeof(choose),0);
            User us = User();
            string s[100];
            switch(choose){
                case 1:
                    us.SignUp();
                    break;
                case 2:
                   us.SignIn();
                    break;
                case 3:
                  //  us.ShowMess(us.id);
                    break;
                case 4:
                    //us.ShowMessDetail(us.id);
                    break;
                case 5:
                   // us.ShowMessRec(us.id);
                    break;
                case 6:
                  //  us.ShowMessSen(us.id);
                    break;
                case 7:
                  //  us.SendMess(us.id);
                    break;
                case 8:
                   // us.AddFriend(us.id);
                    break;
                case 9:
                  //  us.ShowFriend(us.id,s);
                    break;
                case 10:
                  //  us.ShowFriendByCity(us.id);
                case 11:
                //    us.EditInfoFriend(us);
                  //  us.BlockFriend(us.id);
                    break;
                case 12:
                    us.SignOut();
                    break;

                default:
                    cout << "Xin moi nhap lai\n";
                    break;

            }
    }
    return 0;
}
