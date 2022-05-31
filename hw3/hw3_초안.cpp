#include "hw3.h"
using namespace std; 

// Account class 멤버 함수 구현

// Function : void createAccount(string name, string ssn, string ID, string password)
// Description: Account 객체를 생성하고 name, ssn, ID, password data 저장
// Parameters //  
// name : 객체의 name data
// ssn : 객체의 ssn data. Social Security Number
// ID : 객체의 ID data
// password : 객체의 password data
// Return Value : void
// 
// // Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// 
// // Revsions :
// 1. When & Who :  
// What :  
 

void Account::createAccount(string name, string ssn, string ID, string password)
{
	this->name = name;
	this->ssn = ssn;
	this->ID = ID;
	this->password = password;
	this->logStatus = true; //계정 생성시 로그인 상태로 전환
}

// getLogStatus() : 멤버객체의 LogStauts를 Bool로 리턴
// setLogStatus() : 멤버객체의 LogStauts의 Bool값을 반전
// getID() : 멤버객체의 ID를 스트링으로 리턴
// getPw() : 멤버객체의 password를 스트링으로 리턴
// getName() : 멤버객체의 name을 스트링으로 리턴
// getSsn() : 멤버객체의 ssn을 스트링으로 리턴

bool Account::getLogStatus() { return this->logStatus; }
bool Account::setLogStatus()
{
	if (this->logStatus == false) { this->logStatus = true; }
	else { this->logStatus = false; }
}
string Account::getID() { return this->ID; } 
string Account::getPassword() { return this->password; } 
string Account::getName() { return this->name; } 
string Account::getSsn() { return this->ssn; }   


// Function : void storeAccount(string& name, string& ssn, string& ID, string& password)
// Description: 생성한 Account 객체를 AccountDB내에 전달해 저장. 리스트 맨 앞 인덱스부터 저장
// Parameters //  
// name : 객체의 name data
// ssn : 객체의 ssn data. Social Security Number
// ID : 객체의 ID data
// password : 객체의 password data
// Return Value : void
// 
// // Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// 
// // Revsions :
// 1. When & Who :  
// What :  


void AccountDB::storeAccount(Account* account)
{	
	int i = 0;
	while (this->accounts[i] != NULL)
	{
		i++;
		if (i == MAX_VALUE) break;
	}
	if (i != MAX_VALUE)
	{
		this->accounts[i] = account;
	} 
}

// Function : int getAccountIndex(string ID)
// Description: AccountDB내에서 해당 ID를 가진 객체의 포인터를 리턴
// Parameters 
// ID : 객체의 ID data 
// Return Value : Account* 
// 
// // Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// 
// // Revsions :
// 1. When & Who :  
// What :  

Account* AccountDB::getAccountIndex(string ID)
{	
	int i = 0;
	while (this->accounts[i] != NULL) {
		if (this->accounts[i]->getID() == ID) {
			return this->accounts[i];
		}
	}
	return NULL;
}

// Function : void deleteAccount(string ID)
// Description: AccountDB내에서 해당 ID를 가진 객체의 Index를 찾아내어 해당 객체를 DB에서 삭제
// Parameters 
// ID : 객체의 ID data 
// Return Value : void
// 
// // Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// 
// // Revsions :
// 1. When & Who :  
// What :  

void AccountDB::deleteAccount(string ID)
{
	int i = 0;
	while (this->accounts[i] != NULL) {
		if (this->accounts[i]->getID() == ID) {
			this->accounts[i] = NULL;
		}
	}
}

// Function : bool checkAccount(string ID, string password)
// Description: AccountDB내에서 parameter에 해당하는 ID와 Password를 가진 account가 있는지 확인 후 그 유효성을 Boolean으로 리턴
// Parameters 
// ID : 객체의 ID data 
// Return Value : Boolean
// 
// // Created: 2022/5/30 12:00 pm
// Author: Ahhyun Kim
// 
// // Revsions :
// 1. When & Who :  
// What :  

bool AccountDB::checkAccount(string ID, string password) 
{ 
	int i = 0;
	while (this->accounts != NULL)
	{
		i++;
		if (accounts[i]->getID() == ID && accounts[i]->getPassword() == password)
		{
			return true;
		}
	} 
	return false;
}

Account* AccountDB::logIn(string ID, string password)
{	
	getAccountIndex(ID)->setLogStatus(); 
}

Account* AccountDB::logOut(string ID)
{
	
	getAccountIndex(ID)->setLogStatus();
	 
} 
 
