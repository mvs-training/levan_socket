#include <iostream>
#include "ServerHeader.h"
//#include "sha1.hpp"
#include<bits/stdc++.h>
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

using namespace std;


int ConnectSQlite::callback(void *NotUsed, int argc, char **argv, char **azColName){
           int i;
           for(i=0; i<argc; i++){
              printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
           }
           printf("\n");
           return 0;
        }
void ConnectSQlite::Open(){
        rc = sqlite3_open("We4.db", &db);
       if( rc ){

          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          exit(0);
       }else{
          //fprintf(stderr, "Opened database successfully\n");

       }

}
void ConnectSQlite::RunInsertParamSQL(sqlite3 *db, char *fn, char *ln,int id ){
  if (!db)return;
  // Insert data item into myTable
  szSQL = "insert into user (username, password,city) values (?,?,?)";

  int rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

  if( rc == SQLITE_OK ) {
    // bind the value
    sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
    sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
    sqlite3_bind_int(stmt, 3, id);
   // sqlite3_bind_int(stmt, 3, age);

    // commit
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }else{

      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      // break the loop if error occur
  }
}
int ConnectSQlite::RunSelectParamSQL(sqlite3 *db,char *us, char *pa){
        int id = 0;
        if (!db)return 0;

        szSQL = "SELECT * FROM  user WHERE username = ? and password = ? ";

        rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);

       if( rc == SQLITE_OK ) {
            // bind the value
            sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
            sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
            // commit
           while(sqlite3_step(stmt) == SQLITE_ROW) {
                stringstream str;
                str << sqlite3_column_text(stmt, 0);
                str >> id ;
            }
            sqlite3_finalize(stmt);


      }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
    return id;

}

void ConnectSQlite::WriteCity(char *name){
    szSQL = "INSERT INTO city(name) VALUES(?)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_text(stmt,1,name,strlen(name),0);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }

}

bool ConnectSQlite::CheckCity(char *name){
    int hascity = 0;
    szSQL = "SELECT idc FROM city WHERE name = ? ";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_text(stmt,1,name,strlen(name),0);
        // commit
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> hascity;

            if(hascity != 0) hascity = 1;
            else hascity = 0;

            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
    return hascity;
}
const unsigned char* ConnectSQlite::TranIdtoCity(int id){
     const unsigned char* s;
    szSQL = "SELECT name FROM city WHERE idc = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK){
        sqlite3_bind_int(stmt,1,id);
        if(sqlite3_step(stmt) == SQLITE_ROW){
            s = sqlite3_column_text(stmt,0);
        }
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return s;
}

const unsigned char* ConnectSQlite::TranIdtoUser(int id){
     const unsigned char* s;
    szSQL = "SELECT username FROM User WHERE id = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK){
        sqlite3_bind_int(stmt,1,id);
        if(sqlite3_step(stmt) == SQLITE_ROW){
            s = sqlite3_column_text(stmt,0);
        }
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return s;
}

int ConnectSQlite::TransNameToId(char *frien){
    int id2 = -1;
    szSQL = "SELECT id FROM User WHERE username = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

    if( rc == SQLITE_OK ){
        sqlite3_bind_text(stmt,1,frien,strlen(frien),0);
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> id2 ;

        }
        sqlite3_finalize(stmt);
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return id2;

}

int ConnectSQlite::TranCitytoId(char *name){

    int id2 = -1;
    szSQL = "SELECT idc FROM city WHERE name = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

    if( rc == SQLITE_OK ){
        sqlite3_bind_text(stmt,1,name,strlen(name),0);
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> id2 ;

        }
        sqlite3_finalize(stmt);
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return id2;
}



