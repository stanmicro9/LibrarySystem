#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype> //for the isdigit() "built-in fn" function>>>checks if the input is all digits or not
#include <conio.h> // For _getch()

int numofbooks = 15;

using namespace std;


struct Student {
string name;
int ID;
string Booky[100]; //books
}s[100];
int numofstudents = 7;


//BOOKS:
struct Book {
string code;
string name;
string category;
string authorname;
int year;
string availability;
}books[100];


//BOTH
string registr(int& numofstudents,Student (&s)[100]);
void listingbooks(int numofbooks);
void book();
int logout();

//STUDENT
int Slogin(int numofstudents);
void Smenu(int Sindex,string (&Booky)[100], Student(&s)[100], Book(&books)[100]);
void editinfo(int Sindex,Student (&s)[100]);
void BorrowB(int Sindex,int numofbooks, string (&Booky)[100], Book (&books)[100]);
void BBlog(int Sindex);
void avBooks(int numofbooks);
void modifyOrder(int Sindex,int numofbooks,int prevbook,Book (&books)[100]);
void returnBook(int Sindex, Student(&s)[100], Book(&books)[100]);

//ADMIN
void Alogin();
void Amenu(int& numofbooks,Book(&books)[100]);
void addingbooks(int& numofbooks,Book(&books)[100]);
void DeleteB(int& numofbooks, Book(&books)[100]);
void modifyingbooks(Book(&books)[100]);



//FILES
void readstudents()
{
ifstream file;
file.open("students.txt", ios::in);
int number = 0;
while (file.good())
{
file >> s[number].name;
file >> s[number].ID;
//for (int i = 0; i < 100; i++) // Changed the loop condition from 1 to 100
//{
// if (!file.eof()) // Check if end of the file is reached
// {
// getline(file, s[number].Booky[i]);
// }
// else
// {
// break;
// }
//}

for (int i = 0; i < 100; i++) // Changed the loop condition from 1 to 100
{
if (!s[number].Booky[i].empty())
{
getline(file, s[number].Booky[i]);
}
else
{
break; // Added break statement to exit the loop when an empty book is encountered
}
}

number++;
}

file.close();
}

void readbooks(Book(&books)[100], int& numofbooks) {
ifstream file;
file.open("books.txt", ios::in);
int i = 0;
while (file.good())
{
file >> books[i].code;
file >> books[i].name;
file >> books[i].category;
file >> books[i].authorname;
file >> books[i].year;
file >> books[i].availability;

i++;
}
file.close();
}

void savestudent()
{
ofstream file;
file.open("students.txt", ios::out | ios::trunc);
int number = 0;
while (!s[number].name.empty()) // Changed the loop condition to check if student name is not empty
{
file << s[number].name << endl
<< s[number].ID << endl;
for (int i = 0; i < 100; i++)
{
if (!s[number].Booky[i].empty())
{
file << s[number].Booky[i] << endl;
}
else
{
break; // Added break statement to exit the loop when an empty book is encountered
}
}
number++;
}
file.close();
}

void savebooks(Book(&books)[100], int& numofbooks) {
ofstream file;
file.open("books.txt", ios::out | ios::trunc);
int i = 0;
while (file.good())
{
if (!books[i].name.empty()) {

file << books[i].code << endl;
file << books[i].name << endl;
file << books[i].category << endl;
file << books[i].authorname << endl;
file << books[i].year << endl;
file << books[i].availability << endl;

i++;
}
else
break;
}
file.close();
}



void about() {
system("cls");
cout << "System developers:\n******************\n\n";
    cout<<"1-Mariam Khaled\n2-Malak Mohannad\n3-Roki\n4-Mariam Ahmad\n5-Malak Gholam\n6-Roaa Hazem\n7-Mariem Saleh\n\n******************\n";
cout << "To go back, press backspace";
char key;
while (true) {
key = _getch(); //we use _getch() to read the key pressed from the console and store it in the key variable
if (key == '\b') { // Check if it's the backspace key
system("cls");
return;
}
//if another key was pressed, nth happens
}

}