// 수정이 필요합니다. account 클래스가 private 변수로 logstatus를 갖고 있습니다. 
Account* Login::getLoginAccount()
{

}

// 회원가입, 탈퇴, 로그인, 로그아웃 컨트롤과 바운더리

//
// 회원가입 바운더리, 컨트롤 클래스 구현
//

// 회원가입 바운더리 클래스 생성자
CreateAccountUI::CreateAccountUI(CreateAccount* createAccount)
{
	this->createAccount = createAccount;
}

// 회원가입 바운더리에서 계정 정보를 입력하는 함수
void CreateAccountUI::enterAccountInfo()
{
	string name;
	string ssn;
	string id;
	string password;
	fin >> name >> ssn >> id >> password;
	this->createAccount->createNewAccount(name, ssn, id, password);
}

// 회원가입 컨트롤 클래스 생성자
CreateAccount::CreateAccount()
{
	CreateAccountUI* createAccountUi = new CreateAccountUI(this);
	this->createAccountUi = createAccountUi;
}

// 회원가입 클래스에서 새 계정을 생성하는 함수
void CreateAccount::createNewAccount(string name, string ssn, string id, string password)
{
	AccountDB* accounts;
	Account* account;
	if (!accounts->checkAccount(id, password))
	{
		account->createAccount(name, ssn, id, password);
		fout << "1.1. 회원가입" << endl << "> " << name << " " << ssn << " " << id << " " << password << endl;
	}
}


//
// 회원탈퇴 바운더리, 컨트롤 
//

// 회원탈퇴 바운더리 클래스 생성자
DeleteAccountUI::DeleteAccountUI(DeleteAccount* deleteAccount)
{
	this->deleteAccount = deleteAccount;
}

// 회원탈퇴 정보 입력받는 함수
void DeleteAccountUI::enterDeleteInfo()
{
	string id;
	fin >> id;
	this->deleteAccount->deleteThisAccount(id);
}

// 회원탈퇴 컨트롤 클래스 생성자
DeleteAccount::DeleteAccount()
{
	DeleteAccountUI* deleteAccountUi = new DeleteAccountUI(this);
	this->deleteAccountUi = deleteAccountUi;
}

// 회원가입 클래스에서 특정 계정을 탈퇴하는 함수
void DeleteAccount::deleteThisAccount(string id)
{
	AccountDB* accounts;
	accounts->deleteAccount(id);
	fout << "1.2. 회원탈퇴" << endl << "> " << id << endl;
}

//
// 로그인 바운더리, 컨트롤 클래스 구현
//


// 로그인 바운더리 클래스 생성자
LoginUI::LoginUI(Login* login) {
	this->login = login;
}

// 로그인 바운더리가 정보를 입력받는 함수
void LoginUI::enterLoginInfo() {
	string id;
	string password;
	fin >> id >> password;
	this->login->requestLogin(id, password);
}

// 로그인 컨트롤 클래스 생성자
Login::Login() 
{
	LoginUI* loginUi = new LoginUI(this);
	this->loginUi = loginUi;
} 

// 로그인 컨트롤에서 로그인을 요청하는 함수
void Login::requestLogin(string id, string password)
{
	AccountDB* accounts;
	if (accounts->checkAccount(id, password))
	{
		accounts->logIn(id, password);
		fout << "2.1. 로그인" << endl << "> " << id << " " << password << endl;
	}
}


// 로그인 중인 상태의 Account를 반환하는 함수
// 구현 수정이 필요합니다.
Account* Login::getLoginAccount()
{
	//AccountDB* accounts;
	//Account* account;
	//accounts->getAccountIndex(account->getID());
}



//
// 로그아웃 바운더리, 컨트롤 클래스 구현
//


// 로그아웃 바운더리 클래스 생성자
LogOutUI::LogOutUI(LogOut* logOut) {
	this->logOut = logOut;
}

// 로그아웃 바운더리가 정보를 입력받는 함수
void LogOutUI::enterLogOutInfo() {
	string id;
	fin >> id;
	this->logOut->requestLogOut(id);
}

// 로그아웃 컨트롤 클래스 생성자
LogOut::LogOut()
{
	LogOutUI* logOutUi = new LogOutUI(this);
	this->logOutUi = logOutUi;
}

// 로그인 컨트롤에서 로그인을 요청하는 함수
void LogOut::requestLogOut(string id)
{
	AccountDB* accounts;
	if (accounts->getAccountIndex(id)->getLogStatus())
	{
		accounts->logOut(id);
		fout << "2.2. 로그아웃" << endl << "> " << id << endl;
	}
}