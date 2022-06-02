#include "SE_HW3.h"

//Function: void SelectMenu::doTask()
//Description: 입력 파일에서 메뉴를 나타내는 숫자 2개를 읽어서 어떤 메뉴에 해당하는지 switch문으로 판별한다. 그리고 해당하는 메뉴의 컨트롤 클래스를 생성한다.
//Author: 조은비
void SelectMenu::doTask() {
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;
    AccountDB* accountDB = new AccountDB(); // DB 접근 용이하게 하기 위함
    Login* login = 0; // 로그인한 사용자 접근 용이하게 하기 위함
    Seller* seller = 0;
    Buyer* buyer = 0;
    SearchProduct* searchproduct = 0; // 검색한 상품을 나타냄
    vector<string> boughtListSellerIDList; // 구매 내역에 있는 상품들의 판매자 ID 리스트
    vector<string> sortedBoughtListNames;
    vector<Seller*> sellerList;
    vector<Buyer*> buyerList;

    fin.open(INPUT_FILE_NAME);
    fout.open(OUTPUT_FILE_NAME);
    

    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        fin >> menu_level_1;
        fin >> menu_level_2;
        //cout << "db 데이터 개수 " << accountDB->returnsize();
        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
        case 1:
        {
            switch ((menu_level_2))
            {
            case 1:
            {
                fout << "1.1. 회원가입" << endl;
                CreateAccount* createAccount;
                createAccount = new CreateAccount(accountDB);

                break;
            }
            case 2:
            {
                fout << "1.2. 회원탈퇴" << endl;
                DeleteAccount* deleteAccount;
                deleteAccount = new DeleteAccount(accountDB, login->getLoginAccount());
                break;
            }
            }
            break;
        }
        case 2:
        {
            switch ((menu_level_2))
            {
            case 1:
            {
                //Login* login;
                fout << "2.1. 로그인" << endl;
                login = new Login(accountDB);
                break;
            }
            case 2:
            {
                fout << "2.2. 로그아웃" << endl;
                LogOut* logOut;
                logOut = new LogOut(accountDB, login->getLoginAccount());
                break;
            }
            }
            break;
        }
        case 3: 
        {
            bool find = false;
            unsigned int i = 0;
            while (i < sellerList.size()) {
                if (sellerList[i]->getID() == login->getLoginAccount()->getID()) { // 현재 로그인한 계정이 이미 판매자 리스트에 등록되어 있는지 체크
                    find = true;
                    break;
                }
            }
            if (find) {
                seller = sellerList[i];
            }
            else {
                seller = new Seller(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); // 판매자 계정으로 등록
                sellerList.push_back(seller); //판매자 리스트에 추가
            }
            switch (menu_level_2)
            {
                //cout << "현재 로그인한 계정" << login->getLoginAccount()->getID();
                //seller = (Seller*)login->getLoginAccount();
                //cout << "현재 로그인한 계정" << seller->getID();
            case 1: // "3.1. 판매 의류 등록 메뉴 부분
            { // control class 생성
                //cout << "현재 로그인한 계정" << login->getLoginAccount()->getID();
                //seller = new Seller(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); // 판매자 계정으로 등록
                //sellerList.push_back(seller); //판매자 리스트에 추가
                fout << "3.1. 판매 의류 등록 " << endl;
                //seller = (Seller*)login->getLoginAccount();
                //seller = (Seller*)login->getLoginAccount();
                AddClothes* registClothes = new AddClothes(seller); 
                break; 
            }
            case 2: // 3.2 등록 상품 조회(판매중)
            {
                fout << "3.2. 등록 상품 조회 " << endl;
                CheckPrdouctListOnSale* checkProudctListOnSale = new CheckPrdouctListOnSale(seller);

                break;
            }
            case 3: // 3.3 판매 완료 상품 조회
            {
                fout << "3.3 판매 완료 상품 조회 " << endl;
                CheckPrdouctInfoSold* checkPrdouctInfoSold = new CheckPrdouctInfoSold(seller);
                break;
            }
            }
            break;
        }
        case 4:
        {
            bool find = false;
            unsigned int i = 0;
            while (i < buyerList.size()) {
                if (buyerList[i]->getID() == login->getLoginAccount()->getID()) { // 현재 로그인한 계정이 이미 구매자 리스트에 등록되어 있는지 체크
                    find = true;
                    break;
                }
                i++;
            }
            if (find) {
                buyer = buyerList[i];
            }
            else {
                buyer = new Buyer(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); //구매자 계정으로 등록
                buyerList.push_back(buyer); //구매자 리스트에 추가
            }
            switch (menu_level_2)
            {
            case 1:   // "4.1. 상품 검색“ 메뉴 부분
            {
                // 상품 검색 컨트롤 클래스 생성
                fout << "4.1. 상품 정보 검색 " << endl;
                searchproduct = new SearchProduct(sellerList);
                break;
            }
            case 2:   // "4.2. 상품 구매“ 메뉴 부분
            {
                // 상품 구매 컨트롤 클래스 생성
                fout << "4.2. 상품 구매 " << endl;
                BuyProduct* buyproduct = new BuyProduct(buyer, searchproduct->getSearchProductSeller(), searchproduct->getSearchProduct());
                break;
            }
            case 3:   // "4.3. 구매 내역 조회“ 메뉴 부분
            {
                // 구매 내역 조회 컨트롤 클래스 생성
                fout << "4.3. 상품 구매 내역 조회 " << endl;
                SeeBoughtList* seeboughtlist = new SeeBoughtList(buyer, sellerList);
                boughtListSellerIDList = seeboughtlist->getSellerIDList();
                sortedBoughtListNames = seeboughtlist->getSortedBoughtProductNameList();
                break;
            }
            case 4:   // "4.4. 구매 만족도 평가“ 메뉴 부분
            {
                // 구매 만족도 평가 컨트롤 클래스 생성
                fout << "4.4. 상품 구매 만족도 평가 " << endl;
                EvaluateBuySatisfaction* evaluatebuysatisfaction = new EvaluateBuySatisfaction(buyer, boughtListSellerIDList, sortedBoughtListNames);
                break;
            }
            }
            break;
        }
        case 5: {
            bool find = false;
            unsigned int i = 0;
            while (i < sellerList.size()) {
                if (sellerList[i]->getID() == login->getLoginAccount()->getID()) { // 현재 로그인한 계정이 이미 판매자 리스트에 등록되어 있는지 체크
                    find = true;
                    break;
                }
            }
            if (find) {
                seller = sellerList[i];
            }
            else {
                seller = new Seller(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); // 판매자 계정으로 등록
                sellerList.push_back(seller); //판매자 리스트에 추가
            }
            switch (menu_level_2)
            {
            case 1://판매상품통계
                fout << "5.1 판매 상품 통계 " << endl;
                PrintStatistics* printStatistics = new PrintStatistics(seller);
                break;
            }

        }
        case 6: {
            switch (menu_level_2)
            {
            case 1: // "6.1. 종료“ 메뉴 부분
            {
                programExit(); is_program_exit = 1; break;
            }
            }
            break;
        }
        }
    }
}

