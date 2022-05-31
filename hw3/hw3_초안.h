#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#define MAX_STRING 32
#define MAX_VALUE 100
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

//파일 입출력 전역변수
ifstream fin;
ofstream fout;


// Class : Account
// Description: 회원 계정의 Entity class
// 
// Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// mail: gracias9022@g.hongik.mail.com
//
// Revsions :
// 1. When & Who :  
// What :   
//

class Account
{
private:
	string name;
	string ssn;
	string ID;
	string password;
	bool logStatus;

public:  
	void createAccount(string name, string ssn, string ID, string password); 
	bool getLogStatus();
	bool setLogStatus();
	string getID();
	string getPassword();
	string getName();
	string getSsn(); 
};


// Class : AccountDB
// Description: 회원 계정 정보를 저장하과 관리하는 DB Entity 클래스 
// ……………………………………….
// ………………………………………
// Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// mail: gracias9022@g.hongik.mail.com
//
// Revsions :
// 1. When & Who :  
// What :   
//


class AccountDB
{
private:
	Account* accounts[MAX_VALUE];
public:
	void storeAccount(Account* account);
	void deleteAccount(string ID);
	Account* getAccountIndex(string ID);
	bool checkAccount(string ID, string password);
	Account* logIn(string ID, string password);
	Account* logOut(string ID);
};


// 회원가입, 탈퇴, 로그인, 로그아웃 컨트롤과 바운더리
class SelectMenu {

public:
	void doTask();
};

//Class : 회원가입 바운더리
class CreateAccountUI {
	CreateAccount* createAccount;
public:
	CreateAccountUI(CreateAccount* createAccount);
	void enterAccountInfo();
};


//Class : 회원가입 컨트롤
class CreateAccount {
	CreateAccountUI* createAccountUi;
	Account* account;
public:
	CreateAccount();
	void createNewAccount(string name, string ssn, string id, string password);
};


//Class : 회원탈퇴 바운더리
class DeleteAccountUI {
	DeleteAccount* deleteAccount;
public:
	DeleteAccountUI(DeleteAccount* deleteAccount);
	void enterDeleteInfo();
};

//Class : 회원탈퇴 컨트롤
class DeleteAccount {
	DeleteAccountUI* deleteAccountUi;
	Account* account;
public:
	DeleteAccount();
	void deleteThisAccount(string id);
};


//Class : 로그인 바운더리
class LoginUI {
	Login* login;
public:
	LoginUI(Login* login);
	void enterLoginInfo();
};


//Class : 로그인 컨트롤
class Login {
	LoginUI* loginUi; 
	Account* loginPointer; // 로그인을 시도한 계정을 가리키는 포인터
public:
	Login();
	void requestLogin(string ID, string password);
	Account* getLoginAccount(); // 로그인한 회원을 반환
};


//Class : 로그아웃 바운더리
class LogOutUI {
	LogOut* logOut;
public:
	LogOutUI(LogOut* logOut);
	void enterLogOutInfo();
};


//Class : 로그인 컨트롤
class LogOut{
	LogOutUI* logOutUi; 
	Account* logOutPointer; // 로그인을 시도한 계정을 가리키는 포인터
public:
	LogOut();
	void requestLogOut(string ID);
};

