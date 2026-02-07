#include<iostream>
#include<string>
#define MIN_BALANCE 500
#include<map>
#include<vector>
#include<fstream>
using namespace std;
class InSufficientFunds{};
class Account
{
	private:
		     string firstName;
		     string lastName;
		     string address;
		     int age;
		     string email;
		     long accountNumber;
		     float balance;
		     static long NextAccNo;//For Automatically Assigning The Account Numbers we have taken this static
	public:
		     Account(){};//Non-parameterised constructor
		     Account(string firstName, string lastName, string address, int age, string email, float balance);//Parameterised constructor
		     string getFirstName()
		     {
		     	return firstName;
			 }
			 string getLastName()
			 {
			 	return lastName;
			 }
			 string getAddress()
			 {
			 	return address;
			 }
			 int getAge()
			 {
			 	return age;
			 }
			 string getEmail()
			 {
			 	return email;
			 }
			 long getAccountNumber()
			 {
			 	return accountNumber;
			 }		     
			 float getBalance()
			 {
			 	return balance;
			 }
			 
			 //Functions for the class Account
			 void deposit(float amount);
			 void withdraw(float amount);
			 static long getLastAccountNumber();
			 static void setLastAccountNumber(long accountNumber);
			 friend ofstream & operator<<(ofstream &ofs, Account &acc);
			 friend ifstream & operator>>(ifstream &ifs, Account &acc);
			 friend ostream & operator<<(ostream &os,Account &acc);
};
long Account::NextAccNo=0;
class Bank
{
	map<long,Account> accounts;
	public:
		   Bank();
		   Account OpenAccount(string firstName, string lastName,string address, int age, string email,float balance);
		   Account BalanceEnquiry(long accountNumber);
		   Account deposit(long accountNumber, float amount);
		   Account withdraw(long accountNumber, float amount);
		   void CloseAccount(long accountNumber);
		   void showAllAccounts();
		   ~Bank();
};
int main()
{
	Bank b;
	Account acc;
	int choice;
	string firstName,lastName;
	long accountNumber;
	float balance;
	float amount;
	string email;
	int age;
	string address;
	cout<<"***********Banking System***************";
	do
	{
		cout<<"\n\tSelect one option below";
		cout<<"\n\t1.Open an Account:";
		cout<<"\n\t2.Balance Enquiry:";
		cout<<"\n\t3.Deposit:";
		cout<<"\n\t4.Withdrawal:";
		cout<<"\n\t5.Close An Account:";
		cout<<"\n\t6.Show All Accounts:";
		cout<<"\n\t7.Quit:";
		cout<<"\nEnter Your Choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				   cout<<"\nEnter Your First Name:";
				   cin>>firstName;
				   cout<<"\nEnter Your Last Name:";
				   cin>>lastName;
				   cout<<"\nEnter Your Address:";
				   cin.ignore();
				   getline(cin,address);
				   cout<<"\nEnter Your Age:";
				   cin>>age;
				   cout<<"\nEnter Your Email:";
				   cin>>email;
				   cout<<"\nEnter Balance:";
				   cin>>balance;
				   acc=b.OpenAccount(firstName, lastName, address, age, email, balance);
				   cout<<"Congratulations!!!! Your Account is Created"<<endl;
				   cout<<acc;
				   break;
			case 2:
				   cout<<"Enter Account Number:";
				   cin>>accountNumber;
				   acc=b.BalanceEnquiry(accountNumber);
				   cout<<endl<<"Account Details:"<<endl;
				   cout<<acc;
				   break;
			case 3:
			       cout<<"Enter Account Number:";
				   cin>>accountNumber;
				   cout<<"Enter Amount:";
				   cin>>amount;
				   acc=b.deposit(accountNumber,amount);
				   cout<<endl<<"Amount is Deposited:"<<amount<<endl;
				   cout<<acc;
				   break;
		    case 4:
		    	  cout<<"Enter Account Number:";
		    	  cin>>accountNumber;
		    	  cout<<"Enter Amount U Want to Withdraw:";
		    	  cin>>amount;
		    	  acc=b.withdraw(accountNumber,amount);
		    	  cout<<endl<<"Withdrawal Amount:"<<amount<<endl;
		    	  cout<<acc;
		    	  break;
			case 5:
			      cout<<"Enter Account Number:";
				  cin>>accountNumber;
				  b.CloseAccount(accountNumber);
				  cout<<endl<<"Your Account is Closed........."<<endl;
				  break;
			case 6:
			      b.showAllAccounts();
				  break;
			case 7:
			       break;
			default:
			       cout<<"----Enter Correct Choice----";  			
		}
	}
	while(choice!=7);
	return 0;
}
Account::Account(string firstName,string lastName,string address,int age, string email, float balance)
{
	NextAccNo++;
	accountNumber=NextAccNo;
	this->firstName=firstName;
	this->lastName=lastName;
	this->address=address;
	this->age=age;
	this->email=email;
	this->balance=balance;
}
void Account::deposit(float amount)
{
	balance=balance+amount;
}
void Account::withdraw(float amount)
{
	if(balance-amount<MIN_BALANCE)
	{
		throw InSufficientFunds();
	}
	else
	{
		balance-=amount;
	}
}
void Account::setLastAccountNumber(long accountNumber)
{
	NextAccNo=accountNumber;
}
long Account::getLastAccountNumber()
{
	return NextAccNo;
}
ofstream & operator<<(ofstream &ofs, Account &acc)
{
	ofs<<acc.accountNumber<<endl;
	ofs<<acc.firstName<<endl;
	ofs<<acc.lastName<<endl;
	ofs<<acc.balance<<endl;
	ofs<<acc.email<<endl;
	ofs<<acc.age<<endl;
	ofs<<acc.address<<endl;
	return ofs;
}
ifstream & operator>>(ifstream &ifs, Account &acc)
{
	ifs>>acc.accountNumber;
	ifs>>acc.firstName;
	ifs>>acc.lastName;
	ifs>>acc.balance;
	ifs>>acc.email;
	ifs>>acc.age;
	ifs>>acc.address;
	return ifs;
}
ostream & operator<<(ostream &os,Account &acc)
{
	os<<"First Name:"<<acc.getFirstName()<<endl;
	os<<"Last Name:"<<acc.getLastName()<<endl;
	os<<"Balance:"<<acc.getBalance()<<endl;
	os<<"Account Number:"<<acc.getAccountNumber()<<endl;
	os<<"Email:"<<acc.getEmail()<<endl;;
	os<<"Age:"<<acc.getAge()<<endl;
	os<<"Address:"<<acc.getAddress()<<endl;
	return os;
}
Bank::Bank()
{
	Account account;
	ifstream infile;
	infile.open("Bank.data");
	if(!infile)
	{
		//cout<<"Error in opening a file";
		return ;
	}
	while(!infile.eof())
	{
		infile>>account;
		accounts.insert(pair<long,Account>(account.getAccountNumber(),account));
	}
	Account::setLastAccountNumber(account.getAccountNumber());
	infile.close();
}
Account Bank::OpenAccount(string firstName,string lastName,string address, int age, string email,float balance)
{
	ofstream outfile;
	Account account(firstName,lastName,address,age,email,balance);
	accounts.insert(pair<long,Account>(account.getAccountNumber(),account));
	outfile.open("Bank.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		outfile<<itr->second;
	}
	outfile.close();
	return account;
}
Account Bank::BalanceEnquiry(long accountNumber)
{
	map<long,Account>::iterator itr=accounts.find(accountNumber);
	return itr->second;
}
Account Bank::deposit(long accountNumber,float amount)
{
	map<long,Account>::iterator itr=accounts.find(accountNumber);
	itr->second.deposit(amount);
	return itr->second;
}
Account Bank::withdraw(long accountNumber,float amount)
{
	map<long,Account>::iterator itr=accounts.find(accountNumber);
	itr->second.withdraw(amount);
	return itr->second;
}
void Bank::CloseAccount(long accountNumber)
{
	map<long,Account>::iterator itr=accounts.find(accountNumber);
	cout<<"Account Deleted"<<itr->second;
	accounts.erase(accountNumber);
}
void Bank::showAllAccounts()
{
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
        cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
    }
}
Bank::~Bank()
{
	ofstream outfile;
	outfile.open("Bank.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		outfile<<itr->second;
	}
	outfile.close();
}	