void SelectMenu::programExit() {
    fout << "6.1. 종료" << endl;
}

//판매자 계정 생성
Seller::Seller(string name, string ssn, string ID, string password) {
    this->createAccount(name, ssn, ID, password);
}

//구매자 계정 생성
Buyer::Buyer(string name, string ssn, string ID, string password) {
    this->createAccount(name, ssn, ID, password);
}

//정렬된 구매내역 상품명 리스트 반환
vector<string> SeeBoughtList::getSortedBoughtProductNameList() {
    return this->sortedBoughtProductNames;
}

//Function: Account* Login::getLoginAccount()
//Description: 현재 로그인 상태인 계정을 가리키는 포인터를 반환한다.
// Return Value : Account*
//Author: 조은비
Account* Login::getLoginAccount() {
    return this->loginPointer;
    //return 0;
}

//Function: void Account::createAccount(string name, string ssn, string ID, string password)
//Description: 입력받은 정보를 토대로 회원의 계정을 생성한다.
//Parameter : string name - 회원 계정 이름, string ssn - 회원 주민번호 , string ID - 회원 아이디, string password - 회원 비밀번호
//Return Value : void
//Author: 김아현
void Account::createAccount(string name, string ssn, string ID, string password)
{
    this->name = name;
    this->ssn = ssn;
    this->ID = ID;
    this->password = password;
}

//Function: bool Account::getLogStatus()
//Description: 객체의 로그인 상태를 반환한다.
//Return Value : bool
//Author: 김아현

bool Account::getLogStatus() { return this->logStatus; }

//Function: bool Account::setLogStatus()
//Description: 객체의 로그인 상태를 반전한다.
//Return Value : void
//Author: 김아현

void Account::setLogStatus()
{
    if (this->logStatus == false) { this->logStatus = true; }
    else { this->logStatus = false; }
}

//Function: string Account::getID()
//Description: 객체의 ID를 스트링으로 리턴한다.
//Return Value : string
//Author: 김아현  
  
string Account::getID() { return this->ID; }

//Function: string Account::getPassword()
//Description: 객체의 Password를 스트링으로 리턴한다.
//Return Value : string
//Author: 김아현  

string Account::getPassword() { return this->password; }

//Function: string Account::getName()
//Description: 객체의 Name을 스트링으로 리턴한다.
//Return Value : string
//Author: 김아현  

string Account::getName() { return this->name; }


//Function: string Account::getSsn()
//Description: 객체의 ssn을 스트링으로 리턴한다.
//Return Value : string
//Author: 김아현  

string Account::getSsn() { return this->ssn; }


// Function : void AccountDB::storeAccount(Account* account)
// Description: 생성한 Account 객체를 AccountDB내에 전달해 저장한다.
// Parameter : Account* account -  회원 맴버 객체
// Return Value : void
// Author: 김아현

void AccountDB::storeAccount(Account* account)
{
    this->accounts.push_back(account);
}

// Function : Account* AccountDB::getAccountIndex(string ID)
// Description: AccountDB내에서 해당 ID를 가진 객체의 포인터를 리턴 
// Parameter : string ID - 회원 아이디 
// Return Value : Account* 
// Author: 김아현
// // Revsions : 조은비  

Account* AccountDB::getAccountIndex(string ID)
{ 
    unsigned int i = 0;
    while (i < this->accounts.size()) {
        if (this->accounts[i]->getID() == ID) {
            return this->accounts[i];
        }
        i++;
    }
    return 0;
}

// Function : void AccountDB::deleteAccount(string ID)
// Description: AccountDB내에서 해당 ID를 가진 객체의 Index를 찾아내어 해당 객체를 DB에서 삭제 
// Parameter : string ID - 회원 아이디 
// Return Value : void 
// Author: 김아현
// // Revsions : 조은비 

void AccountDB::deleteAccount(string ID)
{
    unsigned int i = 0;
    vector<Account*> ::iterator iter;
    iter = this->accounts.begin();
    while (iter != this->accounts.end()) {
        if (this->accounts[i]->getID() == ID) {
            this->accounts.erase(iter);
            break;
        }
        iter++;
        i++;
    }
}

// Function : bool AccountDB::checkAccount(string ID, string password)
// Description: AccountDB내에서 parameter에 해당하는 ID와 Password를 가진 account가 있는지 확인 후 그 유효성을 Boolean으로 리턴
// Parameter : string ID - 회원 아이디, string password - 회원 비밀번호
// Return Value : Bool 
// Author: 김아현

bool AccountDB::checkAccount(string ID, string password)
{
    unsigned int i = 0;
    while (i < this->accounts.size())
    {
        if (accounts[i]->getID() == ID && accounts[i]->getPassword() == password)
        {
            return true;
        }
        i++;
    }
    return false;
}

// Function : void AccountDB::logIn(string ID, string password)
// Description : AccountDB내에서 parameter에 해당하는 ID와 Password를 가진 account가 있는지 확인 후 로그인
// Parameter : string ID - 회원 아이디, string password - 회원 비밀번호
// Return Value : void
// Author: 김아현

void AccountDB::logIn(string ID, string password)
{
    getAccountIndex(ID)->setLogStatus();
}

// Function : void AccountDB::logOut(string ID, string password)
// Description : AccountDB내에서 parameter에 해당하는 ID와 Password를 가진 account가 있는지 확인 후 로그아웃
// Parameter : string ID - 회원 아이디, string password - 회원 비밀번호
// Return Value : void
// Author: 김아현

