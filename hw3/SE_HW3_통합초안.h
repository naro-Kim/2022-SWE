#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

using namespace std;

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

//파일 입출력 전역변수
static ifstream fin;
static ofstream fout;

//클래스 전방 선언
class Login;
class LoginUI;
class LogOutUI;
class LogOut;
class CreateAccountUI;
class CreateAccount;
class DeleteAccountUI;
class DeleteAccount;
class Account;
class CheckPrdouctListOnSaleUI;
class CheckPrdouctListOnSale;
class PrintStatisticsUI;
class PrintStatistics;
class AddClothesUI;
class AddClothes;
class SearchProductUI;
class SearchProduct;
class BuyProductUI;
class BuyProduct;
class SeeBoughtListUI;
class SeeBoughtList;
class EvaluateBuySatisfactionUI;
class EvaluateBuySatisfaction;
class SelectMenu;
class AccountDB;
class Seller;
class Buyer;
class Product;
class ProductCollection;

//Class : 회원가입 바운더리
//Description : 입력 파일에서 계정정보를 읽어들이고 출력 파일에 생성된 계정 정보를 출력하는 작업을 한다.
//Author : 김아현
class CreateAccountUI {
	CreateAccount* createAccount;
public:
	CreateAccountUI(CreateAccount* createAccount);
	void enterAccountInfo();
	void printResult(string name, string ssn, string ID, string password);
};

//Class : 회원가입 컨트롤
//Description : 회원가입 바운더리 클래스를 생성하고, 바운더리 클래스로부터 전달받은 계정명으로 회원 계정을 생성한다.
//Author : 김아현
class CreateAccount {
	CreateAccountUI* createAccountUi;
	AccountDB* accountDB;
public:
	CreateAccount(AccountDB *accountDB);
	void createNewAccount(string name, string ssn, string id, string password);
};


//Class : 회원탈퇴 바운더리
//Description : 입력 파일에서 계정정보를 읽어들이고 DB에서 해당 계정정보와 일치하는 계정을 삭제한다.
//Author : 김아현
class DeleteAccountUI {
	DeleteAccount* deleteAccount;
public:
	DeleteAccountUI(DeleteAccount* deleteAccount);
	void enterDeleteInfo(Account* loginPointer);
	void printResult(string id);
};


//Class : 회원탈퇴 컨트롤
//Description : 회원탈퇴 바운더리 클래스를 생성하고, 바운더리 클래스로부터 전달받은 아이디로 회원 계정을 탈퇴한다.
//Author : 김아현
class DeleteAccount {
	DeleteAccountUI* deleteAccountUi;
	Account* loginPointer; // 로그인한 계정을 가리키는 포인터
	AccountDB* accountDB;
public:
	DeleteAccount(AccountDB* accountDB, Account* loginPointer);
	void deleteThisAccount(Account* loginPointer);
};


//Class : 로그인 바운더리
//Description : 입력 파일에서 계정정보를 읽어들이고 출력 파일에 로그인 계정 정보를 출력하는 작업을 한다.
//Author : 김아현
class LoginUI {
	Login* login;
public:
	LoginUI(Login* login);
	void enterLoginInfo();
	void printResult(string ID, string password);
};

//Class : 로그인 컨트롤
//Description : 로그인 바운더리 클래스를 생성하고, 바운더리 클래스로부터 전달받은 정보에 해당하는 계정으로 로그인한다.
//Author : 김아현
class Login {
	LoginUI* loginUi;
	Account* loginPointer; // 로그인을 시도한 계정을 가리키는 포인터
	AccountDB* accountDB;
public:
	Login(AccountDB* accountDB);
	void requestLogin(string ID, string password);
	Account* getLoginAccount(); // 로그인한 회원을 반환
};

//Class : 로그아웃 바운더리
//Description : 입력 파일에서 계정정보를 읽어들이고 출력 파일에 로그아웃한 계정 정보를 출력하는 작업을 한다.
//Author : 김아현
class LogOutUI {
	LogOut* logOut;
public:
	LogOutUI(LogOut* logOut);
	void enterLogOutInfo();
	void printResult(string ID);
};


//Class : 로그아웃 컨트롤
//Description : 로그아웃 바운더리 클래스를 생성하고, 바운더리 클래스로부터 전달받은 정보에 해당하는 계정의 로그인 유무를 확인하고 로그아웃한다.
//Author : 김아현
class LogOut {
	LogOutUI* logOutUi;
	Account* logOutPointer; // 로그아웃을 시도한 계정을 가리키는 포인터
	AccountDB* accountDB;
public:
	LogOut(AccountDB* accountDB, Account *loginPointer);
	void requestLogOut();
};

class CheckPrdouctListOnSale {
private:
	Seller* seller;
public:
	CheckPrdouctListOnSale(Seller* seller);
	vector<Product*> ShowProductlist();

};