void mainmenu(int& numofbooks, int& numofstudents,Student (&s)[100],Book (&books)[100]) {

//centering the sentance in the console
cout << setw(50 + "WELCOME TO OUR LIBRARY MANAGEMENT SYSTEM"s.length() / 2) << "WELCOME TO OUR LIBRARY MANAGEMENT SYSTEM\n";
//s suffix after the string literal is a C++14 feature that allows the creation of std::string objects directly from string literals
//user-defined literals allow you to define your own suffixes for literal values of various types, including strings
//the s suffix is a user-defined literal for std::string objects. When you add the s suffix to a string literal
//it creates a std::string object initialized with the contents of the string literal.


int choice;
cout << "1-Log In As A Student\n";
cout << "2-Log In As An Admin\n";
cout << "3-New Account Registration\n";
cout << "4-About Developers\n";
cout << "5-Exit Program\n";
cout << "Enter your choice: ";
cin >> choice;
system("cls");
int Stuindex;
string reg;

switch (choice)
{
case 1:
Stuindex = Slogin(numofstudents);
if (Stuindex == -1) cout << "Invalid username or password, please try again!\n\n";
else if (Stuindex == -2) cout << "Error, please enter a numeric password and try again.\n";
else Smenu(Stuindex, s[Stuindex].Booky,s,books);
return mainmenu(numofbooks,numofstudents,s,books);
break;
case 2:
Alogin();
Amenu(numofbooks,books);
return mainmenu(numofbooks, numofstudents, s, books);
break;
case 3:
reg = registr(numofstudents,s);
if (reg == "nope") {
system("cls");
cout << "Error, please enter a numeric password and try again.\n\n";
}
else if (reg == "yup") {
cout << "registration is completed\n\n";
}
return mainmenu(numofbooks, numofstudents, s, books);
break;

case 4:
about();
return mainmenu(numofbooks, numofstudents, s, books);
break;
case 5:
break;
default:
cout << "wrong choice, please enter a valid choice!" << endl;
return mainmenu(numofbooks, numofstudents, s, books);
break;
}
}

int main() {
ios_base::sync_with_stdio(0);
cin.tie(NULL);

//books
books[0] = { "474701","Rich Dad Poor Dad","Personal Finance","Rober Kiyosaki and Sharon L.Lechter",2000, "Available" };
books[1] = { "474702","Verity","Romantic Thriller","Collen Hoover",2018, "Not Available" };
books[2] = { "474703","Again, But Better","Romance novel","Christine Riccio",2021 , "Not Available" };
books[3] = { "474704","The Selection","Fantasy Fiction","Kiera Cass",2012, "Available" };
books[4] = { "474705","The Cruel Prince","Fantasy Fiction","Holly Black",2018, "Available" };
books[5] = { "474706","Mythos","Historical Fiction","Stephen Fry",2017 , "Available" };
books[6] = { "474707","The book theif","Historical Fiction","Markus Zusak",2005, "Not Available" };
books[7] = { "474708","The silent patient","pyschological thriller","Alex Michaelides",2019 , "Not Available" };
books[8] = { "474709","Two can keep a secret","Mystery","Karen M.McManus",2019 , "Available" };
books[9] = { "474710","The rules of life","self-help book","Richard Templar",2005 , "Available" };
books[10] = { "474711","A good girl's guide to murder","crime and mystery","Holly Jackson",2019, "Available" };
books[11] = { "474712","Oliver Twist","Social novel","Charles Dickens",1837 , "Not Available" };
books[12] = { "474713","Layla","thriller","Colleen Hoover",2020, "Available" };
books[13] = { "474714","Pride and Prejudice","romance novel","Jane Austen",1813 , "Not Available" };
books[14] = { "474715","The strength in our scars","Poetry","Bianca Sparacino",2017, "Available" };

//users
s[0] = { "Roa Elsayed",2022170566,{"Verity"}};
s[1] = { "Roaa Badawi",2022170565,{"Again, But Better"}};
s[2] = { "Malak Mohannad",2022170435,{"The book theif"}};
s[3] = { "Malak Gholam",2022170434,{"The silent patient"}};
s[4] = { "Mariam Saleh",2022170414 ,{"Oliver Twist"}};
s[5] = { "Mariam Ahmed",2022170409,{"Pride and Prejudice"} };
s[6] = { "Mariam Khaled",2022170413};


mainmenu(numofbooks, numofstudents, s, books);

return 0;
}


