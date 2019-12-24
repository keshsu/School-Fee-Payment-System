#include<string>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<Windows.h>
#include<iomanip>

/*
Include directly the different headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce the build time.
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h> 

using namespace std;

void menu();
void add();
void listing();
void edit();
void search();
void payment();
void del();
void password();
void setting();
void not_found();
void title(char *t);

int cls, r;
char un[15], p[15], c;
float amt, tamt;
int n = 0, i=0, k, id;
char cheec;


// Initialization of MySQL Variables
sql::Driver *driver;
sql::Connection *con;	// To establish a connection to MySQL Server, we retrieve an instance of sql::Connection.
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *pstmt;


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void interror()
{
	//system("color 74");
	gotoxy(0,2+i); cout << "Enter integer value only";
	cin.clear();
	cin.ignore(256, '\n');
	i = i + 2;
}
void not_found()
{
	system("cls");
	system("color 74");
	gotoxy(65, 15); cout << "Data not found !!!";
}

void title(char *t)
{
	gotoxy(60, 2);
	cout << t;
	cout << "\n_____________________________________________________________________________________________________________________________________________________\n";
}


class data
{
public:
	char first_name[25], last_name[25];
	int student_id, roll_no, class_no;
	string pho_no;
	float amt;
	void get()
	{
		gotoxy(50, 6); cout << "Student Id:";
		cin >> student_id;
		while (cin.fail())
		{
			interror();
			gotoxy(50, 6); cout << "Student Id:";
			cin >> student_id;
		}
		i = i + 2;
		gotoxy(45, 7); cout << "------------------------------";
		gotoxy(50, 8); cout << "Class:";
		cin >> class_no;
		while (cin.fail())
		{
			interror();
			gotoxy(50, 8); cout << "Class:";
			cin >> class_no;
		}
		i = i + 2;
		gotoxy(45, 9); cout << "------------------------------";
		gotoxy(50, 10); cout << "Roll no.:";
		cin >> roll_no;
		while (cin.fail())
		{
			interror();
			gotoxy(50, 10); cout << "Roll no.:";
			cin >> roll_no;
		}
		gotoxy(45, 11); cout << "------------------------------";
		gotoxy(50, 12); cout << "First Name:";
		cin >> first_name;
		gotoxy(45, 13); cout << "------------------------------";
		gotoxy(50, 14); cout << "Last Name:";
		cin >> last_name;
		gotoxy(45, 15); cout << "------------------------------";
		gotoxy(50, 16); cout << "Phone number:";
		cin >> pho_no;
		gotoxy(45, 17); cout << "------------------------------";
		gotoxy(50, 18); cout << "Total amount:";
		cin >> amt;
		gotoxy(45, 19); cout << "------------------------------";
	}
	void show_h()
	{
		gotoxy(13, 4);
		cout << "\tStudent Id" << setw(15) << "Class" << setw(15) << "Roll No" << setw(15) << "First Name" << setw(17) << "Last Name"
			<< setw(17) << "Phone Number" << setw(17) << "Total Amount";
		cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
	void getid()
	{
		gotoxy(55,10); cout << "Enter Student id to continue:";
		cin >> student_id;
		while (cin.fail())
		{
			gotoxy(0,10); cout << "Enter integer value only";
			cin.clear();
			cin.ignore(256, '\n');
			gotoxy(55, 10); cout << "Enter Student id to continue:";
			cin >> student_id;
		}
		system("cls");
	}
	void showdata()
	{
		gotoxy(100, 4); cout <<"     Old Data";
		gotoxy(100, 5); cout << "------------------";
		gotoxy(100, 6); cout << "Student Id:" << res->getInt("Student_Id");
		gotoxy(95, 7); cout << "------------------------------";
		gotoxy(100, 8); cout << "Class:" << res->getInt("Class_No");
		gotoxy(95, 9); cout << "------------------------------";
		gotoxy(100, 10); cout << "Roll Number:" << res->getInt("Roll_no");
		gotoxy(95, 11); cout << "------------------------------";
		gotoxy(100, 12); cout << "First Name:" << res->getString("First_Name");
		gotoxy(95, 13); cout << "------------------------------";
		gotoxy(100, 14); cout << "Last Name:" << res->getString("Last_Name");
		gotoxy(95, 15); cout << "------------------------------";
		gotoxy(100, 16); cout << "Phone Number:" << res->getString("Phone_No");
		gotoxy(95, 17); cout << "------------------------------";
		gotoxy(100, 18); cout << "Total Amount:" << res->getString("Total_Amount");
		gotoxy(95, 19); cout << "------------------------------";
	}
	void showdata2()
	{
		gotoxy(60, 6); cout << "Student Id:" << res->getInt("Student_Id");
		gotoxy(60, 8); cout << "Class:" << res->getInt("Class_No");
		gotoxy(60, 10); cout << "Roll Number:" << res->getInt("Roll_no");
		gotoxy(60, 12); cout << "First Name:" << res->getString("First_Name");
		gotoxy(60, 14); cout << "Last Name:" << res->getString("Last_Name");
		gotoxy(60, 16); cout << "Phone Number:" << res->getString("Phone_No");
		gotoxy(60, 18); cout << "Total Amount:" << res->getString("Total_Amount");
	}
}d, d1;


class password
{
public:
	char  p[30], un[30];
	int ck = 80;

	void getpass()
	{
		for (i = 0; i<15; i++)
		{
			p[i] = _getch();
			n = p[i];

			if (n == 13)    //13 is ASCII value of Enter
				break;		//to break loop when press Enter

			if (n == 8)		// 8 is ASCII value of Backspace
			{
				i--;
				cout << "\b \b"; // to erase the entered data
			}

			else

				cout<<"*";
		}
		p[i] = '\0';    //end the string
	}

	void getuser_name()
	{
		gotoxy(60, 15); cout << "User Name:";
		cin >> un;
	}
}pass, pass1, pass2;


void add()
{
	char t[] = "ADD RECORDS";
	try
	{
		system("cls");
		// Create a connection
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");	// Connect to the MySQL "school" database
		stmt = con->createStatement();

		title(t);

		d.get();
		gotoxy(50,20); cout << "\nDo you want to save it ? (y/n)";
		c = _getche();
		if (c == 'y' || c == 'Y')
		{
			/* '?' is the supported placeholder syntax */
			pstmt = con->prepareStatement("INSERT INTO student VALUES (?,?,?,?,?,?,?)");

			// passing values for the placeholder
			pstmt->setInt(1, d.student_id);
			pstmt->setInt(2, d.class_no);
			pstmt->setInt(3, d.roll_no);
			pstmt->setString(4, d.first_name);
			pstmt->setString(5, d.last_name);
			pstmt->setString(6, d.pho_no);
			pstmt->setDouble(7, d.amt);
			pstmt->executeUpdate();	// Executing the query.

			// deleting the prepared statement and connection variable.
			delete stmt;
			delete pstmt;
			delete con;

			gotoxy(50, 22); cout << "\n\nEnter y if you want to add another record:";
			c = _getche();
			if (c == 'y' || c == 'Y')
			{
				add();
			}
			system("cls");
			system("color 72");
			gotoxy(65, 15); cout << "Data sucessful added..";
		}
	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "database connection fail";
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}
	_getch();
}