class CheckPrdouctListOnSaleUI {
private:
	CheckPrdouctListOnSale* checkPrdouctListOnSale;
	vector<Product*> list;
public:
	CheckPrdouctListOnSaleUI(CheckPrdouctListOnSale* checkPrdouctListOnSale);
	void startInterface();
	//void checkProudctListOnSale(); //판매자가 조회버튼을 눌렀을때 작동하는 함수. 이번 시스템에서는 정보를 받는 함수
	void outputList();
};

class CheckPrdouctInfoSold {
private:
	Seller* seller;
public:
	CheckPrdouctInfoSold(Seller* seller);
	vector<Product*> showProductInfo();
};

class CheckPrdouctInfoSoldUI {
private:
	vector<Product*> list;
	CheckPrdouctInfoSold* checkProudctInfoSold;
public:
	CheckPrdouctInfoSoldUI(CheckPrdouctInfoSold* checkPrdouctInfoSold);
	void startInterface();
	void outputList();
	//void checkProudctInfoSold(); //판매자가 조회버튼을 눌렀을때 작동하는 함수. 이번 시스템에서는 정보를 받는 함수
};
class PrintStatistics {
private:
	Seller* seller;
	int totalProfit;	//총 판매금액
	int averageBuySatisfaction; //평균구매만족도
public:
	PrintStatistics(Seller* seller);
	vector<Product*> printStatisticsinfo();
};
class PrintStatisticsUI {
private:
	vector<Product*> list;
	PrintStatistics* printStatistics;
public:
	PrintStatisticsUI(PrintStatistics* printStatistics);
	void startInterface();
	void outputList();
	//void printStatistics();
};
class AddClothes {
private:
	Seller* seller;
public:
	AddClothes(Seller* seller);
	void addNewClothes(string productName, string productCompanyName, int price, int stockNum);
};
class AddClothesUI {
public:
	AddClothesUI(AddClothes* addClothes, Seller* seller);
	void startInterface();
	void output(string productName, string productCompanyName, int price, int stockNum);
private:
	Seller* seller;
	AddClothes* addClothes;
};

//Class : 상품 검색 바운더리
//Description : 입력 파일에서 상품명을 읽어들이고 출력 파일에 상품 검색 결과를 쓰는 작업을 한다.
//Author : 조은비
class SearchProductUI {
	SearchProduct *searchProduct;
public:
	SearchProductUI(SearchProduct *searchProduct);
	void enterProductName();
	void printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction);
};

//Class : 상품 검색 컨트롤
//Description : 상품 검색 바운더리 클래스를 생성하고, 바운더리 클래스에서 전달받은 상품명으로 상품 검색을 수행한다.
//Author : 조은비
class SearchProduct {
	SearchProductUI *searchProductUI;
	vector<Seller*> listSeller;
	Seller *searchProductSeller;
	Product *searchProduct; 
public:
	SearchProduct(vector<Seller*> sellerList);
	void showSearchProductInfo(string productName);
	Seller* getSearchProductSeller(); 
	Product* getSearchProduct(); 
};

//Class : 상품 구매 바운더리
//Description : 출력 파일에 상품 구매 결과를 쓰는 작업을 한다.
//Author : 조은비
class BuyProductUI {
	BuyProduct *buyProduct;
public:
	BuyProductUI(BuyProduct *buyProduct);
	void printResult(string sellerID, string productName);
};

//Class : 상품 구매 컨트롤
//Description : 검색한 상품 구매를 진행한다.
//Author : 조은비
class BuyProduct {
	BuyProductUI *buyProductUI;
	Seller *searchProductSeller; 
	Product *searchProduct; 
	Buyer *buyer;
public:
	BuyProduct(Buyer *buyer, Seller *searchProductSeller, Product *searchProduct);
};

//Class : 구매 내역 조회 바운더리
//Description : 출력 파일에 구매 내역 조회 결과를 쓰는 작업을 한다.
//Author : 조은비
class SeeBoughtListUI {
	SeeBoughtList *seeBoughtList;
public:
	SeeBoughtListUI(SeeBoughtList *seeBoughtList);
	void printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction);
};

//Class : 구매 내역 조회 컨트롤
//Description : 구매 내역을 상품명의 오름차순으로 정렬하여 조회한다.
//Author : 조은비
class SeeBoughtList {
	SeeBoughtListUI *seeBoughtListUI;
	vector<Seller*> listSeller;
	//Seller * listseller[MAX_VALUE];
	Buyer *buyer;
	vector<string> sellerID;
	vector<string> sortedBoughtProductNames;
	//string sellerid[MAX_VALUE];
public:
	SeeBoughtList(Buyer* buyer, vector<Seller*> sellerList);
	void showBoughtListInfo();
	vector<string> getSellerIDList();
	vector<string> getSortedBoughtProductNameList();
};