void AccountDB::logOut(string ID)
{

    getAccountIndex(ID)->setLogStatus();

}
 
// 회원가입 바운더리 클래스 생성자

CreateAccountUI::CreateAccountUI(CreateAccount* createAccount)
{
    this->createAccount = createAccount;
}

// Function :void CreateAccountUI::enterAccountInfo()
// Description : 회원가입 바운더리에서 계정 정보를 입력하는 함수
// Return Value : void
// Author: 김아현

void CreateAccountUI::enterAccountInfo()
{
    string name;
    string ssn;
    string id;
    string password;
    fin >> name >> ssn >> id >> password;
    this->createAccount->createNewAccount(name, ssn, id, password);
}

// Function : void CreateAccountUI::printResult(string name, string ssn, string ID, string password) 
// Description : 회원가입 바운더리에서 계정 생성 후 결과로 해당 계정의 정보를 출력하는 함수
// Parameter : string name - 회원 계정 이름, string ssn - 회원 주민번호 , string ID - 회원 아이디, string password - 회원 비밀번호
// Return Value : void
// Author: 조은비

void CreateAccountUI::printResult(string name, string ssn, string ID, string password) {
    fout << "> " << name << " " << ssn << " " << ID << " " << password << endl;
}

// 회원가입 컨트롤 클래스 생성자
CreateAccount::CreateAccount(AccountDB* accountDB)
{
    CreateAccountUI* createAccountUi = new CreateAccountUI(this);
    this->createAccountUi = createAccountUi;
    this->accountDB = accountDB;
    this->createAccountUi->enterAccountInfo();
}
 
// Function : void CreateAccount::createNewAccount(string name, string ssn, string id, string password) 
// Description : 회원가입 컨트롤에서 AccountDB내에 계정이 없다면 새 계정을 생성해 저장하고 그 결과를 출력하는 함수
// Parameter : string name - 회원 계정 이름, string ssn - 회원 주민번호 , string ID - 회원 아이디, string password - 회원 비밀번호
// Return Value : void
// Author: 김아현
// // Revsions : 조은비

void CreateAccount::createNewAccount(string name, string ssn, string id, string password)
{ 
    if (!this->accountDB->checkAccount(id, password))
    {
        Account* account = new Account();
        account->createAccount(name, ssn, id, password);
        this->accountDB->storeAccount(account);
        this->createAccountUi->printResult(name, ssn, id, password); 
    }
}

// 회원탈퇴 바운더리 클래스 생성자
DeleteAccountUI::DeleteAccountUI(DeleteAccount* deleteAccount)
{
    this->deleteAccount = deleteAccount;
}


/// 회원탈퇴 컨트롤 클래스 생성자
DeleteAccount::DeleteAccount(AccountDB* accountDB, Account* loginPointer)
{
    DeleteAccountUI* deleteAccountUi = new DeleteAccountUI(this);
    this->deleteAccountUi = deleteAccountUi;
    this->accountDB = accountDB;
    this->loginPointer = loginPointer; //로그인한 계정을 가리키는 포인터
    this->deleteAccountUi->enterDeleteInfo(loginPointer);
}


// Function : void DeleteAccountUI::enterDeleteInfo(Account* loginPointer)
// Description : 회원탈퇴 삭제할 계정의 ID를 입력받는 함수
// Parameter : Account* loginPointer - 로그인한 회원을 가리키는 포인터
// Return Value : void
// Author: 김아현

void DeleteAccountUI::enterDeleteInfo(Account* loginPointer)
{
    this->deleteAccount->deleteThisAccount(loginPointer);
}


//Function: void DeleteAccount::deleteThisAccount(Account* loginPointer)
//Description: 로그인했던 회원을 대상으로 AccountDB로 부터 해당 회원의 계정을 삭제하는 함수
//Parameter : Account* loginPointer - 로그인한 회원을 가리키는 포인터
//Return Value : void
//Author: 김아현

void DeleteAccount::deleteThisAccount(Account* loginPointer)
{
    this->accountDB->deleteAccount(loginPointer->getID());
    this->deleteAccountUi->printResult(loginPointer->getID());
}

// Function : void DeleteAccountUI::printResult(string id)
// Description : 회원탈퇴 바운더리에서 계정 삭제 후 결과로 해당 계정의 정보를 출력하는 함수
// Parameter : string ID - 회원 아이디
// Return Value : void
// Author: 김아현

void DeleteAccountUI::printResult(string id) {
    fout << "> " << id << endl;
}

// 로그인 바운더리 클래스 생성자
LoginUI::LoginUI(Login* login) {
    this->login = login;
}

// Function : void LoginUI::enterLoginInfo()
// Description : 로그인 바운더리가 로그인 할 계정의 ID와 password 정보를 입력받는 함수
// Parameter : string id - 삭제할 회원 id
// Return Value : void
// Author: 김아현
// // Revsions : 조은비

void LoginUI::enterLoginInfo() {
    string id;
    string password;
    fin >> id;
    fin >> password; 
    this->login->requestLogin(id, password);
}

// Function : void LoginUI::printResult(string id, string password)
// Description : 로그인 바운더리에서 로그인 후 해당 계정의 정보를 출력하는 함수
// Parameter : string id - 회원 아이디, string password - 회원 아이디 비밀번호)
// Return Value : void
// Author: 김아현

void LoginUI::printResult(string id, string password)
{
    fout << "> " << id << " " << password << endl;
}


// 로그인 컨트롤 클래스 생성자
Login::Login(AccountDB* accountDB)
{
    LoginUI* loginUi = new LoginUI(this);
    this->loginUi = loginUi;
    this->accountDB = accountDB;
    this->loginPointer = 0;
    this->loginUi->enterLoginInfo();
}

// Function : void Login::requestLogin(string id, string password)
// Description : 로그인 컨트롤에서 로그인을 요청하는 함수
// Parameter : string id - 로그인할 id, string password - 로그인할 id의 비밀번호
// Return Value : void
// Author: 김아현
// // Revsions : 조은비

void Login::requestLogin(string id, string password)
{
    //AccountDB* accounts;
    if (this->accountDB->checkAccount(id, password))
    {
        this->accountDB->logIn(id, password);
        this->loginPointer = this->accountDB->getAccountIndex(id);
        //fout << "> " << id << " " << password << endl;
        this->loginUi->printResult(id, password);
    }
} 

