#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Transaction {
    string date;
    string accountNumber;
    string amount;
    string transactionType;
};

struct User {
    string name;
    string accountNumber;
    string contactInfo;
    string number;
};
int ConvertStringToInt(const string& inputString) {
    int result = 0;

    size_t i = 0;

    for (i; i < inputString.size(); i++) {
        char currentChar = inputString[i];
        if (currentChar == '/') break ;
        if (currentChar >= '0' && currentChar <= '9') {
        	int digit = currentChar - '0';
            result = result * 10 + digit;
            
        } else {
            return 0;
        }
    }

    return result;
}
void readTransactionsFromFile(Transaction transactions[], int size) {
    ifstream file("transaction.csv");
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            getline(file, transactions[i].date, ',');
            getline(file, transactions[i].accountNumber, ',');
            getline(file, transactions[i].amount, ',');
            getline(file, transactions[i].transactionType, '\n');
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << "\n";
    }
}

void readUsersFromFile( User users[], int size) {
    ifstream file("users.csv");
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            getline(file, users[i].name, ',');
            getline(file, users[i].accountNumber, ',');
            getline(file, users[i].contactInfo, ',');
            getline(file, users[i].number, '\n');
        }
        file.close();
    } else {
        cout << "Unable to open file: " << "\n";
    }
}

void displayUserTransactions(const Transaction transactions[], int numTransactions, const string& accountNumber) {
    cout << "Transactions for account number: " << accountNumber << "\n";
    bool found = false;
    for (int i = 0; i < numTransactions; i++) {
        if (transactions[i].accountNumber == accountNumber) {
            found = true;
            cout << "Transaction " << i + 1 << ":\n";
            cout << "Date: " << transactions[i].date << "\n";
            cout << "Account Number: " << transactions[i].accountNumber << "\n";
            cout << "Amount: " << transactions[i].amount << "\n";
            cout << "Transaction Type: " << transactions[i].transactionType << "\n\n";
        }
    }
    if (!found) {
        cout << "No transactions found for this account number.\n";
    }
}

void displayUsers(const User users[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "User " << i + 1 << ":\n";
        cout << "Name: " << users[i].name << "\n";
        cout << "Account Number: " << users[i].accountNumber << "\n";
        cout << "Contact Information: " << users[i].contactInfo << "\n";
        cout << "Number: " << users[i].number << "\n\n";
    }
}

