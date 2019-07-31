/*This is a contact Management System using file handling*/
#include "pch.h"
#include<iostream>
#include<string.h>
#include<fstream>
#include<string>  //necessary header files are declared.
using namespace std;
char press;
class Manage  //class declaration
{
	string phone = " ";
	char name[20], email[30];

public: //declaration of various functions under the class
	void menu();
	void input_press();
	void check_press();
	void add_contact();
	void save_contact();
	void display();
	void display_contact();
	void search_contact(string);
	void edit_contact();
	void delete_contact();
	string getPhone() { return phone; }
	char* getName() { return name; }
	char* getEmail() { return email; }
};

fstream fp;
Manage m;

void Manage::menu() //displays the menu
{
	cout << "Press 0 to exit" << endl;
	cout << "Press 1 to add contact" << endl;
	cout << "Press 2 to display all contacts" << endl;
	cout << "Press 3 to search contact" << endl;
	cout << "Press 4 to edit contact" << endl;
	cout << "Press 5 to delete contact" << endl;
}
void Manage::input_press() //takes a number from the user to do execute a particular function
{
	cout << "Press a number:";
	cin >> press;
	check_press();
}
void Manage::check_press() //checks if the input is valid
{
	while (1)
	{
		if (press == '0' || press == '1' || press == '2' || press == '3' || press == '4' || press == '5')
			break;
		else
			input_press();
	}
}
void Manage::add_contact() //function for adding the contacts
{
	cout << "Enter the phone:";
	cin >> phone;
	cout << endl;
	cout << "Enter the name:";
	cin >> name;
	cin.ignore();
	cout << endl;
	cout << "Enter the email:";
	cin >> email;
	cin.ignore();
	cout << endl;
}
void Manage::save_contact() //writes the contact details in a text file
{
	fp.open("details.txt", ios::out | ios::app);
	m.add_contact();
	fp.write((char*)& m, sizeof(Manage));
	fp.close();
	cout << endl << endl << "Contact has been created successfully!" << endl;
	getchar();
}
void Manage::display() // for displaying a particular contact detail
{
	cout << endl << "Phone:" << phone;
	cout << endl << "Name:" << name;
	cout << endl << "Email:" << email;
}
void Manage::display_contact() // for displaying all the contacts
{
	cout << "Here are the list of all contacts:" << endl;
	fp.open("details.txt", ios::in);
	while (fp.read((char*)& m, sizeof(Manage)))
	{
		m.display();
		cout << endl;
	}
	fp.close();
}
void Manage::search_contact(string  num) // for searching a particular contact detail based on the number
{
	bool found;
	found = false;
	fp.open("details.txt", ios::in);
	while (fp.read((char*)& m, sizeof(Manage)))
	{
		if (m.getPhone() == num)
		{
			m.display();
			found = true;
		}
	}
	fp.close();
	if (found == false)
	{
		cout << "No records found!" << endl;
	}
	getchar();
}
void Manage::edit_contact() // for editing a particular contact detail based on the number
{
	string num;
	bool found = false;
	cout << "Enter the number to edit:";
	cin >> num;
	cout << endl;
	fp.open("details.txt", ios::in | ios::out);
	while (fp.read((char*)& m, sizeof(Manage)) && found == false)
	{
		if (m.getPhone() == num)
		{
			m.display();
			cout << "\nPlease enter the new details of the contact:";
			m.add_contact();
			int pos = sizeof(m);
			fp.seekp(pos, ios::cur);
			fp.write((char*)& m, sizeof(m));
			cout << "Contact was successfully updated!" << endl;
			found = true;
		}
	}
	fp.close();
	if (found == false)
	{
		cout << "Contact not found!" << endl;
	}
}
void Manage::delete_contact() // for deleting a contact
{
	string num;
	cout << "Please enter the contact number:" << endl;
	cin >> num;
	fp.open("details.txt", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.txt", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)& m, sizeof(Manage)))
	{
		if (m.getPhone() != num)
		{
			fp2.write((char*)& m, sizeof(Manage));
		}
	}
	fp2.close();
	fp.close();
	remove("details.txt");
	rename("temp.txt", "details.txt");
	cout << "Contact has been deleted!" << endl;
}
int main() //start of main
{
	while (1) 
	{
		m.menu();
		m.input_press();
		if (press == '1')
			m.save_contact();
		else if (press == '2')
			m.display_contact();
		else if (press == '3')
		{
			string num;
			cout << "Enter the phone number:";
			cin >> num;
			m.search_contact(num);
		}
		else if (press == '4')
			m.edit_contact();
		else if (press == '5')
			m.delete_contact();
		else if (press == '0')// exits from the loop
			break;
	}
	return 0;
} //end of main