// 로그아웃 바운더리 클래스 생성자
LogOutUI::LogOutUI(LogOut* logOut) {
    this->logOut = logOut;
}

// Function : void LogOutUI::enterLogOutInfo()
// Description : 로그아웃 바운더리에 로그아웃 정보를 요청하는 함수 
// Return Value : void
// Author: 김아현
// // Revsions : 조은비 

void LogOutUI::enterLogOutInfo() 
{ 
    this->logOut->requestLogOut();
}

// Function : void LogOutUI::printResult(Account* account)
// Description : 로그아웃 바운더리에서 로그아웃 후 결과로 해당 계정의 정보를 출력하는 함수
// Parameter :
// Return Value : void
// Author: 김아현

void LogOutUI::printResult() {
    //fout << "> " << logOutPointer->getID() << endl;
    
}

// 로그아웃 컨트롤 클래스 생성자
LogOut::LogOut(AccountDB* accountDB, Account* loginPointer)
{
    LogOutUI* logOutUi = new LogOutUI(this);
    this->logOutUi = logOutUi;
    this->accountDB = accountDB;
    this->logOutPointer = loginPointer; //로그인한 계정을 가리키는 포인터
    this->logOutUi->enterLogOutInfo();
}

// Function : void LogOut::requestLogOut()
// Description : 로그아웃 컨트롤에서 accountDB로 해당 계정의 로그아웃을 요청하는 함수 
// Return Value : void
// Author: 김아현
// // Revsions : 조은비 

void LogOut::requestLogOut()
{
    //AccountDB* accounts;
    /*if (this->accountDB->getAccountIndex(id)->getLogStatus())
    {
        this->accountDB->logOut(id);
        fout << "2.2. 로그아웃" << endl << "> " << id << endl;
    }*/
    this->accountDB->logOut(this->logOutPointer->getID());
    fout << "> " << this->logOutPointer->getID() << endl;
}

/*
PrintStatistics::PrintStatistics(Seller* seller) {
    this->seller = seller;
    PrintStatisticsUI* printStatisticsUI = new PrintStatisticsUI(this);
    printStatisticsUI->startInterface();
}
PrintStatisticsUI::PrintStatisticsUI(PrintStatistics* printStatistics) {
    this->printStatistics = printStatistics;
}

void PrintStatisticsUI::outputList() {
    unsigned int i = 0;
    Product* product;
    while(list.getProduct(i)) {
        product = list.getProduct(i);
        fout << product->getProductName();
        fout << " ";
        fout << product->getPrice() * product->getOriginalStockNum();  //제품단가와 판패된 총 재고를 곱하여 총판매액을 구한다.
        fout << " ";
        unsigned int order = 0;
        int sum = 0;
        float average = 0;
        vector<int> buySatisfaction = product->getSatisfaction();
        while (order < buySatisfaction.size()) {
            sum += buySatisfaction[order];
            order++;
        }
        if (sum != 0) {
            average = round(sum / (float)(order + 1));
        }
        fout << average; //평균구매만족도
        fout << " " << endl;
    }
}
void PrintStatisticsUI::startInterface() {
    list = printStatistics->printStatisticsinfo();
    outputList();
}
ProductCollection PrintStatistics::printStatisticsinfo() {
    ProductCollection list;
    list = seller->listProduct_OnSold();
    return list;
}
CheckPrdouctInfoSold::CheckPrdouctInfoSold(Seller* seller) {
    this->seller = seller;
    CheckPrdouctInfoSoldUI* checkPrdouctInfoSoldUI = new CheckPrdouctInfoSoldUI(this);
    checkPrdouctInfoSoldUI->startInterface();
}
CheckPrdouctListOnSale::CheckPrdouctListOnSale(Seller* seller) {
    this->seller = seller;
    CheckPrdouctListOnSaleUI* checkPrdouctListOnSaleUI = new CheckPrdouctListOnSaleUI(this);
    checkPrdouctListOnSaleUI->startInterface();
}
CheckPrdouctInfoSoldUI::CheckPrdouctInfoSoldUI(CheckPrdouctInfoSold* checkPrdouctInfoSold) {
    this->checkProudctInfoSold = checkPrdouctInfoSold;
}
CheckPrdouctListOnSaleUI::CheckPrdouctListOnSaleUI(CheckPrdouctListOnSale* checkPrdouctListOnSale) {
    this->checkPrdouctListOnSale = checkPrdouctListOnSale;
}
void CheckPrdouctInfoSoldUI::startInterface() {
    list = checkProudctInfoSold->showProductInfo();
    outputList();
}
void CheckPrdouctListOnSaleUI::startInterface() {
    list = checkPrdouctListOnSale->ShowProductlist();
    outputList();
}
void CheckPrdouctInfoSoldUI::outputList() {
    unsigned int i = 0;
    Product* product;
    while (list.getProduct(i)) {
        product = list.getProduct(i);
        fout << product->getProductName();
        fout << " ";
        fout << product->getProductCompanyName();
        fout << " ";
        fout << product->getPrice();
        fout << " ";
        fout << product->getStockNum();
        fout << " ";
        unsigned int order = 0;
        int sum = 0;
        float average = 0;
        vector<int> buySatisfaction = product->getSatisfaction();
        while (order < buySatisfaction.size()) {
            sum += buySatisfaction[order];
            order++;
        }
        if (sum != 0) {
            average = round(sum / (float)(order + 1));
        }
        fout << average; //평균구매만족도
        fout << " " << endl;
    }
}
void CheckPrdouctListOnSaleUI::outputList() {
    unsigned int i = 0;
    Product* product;
    while (list.getProduct(i)) {
        product = list.getProduct(i);
        fout << " ";
        fout << product->getProductName();
        fout << " ";
        fout << product->getProductCompanyName();
        fout << " ";
        fout << product->getPrice();
        fout << " ";
        fout << product->getOriginalStockNum();
        fout << " " << endl;

    }
}
ProductCollection CheckPrdouctInfoSold::showProductInfo() {
    ProductCollection list;
    list = seller->listProduct_OnSold();
    return list;
}
ProductCollection CheckPrdouctListOnSale::ShowProductlist() {
    ProductCollection list;
    list = seller->listProduct_OnSale();
    return list;
}
int Product::getOriginalStockNum() { return originalStockNum; }
//int Product::getStockNum() { return stockNum; }
//int Product::getProfit() { return price; }
//int Product::getSatisfaction() { return buySatisfaction; }
//string Product::getProductName() { return productName; }
//string Product::getProductCompanyName() { return productCompanyName; }
/*Seller::listProduct_OnSold() {
    vector<Product*> list;
    for (int i = 0; i < product.size(); i++) {
        if (product[i]->getStockNum() == 0) {
            list.push_back(product[i]);
        }

    }
    return list;
}
vector<Product*> Seller::listProductOnSale() {
    vector<Product*> list;
    for (int i = 0; i < product.size(); i++) {
        if (product[i]->getStockNum() > 0) {
            list.push_back(product[i]);
        }

    }
    return list;
}*/
/*
AddClothes::AddClothes(Seller* seller) {
    this->seller = seller;
    AddClothesUI* addClothesUI = new AddClothesUI(this, this->seller);
    addClothesUI->startInterface();
}
AddClothesUI::AddClothesUI(AddClothes* addClothes, Seller* seller) {
    this->addClothes = addClothes;
    this->seller = seller;
}
void AddClothesUI::output(Seller* seller) {

    /*fout << seller->listProduct_OnSale().getProduct->getProductName();
    fout << " ";
    fout << seller->listProduct_OnSale().back()->getProductCompanyName();  //제품단가와 판패된 총 재고를 곱하여 총판매액을 구한다.
    fout << " ";
    fout << seller->listProductOnSale().back()->getPorfit(); //평균구매만족도
    fout << " " << seller->listProductOnSale().back()->getStockNum() << endl;
    
}
void AddClothesUI::startInterface() {
    string productName;
    string productCompanyName;
    int price;
    int stockNum;
    fin >> productName >> productCompanyName >> price >> stockNum;
    addClothes->addNewClothes(productName, productCompanyName, price, stockNum);
    output(this->seller);

}
void AddClothes::addNewClothes(string productName, string productCompanyName, int price, int stockNum) {

    seller->addNewClothes(productName, productCompanyName, price, stockNum);
}
void Seller::addNewClothes(string productName, string productCompanyName, int price, int stockNum) {
    Product* newProduct = new Product(productName, productCompanyName, price, stockNum);
    this->onSaleProductCollection.addProduct(newProduct);
    //product.push_back(newProduct);
}
Product::Product(string productName, string productCompanyName, int price, int stockNum) {
    this->productName = productName;
    this->productCompanyName = productCompanyName;
    this->price = price;
    this->stockNum = stockNum;
    originalStockNum = stockNum; //초기재고량 
}
*/

