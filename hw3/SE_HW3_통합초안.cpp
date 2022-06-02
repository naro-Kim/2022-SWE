#include "SE_HW3.h"

//Function: void SelectMenu::doTask()
//Description: �Է� ���Ͽ��� �޴��� ��Ÿ���� ���� 2���� �о � �޴��� �ش��ϴ��� switch������ �Ǻ��Ѵ�. �׸��� �ش��ϴ� �޴��� ��Ʈ�� Ŭ������ �����Ѵ�.
//Author: ������
void SelectMenu::doTask() {
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;
    AccountDB* accountDB = new AccountDB(); // DB ���� �����ϰ� �ϱ� ����
    Login* login = 0; // �α����� ����� ���� �����ϰ� �ϱ� ����
    Seller* seller = 0;
    Buyer* buyer = 0;
    SearchProduct* searchproduct = 0; // �˻��� ��ǰ�� ��Ÿ��
    vector<string> boughtListSellerIDList; // ���� ������ �ִ� ��ǰ���� �Ǹ��� ID ����Ʈ
    vector<string> sortedBoughtListNames;
    vector<Seller*> sellerList;
    vector<Buyer*> buyerList;

    fin.open(INPUT_FILE_NAME);
    fout.open(OUTPUT_FILE_NAME);
    

    while (!is_program_exit)
    {
        // �Է����Ͽ��� �޴� ���� 2���� �б�
        fin >> menu_level_1;
        fin >> menu_level_2;
        //cout << "db ������ ���� " << accountDB->returnsize();
        // �޴� ���� �� �ش� ���� ����
        switch (menu_level_1)
        {
        case 1:
        {
            switch ((menu_level_2))
            {
            case 1:
            {
                fout << "1.1. ȸ������" << endl;
                CreateAccount* createAccount;
                createAccount = new CreateAccount(accountDB);

                break;
            }
            case 2:
            {
                fout << "1.2. ȸ��Ż��" << endl;
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
                fout << "2.1. �α���" << endl;
                login = new Login(accountDB);
                break;
            }
            case 2:
            {
                fout << "2.2. �α׾ƿ�" << endl;
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
                if (sellerList[i]->getID() == login->getLoginAccount()->getID()) { // ���� �α����� ������ �̹� �Ǹ��� ����Ʈ�� ��ϵǾ� �ִ��� üũ
                    find = true;
                    break;
                }
            }
            if (find) {
                seller = sellerList[i];
            }
            else {
                seller = new Seller(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); // �Ǹ��� �������� ���
                sellerList.push_back(seller); //�Ǹ��� ����Ʈ�� �߰�
            }
            switch (menu_level_2)
            {
                //cout << "���� �α����� ����" << login->getLoginAccount()->getID();
                //seller = (Seller*)login->getLoginAccount();
                //cout << "���� �α����� ����" << seller->getID();
            case 1: // "3.1. �Ǹ� �Ƿ� ��� �޴� �κ�
            { // control class ����
                //cout << "���� �α����� ����" << login->getLoginAccount()->getID();
                //seller = new Seller(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); // �Ǹ��� �������� ���
                //sellerList.push_back(seller); //�Ǹ��� ����Ʈ�� �߰�
                fout << "3.1. �Ǹ� �Ƿ� ��� " << endl;
                //seller = (Seller*)login->getLoginAccount();
                //seller = (Seller*)login->getLoginAccount();
                AddClothes* registClothes = new AddClothes(seller); 
                break; 
            }
            case 2: // 3.2 ��� ��ǰ ��ȸ(�Ǹ���)
            {
                fout << "3.2. ��� ��ǰ ��ȸ " << endl;
                CheckPrdouctListOnSale* checkProudctListOnSale = new CheckPrdouctListOnSale(seller);

                break;
            }
            case 3: // 3.3 �Ǹ� �Ϸ� ��ǰ ��ȸ
            {
                fout << "3.3 �Ǹ� �Ϸ� ��ǰ ��ȸ " << endl;
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
                if (buyerList[i]->getID() == login->getLoginAccount()->getID()) { // ���� �α����� ������ �̹� ������ ����Ʈ�� ��ϵǾ� �ִ��� üũ
                    find = true;
                    break;
                }
                i++;
            }
            if (find) {
                buyer = buyerList[i];
            }
            else {
                buyer = new Buyer(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); //������ �������� ���
                buyerList.push_back(buyer); //������ ����Ʈ�� �߰�
            }
            switch (menu_level_2)
            {
            case 1:   // "4.1. ��ǰ �˻��� �޴� �κ�
            {
                // ��ǰ �˻� ��Ʈ�� Ŭ���� ����
                fout << "4.1. ��ǰ ���� �˻� " << endl;
                searchproduct = new SearchProduct(sellerList);
                break;
            }
            case 2:   // "4.2. ��ǰ ���š� �޴� �κ�
            {
                // ��ǰ ���� ��Ʈ�� Ŭ���� ����
                fout << "4.2. ��ǰ ���� " << endl;
                BuyProduct* buyproduct = new BuyProduct(buyer, searchproduct->getSearchProductSeller(), searchproduct->getSearchProduct());
                break;
            }
            case 3:   // "4.3. ���� ���� ��ȸ�� �޴� �κ�
            {
                // ���� ���� ��ȸ ��Ʈ�� Ŭ���� ����
                fout << "4.3. ��ǰ ���� ���� ��ȸ " << endl;
                SeeBoughtList* seeboughtlist = new SeeBoughtList(buyer, sellerList);
                boughtListSellerIDList = seeboughtlist->getSellerIDList();
                sortedBoughtListNames = seeboughtlist->getSortedBoughtProductNameList();
                break;
            }
            case 4:   // "4.4. ���� ������ �򰡡� �޴� �κ�
            {
                // ���� ������ �� ��Ʈ�� Ŭ���� ����
                fout << "4.4. ��ǰ ���� ������ �� " << endl;
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
                if (sellerList[i]->getID() == login->getLoginAccount()->getID()) { // ���� �α����� ������ �̹� �Ǹ��� ����Ʈ�� ��ϵǾ� �ִ��� üũ
                    find = true;
                    break;
                }
            }
            if (find) {
                seller = sellerList[i];
            }
            else {
                seller = new Seller(login->getLoginAccount()->getName(), login->getLoginAccount()->getSsn(), login->getLoginAccount()->getID(), login->getLoginAccount()->getPassword()); // �Ǹ��� �������� ���
                sellerList.push_back(seller); //�Ǹ��� ����Ʈ�� �߰�
            }
            switch (menu_level_2)
            {
            case 1://�ǸŻ�ǰ���
                fout << "5.1 �Ǹ� ��ǰ ��� " << endl;
                PrintStatistics* printStatistics = new PrintStatistics(seller);
                break;
            }

        }
        case 6: {
            switch (menu_level_2)
            {
            case 1: // "6.1. ���ᡰ �޴� �κ�
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
    fout << "6.1. ����" << endl;
}

//�Ǹ��� ���� ����
Seller::Seller(string name, string ssn, string ID, string password) {
    this->createAccount(name, ssn, ID, password);
}

//������ ���� ����
Buyer::Buyer(string name, string ssn, string ID, string password) {
    this->createAccount(name, ssn, ID, password);
}

//���ĵ� ���ų��� ��ǰ�� ����Ʈ ��ȯ
vector<string> SeeBoughtList::getSortedBoughtProductNameList() {
    return this->sortedBoughtProductNames;
}

//Function: Account* Login::getLoginAccount()
//Description: ���� �α��� ������ ������ ����Ű�� �����͸� ��ȯ�Ѵ�.
// Return Value : Account*
//Author: ������
Account* Login::getLoginAccount() {
    return this->loginPointer;
    //return 0;
}

//Function: void Account::createAccount(string name, string ssn, string ID, string password)
//Description: �Է¹��� ������ ���� ȸ���� ������ �����Ѵ�.
//Parameter : string name - ȸ�� ���� �̸�, string ssn - ȸ�� �ֹι�ȣ , string ID - ȸ�� ���̵�, string password - ȸ�� ��й�ȣ
//Return Value : void
//Author: �����
void Account::createAccount(string name, string ssn, string ID, string password)
{
    this->name = name;
    this->ssn = ssn;
    this->ID = ID;
    this->password = password;
}

//Function: bool Account::getLogStatus()
//Description: ��ü�� �α��� ���¸� ��ȯ�Ѵ�.
//Return Value : bool
//Author: �����

bool Account::getLogStatus() { return this->logStatus; }

//Function: bool Account::setLogStatus()
//Description: ��ü�� �α��� ���¸� �����Ѵ�.
//Return Value : void
//Author: �����

void Account::setLogStatus()
{
    if (this->logStatus == false) { this->logStatus = true; }
    else { this->logStatus = false; }
}

//Function: string Account::getID()
//Description: ��ü�� ID�� ��Ʈ������ �����Ѵ�.
//Return Value : string
//Author: �����  
  
string Account::getID() { return this->ID; }

//Function: string Account::getPassword()
//Description: ��ü�� Password�� ��Ʈ������ �����Ѵ�.
//Return Value : string
//Author: �����  

string Account::getPassword() { return this->password; }

//Function: string Account::getName()
//Description: ��ü�� Name�� ��Ʈ������ �����Ѵ�.
//Return Value : string
//Author: �����  

string Account::getName() { return this->name; }


//Function: string Account::getSsn()
//Description: ��ü�� ssn�� ��Ʈ������ �����Ѵ�.
//Return Value : string
//Author: �����  

string Account::getSsn() { return this->ssn; }


// Function : void AccountDB::storeAccount(Account* account)
// Description: ������ Account ��ü�� AccountDB���� ������ �����Ѵ�.
// Parameter : Account* account -  ȸ�� �ɹ� ��ü
// Return Value : void
// Author: �����

void AccountDB::storeAccount(Account* account)
{
    this->accounts.push_back(account);
}

// Function : Account* AccountDB::getAccountIndex(string ID)
// Description: AccountDB������ �ش� ID�� ���� ��ü�� �����͸� ���� 
// Parameter : string ID - ȸ�� ���̵� 
// Return Value : Account* 
// Author: �����
// // Revsions : ������  

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
// Description: AccountDB������ �ش� ID�� ���� ��ü�� Index�� ã�Ƴ��� �ش� ��ü�� DB���� ���� 
// Parameter : string ID - ȸ�� ���̵� 
// Return Value : void 
// Author: �����
// // Revsions : ������ 

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
// Description: AccountDB������ parameter�� �ش��ϴ� ID�� Password�� ���� account�� �ִ��� Ȯ�� �� �� ��ȿ���� Boolean���� ����
// Parameter : string ID - ȸ�� ���̵�, string password - ȸ�� ��й�ȣ
// Return Value : Bool 
// Author: �����

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
// Description : AccountDB������ parameter�� �ش��ϴ� ID�� Password�� ���� account�� �ִ��� Ȯ�� �� �α���
// Parameter : string ID - ȸ�� ���̵�, string password - ȸ�� ��й�ȣ
// Return Value : void
// Author: �����

void AccountDB::logIn(string ID, string password)
{
    getAccountIndex(ID)->setLogStatus();
}

// Function : void AccountDB::logOut(string ID, string password)
// Description : AccountDB������ parameter�� �ش��ϴ� ID�� Password�� ���� account�� �ִ��� Ȯ�� �� �α׾ƿ�
// Parameter : string ID - ȸ�� ���̵�, string password - ȸ�� ��й�ȣ
// Return Value : void
// Author: �����

void AccountDB::logOut(string ID)
{

    getAccountIndex(ID)->setLogStatus();

}
 
// ȸ������ �ٿ���� Ŭ���� ������

CreateAccountUI::CreateAccountUI(CreateAccount* createAccount)
{
    this->createAccount = createAccount;
}

// Function :void CreateAccountUI::enterAccountInfo()
// Description : ȸ������ �ٿ�������� ���� ������ �Է��ϴ� �Լ�
// Return Value : void
// Author: �����

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
// Description : ȸ������ �ٿ�������� ���� ���� �� ����� �ش� ������ ������ ����ϴ� �Լ�
// Parameter : string name - ȸ�� ���� �̸�, string ssn - ȸ�� �ֹι�ȣ , string ID - ȸ�� ���̵�, string password - ȸ�� ��й�ȣ
// Return Value : void
// Author: ������

void CreateAccountUI::printResult(string name, string ssn, string ID, string password) {
    fout << "> " << name << " " << ssn << " " << ID << " " << password << endl;
}

// ȸ������ ��Ʈ�� Ŭ���� ������
CreateAccount::CreateAccount(AccountDB* accountDB)
{
    CreateAccountUI* createAccountUi = new CreateAccountUI(this);
    this->createAccountUi = createAccountUi;
    this->accountDB = accountDB;
    this->createAccountUi->enterAccountInfo();
}
 
// Function : void CreateAccount::createNewAccount(string name, string ssn, string id, string password) 
// Description : ȸ������ ��Ʈ�ѿ��� AccountDB���� ������ ���ٸ� �� ������ ������ �����ϰ� �� ����� ����ϴ� �Լ�
// Parameter : string name - ȸ�� ���� �̸�, string ssn - ȸ�� �ֹι�ȣ , string ID - ȸ�� ���̵�, string password - ȸ�� ��й�ȣ
// Return Value : void
// Author: �����
// // Revsions : ������

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

// ȸ��Ż�� �ٿ���� Ŭ���� ������
DeleteAccountUI::DeleteAccountUI(DeleteAccount* deleteAccount)
{
    this->deleteAccount = deleteAccount;
}


/// ȸ��Ż�� ��Ʈ�� Ŭ���� ������
DeleteAccount::DeleteAccount(AccountDB* accountDB, Account* loginPointer)
{
    DeleteAccountUI* deleteAccountUi = new DeleteAccountUI(this);
    this->deleteAccountUi = deleteAccountUi;
    this->accountDB = accountDB;
    this->loginPointer = loginPointer; //�α����� ������ ����Ű�� ������
    this->deleteAccountUi->enterDeleteInfo(loginPointer);
}


// Function : void DeleteAccountUI::enterDeleteInfo(Account* loginPointer)
// Description : ȸ��Ż�� ������ ������ ID�� �Է¹޴� �Լ�
// Parameter : Account* loginPointer - �α����� ȸ���� ����Ű�� ������
// Return Value : void
// Author: �����

void DeleteAccountUI::enterDeleteInfo(Account* loginPointer)
{
    this->deleteAccount->deleteThisAccount(loginPointer);
}


//Function: void DeleteAccount::deleteThisAccount(Account* loginPointer)
//Description: �α����ߴ� ȸ���� ������� AccountDB�� ���� �ش� ȸ���� ������ �����ϴ� �Լ�
//Parameter : Account* loginPointer - �α����� ȸ���� ����Ű�� ������
//Return Value : void
//Author: �����

void DeleteAccount::deleteThisAccount(Account* loginPointer)
{
    this->accountDB->deleteAccount(loginPointer->getID());
    this->deleteAccountUi->printResult(loginPointer->getID());
}

// Function : void DeleteAccountUI::printResult(string id)
// Description : ȸ��Ż�� �ٿ�������� ���� ���� �� ����� �ش� ������ ������ ����ϴ� �Լ�
// Parameter : string ID - ȸ�� ���̵�
// Return Value : void
// Author: �����

void DeleteAccountUI::printResult(string id) {
    fout << "> " << id << endl;
}

// �α��� �ٿ���� Ŭ���� ������
LoginUI::LoginUI(Login* login) {
    this->login = login;
}

// Function : void LoginUI::enterLoginInfo()
// Description : �α��� �ٿ������ �α��� �� ������ ID�� password ������ �Է¹޴� �Լ�
// Parameter : string id - ������ ȸ�� id
// Return Value : void
// Author: �����
// // Revsions : ������

void LoginUI::enterLoginInfo() {
    string id;
    string password;
    fin >> id;
    fin >> password; 
    this->login->requestLogin(id, password);
}

// Function : void LoginUI::printResult(string id, string password)
// Description : �α��� �ٿ�������� �α��� �� �ش� ������ ������ ����ϴ� �Լ�
// Parameter : string id - ȸ�� ���̵�, string password - ȸ�� ���̵� ��й�ȣ)
// Return Value : void
// Author: �����

void LoginUI::printResult(string id, string password)
{
    fout << "> " << id << " " << password << endl;
}


// �α��� ��Ʈ�� Ŭ���� ������
Login::Login(AccountDB* accountDB)
{
    LoginUI* loginUi = new LoginUI(this);
    this->loginUi = loginUi;
    this->accountDB = accountDB;
    this->loginPointer = 0;
    this->loginUi->enterLoginInfo();
}

// Function : void Login::requestLogin(string id, string password)
// Description : �α��� ��Ʈ�ѿ��� �α����� ��û�ϴ� �Լ�
// Parameter : string id - �α����� id, string password - �α����� id�� ��й�ȣ
// Return Value : void
// Author: �����
// // Revsions : ������

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

// �α׾ƿ� �ٿ���� Ŭ���� ������
LogOutUI::LogOutUI(LogOut* logOut) {
    this->logOut = logOut;
}

// Function : void LogOutUI::enterLogOutInfo()
// Description : �α׾ƿ� �ٿ������ �α׾ƿ� ������ ��û�ϴ� �Լ� 
// Return Value : void
// Author: �����
// // Revsions : ������ 

void LogOutUI::enterLogOutInfo() 
{ 
    this->logOut->requestLogOut();
}

// Function : void LogOutUI::printResult(Account* account)
// Description : �α׾ƿ� �ٿ�������� �α׾ƿ� �� ����� �ش� ������ ������ ����ϴ� �Լ�
// Parameter :
// Return Value : void
// Author: �����

void LogOutUI::printResult() {
    //fout << "> " << logOutPointer->getID() << endl;
    
}

// �α׾ƿ� ��Ʈ�� Ŭ���� ������
LogOut::LogOut(AccountDB* accountDB, Account* loginPointer)
{
    LogOutUI* logOutUi = new LogOutUI(this);
    this->logOutUi = logOutUi;
    this->accountDB = accountDB;
    this->logOutPointer = loginPointer; //�α����� ������ ����Ű�� ������
    this->logOutUi->enterLogOutInfo();
}

// Function : void LogOut::requestLogOut()
// Description : �α׾ƿ� ��Ʈ�ѿ��� accountDB�� �ش� ������ �α׾ƿ��� ��û�ϴ� �Լ� 
// Return Value : void
// Author: �����
// // Revsions : ������ 

void LogOut::requestLogOut()
{
    //AccountDB* accounts;
    /*if (this->accountDB->getAccountIndex(id)->getLogStatus())
    {
        this->accountDB->logOut(id);
        fout << "2.2. �α׾ƿ�" << endl << "> " << id << endl;
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
        fout << product->getPrice() * product->getOriginalStockNum();  //��ǰ�ܰ��� ���е� �� ��� ���Ͽ� ���Ǹž��� ���Ѵ�.
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
        fout << average; //��ձ��Ÿ�����
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
        fout << average; //��ձ��Ÿ�����
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
    fout << seller->listProduct_OnSale().back()->getProductCompanyName();  //��ǰ�ܰ��� ���е� �� ��� ���Ͽ� ���Ǹž��� ���Ѵ�.
    fout << " ";
    fout << seller->listProductOnSale().back()->getPorfit(); //��ձ��Ÿ�����
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
    originalStockNum = stockNum; //�ʱ���� 
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
        fout << list[i]->getPrice() * list[i]->getOriginalStockNum();  //��ǰ�ܰ��� ���е� �� ��� ���Ͽ� ���Ǹž��� ���Ѵ�.
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
        fout << average; //��ձ��Ÿ�����
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
    sort(productNames.begin(), productNames.end()); // ����
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
        fout << list[i]->getSatisfacation(); //��ձ��Ÿ�����
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
    fout << productCompanyName;  //��ǰ�ܰ��� ���е� �� ��� ���Ͽ� ���Ǹž��� ���Ѵ�.
    fout << " ";
    fout << price; //��ձ��Ÿ�����
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
    this->product.addProduct(newProduct);  //product collection class��
}
void ProductCollection::addProduct(Product* product) {
    this->product.push_back(product);
}

Product::Product(string productName, string productCompanyName, int price, int stockNum) {
    this->productName = productName;
    this->productCompanyName = productCompanyName;
    this->price = price;
    this->stockNum = stockNum;
    originalStockNum = stockNum; //�ʱ���� 
}
vector<Product*> ProductCollection::getProductlist()
{
    return product;
}

//��ǰ �˻� �ٿ���� Ŭ���� ������
SearchProductUI::SearchProductUI(SearchProduct* searchProduct) {
    this->searchProduct = searchProduct;
}

//Function: void SearchProductUI::enterProductName()
//Description: �Է� ���Ͽ��� ��ǰ���� �о���̰� �� ��ǰ���� ��ǰ �˻� ��Ʈ�� ��ü�� ��ǰ �˻��� �����ϴ� �Լ��� ���ڷ� �ְ� ȣ���Ѵ�.
//Author: ������
void SearchProductUI::enterProductName() {
    string productName;
    fin >> productName;
    this->searchProduct->showSearchProductInfo(productName);
}

//Function: void SearchProductUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, float averageSatisfaction)
//Description: ��ǰ �˻� ����� ��� ���Ͽ� ����.
//Parameter : string sellerID - �Ǹ���ID, string producName - ��ǰ��, string productComapanyName - ��ǰȸ���, 
//int price - ��ǰ ����, int stockNum - ��ǰ ���, int averageSatisfaction - ��� ���Ÿ�����
//Author: ������
void SearchProductUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction) {
    
    fout << "> " << sellerID << " " << productName << " " << productCompanyName << " " << price << " " << stockNum << " " << averageSatisfaction << endl;
}

//��ǰ �˻� ��Ʈ�� Ŭ���� ������
SearchProduct::SearchProduct(vector<Seller*> sellerList) {
    SearchProductUI* searchProductUI = new SearchProductUI(this);
    this->searchProductUI = searchProductUI;
    this->searchProduct = 0;
    this->searchProductSeller = 0;
    this->listSeller = sellerList;
    this->searchProductUI->enterProductName();
}

//Function: void SearchProduct::showSearchProductInfo(string name)
//Description: ��ǰ �˻��� �����ϰ� �� ����� ���ڷ� �����Ͽ� ��ǰ �˻� �ٿ������ printResult �Լ��� ȣ���Ѵ�.
//Parameter : string productName - ��ǰ��
//Author: ������
void SearchProduct::showSearchProductInfo(string productName) {
    bool find = false;
    unsigned int i = 0;
    vector<Product*> saleProducts;
    Product* product = 0;
    while (i < listSeller.size()) {
        saleProducts = listSeller[i]->listProduct_OnSale(); // �Ǹ����� ����Ʈ ������
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
//Description: �˻��� ��ǰ�� �Ǹ��ڸ� ����Ű�� �����͸� ��ȯ�Ѵ�.
//Return Value : Seller*
//Author: ������
Seller* SearchProduct::getSearchProductSeller() {
    return this->searchProductSeller;
}

//Function: Product* SearchProduct::getSearchProduct()
//Description: �˻��� ��ǰ�� ����Ű�� �����͸� ��ȯ�Ѵ�.
//Return Value : Product*
//Author: ������
Product* SearchProduct::getSearchProduct() {
    return this->searchProduct;
}

//��ǰ ���� �ٿ���� Ŭ���� ������
BuyProductUI::BuyProductUI(BuyProduct* buyProduct) {
    this->buyProduct = buyProduct;
}

//Function: void BuyProductUI::printResult(string sellerID, string productName)
//Description: ��ǰ ���� ����� ����Ѵ�.
//Parameter : string sellerID - ������ ��ǰ�� �Ǹ��� ID, string productName - ������ ��ǰ��
//Author: ������
void BuyProductUI::printResult(string sellerID, string productName) {
    fout << "> " << sellerID << " " << productName << endl;
}

//��ǰ ���� ��Ʈ�� Ŭ���� ������
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

//���� ���� ��ȸ �ٿ���� Ŭ���� ������
SeeBoughtListUI::SeeBoughtListUI(SeeBoughtList* seeBoughtList) {
    this->seeBoughtList = seeBoughtList;
}

//Function: void SeeBoughtListUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction)
//Description: ���� ���� ��ȸ ����� ����Ѵ�.
//Parameter : string sellerID - �Ǹ���ID, string producName - ��ǰ��, string productComapanyName - ��ǰȸ���, 
//int price - ��ǰ ����, int stockNum - ��ǰ ���, int averageSatisfaction - ��� ���Ÿ�����
//Author: ������
void SeeBoughtListUI::printResult(string sellerID, string productName, string productCompanyName, int price, int stockNum, int averageSatisfaction) {
    fout << "> " << sellerID << " " << productName << " " << productCompanyName << " " << price << " " << stockNum << " " << averageSatisfaction << endl;
}

//���� ���� ��ȸ ��Ʈ�� Ŭ���� ������
SeeBoughtList::SeeBoughtList(Buyer* buyer, vector<Seller*> sellerList) {
    SeeBoughtListUI *seeBoughtListUI = new SeeBoughtListUI(this);
    this->seeBoughtListUI = seeBoughtListUI;
    this->buyer = buyer;
    this->listSeller = sellerList;
    this->showBoughtListInfo();
}

//Function: void SeeBoughtList::showBoughtListInfo()
//Description: ���� ������ ��ǰ���� �������� ������������ �����ϰ� ��ȸ�� ������ �ٿ���� printResult �Լ��� ���ڷ� �־� ȣ���Ѵ�.
//Author: ������
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
                products = listSeller[j]->listProduct_OnSold(); // �Ǹ� �Ϸ�� ��Ͽ��� ã��
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
        this->sellerID.push_back(listSeller[j]->getSellerID()); // ���ĵ� ���� ������ ��ǰ�� �Ǹ��� id ����
        product = this->buyer->listBoughtProducts().findProduct(sortedBoughtProductNames[i]); // ���ĵ� ��ǰ�� �������� ���� �������� �ش� ��ǰ ã��
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
//Description: ���� ������ �Ǹ��� ID ����Ʈ�� ��ȯ�Ѵ�.
//Return Value : vector<string>
//Author: ������
vector<string> SeeBoughtList::getSellerIDList() {
    return this->sellerID;
}

//���Ÿ����� �� �ٿ���� Ŭ���� ������
EvaluateBuySatisfactionUI::EvaluateBuySatisfactionUI(EvaluateBuySatisfaction* evaluateBuySatisfaction) {
    this->evaluateBuySatisfaction = evaluateBuySatisfaction;
}

//Function: void EvaluateBuySatisfactionUI::enterProductNameAndBuySatisfaction()
//Description: �Է� ���Ͽ��� ��ǰ��� ���� ������ ���� �о���̰� ��Ʈ�� addSatisfaction�Լ��� ���ڷ� �־� ȣ���Ѵ�.
//Author: ������
void EvaluateBuySatisfactionUI::enterProductNameAndBuySatisfaction() {
    string productName;
    int satisfaction;
    fin >> productName;
    fin >> satisfaction;
    this->evaluateBuySatisfaction->addSatisfaction(productName, satisfaction);
}

//Function: void EvaluateBuySatisfactionUI::printResult(string sellerID, string productName, int satisfaction)
//Description: ���� ������ �� ����� ������Ͽ� ����.
//Parameter : string sellerID - �Ǹ��� ID, string productName - ��ǰ��, int satisfaction - ���� ���� ������
//Author: ������
void EvaluateBuySatisfactionUI::printResult(string sellerID, string productName, int satisfaction) {
    fout << "> " << sellerID << " " << productName << " " << satisfaction << endl;
}

//���Ÿ����� �� ��Ʈ�� Ŭ���� ������
EvaluateBuySatisfaction::EvaluateBuySatisfaction(Buyer* buyer, vector<string> boughtListSellerID, vector<string> sortedBoughtListNames) {
    EvaluateBuySatisfactionUI *evaluateBuySatisfactionUI = new EvaluateBuySatisfactionUI(this);
    this->evaluateBuySatisfactionUI = evaluateBuySatisfactionUI;
    this->buyer = buyer;
    this->boughtListSellerID = boughtListSellerID;
    this->sortedBoughtListNames = sortedBoughtListNames;
    this->evaluateBuySatisfactionUI->enterProductNameAndBuySatisfaction();
}

//Function: void EvaluateBuySatisfaction::addSatisfaction(string productName, int satisfaction)
//Description: ���� ���� �������� �ش� ��ǰ�� �߰��Ѵ�.
//Parameter : string productName - ��ǰ��, int satisfaction - ���� ���� ������
//Author: ������
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
//Description: �Ǹ��� ID�� ��ȯ�Ѵ�.
//Return Value : string
//Author: ������
string Seller::getSellerID() {
    return this->getID();
}

//Function : ProductCollection Buyer::listBoughtProducts()
//Description: ���ų����� ��ȯ�Ѵ�.
//Return Value : ProductCollection
//Author: ������
ProductCollection Buyer::listBoughtProducts() {
    return this->boughtProductCollection;
}

//Function : void Buyer::addProductToBoughtList(Product* product)
//Description: ������ ��ǰ�� ���� ������ �߰��Ѵ�.
//Author: ������
void Buyer::addProductToBoughtList(Product* product) {
    this->boughtProductCollection.addProduct(product);
}

//Function : int Product::getPrice()
//Description: ��ǰ ������ ��ȯ�Ѵ�.
//Return Value : int
//Author: ������
int Product::getPrice() {
    return this->price;
}

//Function : vector<int> Product::getSatisfaction()
//Description: ���� ������ ����Ʈ�� ��ȯ�Ѵ�.
//Return Value : vector<int>
//Author: ������
vector<int> Product::getSatisfaction() {
    return this->buySatisfaction;
}

//Function : void Product::addBuySatisfaction(int satisfaction)
//Description: �򰡹��� ���� ������ ���� ���� ���� ������ ����Ʈ�� �߰��Ѵ�. 
//Parameter : int satisfaction - ������
//Author: ������
void Product::addBuySatisfaction(int satisfaction) {
    this->buySatisfaction.push_back(satisfaction);
}

//Function : void Product::decreaseStockNum()
//Description: ��ǰ ��� 1 ���ҽ�Ų��. 
//Author: ������
void Product::decreaseStockNum() {
    this->stockNum--;
}

//Function : Product* ProductCollection::getProduct(unsigned int order)
//Description: ��ǰ ����Ʈ���� ���ڷ� ���� �ش� ������ ��ǰ�� ����Ű�� �����͸� ��ȯ�Ѵ�. �ش� �������� ��ȯ�� �� ������ 0(null)�� ��ȯ�Ѵ�.
//Parameter : unsigned int order - index ����
//Return Value : Product*
//Author: ������
Product* ProductCollection::getProduct(unsigned int order) {
    if (order < this->product.size()) {
        return this->product[order];
    }
    else return 0;
}

//��ǰ ����Ʈ�� ��ǰ �߰�
/*void ProductCollection::addProduct(Product* product) {
    this->product.push_back(product);
}*/

//Function : Product* ProductCollection::findProduct(string name)
//Description: ��ǰ ����Ʈ���� ���ڷ� ���� ��ǰ��� ��ġ�ϴ� �̸��� ���� ��ǰ�� ã�´�. ã���� �ش� ��ǰ�� ����Ű�� �����͸� ��ȯ�ϰ� ������ 0(null)�� ��ȯ�Ѵ�.
//Parameter : string name - ��ǰ��
//Return Value : Product*
//Author: ������
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