void ConnectSQlite::WriteToFriend(sqlite3 *db,int id1, int id2){
    if (!db)return ;
     szSQL = "INSERT INTO Friend VALUES (?,?,?,?,?)";
     rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
     if( rc == SQLITE_OK ) {
            // bind the value
        int isblock = 0;
        time_t hientai = time(0);
        char *dt = ctime(&hientai);
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_text(stmt,3,dt,strlen(dt),0);
        sqlite3_bind_int(stmt,4,isblock);
        sqlite3_bind_int(stmt,4,0);
        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "Write Friend SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::ShowFriendByTime(int id){


}

void ConnectSQlite::ShowFriendByCity(int id){
    szSQL = "SELECT city.idc,User.id FROM city, User,Friend WHERE (Friend.id1 = ? or Friend.id2 = ?) and (User.id = Friend.id1 or User.id = Friend.id2)  and User.city = city.idc and User.id != ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id);
        sqlite3_bind_int(stmt,2,id);
        sqlite3_bind_int(stmt,3,id);
        // commit
        int a[100][100];
        int b[100],c[100];
        memset(b,0,sizeof(b));
        memset(a,0,sizeof(a));
        int coun = 0;
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            int idc,idn;
            stringstream str,st;
            str << sqlite3_column_text(stmt, 0);
            str >> idc;
            if(a[idc][0] ==0 ){c[coun] = idc; coun++;}
            st << sqlite3_column_text(stmt, 1);
            st >> idn;
           // cout << idc << "  " << idn << endl;
            a[idc][b[idc]] = idn;
            //cout << idc << " " << b[idc] << "  " << a[idc][b[idc]] << endl;
            b[idc]++;

        }
        for(int i = 0; i< coun;i++) {
            cout << TranIdtoCity(c[i]) << endl ;
            for(int j =0; j< b[c[i]]; j++) {
                cout << "  " <<  j+1 << "."  << TranIdtoUser(a[c[i]][j]) << endl;

            }
            cout << endl;
        }
        sqlite3_finalize(stmt);

            cout <<"-------------------------------------\n";
    }else{

          fprintf(stderr, "City SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }

}
void ConnectSQlite::ShowFriend(sqlite3 *db,int id1,string s[]){
    cout << "-------List Friends-----------\n";
    if (!db)return ;
    szSQL = "SELECT DISTINCT user.username FROM"
                "(SELECT * FROM friend where (id1 = ? OR id2 = ?) AND RelationshipStatus != 1 )  as A LEFT JOIN user ON (A.id2 = user.id OR A.id1 = user.id)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id1);
        // commit

        int i = 0,t =1;

        while(sqlite3_step(stmt) == SQLITE_ROW) {
           s[i] = string((const char *) sqlite3_column_text(stmt, 0)) ;
           cout <<t << "." <<  s[i] << endl;
           i++; t++;
        }
        sqlite3_finalize(stmt);

            cout <<"-------------------------------------\n";
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

int ConnectSQlite::CheckBlock(int id1, int id2){
    int isblock = 0;
     if (!db)return 0;
     szSQL = "SELECT RelationshipStatus FROM Friend WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
     rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,3,id2);
        sqlite3_bind_int(stmt,4,id1);

        // commit
        //sqlite3_step(stmt);
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> isblock ;
            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
      return isblock;
}

int ConnectSQlite::CheckWhoBlock(int id1,int id2){
    int whoblock = 0;
    szSQL = "SELECT whoblock FROM Friend WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,4,id1);
        sqlite3_bind_int(stmt,3,id2);
        //sqlite3_step(stmt);
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> whoblock ;
            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
      return whoblock;
}

bool ConnectSQlite::CheckFriend(sqlite3 *db, int id1,int id2){
    int isFriend = 0;
    szSQL = "SELECT * FROM Friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
      if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,3,id2);
        sqlite3_bind_int(stmt,4,id1);
        // commit
       if(sqlite3_step(stmt) == SQLITE_ROW ){
           stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> isFriend;

            if(isFriend != 0) isFriend = 1;
            else isFriend = 0;

            sqlite3_finalize(stmt);
        }
    }else{

          fprintf(stderr, "Check Friend SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
      return isFriend;
}

void ConnectSQlite::UpdateStatusFriend(sqlite3 *db,int status,int id1, int id2){
     if (!db)return ;
     int who = 0;
     if (status == 1) who = id1;

     szSQL = "UPDATE Friend SET RelationshipStatus = ? , whoblock = ? WHERE (id1 = ? AND id2 = ?) OR (id1 = ? AND id2 = ?)";
     rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
     if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,status);
        sqlite3_bind_int(stmt,2,who);
        sqlite3_bind_int(stmt,3,id1);
        sqlite3_bind_int(stmt,4,id2);
        sqlite3_bind_int(stmt,5,id2);
        sqlite3_bind_int(stmt,6,id1);
        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::WriteToMess(sqlite3 *db,int id1, int id2,char *mes,char *time){
         szSQL = "INSERT INTO messenger VALUES (?,?,?,?,1)";
         rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
         if( rc == SQLITE_OK ) {
                // bind the value
            sqlite3_bind_int(stmt,1,id1);
            sqlite3_bind_int(stmt,2,id2);
            sqlite3_bind_text(stmt,3,mes,strlen(mes),0);
            sqlite3_bind_text(stmt,4,time,strlen(time),0);
            // commit
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);

        }else{

              fprintf(stderr, "writetomess SQL error: %s\n", zErrMsg);
              sqlite3_free(zErrMsg);
              // break the loop if error occur
          }

}