PrintStatistics::PrintStatistics(Seller* seller) {
    this->seller = seller;
    PrintStatisticsUI* printStatisticsUI = new PrintStatisticsUI(this);
    printStatisticsUI->startInterface();
}
PrintStatisticsUI::PrintStatisticsUI(PrintStatistics* printStatistics) {
    this->printStatistics = printStatistics;
}

void PrintStatisticsUI::outputList() {
    fout << "> ";
    for (unsigned int i = 0; i < list.size(); i++) {
        fout << " ";
        fout << list[i]->getProductName();
        fout << " ";
        fout << list[i]->getPrice() * list[i]->getOriginalStockNum();  //제품단가와 판패된 총 재고를 곱하여 총판매액을 구한다.
        fout << " ";
        unsigned int order = 0;
        int sum = 0;
        int average = 0;
        vector<int> buySatisfaction = list[i]->getSatisfaction();
        while (order < buySatisfaction.size()) {
            sum += buySatisfaction[order];
            order++;
        }
        if (sum != 0) {
            average = round(sum / (float)order);
        }
        fout << average; //평균구매만족도
        fout << " " << endl;
    }
}
void PrintStatisticsUI::startInterface() {
    list = printStatistics->printStatisticsinfo();
    outputList();
}
vector<Product*> PrintStatistics::printStatisticsinfo() {
    vector<Product*> list;
    list = seller->listProduct_OnSold();
    return list;
}
CheckPrdouctInfoSold::CheckPrdouctInfoSold(Seller* seller) {
    this->seller = seller;
    CheckPrdouctInfoSoldUI* checkPrdouctInfoSoldUI = new CheckPrdouctInfoSoldUI(this);
    checkPrdouctInfoSoldUI->startInterface();
}
CheckPrdouctListOnSale::CheckPrdouctListOnSale(Seller* seller) {
    this->seller = seller;
    CheckPrdouctListOnSaleUI* checkPrdouctListOnSaleUI = new CheckPrdouctListOnSaleUI(this);
    checkPrdouctListOnSaleUI->startInterface();
}
CheckPrdouctInfoSoldUI::CheckPrdouctInfoSoldUI(CheckPrdouctInfoSold* checkPrdouctInfoSold) {
    this->checkProudctInfoSold = checkPrdouctInfoSold;
}