//BOTH
string registr(int& numofstudents,Student (&s)[100]) {
string reguser;
int regpass;
cout << "Enter the username: ";
cin.ignore();
getline(cin, reguser);
cout << "Enter the password (must be numeric): ";

//////As when the user enters the pass as letters, the program dont crash
string input;
getline(cin, input);
bool is_valid_input = true;
for (size_t i = 0; i < input.size(); i++) {
if (!isdigit(input[i])) {
is_valid_input = false;
break;
}
}
if (is_valid_input == true) {
regpass = stoi(input);
//////
s[numofstudents].name = reguser;
s[numofstudents].ID = regpass;
system("cls");
numofstudents++;
return "yup";
}
//in case the pass had letters
else {
return "nope";
}
}

void listingbooks(int numofbooks)
{
book();
int choice;
cout << "1-Choose a book to view it\n" << "2-Main menu\n" << "Your choice: ";
cin >> choice;
if (choice == 2) { system("cls"); return; }


else if (choice == 1) {
int x;
cout << '\n' << "Enter the book number:" << '\n';
cin >> x;
system("cls");

if (x>0 && x<=numofbooks)
{
cout << "Code: " << books[x - 1].code << '\n';
cout << "Book Name: " << books[x - 1].name << '\n';
cout << "Category: " << books[x - 1].category << '\n';
cout << "Author Name: " << books[x - 1].authorname << '\n';
cout << "Year Published: " << books[x - 1].year << '\n';
cout << "Availability for borrwing: " << books[x - 1].availability << "\n\n";

cout << "To go back, press backspace";
char key;
while (true) {
key = _getch(); //we use _getch() to read the key pressed from the console and store it in the key variable
if (key == '\b') { // Check if it's the backspace key
system("cls");
return listingbooks(numofbooks); // goes back to the original list \\RECURSIVE CALL//
}
//if another key was pressed, nth happens
}
   }

else {
cout << "Invalid book number, please choose a book from the list\n\n";
return listingbooks(numofbooks);
}
}


else {
system("cls");  cout << "Invalid choice, please try again\n\n";  return listingbooks(numofbooks);
}

}

int logout() {
char exit;
cout << "Are you sure you want to logout?\n\n" << "Y FOR YES & N FOR NO\n" << "Y or N ?: ";
cin >> exit;
if (exit == 'N' || exit == 'n') {
system("cls");
return 0;
}
else if (exit == 'Y' || exit == 'y') {
system("cls");
return 1;
}
else return 2;
}


//STUDENT
int Slogin(int numofstudents) {
string user;
int pass;
bool in = false;
cout << "name: ";
cin.ignore();
getline(cin, user);
cout << "password: ";

//////As when the user enters the pass as letters, the program dont crash
string input;
getline(cin, input);
bool is_valid_input = true;
for (size_t i = 0; i < input.size(); i++) {
if (!isdigit(input[i])) {
is_valid_input = false;
break;
}
}
if (is_valid_input) {
pass = stoi(input);
//////
int Sindex;
for (int i = 0; i < numofstudents; i++) {
if (user == s[i].name && pass == s[i].ID) {
in = true;
Sindex = i;
break;
}
}

if (in == true) {
system("cls");
cout << "Successfully logged in\n\n" << "                                       WELCOME!\n";
return Sindex;
}
else {
system("cls");
return -1;
}
}
//in case the pass had letters
else {
system("cls");
return -2;
}

}