void listing()
{
	char t[] = "  LIST RECORDS";
	try
	{
		system("cls");
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();
		title(t);

		int k = 0;
		pstmt = con->prepareStatement("SELECT DISTINCT Class_No FROM student ORDER BY Class_No ASC");
		res = pstmt->executeQuery();
		res->afterLast();

		gotoxy(120, 5); cout << "list of class:";
		while (res->previous())
		{
			gotoxy(125, 6 + k);
			cout << res->getInt("Class_No");
			k++;
		}
		gotoxy(7, 5); cout << "Enter class No which records you want to see:";
		cin >> cls;
		while (cin.fail())
		{
			gotoxy(0, 10); cout << "Enter integer value only";
			cin.clear();
			cin.ignore(256, '\n');
			gotoxy(7, 5); cout << "Enter class No which records you want to see:";
			cin >> cls;
		}
		system("cls");
		pstmt = con->prepareStatement("SELECT * FROM student where Class_No=? ORDER BY Roll_no ASC");
		pstmt->setInt(1, cls);
		res = pstmt->executeQuery();
		/* Fetch in reverse = descending order! */
		if (res->next())
		{
			d.show_h();
			res->afterLast();
			int i = 0;
			while (res->previous())
			{
				title(t);
				gotoxy(13, 6+i);
				cout << "\t  " << res->getInt("Student_Id") << setw(20);
				cout << res->getInt("Class_No") << setw(13);
				cout << res->getInt("Roll_no") << setw(17);
				cout << res->getString("First_Name") << setw(17);
				cout << res->getString("Last_Name") << setw(16);
				cout << res->getString("Phone_No") << setw(18);
				cout << res->getString("Total_Amount");
				cout << "\n----------------------------------------------------------------------------------------------------------------------------------------------------\n";
				i = i + 2;
			}
		}
		else
		{
			not_found();
		}
		delete stmt;
		delete pstmt;
		delete res;
		delete con;
	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "database connection fail";
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}

	_getch();
}
void edit()
{
	char t[] = "EDIT RECORDS";
	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();

		title(t);
		d1.getid();
		title(t);

		pstmt = con->prepareStatement("SELECT *FROM student where Student_Id=?");
		pstmt->setInt(1, d1.student_id);
		res = pstmt->executeQuery();
		if (res->next())
		{
			d.showdata();
			/* '?' is the supported placeholder syntax */
			pstmt = con->prepareStatement("UPDATE student SET Student_Id=?,Class_No=?,Roll_No=?,First_Name=?,Last_Name=?,Phone_No=?,Total_Amount=? WHERE Student_Id=?");
			gotoxy(50, 4); cout << "     Old Data";
			gotoxy(50, 5); cout << "------------------";
			d.get();
			pstmt->setInt(8, d1.student_id);
			pstmt->setInt(1, d.student_id);
			pstmt->setInt(2, d.class_no);
			pstmt->setInt(3, d.roll_no);
			pstmt->setString(4, d.first_name);
			pstmt->setString(5, d.last_name);
			pstmt->setString(6, d.pho_no);
			pstmt->setDouble(7, d.amt);
			pstmt->executeUpdate();
			delete stmt;
			delete pstmt;
			delete con;
			system("cls");
			system("color 72");
			gotoxy(65, 15); cout << "Update sucessful.......";
		}
		else
		{
			not_found();
		}
	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "database connection fail";
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}

	_getch();
}
void search()
{
	char t[] = "SEARCH RECORDS";
	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();

		title(t);
		d1.getid();
		title(t);

		pstmt = con->prepareStatement("SELECT * FROM student where Student_Id=?");
		pstmt->setInt(1, d1.student_id);
		res = pstmt->executeQuery();
		if (res->next())
		{
			d.showdata2();
		}
		else
		{
			not_found();
		}
		delete stmt;
		delete pstmt;
		delete res;
		delete con;

	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "Database connection fail" << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}
	_getch();
}