void CheckPrdouctInfoSoldUI::startInterface() {
    list = checkProudctInfoSold->showProductInfo();
    outputList();
}
CheckPrdouctListOnSaleUI::CheckPrdouctListOnSaleUI(CheckPrdouctListOnSale* checkPrdouctListOnSale) {
    this->checkPrdouctListOnSale = checkPrdouctListOnSale;
}
void CheckPrdouctListOnSaleUI::startInterface() {
    list = checkPrdouctListOnSale->ShowProductlist();
    outputList();
}
void CheckPrdouctInfoSoldUI::outputList() {
    vector<string> productNames;
    unsigned int i = 0;
    while (i < this->list.size()) {
        productNames.push_back(list[i]->getProductName());
        i++;
    }
    sort(productNames.begin(), productNames.end()); // 정렬
    i = 0;
    while (i < productNames.size()) {
        unsigned j = 0;
        while (j < this->list.size()) {
            if (productNames[i] == list[j]->getProductName()) {
                break;
            }
            j++;
        }
        fout << list[j]->getProductName();
        fout << " ";
        fout << list[j]->getProductCompanyName();
        fout << " ";
        fout << list[j]->getPrice();
        fout << " ";
        fout << list[j]->getStockNum();
        fout << " ";
        vector<int> buySatisfaction = list[j]->getSatisfaction();
        unsigned int order = 0;
        int sum = 0;
        int average = 0;
        while (order < buySatisfaction.size()) {
            sum += buySatisfaction[order];
            order++;
        }
        if (sum != 0) {
            //cout << sum << order << endl;
            average = round(sum / (float)order);
        }
        fout << average << endl;
        i++;
    }
    /*sort(list.begin(), list.end());
    for (int i = 0; i < list.size(); i++) {
        fout << list[i]->getProductName();
        fout << " ";
        fout << list[i]->getProductCompanyName();
        fout << " ";
        fout << list[i]->getPrice();
        fout << " ";
        fout << list[i]->getStockNum();
        fout << " ";
        fout << list[i]->getSatisfacation(); //평균구매만족도
        fout << " " << endl;
    }*/
}
void CheckPrdouctListOnSaleUI::outputList() {
    fout << ">";
    for (unsigned int i = 0; i < list.size(); i++) {
        fout << " ";
        fout << list[i]->getProductName();
        fout << " ";
        fout << list[i]->getProductCompanyName();
        fout << " ";
        fout << list[i]->getPrice();
        fout << " ";
        fout << list[i]->getOriginalStockNum();
        fout << " " << endl;

    }
}
vector<Product*> CheckPrdouctInfoSold::showProductInfo() {
    vector<Product*> list;
    list = seller->listProduct_OnSold();
    return list;
}
vector<Product*> CheckPrdouctListOnSale::ShowProductlist() {
    vector<Product*> list;
    list = seller->listProduct_OnSale();
    return list;
}
int Product::getOriginalStockNum() { return originalStockNum; }
int Product::getStockNum() { return stockNum; }
//int Product::getPorfit() { return price; }
//int Product::getSatisfacation() { return buySatisfaction; }
string Product::getProductName() { return productName; }
string Product::getProductCompanyName() { return productCompanyName; }
vector<Product*> Seller::listProduct_OnSold() {
    vector<Product*> list;
    for (unsigned int i = 0; i < this->product.getProductlist().size(); i++) {
        if (this->product.getProductlist()[i]->getStockNum() == 0) {
            list.push_back(this->product.getProductlist()[i]);
        }

    }
    return list;
}
vector<Product*> Seller::listProduct_OnSale() {
    vector<Product*> list;
    for (unsigned int i = 0; i < this->product.getProductlist().size(); i++) {
        if (this->product.getProductlist()[i]->getStockNum() > 0) {
            list.push_back(this->product.getProductlist()[i]);
        }

    }
    return list;
}
AddClothes::AddClothes(Seller* seller) {
    this->seller = seller;
    AddClothesUI* addClothesUI = new AddClothesUI(this, this->seller);
    addClothesUI->startInterface();
}
AddClothesUI::AddClothesUI(AddClothes* addClothes, Seller* seller) {
    this->addClothes = addClothes;
    this->seller = seller;
}
void AddClothesUI::output(string productName, string productCompanyName, int price, int stockNum) {

    fout << "> ";
    fout << productName;
    fout << " ";
    fout << productCompanyName;  //제품단가와 판패된 총 재고를 곱하여 총판매액을 구한다.
    fout << " ";
    fout << price; //평균구매만족도
    fout << " " << stockNum << endl;

}
void AddClothesUI::startInterface() {
    string productName;
    string productCompanyName;
    int price;
    int stockNum;
    fin >> productName >> productCompanyName >> price >> stockNum;
    addClothes->addNewClothes(productName, productCompanyName, price, stockNum);
    output(productName, productCompanyName, price, stockNum);

}
void AddClothes::addNewClothes(string productName, string productCompanyName, int price, int stockNum) {

    seller->addNewClothes(productName, productCompanyName, price, stockNum);
}
void Seller::addNewClothes(string productName, string productCompanyName, int price, int stockNum) {
    Product* newProduct = new Product(productName, productCompanyName, price, stockNum);
    this->product.addProduct(newProduct);  //product collection class에
}
void ProductCollection::addProduct(Product* product) {
    this->product.push_back(product);
}

Product::Product(string productName, string productCompanyName, int price, int stockNum) {
    this->productName = productName;
    this->productCompanyName = productCompanyName;
    this->price = price;
    this->stockNum = stockNum;
    originalStockNum = stockNum; //초기재고량 
}
vector<Product*> ProductCollection::getProductlist()
{
    return product;
}

//상품 검색 바운더리 클래스 생성자
SearchProductUI::SearchProductUI(SearchProduct* searchProduct) {
    this->searchProduct = searchProduct;
}

//Function: void SearchProductUI::enterProductName()
//Description: 입력 파일에서 상품명을 읽어들이고 이 상품명을 상품 검색 컨트롤 객체의 상품 검색을 수행하는 함수에 인자로 넣고 호출한다.
//Author: 조은비
void SearchProductUI::enterProductName() {
    string productName;
    fin >> productName;
    this->searchProduct->showSearchProductInfo(productName);
}

//Function: void SearchProductUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, float averageSatisfaction)
//Description: 상품 검색 결과를 출력 파일에 쓴다.
//Parameter : string sellerID - 판매자ID, string producName - 상품명, string productComapanyName - 상품회사명, 
//int price - 상품 가격, int stockNum - 상품 재고, int averageSatisfaction - 평균 구매만족도
//Author: 조은비
void SearchProductUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction) {
    
    fout << "> " << sellerID << " " << productName << " " << productCompanyName << " " << price << " " << stockNum << " " << averageSatisfaction << endl;
}

//상품 검색 컨트롤 클래스 생성자
SearchProduct::SearchProduct(vector<Seller*> sellerList) {
    SearchProductUI* searchProductUI = new SearchProductUI(this);
    this->searchProductUI = searchProductUI;
    this->searchProduct = 0;
    this->searchProductSeller = 0;
    this->listSeller = sellerList;
    this->searchProductUI->enterProductName();
}