void Smenu(int Sindex, string (&Booky)[100],Student(&s)[100], Book(&books)[100]) {
int choice;
cout << "1-User's info\n2-List of books\n3-Books available for borrowing\n4-Books borrowed log\n5-Return a book\n6-Log out\nEnter your choice: ";
cin >> choice;


system("cls");
switch (choice) {
case 1: 
editinfo(Sindex,s);
return Smenu(Sindex,s[Sindex].Booky,s,books);
break;

case 2:  
listingbooks(numofbooks);
return Smenu(Sindex, s[Sindex].Booky,s,books);
break;

case 3: 
BorrowB(Sindex, numofbooks, s[Sindex].Booky,books);
return Smenu(Sindex, s[Sindex].Booky,s,books);
break;

case 4:
BBlog(Sindex);
return Smenu(Sindex, s[Sindex].Booky,s,books);
break;


case 5:
returnBook(Sindex, s, books);
return Smenu(Sindex, s[Sindex].Booky, s, books);
break;

case 6: 
 {
system("cls");
int answer = logout();
if (answer == 0) return Smenu(Sindex, s[Sindex].Booky,s,books);
else if (answer == 1) { cout << "successfully logged out.\n\n"; }
else if (answer == 2) {
system("cls");
cout << "Invalid answer, please try again!\n\n";
return Smenu(Sindex, s[Sindex].Booky,s,books);
}
break;
 }

default: 
cout << "wrong choice, please enter a valid choice!\n\n";
return Smenu(Sindex, s[Sindex].Booky,s,books);
break;
}
}

void editinfo(int Sindex, Student(&s)[100]) {
system("cls");
string n;
int choice,pass;
string passstr;

cout << "Current user's info:\n";
cout << "User's name: "<<s[Sindex].name << endl <<"User's password: "<< s[Sindex].ID << endl;
cout << "1-Edit info\n2-Main menu\nEnter your choice: ";
cin >> choice;

switch (choice) {
case 1:
cout << "Enter new information or press enter to keep the old info\nEnter new name: ";

cin.ignore();
getline(cin, n);
if (!n.empty())
s[Sindex].name = n;

//Checking it is all numeric/digits b4 putting it in the pass
cout << "Enter new password (must be numeric): ";
getline(cin, passstr); // the year attribute is read as a string and then converted to an integer using stoi
if (!passstr.empty()) { //in case he didnt press enter
bool is_valid_passstr = false;
for (size_t i = 0; i < passstr.size(); i++) {
if (isdigit(passstr[i])) {
is_valid_passstr = true;
   }
   }
if (is_valid_passstr == true) {
pass = stoi(passstr);
s[Sindex].ID = pass;
}
else {
system("cls");
cout << "Error! Please enter a numeric password and try again.\n\n";
return;
}
}

system("cls");
cout << "Info updated successfully\n***************************\n";
break;


case 2: 
system("cls");
break;

default: 
system("cls");
cout << "invalid choice, please try again.\n";
break;
}
}

void book() {
cout << "List of books:\n";
for (int i = 0; i < numofbooks; i++) {
cout << i + 1 << ". " << books[i].name << endl;
} cout << "***************************************\n\n";
}

void BorrowB(int Sindex,int numofbooks, string(&Booky)[100], Book (&books)[100])
{ 
avBooks(numofbooks);
cout << "1-Borrow a book\n2-main menu\nEnter your choice: ";
int choice;
cin >> choice;
switch (choice) {
case 1:
int bookNumber;
cout << "Enter the book number to borrow: ";
cin >> bookNumber;
system("cls");
if (bookNumber <= numofbooks) {
bookNumber--; 
if (books[bookNumber].availability == "Available") {
cout << "Book borrowed: " << books[bookNumber].name << endl;
cout << "Book code: " << books[bookNumber].code << endl;
for (int i = 0; i < 100; i++) {
if (s[Sindex].Booky[i] == "") {
s[Sindex].Booky[i] = books[bookNumber].name;
books[bookNumber].availability = "Not Available";
cout << "Book borrowed successfully!\n\n";
modifyOrder(Sindex, numofbooks, bookNumber,books);
break;
}
}
}
else {
system("cls");
cout << "Please choose an available book from the list\n\n";
return BorrowB(Sindex, numofbooks,s[Sindex].Booky, books);
}
}
else {
cout << "Invalid book number, please try again!\n\n";
return BorrowB(Sindex, numofbooks, s[Sindex].Booky, books);
}
break;

case 2:
system("cls");
break;

default:
system("cls");
cout << "wrong choice, please enter a valid choice!\n\n";
return BorrowB(Sindex,numofbooks, s[Sindex].Booky, books);
break;
}

}

void BBlog(int Sindex) {
system("cls");
cout << "Log of previously borrowed books:\n";
int j = 1;
for (int i = 0; i < 100; i++) {
if (s[Sindex].Booky[i] != "") {
cout << j << ". " << s[Sindex].Booky[i] << endl;
j++;
}
}
cout << "\n***************************************\n" << endl;
cout << "press backspace for main menu";
char key;
while (true) {
key = _getch();
if (key == '\b') {
system("cls");
return;
}
}
}

