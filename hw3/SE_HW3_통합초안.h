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

//���� ����� ��������
static ifstream fin;
static ofstream fout;

//Ŭ���� ���� ����
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

//Class : ȸ������ �ٿ����
//Description : �Է� ���Ͽ��� ���������� �о���̰� ��� ���Ͽ� ������ ���� ������ ����ϴ� �۾��� �Ѵ�.
//Author : �����
class CreateAccountUI {
	CreateAccount* createAccount;
public:
	CreateAccountUI(CreateAccount* createAccount);
	void enterAccountInfo();
	void printResult(string name, string ssn, string ID, string password);
};

//Class : ȸ������ ��Ʈ��
//Description : ȸ������ �ٿ���� Ŭ������ �����ϰ�, �ٿ���� Ŭ�����κ��� ���޹��� ���������� ȸ�� ������ �����Ѵ�.
//Author : �����
class CreateAccount {
	CreateAccountUI* createAccountUi;
	AccountDB* accountDB;
public:
	CreateAccount(AccountDB *accountDB);
	void createNewAccount(string name, string ssn, string id, string password);
};


//Class : ȸ��Ż�� �ٿ����
//Description : �Է� ���Ͽ��� ���������� �о���̰� DB���� �ش� ���������� ��ġ�ϴ� ������ �����Ѵ�.
//Author : �����
class DeleteAccountUI {
	DeleteAccount* deleteAccount;
public:
	DeleteAccountUI(DeleteAccount* deleteAccount);
	void enterDeleteInfo(Account* loginPointer);
	void printResult(string id);
};


//Class : ȸ��Ż�� ��Ʈ��
//Description : ȸ��Ż�� �ٿ���� Ŭ������ �����ϰ�, �ٿ���� Ŭ�����κ��� ���޹��� ���̵�� ȸ�� ������ Ż���Ѵ�.
//Author : �����
class DeleteAccount {
	DeleteAccountUI* deleteAccountUi;
	Account* loginPointer; // �α����� ������ ����Ű�� ������
	AccountDB* accountDB;
public:
	DeleteAccount(AccountDB* accountDB, Account* loginPointer);
	void deleteThisAccount(Account* loginPointer);
};


//Class : �α��� �ٿ����
//Description : �Է� ���Ͽ��� ���������� �о���̰� ��� ���Ͽ� �α��� ���� ������ ����ϴ� �۾��� �Ѵ�.
//Author : �����
class LoginUI {
	Login* login;
public:
	LoginUI(Login* login);
	void enterLoginInfo();
	void printResult(string ID, string password);
};

//Class : �α��� ��Ʈ��
//Description : �α��� �ٿ���� Ŭ������ �����ϰ�, �ٿ���� Ŭ�����κ��� ���޹��� ������ �ش��ϴ� �������� �α����Ѵ�.
//Author : �����
class Login {
	LoginUI* loginUi;
	Account* loginPointer; // �α����� �õ��� ������ ����Ű�� ������
	AccountDB* accountDB;
public:
	Login(AccountDB* accountDB);
	void requestLogin(string ID, string password);
	Account* getLoginAccount(); // �α����� ȸ���� ��ȯ
};

//Class : �α׾ƿ� �ٿ����
//Description : �Է� ���Ͽ��� ���������� �о���̰� ��� ���Ͽ� �α׾ƿ��� ���� ������ ����ϴ� �۾��� �Ѵ�.
//Author : �����
class LogOutUI {
	LogOut* logOut;
public:
	LogOutUI(LogOut* logOut);
	void enterLogOutInfo();
	void printResult(string ID);
};


//Class : �α׾ƿ� ��Ʈ��
//Description : �α׾ƿ� �ٿ���� Ŭ������ �����ϰ�, �ٿ���� Ŭ�����κ��� ���޹��� ������ �ش��ϴ� ������ �α��� ������ Ȯ���ϰ� �α׾ƿ��Ѵ�.
//Author : �����
class LogOut {
	LogOutUI* logOutUi;
	Account* logOutPointer; // �α׾ƿ��� �õ��� ������ ����Ű�� ������
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
	//void checkProudctListOnSale(); //�Ǹ��ڰ� ��ȸ��ư�� �������� �۵��ϴ� �Լ�. �̹� �ý��ۿ����� ������ �޴� �Լ�
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
	//void checkProudctInfoSold(); //�Ǹ��ڰ� ��ȸ��ư�� �������� �۵��ϴ� �Լ�. �̹� �ý��ۿ����� ������ �޴� �Լ�
};
class PrintStatistics {
private:
	Seller* seller;
	int totalProfit;	//�� �Ǹűݾ�
	int averageBuySatisfaction; //��ձ��Ÿ�����
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

//Class : ��ǰ �˻� �ٿ����
//Description : �Է� ���Ͽ��� ��ǰ���� �о���̰� ��� ���Ͽ� ��ǰ �˻� ����� ���� �۾��� �Ѵ�.
//Author : ������
class SearchProductUI {
	SearchProduct *searchProduct;
public:
	SearchProductUI(SearchProduct *searchProduct);
	void enterProductName();
	void printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction);
};