//Function: void SearchProduct::showSearchProductInfo(string name)
//Description: 상품 검색을 수행하고 그 결과를 인자로 전달하여 상품 검색 바운더리의 printResult 함수를 호출한다.
//Parameter : string productName - 상품명
//Author: 조은비
void SearchProduct::showSearchProductInfo(string productName) {
    bool find = false;
    unsigned int i = 0;
    vector<Product*> saleProducts;
    Product* product = 0;
    while (i < listSeller.size()) {
        saleProducts = listSeller[i]->listProduct_OnSale(); // 판매중인 리스트 가져옴
        unsigned int j = 0;
        while (j < saleProducts.size()) {
            if (productName == saleProducts[j]->getProductName()) {
                product = saleProducts[j];
                find = true;
                break;
            }
            j++;
        }
        if (find) break;
        i++;
    }
    if (find) {
        unsigned int count = 0;
        int sum = 0;
        int average = 0;
       
        vector<int> buySatisfaction = product->getSatisfaction();
        while (count < buySatisfaction.size()) {
            sum += buySatisfaction[count];
            count++;
        }
        if (sum != 0) {
            average = round(sum / (float)count);
        }
        this->searchProductSeller = listSeller[i];
        this->searchProduct = product;
        this->searchProductUI->printResult(listSeller[i]->getSellerID(), product->getProductName(),
            product->getProductCompanyName(), product->getPrice(), product->getStockNum(), average);
    }
}

//Function: Seller* SearchProduct::getSearchProductSeller()
//Description: 검색한 상품의 판매자를 가리키는 포인터를 반환한다.
//Return Value : Seller*
//Author: 조은비
Seller* SearchProduct::getSearchProductSeller() {
    return this->searchProductSeller;
}

//Function: Product* SearchProduct::getSearchProduct()
//Description: 검색한 상품을 가리키는 포인터를 반환한다.
//Return Value : Product*
//Author: 조은비
Product* SearchProduct::getSearchProduct() {
    return this->searchProduct;
}

//상품 구매 바운더리 클래스 생성자
BuyProductUI::BuyProductUI(BuyProduct* buyProduct) {
    this->buyProduct = buyProduct;
}

//Function: void BuyProductUI::printResult(string sellerID, string productName)
//Description: 상품 구매 결과를 출력한다.
//Parameter : string sellerID - 구매한 상품의 판매자 ID, string productName - 구매한 상품명
//Author: 조은비
void BuyProductUI::printResult(string sellerID, string productName) {
    fout << "> " << sellerID << " " << productName << endl;
}

//상품 구매 컨트롤 클래스 생성자
BuyProduct::BuyProduct(Buyer* buyer, Seller* searchProductSeller, Product* searchProduct) {
    BuyProductUI *buyProductUI = new BuyProductUI(this);
    this->buyProductUI = buyProductUI;
    this->buyer = buyer;
    this->searchProductSeller = searchProductSeller;
    this->searchProduct = searchProduct;
    if (!this->buyer->listBoughtProducts().findProduct(this->searchProduct->getProductName())) {
        this->searchProduct->decreaseStockNum();
        this->buyer->addProductToBoughtList(this->searchProduct);
        this->buyProductUI->printResult(this->searchProductSeller->getSellerID(), this->searchProduct->getProductName());
    }
}

//구매 내역 조회 바운더리 클래스 생성자
SeeBoughtListUI::SeeBoughtListUI(SeeBoughtList* seeBoughtList) {
    this->seeBoughtList = seeBoughtList;
}

//Function: void SeeBoughtListUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction)
//Description: 구매 내역 조회 결과를 출력한다.
//Parameter : string sellerID - 판매자ID, string producName - 상품명, string productComapanyName - 상품회사명, 
//int price - 상품 가격, int stockNum - 상품 재고, int averageSatisfaction - 평균 구매만족도
//Author: 조은비
void SeeBoughtListUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction) {
    fout << "> " << sellerID << " " << productName << " " << productCompanyName << " " << price << " " << stockNum << " " << averageSatisfaction << endl;
}

//구매 내역 조회 컨트롤 클래스 생성자
SeeBoughtList::SeeBoughtList(Buyer* buyer, vector<Seller*> sellerList) {
    SeeBoughtListUI *seeBoughtListUI = new SeeBoughtListUI(this);
    this->seeBoughtListUI = seeBoughtListUI;
    this->buyer = buyer;
    this->listSeller = sellerList;
    this->showBoughtListInfo();
}

//Function: void SeeBoughtList::showBoughtListInfo()
//Description: 구매 내역을 상품명을 기준으로 오름차순으로 정렬하고 조회된 정보를 바운더리 printResult 함수에 인자로 넣어 호출한다.
//Author: 조은비
void SeeBoughtList::showBoughtListInfo() {
    bool find = false;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    ProductCollection boughtProducts = this->buyer->listBoughtProducts();
    vector<Product*> products;
    Product* product;
    vector<string> boughtProductNames;
    while (boughtProducts.getProduct(i)) {
        boughtProductNames.push_back(boughtProducts.getProduct(i)->getProductName());
        i++;
    }
    sort(boughtProductNames.begin(), boughtProductNames.end()); 
    this->sortedBoughtProductNames = boughtProductNames;
    i = 0;
    while (i < sortedBoughtProductNames.size()) {
        while (j < listSeller.size()) {
            products = listSeller[j]->listProduct_OnSale(); 
            while (k < products.size()) {
                if (sortedBoughtProductNames[i] == products[k]->getProductName()) {
                    find = true;
                    break;
                }
                k++;
            }
        
            if (!find) {
                k = 0;
                products = listSeller[j]->listProduct_OnSold(); // 판매 완료된 목록에서 찾기
                while (k < products.size()) {
                    if (sortedBoughtProductNames[i] == products[k]->getProductName()) {
                        find = true;
                        break;
                    }
                    k++;
                }
            }
            if (find) break;
            else k = 0;
            j++;
        }
        this->sellerID.push_back(listSeller[j]->getSellerID()); // 정렬된 기준 구매한 상품의 판매자 id 저장
        product = this->buyer->listBoughtProducts().findProduct(sortedBoughtProductNames[i]); // 정렬된 상품명 기준으로 구매 내역에서 해당 상품 찾기
        unsigned int count = 0;
        int sum = 0;
        int average = 0;
        vector<int> buySatisfaction = product->getSatisfaction();
        while (count < buySatisfaction.size()) {
            sum += buySatisfaction[count];
            count++;
        }
        if (sum != 0) {
            average = round(sum / (float)count);
        }
        this->seeBoughtListUI->printResult(listSeller[j]->getSellerID(), product->getProductName(),
            product->getProductCompanyName(), product->getPrice(), product->getStockNum(), average);
        j = 0;
        i++;
    }
}