void avBooks(int numofbooks) {
cout << "List of available books for borrowing:\n";
for (int i = 0; i < numofbooks; i++) {
if (books[i].availability == "Available") {
cout << i + 1 << ". " << books[i].name << endl;
}
}cout << "***************************************\n" << endl;
}

void modifyOrder(int Sindex, int numofbooks , int prevbook , Book (&book)[100]) {
char modify;
cout << "\nDo you want to modify your order ?\n";
cout << "y for yes || n for no\n";
cin >> modify;
if (modify == 'y' || modify == 'Y') {
avBooks(numofbooks);
cout << "choose the book number you want to borrow instead\n";
int booknumber;
string input;
cin.ignore();
getline(cin, input);
bool is_valid_input = true;
for (size_t i = 0; i < input.size(); i++) {
if (!isdigit(input[i])) {
is_valid_input = false;
break;
}
}
if (is_valid_input) {
booknumber = stoi(input);
if (booknumber <= numofbooks) {
booknumber--;
if (books[booknumber].availability == "Available") {
system("cls");
cout << "Book borrowed: " << books[booknumber].name << endl;
cout << "Book code: " << books[booknumber].code << endl;
for (int i = 0; i < 100; i++) {
if (s[Sindex].Booky[i] == "") {
s[Sindex].Booky[i - 1] = books[booknumber].name;
books[booknumber].availability = "Not Available";
books[prevbook].availability = "Available";
cout << "Order has been modified\n\n";
break;
}
}
}

else { 
system("cls");
cout << "Please choose an available book from the list\n\n";
return modifyOrder(Sindex, numofbooks, prevbook,books);
}
}

else { //if the user entered a number more than the numofbooks in the library
system("cls");
cout << "Invalid book number, please try again!\n";
return modifyOrder(Sindex, numofbooks, prevbook,books);
}
} 

else { //if the user entered a name instead of the number of the book as a mistake
system("cls");
cout << "\nEnter the number of the book.Please try again.\n\n";
return modifyOrder(Sindex, numofbooks, prevbook,books);
}
}

else if (modify == 'n' || modify == 'N') {
system("cls");
return;
}


else {//lw 7t 7rf not y nor n
system("cls");
cout << "Please enter a valid choice.\n";
return modifyOrder(Sindex, numofbooks, prevbook,books);
}
}

void returnBook(int Sindex, Student(&s)[100], Book(&books)[100]) {
system("cls");
int num;
cout << "List of borrowed books:\n";
for (int i = 0; i < 100;i++) {
if (s[Sindex].Booky[i] != "") {
cout << i + 1<<". " << s[Sindex].Booky[i] << endl;
}
else break;
}
cout << "Enter the book number you want to return: ";
cin >> num;
num--;
for (int i = 0; i < numofbooks;i++) {
if (s[Sindex].Booky[num] == books[i].name) {
books[i].availability = "Available";
system("cls");
cout << "Book returned successfully.\n\n";
s[Sindex].Booky[num] = "";
cout << "***************************************\n\n";
break;
}
}
}



//ADMIN
void Alogin() {
string pass;
cout << "Enter password: ";
cin >> pass;
if (pass == "1234")
{
system("cls");
cout << "Successfully logged in.\n" << "                                       WELCOME!\n";
}
else {
cout << "wrong password, please try again.\n\n";
return Alogin();
}
}

void Amenu(int& numofbooks,Book(&books)[100]) {
int choice3;
cout << "1-Books list\n2-Add a new book\n3-Delete a book\n4-Modify a book\n5-Log out\nEnter your choice : ";
cin >> choice3;
switch (choice3)
{
case 1: 
listingbooks(numofbooks);
return Amenu(numofbooks,books);
break;

case 2: 
addingbooks(numofbooks,books);
cout << "Book added successfully\n\n";
return Amenu(numofbooks,books);
break;

case 3: 
DeleteB(numofbooks,books);
return Amenu(numofbooks,books);
break;

case 4: 
modifyingbooks(books);
system("cls");
cout << "Modification done successfully\n";
return Amenu(numofbooks,books); 
break;

case 5: 
 {
system("cls");
int answer = logout();
if (answer == 0) return Amenu(numofbooks,books);
else if (answer == 1) cout << "successfully logged out.\n";
else if (answer == 2) {
system("cls");
cout << "please enter a valid answer.\n";
return Amenu(numofbooks,books);
}
break;
 }

default:
system("cls");
cout << "wrong choice, please enter a valid choice\n";
return Amenu(numofbooks,books);
break;

}
}