//Class : 구매만족도 평가 바운더리
//Description : 입력 파일에서 상품명과 구매 만족도 값을 읽어들이고 출력 파일에 구매 만족도 평가 결과를 쓰는 작업을 한다.
//Author : 조은비
class EvaluateBuySatisfactionUI {
	EvaluateBuySatisfaction *evaluateBuySatisfaction;
public:
	EvaluateBuySatisfactionUI(EvaluateBuySatisfaction *evaluateBuySatisfaction);
	void enterProductNameAndBuySatisfaction();
	void printResult(string sellerID, string productName, int satisfaction);
};

//Class : 구매만족도 평가 컨트롤
//Description : 바운더리에서 전달받은 상품명과 구매 만족도 값을 판단해서 유효한 값인 경우 해당 상품 엔티티에 접근하여 구매 만족도를 추가한다.
//Author : 조은비
class EvaluateBuySatisfaction {
	EvaluateBuySatisfactionUI *evaluateBuySatisfactionUI;
	Buyer *buyer;
	vector<string> boughtListSellerID;
	vector<string> sortedBoughtListNames;
public:
	EvaluateBuySatisfaction(Buyer* buyer, vector<string> boughtListSellerID, vector<string> sortedBoughtListNames);
	void addSatisfaction(string productName, int satisfaction);
};

//Class : 메뉴 바운더리
//Description : 입력 파일에서 메뉴를 나타내는 숫자 2개를 읽어들이고 출력 파일에 해당하는 메뉴의 정보를 쓰는 작업을 한다.
//Author : 조은비
class SelectMenu {

public:
	void doTask();
	void programExit();
};


//Class : 회원 엔티티 
//Description : 회원 엔티티 클래스로, 회원은 이름, SSN, ID, Password, 로그인 상태를 가지고 있다.
//Author : 김아현
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
	void setLogStatus();
	string getID();
	string getPassword();
	string getName();
	string getSsn();
};

//Class : 회원 집합 엔티티
//Description : 회원의 집합 엔티티 클래스로, 계정의 집합을 가지고 있다.
//Author : 김아현
class AccountDB
{
private:
	vector<Account*> accounts;
public:
	void storeAccount(Account* account);
	void deleteAccount(string ID);
	Account* getAccountIndex(string ID);
	bool checkAccount(string ID, string password);
	void logIn(string ID, string password);
	void logOut(string ID); 
};



//Class : 상품 집합
//Description : 상품 엔티티의 집합 클래스이다.
//Author : 조은비
class ProductCollection {
	vector<Product*> product;
	//Product* product[MAX_VALUE];
public:
	Product* getProduct(unsigned int order);
	void addProduct(Product* product);
	Product* findProduct(string name);
	vector<Product*> getProductlist();
};

//Class : 판매자 엔티티 
//Description : 회원 엔티티 클래스를 부모로 하는 판매자 클래스이다. 판매자가 판매중인 목록, 판매 완료된 목록을 가지고 있다.
//Author : 조은비
class Seller : public Account {
	//ProductCollection onSaleProductCollection;
	//ProductCollection onSoldProductCollection;
	ProductCollection product;
public:
	Seller(string name, string ssn, string ID, string password);
	//void reSet();
	void addNewClothes(string productName, string productCompanyName, int price, int stockNum);
	vector<Product*> listProduct_OnSale();
	vector<Product*> listProduct_OnSold();
	string getSellerID();
};

//Class : 구매자 엔티티
//Description : 회원 엔티티 클래스를 부모로 하는 구매자 클래스이다. 구매자가 구매한 상품 내역을 가지고 있다.
//Author : 조은비
class Buyer : public Account {
	ProductCollection boughtProductCollection;
public:
	Buyer(string name, string ssn, string ID, string password);
	ProductCollection listBoughtProducts();
	void addProductToBoughtList(Product *product);
};

//Class : 상품 엔티티
//Description : 상품에 대한 정보인 상품명, 상품회사명, 가격, 재고, 평가받은 구매만족도 리스트를 가지고 있다.
//Author : 조은비
class Product {
	string productName;
	string productCompanyName;
	int price;
	int stockNum;
	int originalStockNum;
	vector<int> buySatisfaction;
	//int buySatisfaction[MAX_VALUE];
public:
	Product(string productName, string productCompanyName, int price, int stockNum);
	string getProductName();
	string getProductCompanyName();
	//int getProfit();
	int getPrice();
	int getStockNum();
	int getOriginalStockNum();
	vector<int> getSatisfaction();
	void addBuySatisfaction(int satisfaction);
	void decreaseStockNum();
};