//Function: vector<string> SeeBoughtList::getSellerIDList()
//Description: 구매 내역의 판매자 ID 리스트를 반환한다.
//Return Value : vector<string>
//Author: 조은비
vector<string> SeeBoughtList::getSellerIDList() {
    return this->sellerID;
}

//구매만족도 평가 바운더리 클래스 생성자
EvaluateBuySatisfactionUI::EvaluateBuySatisfactionUI(EvaluateBuySatisfaction* evaluateBuySatisfaction) {
    this->evaluateBuySatisfaction = evaluateBuySatisfaction;
}

//Function: void EvaluateBuySatisfactionUI::enterProductNameAndBuySatisfaction()
//Description: 입력 파일에서 상품명과 구매 만족도 값을 읽어들이고 컨트롤 addSatisfaction함수에 인자로 넣어 호출한다.
//Author: 조은비
void EvaluateBuySatisfactionUI::enterProductNameAndBuySatisfaction() {
    string productName;
    int satisfaction;
    fin >> productName;
    fin >> satisfaction;
    this->evaluateBuySatisfaction->addSatisfaction(productName, satisfaction);
}

//Function: void EvaluateBuySatisfactionUI::printResult(string sellerID, string productName, int satisfaction)
//Description: 구매 만족도 평가 결과를 출력파일에 쓴다.
//Parameter : string sellerID - 판매자 ID, string productName - 상품명, int satisfaction - 평가한 구매 만족도
//Author: 조은비
void EvaluateBuySatisfactionUI::printResult(string sellerID, string productName, int satisfaction) {
    fout << "> " << sellerID << " " << productName << " " << satisfaction << endl;
}

//구매만족도 평가 컨트롤 클래스 생성자
EvaluateBuySatisfaction::EvaluateBuySatisfaction(Buyer* buyer, vector<string> boughtListSellerID, vector<string> sortedBoughtListNames) {
    EvaluateBuySatisfactionUI *evaluateBuySatisfactionUI = new EvaluateBuySatisfactionUI(this);
    this->evaluateBuySatisfactionUI = evaluateBuySatisfactionUI;
    this->buyer = buyer;
    this->boughtListSellerID = boughtListSellerID;
    this->sortedBoughtListNames = sortedBoughtListNames;
    this->evaluateBuySatisfactionUI->enterProductNameAndBuySatisfaction();
}

//Function: void EvaluateBuySatisfaction::addSatisfaction(string productName, int satisfaction)
//Description: 평가한 구매 만족도를 해당 상품에 추가한다.
//Parameter : string productName - 상품명, int satisfaction - 평가한 구매 만족도
//Author: 조은비
void EvaluateBuySatisfaction::addSatisfaction(string productName, int satisfaction) {
    Product *product;
    product = this->buyer->listBoughtProducts().findProduct(productName);
    if (product) {
        if (satisfaction >= 1 && satisfaction <= 5) {
            product->addBuySatisfaction(satisfaction);
            unsigned int count = 0;
            while (this->sortedBoughtListNames.size()) {
                if (productName == this->sortedBoughtListNames[count]) {
                    break;
                }
                count++;
            }
            this->evaluateBuySatisfactionUI->printResult(this->boughtListSellerID[count], productName, satisfaction);
        }
    }
}

//Function : string Seller::getSellerID()
//Description: 판매자 ID를 반환한다.
//Return Value : string
//Author: 조은비
string Seller::getSellerID() {
    return this->getID();
}

//Function : ProductCollection Buyer::listBoughtProducts()
//Description: 구매내역을 반환한다.
//Return Value : ProductCollection
//Author: 조은비
ProductCollection Buyer::listBoughtProducts() {
    return this->boughtProductCollection;
}

//Function : void Buyer::addProductToBoughtList(Product* product)
//Description: 구매한 상품을 구매 내역에 추가한다.
//Author: 조은비
void Buyer::addProductToBoughtList(Product* product) {
    this->boughtProductCollection.addProduct(product);
}

//Function : int Product::getPrice()
//Description: 상품 가격을 반환한다.
//Return Value : int
//Author: 조은비
int Product::getPrice() {
    return this->price;
}

//Function : vector<int> Product::getSatisfaction()
//Description: 구매 만족도 리스트를 반환한다.
//Return Value : vector<int>
//Author: 조은비
vector<int> Product::getSatisfaction() {
    return this->buySatisfaction;
}

//Function : void Product::addBuySatisfaction(int satisfaction)
//Description: 평가받은 구매 만족도 값을 기존 구매 만족도 리스트에 추가한다. 
//Parameter : int satisfaction - 만족도
//Author: 조은비
void Product::addBuySatisfaction(int satisfaction) {
    this->buySatisfaction.push_back(satisfaction);
}

//Function : void Product::decreaseStockNum()
//Description: 상품 재고를 1 감소시킨다. 
//Author: 조은비
void Product::decreaseStockNum() {
    this->stockNum--;
}

//Function : Product* ProductCollection::getProduct(unsigned int order)
//Description: 상품 리스트에서 인자로 받은 해당 순서의 상품을 가리키는 포인터를 반환한다. 해당 순서에서 반환할 게 없으면 0(null)을 반환한다.
//Parameter : unsigned int order - index 순서
//Return Value : Product*
//Author: 조은비
Product* ProductCollection::getProduct(unsigned int order) {
    if (order < this->product.size()) {
        return this->product[order];
    }
    else return 0;
}

//상품 리스트에 상품 추가
/*void ProductCollection::addProduct(Product* product) {
    this->product.push_back(product);
}*/

//Function : Product* ProductCollection::findProduct(string name)
//Description: 상품 리스트에서 인자로 받은 상품명과 일치하는 이름을 가진 상품을 찾는다. 찾으면 해당 상품을 가리키는 포인터를 반환하고 없으면 0(null)을 반환한다.
//Parameter : string name - 상품명
//Return Value : Product*
//Author: 조은비
Product* ProductCollection::findProduct(string name) {
    unsigned int i = 0;
    while (i < this->product.size()) {
        if (this->product[i]->getProductName() == name) {
            return this->product[i];
        }
        i++;
    }
    return 0;
}