void payment()
{
	char t[] = "PAYMENT";
	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();

		title(t);
		d.getid();
		title(t);

		pstmt = con->prepareStatement("SELECT * FROM student where Student_Id=?");
		pstmt->setInt(1, d.student_id);
		res = pstmt->executeQuery();
		if (res->next())
		{
			d.showdata();
			tamt = res->getDouble("Total_amount");
			//'?' is the supported placeholder syntax
			pstmt = con->prepareStatement("UPDATE student SET Total_Amount=? WHERE Student_Id=?");
			pstmt->setInt(2, d.student_id);
			gotoxy(40, 10); cout << "Total Amount:" << res->getString("Total_Amount") << endl;
			gotoxy(40, 12);
			cout << "Enter Payment amount:";
			cin >> amt;
			tamt = tamt - amt;
			gotoxy(35,13); cout << "____________________________________";
			gotoxy(40, 15); cout << "Remaining amount=" << tamt << endl;
			pstmt->setDouble(1, tamt);
			pstmt->executeUpdate();
			_getch();
			delete stmt;
			delete pstmt;
			delete con;
			system("cls");
			system("color 2");
			gotoxy(65, 15); cout << "Thank you for payment";
		}
		else
		{
			not_found();
		}
	}

	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "Database connection fail";
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}

	_getch();
}
void del()
{
	char t[] = "DELETE RECORDS";
	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();

		title(t);
		d.getid();
		title(t);

		pstmt = con->prepareStatement("SELECT * FROM student WHERE Student_Id=?");
		pstmt->setInt(1, d.student_id);
		res = pstmt->executeQuery();
		if (res->next())
		{
			d.showdata2();

			gotoxy(60,20); cout << "Do you want to Delete it ? (y/n)";
			c = _getche();
			if (c == 'y' || c == 'Y')
			{
				pstmt = con->prepareStatement("DELETE FROM student WHERE Student_Id=?");
				{
					pstmt->setInt(1, d.student_id);
					res = pstmt->executeQuery();
					system("cls");
					system("color 72");
					gotoxy(65, 15); cout << "Data Delete sucessfully......";
				}
			}
		}
		else
		{
			not_found();
		}
		delete stmt;
		delete pstmt;
		delete res;
		delete con;

	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "Database connection fail" << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}
	_getch();
}