void addingbooks(int& numofbooks,Book(&books)[100])
{
system("cls");
string code;
string name;
string category;
string authorname;
int year;

cout << "1-Add a book\n" << "2-Main menu\n" << "Enter your choice: ";
int choice;
cin >> choice;
switch (choice) {
case 1:
system("cls");
cout << "Enter new book code: ";
cin.ignore();
getline(cin, code);
books[numofbooks].code = code;

cout << "book name: ";
getline(cin, name);
books[numofbooks].name = name;

cout << "Enter new book Category: ";
getline(cin, category);
books[numofbooks].category = category;

cout << "Enter new book Author Name: ";
getline(cin, authorname);
books[numofbooks].authorname = authorname;

cout << "Enter the year the new book was published: ";
cin >> year;
books[numofbooks].year = year;
cin.ignore();

numofbooks++;
system("cls");
break;

case 2:
system("cls");
return;
break;

default:
system("cls");
cout << "wrong choice, please enter a valid choice\n";
return addingbooks(numofbooks,books);
break;
}
}

void DeleteB(int& numofbooks, Book(&books)[100]) {
int indexToDelete;
system("cls");
book();
cout << "1-Delete a book\n" << "2-Main menu\n" << "Enter your choice: ";
int choice; cin >> choice;
switch (choice) {
case 1:
cout << "Enter the number of the book you want to delete: ";
cin >> indexToDelete;
for (int i = indexToDelete - 1; i < numofbooks - 1; i++) {
books[i].authorname = books[i + 1].authorname;
books[i].category = books[i + 1].category;
books[i].code = books[i + 1].code;
books[i].name = books[i + 1].name;
books[i].year = books[i + 1].year;
}

books[numofbooks - 1].authorname = "";
books[numofbooks - 1].category = "";
books[numofbooks - 1].code = "";
books[numofbooks - 1].name = "";
books[numofbooks - 1].year = NULL;
cout << "book deleted successfully!!\n";
numofbooks--;

cout << "To go back press backspace";
char key;
while (true) {
key = _getch();
if (key == '\b') {
system("cls");
return;
}
}
break;
case 2:
system("cls");
return;
break;

default:
system("cls");
cout << "wrong choice, please enter a valid choice\n";
return DeleteB(numofbooks,books);
break;
}
}

void modifyingbooks(Book(&books)[100]) {
int indextomodify;
string ncode;
string nname;
string ncategory;
string nauthorname;
system("cls");
book();
cout << "Enter book number you want to modify : ";
cin >> indextomodify;
system("cls");
cout << "Current book information:\n";
cout << "Code: " << books[indextomodify - 1].code << endl;
cout << "Name: " << books[indextomodify - 1].name << endl;
cout << "Category: " << books[indextomodify - 1].category << endl;
cout << "Author name: " << books[indextomodify - 1].authorname << endl;
cout << "Year: " << books[indextomodify - 1].year << endl;

cout << "Enter new information or press enter to keep the old info\n";
cin.ignore();
cout << "Code: ";
getline(cin, ncode);
if (!ncode.empty())
books[indextomodify - 1].code = ncode;

cout << "Name: ";
getline(cin, nname);
if (!nname.empty())
books[indextomodify - 1].name = nname;

cout << "Category: ";
getline(cin, ncategory);
if (!ncategory.empty())
books[indextomodify - 1].category = ncategory;

cout << "Author name: ";
getline(cin, nauthorname);
if (!nauthorname.empty())
books[indextomodify - 1].authorname = nauthorname;

cout << "Year: ";
string nyearstr;
getline(cin, nyearstr);
if (!nyearstr.empty()) {
int nyear = stoi(nyearstr);
books[indextomodify - 1].year = nyear;
}
}