//Class : ��ǰ �˻� ��Ʈ��
//Description : ��ǰ �˻� �ٿ���� Ŭ������ �����ϰ�, �ٿ���� Ŭ�������� ���޹��� ��ǰ������ ��ǰ �˻��� �����Ѵ�.
//Author : ������
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

//Class : ��ǰ ���� �ٿ����
//Description : ��� ���Ͽ� ��ǰ ���� ����� ���� �۾��� �Ѵ�.
//Author : ������
class BuyProductUI {
	BuyProduct *buyProduct;
public:
	BuyProductUI(BuyProduct *buyProduct);
	void printResult(string sellerID, string productName);
};

//Class : ��ǰ ���� ��Ʈ��
//Description : �˻��� ��ǰ ���Ÿ� �����Ѵ�.
//Author : ������
class BuyProduct {
	BuyProductUI *buyProductUI;
	Seller *searchProductSeller; 
	Product *searchProduct; 
	Buyer *buyer;
public:
	BuyProduct(Buyer *buyer, Seller *searchProductSeller, Product *searchProduct);
};

//Class : ���� ���� ��ȸ �ٿ����
//Description : ��� ���Ͽ� ���� ���� ��ȸ ����� ���� �۾��� �Ѵ�.
//Author : ������
class SeeBoughtListUI {
	SeeBoughtList *seeBoughtList;
public:
	SeeBoughtListUI(SeeBoughtList *seeBoughtList);
	void printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction);
};

//Class : ���� ���� ��ȸ ��Ʈ��
//Description : ���� ������ ��ǰ���� ������������ �����Ͽ� ��ȸ�Ѵ�.
//Author : ������
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

//Class : ���Ÿ����� �� �ٿ����
//Description : �Է� ���Ͽ��� ��ǰ��� ���� ������ ���� �о���̰� ��� ���Ͽ� ���� ������ �� ����� ���� �۾��� �Ѵ�.
//Author : ������
class EvaluateBuySatisfactionUI {
	EvaluateBuySatisfaction *evaluateBuySatisfaction;
public:
	EvaluateBuySatisfactionUI(EvaluateBuySatisfaction *evaluateBuySatisfaction);
	void enterProductNameAndBuySatisfaction();
	void printResult(string sellerID, string productName, int satisfaction);
};

//Class : ���Ÿ����� �� ��Ʈ��
//Description : �ٿ�������� ���޹��� ��ǰ��� ���� ������ ���� �Ǵ��ؼ� ��ȿ�� ���� ��� �ش� ��ǰ ��ƼƼ�� �����Ͽ� ���� �������� �߰��Ѵ�.
//Author : ������
class EvaluateBuySatisfaction {
	EvaluateBuySatisfactionUI *evaluateBuySatisfactionUI;
	Buyer *buyer;
	vector<string> boughtListSellerID;
	vector<string> sortedBoughtListNames;
public:
	EvaluateBuySatisfaction(Buyer* buyer, vector<string> boughtListSellerID, vector<string> sortedBoughtListNames);
	void addSatisfaction(string productName, int satisfaction);
};

//Class : �޴� �ٿ����
//Description : �Է� ���Ͽ��� �޴��� ��Ÿ���� ���� 2���� �о���̰� ��� ���Ͽ� �ش��ϴ� �޴��� ������ ���� �۾��� �Ѵ�.
//Author : ������
class SelectMenu {

public:
	void doTask();
	void programExit();
};


//Class : ȸ�� ��ƼƼ 
//Description : ȸ�� ��ƼƼ Ŭ������, ȸ���� �̸�, SSN, ID, Password, �α��� ���¸� ������ �ִ�.
//Author : �����
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

//Class : ȸ�� ���� ��ƼƼ
//Description : ȸ���� ���� ��ƼƼ Ŭ������, ������ ������ ������ �ִ�.
//Author : �����
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



//Class : ��ǰ ����
//Description : ��ǰ ��ƼƼ�� ���� Ŭ�����̴�.
//Author : ������
class ProductCollection {
	vector<Product*> product;
	//Product* product[MAX_VALUE];
public:
	Product* getProduct(unsigned int order);
	void addProduct(Product* product);
	Product* findProduct(string name);
	vector<Product*> getProductlist();
};

//Class : �Ǹ��� ��ƼƼ 
//Description : ȸ�� ��ƼƼ Ŭ������ �θ�� �ϴ� �Ǹ��� Ŭ�����̴�. �Ǹ��ڰ� �Ǹ����� ���, �Ǹ� �Ϸ�� ����� ������ �ִ�.
//Author : ������
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

//Class : ������ ��ƼƼ
//Description : ȸ�� ��ƼƼ Ŭ������ �θ�� �ϴ� ������ Ŭ�����̴�. �����ڰ� ������ ��ǰ ������ ������ �ִ�.
//Author : ������
class Buyer : public Account {
	ProductCollection boughtProductCollection;
public:
	Buyer(string name, string ssn, string ID, string password);
	ProductCollection listBoughtProducts();
	void addProductToBoughtList(Product *product);
};

//Class : ��ǰ ��ƼƼ
//Description : ��ǰ�� ���� ������ ��ǰ��, ��ǰȸ���, ����, ���, �򰡹��� ���Ÿ����� ����Ʈ�� ������ �ִ�.
//Author : ������
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