void displayTransactionsByYear(Transaction transactions[], int numTransactions, const string& accountNumber, int year) {
    cout << "Transactions for year " << year << " for account number " << accountNumber << ":" << endl;


    for (int i = 0; i < numTransactions; i++) {

	int date2 = ConvertStringToInt(transactions[i].date);
	
        if (transactions[i].accountNumber == accountNumber &&  date2 == year) {
            cout << "Date: " << transactions[i].date << ", Amount: " << transactions[i].amount << ", Type: " << transactions[i].transactionType << endl;
        }
    }
}
void displayUnusualTransactions(const Transaction transactions[], int numTransactions, const string& accountNumber) {
    cout << "Unusual transactions for account number: " << accountNumber << "\n";
    
    int counter = 0 ;
    
    for (int i = 0; i < numTransactions; i++) {
    	
        if (transactions[i].accountNumber == accountNumber) {

            double amount = ConvertStringToInt(transactions[i].amount);
			
            if (amount > 1000) {
                cout << "Transaction " << i + 1 << ":\n";
                cout << "Date: " << transactions[i].date << "\n";
                cout << "Account Number: " << transactions[i].accountNumber << "\n";
                cout << "Amount: " << transactions[i].amount << "\n";
                cout << "Transaction Type: " << transactions[i].transactionType << "\n\n";
                counter ++ ;
            }

        }

    }
        if (counter == 0){
            cout << "There is no unusual transactions " << endl ;
		}
}
void saveSpecificTransactionsToFile(const Transaction transactions[], int numTransactions, const string& accountNumber, const string& transactionType) {
    ofstream file("111.txt");
    if (file.is_open()) {
        for (int i = 0; i < numTransactions; i++) {
            if (transactions[i].accountNumber == accountNumber && transactions[i].transactionType == transactionType) {
                file << "Date: " << transactions[i].date << ", ";
                file << "Account Number: " << transactions[i].accountNumber << ", ";
                file << "Amount: " << transactions[i].amount << ", ";
                file << "Transaction Type: " << transactions[i].transactionType << "\n";
            }
        }
        file.close();
    } else {
        cout << "Unable to open file" << "\n";
    }
}
void createNewAccount(User newUser) {
    ofstream file("users.csv", ios::app);
    if (file.is_open()) {
        file << newUser.name << ',' << newUser.accountNumber << ',' << newUser.contactInfo << ',' << newUser.number << '\n';
        file.close();
        cout << "New account created successfully!" << endl;
    } else {
        cout << "Unable to open file for writing" << endl;
    }
}
void addNewTransaction(Transaction transactions[], int numTransactions) {
    string newDate, newAccountNumber, newAmount, newTransactionType;

    cin.ignore(); 

    cout << "Enter date (YYYY/MM/DD): ";
    getline(cin, newDate);

    cout << "Enter account number: ";
    getline(cin, newAccountNumber);

    cout << "Enter amount: ";
    getline(cin, newAmount);

    cout << "Enter transaction type: ";
    getline(cin, newTransactionType);

    transactions[numTransactions].date = newDate;
    transactions[numTransactions].accountNumber = newAccountNumber;
    transactions[numTransactions].amount = newAmount;
    transactions[numTransactions].transactionType = newTransactionType;

    numTransactions++;

    ofstream outfile("transaction.csv", ios::app);
    if (outfile.is_open()) {
        outfile << newDate << ',' << newAccountNumber << ',' << newAmount << ',' << newTransactionType << '\n';
        outfile.close();
        cout << "Transaction added successfully!"<<"\n";
    } else {
        cout << "Unable to open file for writing"<<"\n";
    }
}

int main() {
	
    const int numTransactions = 683;
    const int numUsers = 39;
    Transaction transactions[numTransactions];
    User users[numUsers];

    readTransactionsFromFile( transactions, numTransactions);
    readUsersFromFile( users, numUsers);
    
	string option;
    cout << "Do you want to open a new account? (yes/no): ";
    cin >> option;

    if (option == "yes") {
        User newUser;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, newUser.name);
        cout << "Enter account number: ";
        cin >> newUser.accountNumber;
        cout << "Enter contact info: ";
        cin >> newUser.contactInfo;
        cout << "Enter phone number: ";
        cin >> newUser.number;
        
        createNewAccount(newUser);
	}
    string option2;
    cout << "Do you want to do a new transaction? (yes/no): ";
    cin >> option2;
    if (option2 == "yes"){
    	addNewTransaction(transactions, 684);  
    }
    	string userName; 
    
    	cout << "Enter user name for other options : ";
    	getline(cin, userName);  
	
    	string accountNumber;
    	bool userFound = false;
    	for (int i = 0; i < numUsers; i++) {
        	if (users[i].name == userName) {
            	accountNumber = users[i].accountNumber;
            	userFound = true;
            	cout << users[i].name << endl ;
           	    break;
        	}
    	}
		string transactionType ;
		int yearToDisplay;
		char press ;
    	if (userFound) {
        	displayUserTransactions(transactions, numTransactions, accountNumber);
        	cout << "if you want to see the Unusual Transactions for this account enter y and enter x for else : " ;
        	cin >> press ;
        
        	if (press == 'y')
        		displayUnusualTransactions(transactions, numTransactions, accountNumber) ;
        
    	    cout << "Enter the year for which you want to see the transactions: ";
    	    cin >> yearToDisplay;
	        displayTransactionsByYear(transactions, numTransactions, accountNumber, yearToDisplay);
        
       	    cout << "enter your transaction Type : ";
        	 cin >> transactionType ;
    	     saveSpecificTransactionsToFile(transactions, numTransactions, accountNumber, transactionType);
	    } else {
        	cout << "User not found";
    	}
    return 0 ;

}
//w3schools.com
//stackoverflow.com
//geeksforgeeks.com
