/* 1.Tạo các #include cần thiết */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
/* dành riêng cho AF_INET */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include<pthread.h>
#include <stdlib.h>

#include "ServerHeader.h"
void *dothread(void *);
int server_sockfd, client_sockfd;
    int server_len, client_len;
     struct sockaddr_in server_address;
     struct sockaddr_in client_address;
int main()
{
/*
     int server_sockfd, client_sockfd;
     int server_len, client_len;
     struct sockaddr_in server_address;
     struct sockaddr_in client_address;
*/
     /* 2. Thực hiện khởi tạo socket mới cho trình chủ */
     server_sockfd = socket( AF_INET, SOCK_STREAM, 0 );
     /* 3. Đặt tên và gán địa chỉ kết nối cho socket theo giao thức Internet */
     server_address.sin_family = AF_INET;
     server_address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
     server_address.sin_port = htons( 9735 );
     server_len = sizeof( server_address );

     /* 4. Ràng buộc tên với socket */
     bind( server_sockfd, (struct sockaddr *)&server_address, server_len );

     /* 5. Mở hàng đợi nhận kết nối - cho phép đặt hàng vào hàng đợi tối đa 5 kết nối */
     listen( server_sockfd, 5 );
     /* 6. Lặp vĩnh viễn để chờ và xử lý kết nối của trình khách */
   int *choose;
	client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,(socklen_t*)&client_len);

//	cout << choose << endl;
	while(1){
        //recv(client_sockfd, &choose,sizeof(choose),0);
        void *buff = recvdata(client_sockfd);
        choose = (int *) buff;
		User us = User();
		string s[100];
		cout << choose <<endl;
		switch(*choose){
		    case 1:
		        us.SignUp();
		        break;
		    case 2:
		        us.SignIn();
		        break;
		    case 3:
		        us.ShowMess(us.id);
		        break;
		    case 4:
		        us.ShowMessDetail(us.id);
		        break;
		    case 5:
		        us.ShowMessRec(us.id);
		        break;
		    case 6:
		        us.ShowMessSen(us.id);
		        break;
		    case 7:
		        us.SendMess(us.id);
		        break;
		    case 8:
		        us.AddFriend(us.id);
		        break;
		    case 9:
		        us.ShowFriend(us.id,s);
		        break;
		    case 10:
		        us.ShowFriendByCity(us.id);
		    case 11:
		        us.EditInfoFriend(us);
		      //  us.BlockFriend(us.id);
		        break;
		    case 12:
		         us.SignOut();
		        break;


        }
	}
}

