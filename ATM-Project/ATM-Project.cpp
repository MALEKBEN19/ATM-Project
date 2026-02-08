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
void AtmMainMenuScreen();
void QuickwithDrawMenu();



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
enum enQuickWithDrawAmount{One=1,Two=2,Three=3,Four=4,Five=5,Six=6,Seven=7,Eight=8,Back=9};

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
short ReadMenuOptions(string message)
{
	short Read;
	cout << message;
	cin >> Read;
	return Read;
}
void GoBackToQuickWithDrawMenu() {
	cout << "Press any key to continue...";
	system("pause>0");
	QuickwithDrawMenu();
}
void GoBackToAtmMainMenu() {
	cout << "Press Any Key To Go Back to ATM Menu...";
	system("pause>0");
	AtmMainMenuScreen();
}
string ConvertRecordToLine(stClients &client,string Sperator="#//#") {
	string line="";
	line += client.AccountNumber + Sperator;
	line += client.PinCode + Sperator;
	line += client.Name + Sperator;
	line += client.Phone + Sperator;
	line += to_string(client.AccountBalance);
	return line;
}
void SaveDataInFileAgain(stClients &client,string File) {
	fstream Myfile;
	Myfile.open(File, ios::out | ios::app);
	if (Myfile.is_open()) {
		string Line;
		Line = ConvertRecordToLine(client);
		Myfile << Line << endl;
		Myfile.close();
	}
}

//QuickwithDraw :


void QuickWithDrawFromAccount(int Amount,stClients &Client) {
	char Confirm = 'y';
	if (Client.AccountBalance > Amount) {
		cout << "Are you sure you want to perform this Transaction? Y/N ";
		cin >> Confirm;
		if (toupper(Confirm) == 'Y') {
			Client.AccountBalance -= Amount;
			cout << "\nDone Successfully , New Balance is " << to_string(Client.AccountBalance) << endl;
			SaveDataInFileAgain(Client, ClientList);
		}
		else {
			GoBackToAtmMainMenu();
		}
	}
	else {
		cout << "The Amount Exceeds Your Balance Make another choice.\n";
		GoBackToQuickWithDrawMenu();
	}
}


void PerformQuickWithDrawMenuOption(enQuickWithDrawAmount Amount) {
	switch (Amount) {
	case enQuickWithDrawAmount::One:
		QuickWithDrawFromAccount(20,CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Two:
		QuickWithDrawFromAccount(50, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Three:
		QuickWithDrawFromAccount(100, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Four:
		QuickWithDrawFromAccount(200, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Five:
		QuickWithDrawFromAccount(400, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Six:
		QuickWithDrawFromAccount(600, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Seven:
		QuickWithDrawFromAccount(800, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Eight:
		QuickWithDrawFromAccount(1000, CurrentClient);
		GoBackToAtmMainMenu();
		break;
	case enQuickWithDrawAmount::Back:
		AtmMainMenuScreen();
		break;
	}
}


void QuickwithDrawMenu() {
	system("cls");
	cout << "========================================================\n\n";
	cout << "\t   Quick WithDraw menu Screen\n\n";
	cout << "========================================================\n\n";
	cout << setw(15)<< "[1] " << "$20" <<	setw(11)<<"[2] " <<"$50"<<endl;
	cout << setw(15)<< "[3] " << "$100"<<	setw(10)<<"[4] " <<"$200"<<endl;
	cout << setw(15)<< "[5] " << "$400"<<	setw(10)<<"[6] " <<"$600"<<endl;
	cout << setw(15)<< "[7] " << "$800"<<	setw(10)<<"[8] " <<"$1000"<<endl;
	cout << setw(15)<< "[9] " << "Exit\n";
	cout << "\n========================================================\n";
	cout << "Your Balance is : " << to_string(CurrentClient.AccountBalance) << endl;
	PerformQuickWithDrawMenuOption((enQuickWithDrawAmount)ReadMenuOptions("Choose What to Withdraw From [1] to [8] "));
}



















void PerformMainMenuOption(enAtmMenuOption ReadOption) {
	switch (ReadOption) {
	case enAtmMenuOption::eQuickwithdarw:
		QuickwithDrawMenu();
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
	cout << "Date : " << GetLocalDate().Day << "/" << GetLocalDate().Month 
		<< "/" << GetLocalDate().Year << "." <<" / Account N : "<<CurrentClient.AccountNumber << endl;
	cout << "========================================================\n\n";
	cout << "\t\tATM Main menu Screen\n\n";
	cout << "========================================================\n\n";
	cout << setw(15) << "[1] " << "Quick Withdraw." << endl;
	cout << setw(15) << "[2] " << "Noraml Withdraw." << endl;
	cout << setw(15) << "[3] " << "Deposit." << endl;
	cout << setw(15) << "[4] " << "Check Balance." << endl;
	cout << setw(15) << "[5] " << "Logout." << endl;
	cout << "\n========================================================\n";
	PerformMainMenuOption((enAtmMenuOption)ReadMenuOptions("Please Chosse what You want to do [1 to 5]"));
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

