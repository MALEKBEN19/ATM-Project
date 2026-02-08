#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<ctime>
#pragma warning(disable : 4996)
using namespace std;
void Login();




string ClientList = "Clients.txt";

struct stClients {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkClient = false;
};
struct stDate {
	short Year;
	short Month;
	short Day;
};

stDate GetLocalDate() {
	stDate Mydate;
	time_t t = time(0);
	tm* Mytm = localtime(&t);
	Mydate.Year = Mytm->tm_year + 1900;
	Mydate.Month = Mytm->tm_mon + 1;
	Mydate.Day = Mytm->tm_mday ;
	return Mydate;
}





stClients CurrentClient;

enum enAtmMenuOption{eQuickwithdarw=1,eNormalWithdraw,eDeposit,eSeeBalance,eExtit};
enum enQuickWithDrawAmount{One=20,Two=50,Three=100,Four=200,Five=400,Six=600,Seven=1000,Back=0};

//Tools : 
vector<string>SplitString(string Text ,string Delim) {
	vector<string>vWord;
	string word;
	short Space = 0;
	while ((Space = Text.find(Delim)) != std::string::npos) {
		word = Text.substr(0, Space);
		if (word != "") {
			vWord.push_back(word);
		}
		Text.erase(0, Space + Delim.length());
	}
	if (Text != "") {
		vWord.push_back(Text);
	}
	return vWord;
}
stClients ConvertLineToRecord(string line,string sperator="#//#") {
	vector <string>vWord=SplitString(line,sperator);
	stClients client;
	client.AccountNumber = vWord.at(0);
	client.PinCode = vWord.at(1);
	client.Name = vWord.at(2);
	client.Phone = vWord.at(3);
	client.AccountBalance = stod(vWord.at(4));
	return client;
}
vector<stClients> LoadClientDataFromFile(string File) {
	vector<stClients>vClients;
	fstream MyFile;
	MyFile.open(File, ios::in);
	if (MyFile.is_open()) {
		string Line;
		stClients client;
		while (getline(MyFile, Line)) {
			client = ConvertLineToRecord(Line);
			vClients.push_back(client);
		}
		MyFile.close();
	}
	return vClients;
}
bool FindClientByAccountNumberAndPinCode(string AccountNumber,string PinCode,stClients & client) {
	vector<stClients>vClient = LoadClientDataFromFile(ClientList);
	for (stClients& clt : vClient) {
		if (clt.AccountNumber == AccountNumber && clt.PinCode == PinCode) {
			client = clt;
			return true;
		}
	}
	return false;
}
bool IsClientExist(string Account, string PinCode) {

	if (FindClientByAccountNumberAndPinCode(Account, PinCode,CurrentClient)) {
		return true;
	}
	else {
		return false;
	}
}

//QuickwithDraw :



















short ReadMenuOptions()
{
	short Read;
	cout << "Please Choose What You Want To Do [ 1 to 5 ]  ";
	cin >> Read;
	return Read;
}

void PerformMainMenuOption(enAtmMenuOption ReadOption) {
	switch (ReadOption) {
	case enAtmMenuOption::eQuickwithdarw:

		break;
	case enAtmMenuOption::eNormalWithdraw:

		break;
	case enAtmMenuOption::eDeposit:

		break;
	case enAtmMenuOption::eSeeBalance:

		break;

	case enAtmMenuOption::eExtit:
		Login();
	}
}

void AtmMainMenuScreen() {
	system("cls");
	cout << "========================================================\n";
	cout << "Date : " << GetLocalDate().Day << "/" << GetLocalDate().Month << "/" << GetLocalDate().Year << "." <<" / Account N : "<<CurrentClient.AccountNumber << endl;
	cout << "========================================================\n\n";
	cout << "\t\tATM Main menu Screen\n\n";
	cout << "========================================================\n\n";
	cout << setw(15) << "[1] " << "Quick Withdraw." << endl;
	cout << setw(15) << "[2] " << "Noraml Withdraw." << endl;
	cout << setw(15) << "[3] " << "Deposit." << endl;
	cout << setw(15) << "[4] " << "Check Balance." << endl;
	cout << setw(15) << "[5] " << "Logout." << endl;
	cout << "\n========================================================\n";
	PerformMainMenuOption((enAtmMenuOption)ReadMenuOptions());
}






void Login() {
	bool LoginFailed = false;
	string AccountNum = "";
	string PinCode = "";

	do {
		system("cls");
		
		cout << "---------------------------------------\n";
		cout << "Date : " << GetLocalDate().Day << "/" << GetLocalDate().Month << "/" << GetLocalDate().Year << "." << endl;
		cout << "---------------------------------------\n";
		cout << "\n\t    Login Screen\n\n";
		cout << "---------------------------------------\n";
		if (LoginFailed) {
			cout << "\nInvalid Account/PinCode\n";
		}
		cout << "\nEnter Account Number : ";
		cin >> AccountNum;
		cout << "Enter Pin Code : ";
		cin >> PinCode;
		LoginFailed = !IsClientExist(AccountNum,PinCode);
	} while (LoginFailed);
	AtmMainMenuScreen();
}




int main()
{

	Login();

	system("pause>0");
	return 0;
}