void ConnectSQlite::SelectMessenger(sqlite3 *db, int id){
    if (!db)return ;
    szSQL = "SELECT DISTINCT user.username FROM"
                "(SELECT * FROM messenger where idsen = ? ) as A LEFT JOIN user ON A.idrec = user.id";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            answer.push_back(string((const char *) sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
        cout <<"-----Danh sach tin nhan-------\n" ;
        for( list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
            cout << *it << endl;

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}


void ConnectSQlite::ShowMessDetail(sqlite3 *db,int id1,int id2){
    if (!db)return ;
    cout << "--------Detail--------\n";
    szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (idsen = ? OR idsen = ?) AND (idrec = ? OR idrec =?) ) AS B LEFT JOIN  user ON user.id = B.idsen";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    // cout << id1 << id2;
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        sqlite3_bind_int(stmt,2,id2);
        sqlite3_bind_int(stmt,3,id1);
        sqlite3_bind_int(stmt,4,id2);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 5)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 2)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 3)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::ShowMessRec(int id1){
    if (!db)return ;
    cout << "-------Nhan--------\n";
    szSQL = "select u.username, m.contend,m.time from messenger m,User u where m.idrec = ? and u.id = m.idsen";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    // cout << id1 << id2;
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 0)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 1)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 2)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

void ConnectSQlite::ShowMessSen(int id1){
    if (!db)return ;
    cout << "-------Gui--------\n";
    szSQL = "select u.username, m.contend,m.time from messenger m,User u where m.idsen = ? and u.id = m.idrec";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    // cout << id1 << id2;
    if( rc == SQLITE_OK ) {
            // bind the value
        sqlite3_bind_int(stmt,1,id1);
        // commit
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 0)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 1)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 2)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
          // break the loop if error occur
      }
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

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
    //d0.0.cout << "-------Dien cac thong tin de dang ky!-------" << endl;
    username = new char(100);
    city = new char (100);
    password = new char(100);
    extern int client_sockfd;
    void *buff = recvdata(client_sockfd);
	username = (char *) buff;
	cout << username << endl;

	buff = recvdata(client_sockfd);
	password = (char *) buff;
	cout << password<< endl;

	buff = recvdata(client_sockfd);
	city = (char *) buff;
	cout << city << endl;
	//password = sha1(password);
    //cout << password;


	ConnectSQlite conn ;
	conn.Open();
    if(!conn.CheckCity(city)) conn.WriteCity(city);
    int idc = conn.TranCitytoId(city);
    conn.RunInsertParamSQL(conn.db,username,password,idc);
    char s[100] = "Successfully!\n";
    send(client_sockfd,s,sizeof(s),0);
}
void  User::SignIn(){
    username = new (char);
    password = new (char);

    extern int client_sockfd;

    void *buff = recvdata(client_sockfd);
	username = (char *) buff;
	cout << username << endl;

	buff = recvdata(client_sockfd);
	password = (char *) buff;
	cout << password<< endl;

	//password = sha1(password);
	ConnectSQlite conn ;
	conn.Open();

	if(conn.RunSelectParamSQL(conn.db,username,password) > 0) {
        cout << "Sign in successfuly!\n";
        char s[100] = "Successfully!\n";
        send(client_sockfd,s,sizeof(s),0);
        id = conn.RunSelectParamSQL(conn.db,username,password);
        flag = 1;

	}
	else {
        cout << "Sign in fail!\n";
        flag = 0;
	}
    //conn.SelectUser1();
}
void User::SignOut(){
    flag = 0;
    cout << "-----Ban da dang xuat.-------\n";
}
bool User::isSignIn(){
    ConnectSQlite conn;
    if(flag == 1) return true;
    return false;
}

