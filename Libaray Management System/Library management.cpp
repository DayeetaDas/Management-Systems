/*This is a school Library Management System*/
#include "pch.h"
#include<iostream>//necessary header files are included
#include<string.h>
#include<string>
#include<fstream>
using namespace std;
char press;
class Library	//class is declared with public and private members
{
	string acc_no;
	char name[20], book_name[20], status[20];

public:
	void menu();
	void input_press();
	void check_press();
	void add_account();
	void save_account();
	void account();
	void view_all_accounts();
	void search_account(string);
	void edit_account();
	void delete_account();
	string getacc_no(){ return acc_no; }
	char* getname() { return name; }
	char* getbook_name(){ return book_name; }
	char* getstatus(){ return status; }
};

fstream fp;
Library l;

void Library::menu() //menu is displayed
{
	cout << "Press 0 to exit" << endl;
	cout << "Press 1 to add new account." << endl;
	cout << "Press 2 to display all accounts" << endl;
	cout << "Press 3 to search for an account" << endl;
	cout << "Press 4 to edit an existing account" << endl;
	cout << "Press 5 to delete an existing account" << endl;
}

void Library::input_press() //press is taken as input
{
	cout << "Press a number:";
	cin >> press;
	check_press();
}

void Library::check_press()	//press is checked for validity
{
	while (1)
	{
		if (press == '0' || press == '1' || press == '2' || press == '3' || press == '4' || press == '5')
			break;
		else
			input_press();
	}
}

void Library::add_account()	//function for adding an account
{
	cout << "Enter the account number:";
	cin >> acc_no;
	cout << endl;
	cout << "Enter the name:";
	cin >> name;
	cin.ignore();
	cout << endl;
	cout << "Enter the book's name:";
	cin >> book_name;
	cin.ignore();
	cout << endl;
	cout << "Enter the status:";
	cin >> status;
	cin.ignore();
	cout << endl;
}

void Library::save_account()	//function for writinf account to file
{
	fp.open("details.txt", ios::out | ios::app);
	l.add_account();
	fp.write((char*)&l, sizeof(Library));
	fp.close();
	cout << endl << "Account has been created successfully!" << endl;
}

void Library::account()	//function for storing details of a single account
{
	cout << endl << "Account Number:" << acc_no;
	cout << endl << "Name:" <<name ;
	cout << endl << "Book Name:" <<book_name ;
	cout << endl << "Status:" <<status ;
}

void Library::view_all_accounts()	//function for displaying all accounts
{
	cout << "Here is the list of all the accounts with their details:" << endl;
	fp.open("details.txt", ios::in);
	while (fp.read((char*)&l, sizeof(Library)))
	{
		l.account();
		cout << endl;
	}
	fp.close();
}

void Library::search_account(string num)	//function for searching an account
{
	bool found;
	found = false;
	fp.open("details.txt", ios::in);
	while (fp.read((char*)&l, sizeof(Library)))
	{
		if (l.getacc_no() == num)
		{
			l.account();
			found = true;
		}
	}
	fp.close();
	if (found == false)
	{
		cout << "No record found!" << endl;
	}
}

void Library::edit_account()	//function for editing an account
{
	string num;
	bool found = false;
	cout << "Enter the account number:";
	cin >> num;
	cout << endl;
	fp.open("details.txt", ios::in | ios::out);
	while (fp.read((char*)&l, sizeof(Library)) && found == false)
	{
		if (l.getacc_no() == num)
		{
			l.account();
			cout << "\nPlease enter the enw details:";
			cout << endl;
			l.add_account();
			int pos = sizeof(l);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&l, sizeof(l));
			cout << "The account was successfully updated!" << endl;
			found = true;
		}
	}
	fp.close();
	if (found == false)
	{
		cout << "The account does not exists!" << endl;
	}
}

void Library::delete_account()	//function for deleting an account
{
	string num;
	cout << "Please enter the account number:";
	cin >> num;
	fp.open("details.txt", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.txt", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&l, sizeof(Library)))
	{
		if (l.getacc_no() != num)
		{
			fp2.write((char*)&l, sizeof(Library));
		}
	}
	fp2.close();
	fp.close();
	remove("details.txt");
	rename("temp.txt", "details.txt");
	cout << "The account has been deleted successfully!" << endl;
}

int main()	//start of main
{
	while (1)
	{
		l.menu();
		l.input_press();
		if (press == '1')
			l.save_account();
		else if (press == '2')
			l.view_all_accounts();
		else if (press == '3')
		{
			string num;
			cout << "Enter the account number:";
			cin >> num;
			l.search_account(num);
		}
		else if (press == '4')
			l.edit_account();
		else if (press == '5')
			l.delete_account();
		else if (press == '0')
			break;
	}
	return 0;
}	//end of main