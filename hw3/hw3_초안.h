#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

#define MAX_STRING 32
#define MAX_VALUE 100
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

//���� ����� ��������
ifstream fin;
ofstream fout;


// Class : Account
// Description: ȸ�� ������ Entity class
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
// Description: ȸ�� ���� ������ �����ϰ� �����ϴ� DB Entity Ŭ���� 
// ������������������������������.
// ������������������������������
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


// ȸ������, Ż��, �α���, �α׾ƿ� ��Ʈ�Ѱ� �ٿ����
class SelectMenu {

public:
	void doTask();
};

//Class : ȸ������ �ٿ����
class CreateAccountUI {
	CreateAccount* createAccount;
public:
	CreateAccountUI(CreateAccount* createAccount);
	void enterAccountInfo();
};


//Class : ȸ������ ��Ʈ��
class CreateAccount {
	CreateAccountUI* createAccountUi;
	Account* account;
public:
	CreateAccount();
	void createNewAccount(string name, string ssn, string id, string password);
};


//Class : ȸ��Ż�� �ٿ����
class DeleteAccountUI {
	DeleteAccount* deleteAccount;
public:
	DeleteAccountUI(DeleteAccount* deleteAccount);
	void enterDeleteInfo();
};

//Class : ȸ��Ż�� ��Ʈ��
class DeleteAccount {
	DeleteAccountUI* deleteAccountUi;
	Account* account;
public:
	DeleteAccount();
	void deleteThisAccount(string id);
};


//Class : �α��� �ٿ����
class LoginUI {
	Login* login;
public:
	LoginUI(Login* login);
	void enterLoginInfo();
};


//Class : �α��� ��Ʈ��
class Login {
	LoginUI* loginUi; 
	Account* loginPointer; // �α����� �õ��� ������ ����Ű�� ������
public:
	Login();
	void requestLogin(string ID, string password);
	Account* getLoginAccount(); // �α����� ȸ���� ��ȯ
};


//Class : �α׾ƿ� �ٿ����
class LogOutUI {
	LogOut* logOut;
public:
	LogOutUI(LogOut* logOut);
	void enterLogOutInfo();
};


//Class : �α��� ��Ʈ��
class LogOut{
	LogOutUI* logOutUi; 
	Account* logOutPointer; // �α����� �õ��� ������ ����Ű�� ������
public:
	LogOut();
	void requestLogOut(string ID);
};