void User::EditInfoFriend(User u){

    /* 0: Friends
       1: Block
       2: Close Friend
    */
    if (isSignIn()){
        ShowFriend(u.id);
        cout << "Nhap vao ten ban be can chinh sua: ";
        char *frien = new char;

        cin >> frien;
        ConnectSQlite conn;
        conn.Open();
        int id2 = conn.TransNameToId(frien);
        if(id2 > 0){
            cout << "Tinh trang ban be hien tai: ";
            if(conn.CheckBlock(u.id,id2) == 0) cout << "Friends.\n";
            else if(conn.CheckBlock(u.id,id2) == 1) cout << "isBlock.\n";
            else cout << "Close Friend.\n";
            cout << "------Nhap thay doi-----------\n"
                << "1.Block\n"
                << "2.Bo Block \n"
                << "3.Close Friend\n";
                int choose;
                cin >> choose;
            if(choose == 1 ) {
                if(conn.CheckBlock(u.id,id2) == 0 ){

                    conn.UpdateStatusFriend(conn.db,1,u.id,id2);
                    cout <<"---------Block Successfuly---------\n";
                    string s[100];
                    conn.ShowFriend(conn.db,u.id,s);
                }else cout << "----Ban da block nguoi nay------\n ";

            }
            if(choose == 2) {
                if(conn.CheckBlock(u.id,id2) == 1 && conn.CheckWhoBlock(u.id,id2) == u.id){
                    conn.UpdateStatusFriend(conn.db,0,u.id,id2);
                    cout <<"---------Ban da bo Block nguoi nay---------\n";
                } else { cout << "---Ban khong co quyen bo block hoac chua block---\n";}
            }
            if(choose == 3){
                conn.UpdateStatusFriend(conn.db,2,u.id,id2);
                cout << "-----Ban than da duoc them-------\n";
            }
        }else cout << "-----Tai khoan khon ton tai-----\n";
    }else  cout << "----------Ban chua dang nhap.--------\n\n";

}


void User::AddFriend(int id){
    if (isSignIn()){
        cout << "Nhap ten nguoi ban muon them: ";
        char *newfr;
        newfr = new char;
        cin >> newfr;
        ConnectSQlite conn;
        conn.Open();
        int id2 = conn.TransNameToId(newfr);
        //cout << "OK1" << id2;
        if(id2 > 0){
            if(conn.CheckBlock(id,id2) == 0 && !conn.CheckFriend(conn.db,id,id2) ){
                conn.WriteToFriend(conn.db,id,id2);
                ShowFriend(id);
            }else {
                //conn.CheckBlock(id,id2);
                cout << "------You were blocked by her  or You was friend ----------\n\n\n";
                //conn.CheckFriend(conn.db,id,id2);
            }
        }else cout <<  "----Tai khoan khong ton tai-----------\n";
    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }

}

void User::ShowFriend(int id,string s[]){
    if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowFriend(conn.db,id,s);

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }
}

void User::ShowFriendByCity(int id){
    if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowFriendByCity(id);

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }
}

void User::ShowFriend(int id){
    if (isSignIn()){

        ConnectSQlite conn;
        conn.Open();
        string s[100];
        conn.ShowFriend(conn.db,id,s);

    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }
}