void password()
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();

		system("color 70");
		pass.getuser_name();
		gotoxy(60, 17); cout << "Password:";
		pass.getpass();
		pstmt = con->prepareStatement("select User_Name, password FROM password WHERE User_Name=? and password=?");
		pstmt->setString(1, pass.un);
		pstmt->setString(2, pass.p);
		res = pstmt->executeQuery();
		if (res->next())
		{
			menu();
		}
		else
		{
			system("color 74");
			gotoxy(55, 20); cout << "Wrong User Name/password";
		}
		delete stmt;
		delete pstmt;
		delete res;
		delete con;

		gotoxy(52, 22); cout << "Do you want to try again (y/n):-";
		c = _getche();
		if (c == 'y' || c == 'Y')
		{
			system("cls");
			password();
		}
		else
		{
			exit(0);
		}

	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "Database connection fail" << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}
	_getch();
}

void setting()
{
	char t[] = "PASSWORD SETTING";
	try
	{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("school");
		stmt = con->createStatement();

		title(t);
		pass.getuser_name();
		gotoxy(60, 16); cout << "New Password:";
		pass.getpass();
		gotoxy(60, 17); cout << "Old password:";
		pass1.getpass();

		pstmt = con->prepareStatement("select * FROM password WHERE password=?");
		pstmt->setString(1, pass1.p);
		res = pstmt->executeQuery();
		if (res->next())
		{
			pstmt = con->prepareStatement("UPDATE password SET  User_Name=?, password=?");
			pstmt->setString(1, pass.un);
			pstmt->setString(2, pass.p);
			pstmt->executeUpdate();
		
			system("cls");
			system("color 72");
			gotoxy(60, 16); cout << "Change sucessful.......";
		}
		else
		{
			system("cls");
			system("color 74");
			gotoxy(60, 16); cout << endl << "Wrong password";
			_getch();
		}
		delete stmt;
		delete pstmt;
		delete res;
		delete con;
	}
	catch (sql::SQLException &e)
	{
		system("color 74");
		cout << "Database connection fail" << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << " (MySQLerror code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << endl;
	}
}


int main()
{
	//system("color 70");
	password();
	_getch();
	return 0;
}

void menu()
{
	int chh;
	char t[] = "   MAIN MENU";
	while (1)
	{
		system("color 70");
		system("cls");
		title(t);
		
	    gotoxy(60, 5);  cout << "1. ADD Records" << endl;
		gotoxy(60, 6);  cout << "2. List Records" << endl;
		gotoxy(60, 7); cout << "3. Edit Records" << endl;
		gotoxy(60, 8); cout << "4. Search Records" << endl;
		gotoxy(60, 9); cout << "5. Payment" << endl;
		gotoxy(60, 10); cout << "6. Delete Records" << endl;
		gotoxy(60, 11); cout << "7. Change Password" << endl;
		gotoxy(60, 12); cout << "8. Exit" << endl;
		gotoxy(60, 14); cout << "Enter your choice:";
		chh = _getche();
		switch (chh)
		{
		case '1':
		{
			system("cls");
			add();
			break;
		}
		case '2':
		{
			system("cls");
			listing();
			break;
		}
		case '3':
		{
			system("cls");
			edit();
			break;
		}
		case '4':
		{
			system("cls");
			search();
			break;
		}
		case '5':
		{
			system("cls");
			payment();
			break;
		}
		case '6':
		{
			system("cls");
			del();
			break;
		}

		case '7':
		{
			system("cls");
			setting();
			break;
		}

		case '8':
		{
			system("cls");
			system("color 2");
			gotoxy(60, 16);  cout << "Thank you for useing this software";
			_getch();
			exit(0);
			break;
		}

		default:
		{
			system("cls");
			system("color 74");
			gotoxy(60, 16); cout << "invalid input.......";
			_getch();
			break;
		}

		}
	}

}