void User::ShowMess(int id){
    //cout << id;
   // cout << this->id << " " << this->flag;
    if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.SelectMessenger(conn.db,id);
    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }



}
void User::ShowMessRec(int id){
     if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowMessRec(id);
     }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
     }
}

void User::ShowMessSen(int id){
     if (isSignIn()){
        ConnectSQlite conn;
        conn.Open();
        conn.ShowMessSen(id);
     }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
     }
}

void User::ShowMessDetail(int id1){
    if (isSignIn()){
        int id2;
        cout << "Chon nguoi dung: ";
        char *frien;
        frien = new char;
        cin >> frien;
        ConnectSQlite conn;
        conn.Open();
        id2 = conn.TransNameToId(frien);

        if(id2 > 0)
        conn.ShowMessDetail(conn.db,id1,id2);
        else cout <<  "----Tai khoan khong ton tai-----------\n";

        cout << "Nhan Ctrl + R de gui tiep tin nhan,esc de thoat\n";
        //char esc;
      //  cin.ignore();
        //esc = getch();

            char ctrlL;
            cin.ignore();
            ctrlL = getch();
            if( ctrlL == 18 ){
                 time_t hientai = time(0);
                 char *dt, *mess = new char;
                 dt = ctime(&hientai);
                 cout << "Nhap Tin nhan: \n";
                 cin >> mess;
                 conn.WriteToMess(conn.db,id1,id2,mess,dt);
                 conn.ShowMessDetail(conn.db,id1,id2);
            }


    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    }

}


void User::SendMess(int id){
    if (isSignIn()){
        int id2;
          ConnectSQlite conn;
        conn.Open();
        cout << "1.Nhap nguoi dung\n "
             << "2.Nhan Ctrl + L de hien thi danh sach\n";


        int choose; char choo;
        cin >> choose;
        string s [100];
        char *username = new char;

        if(choose == 1){
            cout << "Nhap ten ban be: ";
            cin >> username;
        }
         if(choose == 2) {

            cout << "Press Ctrl + L to continue.\n";
            cin.ignore();
            choo = getch();

            if(choo == 12){

                ShowFriend(id,s);
                cout << "Chon so thu tu\n";
                int chon;
                cin >> chon;
                //username = s[chon-1];
                memcpy(username, s[chon-1].c_str(), sizeof(s[chon-1]));
                //cout << s[chon-1].c_str() << "  " << username <<  "   " << s[chon-1].length()<<" ok\n";

            }else cout << choo;
        }
        //username = name.c_str();
        id2 = conn.TransNameToId(username);
        //cout << id2;
        if(id2 > 0){
            char *mess,*dt;
            mess = new char;
            dt =new char;
            if(conn.CheckBlock(id,id2)){
                        cout << conn.CheckBlock(id,id2) ;
                        cout << "---------You is blocked by her--------\n";
            }else{
                cout << "Nhap Tin nhan: \n";
                cin >> mess;
                 time_t hientai = time(0);
                 dt = ctime(&hientai);
                 conn.WriteToMess(conn.db,id,id2,mess,dt);
                 conn.ShowMessDetail(conn.db,id,id2);

            }
        }else cout <<  "----Tai khoan khong ton tai-----------\n";

/*
        ConnectSQlite conn;
        conn.Open();
        id2 = conn.TransNameToId(frien);
        //cout << id2;
        if(id2 > 0){
            char *mess,*dt;
            mess = new char;
            dt =new char;
            if(!conn.CheckBlock(id,id2)){
                        cout << "---------You is blocked by her--------\n";
            }else{
                cout << "Nhap Tin nhan: \n";
                cin >> mess;
                 time_t hientai = time(0);
                 dt = ctime(&hientai);
                 conn.WriteToMess(conn.db,id,id2,mess,dt);
                 conn.ShowMessDetail(conn.db,id,id2);
            }
        }else cout <<  "----Tai khoan khong ton tai-----------\n";
    }else {
        cout << "----------Ban chua dang nhap.--------\n\n";
    } */
    }
}

