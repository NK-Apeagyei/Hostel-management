#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

class Room {
private:
    int roomNo;
    int price;
    bool isAvailable;
    char type[10];
    char occupant[50];
    int studentId;
public:
    Room() {}
    Room(int r, int p, bool a, char t[]) {
        roomNo = r;
        price = p;
        isAvailable = a;
        strcpy(type, t);
    }
    void book() {
        isAvailable = false;
    }
    void unbook() {
        isAvailable = true;
    }
    bool available() {
        return isAvailable;
    }
    int getRoomNo() {
        return roomNo;
    }
    // Funtion to get type of room
    char* getType() {
        return type;
    }
    // Function to get price of room
    int getPrice() {
        return price;
    }
    // set student name in room
    void setStudentName(char n[]) {
        strcpy(occupant, n);
    }

    // get student name in room
    char* getStudentName() {
        return occupant;
    }
    // set student id in room
    void setStudentId(int id) {
        studentId = id;
    }

    // get student id in room
    int getStudentId() {
        return studentId;
    }

};
class Hostel {
    Room rooms[100];
    int numRooms;
public:
    Hostel() { // Constructor
        numRooms = 0;
    }

    // Function to add a room
    void addRoom(char type[], int price) {
        rooms[numRooms++] = Room(numRooms + 1, price, true, type);
    }
    // Function to remove a room
    void removeRoom(int roomNo) {
        // find room by room number and remove it
         for (int i = 0; i < numRooms; i++) {
            if (rooms[i].getRoomNo() == roomNo) {
                rooms[i] = rooms[--numRooms];
                break;
            }
        }

    }

    // Function to display all rooms in table format with headers
    void displayRooms() {
        cout << "\t\t\t\tRoom No.\tType\tPrice(GHC)\tAvailability" << endl;
        for (int i = 0; i < numRooms; i++) {
            cout <<"\t\t\t\t"<< rooms[i].getRoomNo() << "\t\t" << rooms[i].getType() << "\t" << rooms[i].getPrice() <<"\t\t" << (rooms[i].available() ? "Available" : "Not Available") << endl;
        }
    }
    // Function to find a room by type and maxprice and display
Room* findRoom(char type[], int maxPrice) {
    // if no rooms are available
    if (numRooms == 0) {
        cout << "\t\t\t\tNo rooms available." << endl;
        return NULL;
    }
    // if rooms are available
    bool found = false;
    cout << "\t\t\t\tRoom No.\tType\tPrice\tAvailability" << endl;
    for (int i = 0; i < numRooms; i++) {
        if (strcmp(rooms[i].getType(), type) == 0 && rooms[i].getPrice() <= maxPrice) { // if room type and price is found
            found = true;
            cout <<"\t\t\t\t"<< rooms[i].getRoomNo() << "\t\t" << rooms[i].getType() << "\t" << rooms[i].getPrice() <<"\t"<< (rooms[i].available() ? "Available" : "Not Available") << endl;
        }
    }
    // if no rooms are found
    if (!found) {
        cout << "\t\t\t\tNo rooms found." << endl;
        return NULL;
    }

    return NULL;
}
// Function to get a room by room number
Room* getRoom(int roomNo) {
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].getRoomNo() == roomNo) { // if room number is found
            return &rooms[i];
        }
    }
    return NULL; // room not found
}
// Function to book a room
void bookRoom(int roomNo, char studentName[], int studentId) {
    Room* room = getRoom(roomNo); // get room by room number
    if (room != NULL && room->available()) { // if room is available
        room->book(); // book room
        room->setStudentName(studentName); // set student name
        room->setStudentId(studentId); // set student id

        cout << "\t\t\t\tRoom " << roomNo << " booked successfully!" << endl;
    }
    else {
        cout << "\t\t\t\tRoom not available." << endl;
    }
}
// Function to unbook a room
void unbookRoom(int roomNo, char studentName[], int studentId) {
    Room* room = getRoom(roomNo); // get room by room number
    // if room is not available and student name and id match
    if (room != NULL && !room->available() && strcmp(room->getStudentName(), studentName) ==0 && room->getStudentId() == studentId) {
        room->unbook();
        cout << "\t\t\t\tRoom " << roomNo << " unbooked successfully!" << endl;
    }
    else {
        cout << "\t\t\t\tRoom not booked or Details incorrect!" << endl;
    }
}
// Function to display all booked rooms in table format with headers
void displayStudents() {
    cout << "\t\t\t\tRoom No.\tType\tPrice\tStudent Name\t\t\tStudent ID" << endl;
    for (int i = 0; i < numRooms; i++) {
        if (!rooms[i].available()) {
            cout <<"\t\t\t\t"<< rooms[i].getRoomNo() << "\t\t" << rooms[i].getType() << "\t" << rooms[i].getPrice() <<"\t"<<left<<setw(25)<< rooms[i].getStudentName() << "\t" << rooms[i].getStudentId() << endl;
        }
    }
}
// Function to validate room booking by studentname and studentid
void validateRoomBooking(int roomNo, char studentName[], int studentId) {
    Room* room = getRoom(roomNo); // get room by room number
    // if room is not available and student name and id match
    if (room != NULL && !room->available() && strcmp(room->getStudentName(), studentName) ==0 && room->getStudentId() == studentId) {
        cout << "\t\t\t\tRoom is booked by " << studentName << " with ID " << studentId << endl;
    }
    else {
        cout << "\t\t\t\tRoom not booked or Details incorrect!" << endl;
    }
}



// Function to get number of rooms
int getNumRooms() {
    cout << "\t\t\t\tNumber of rooms: " << numRooms << endl;
}
};
class User{
public:
string username;
string password;

};
class Admin : public User{
public:
    Admin(){
        username = "admin1";
        password = "pass1";
}
// function to authenticate admin
bool authenticate(string username, string password){
    if (this->username == username && this->password == password){ // if username and password match
        return true;
    }else{return false;}
}
};


// FILE HANDLING FUNCTIONS
// file to store rooms and their details
void saveRooms(Hostel h) {
ofstream file("rooms.dat", ios::binary); // open file in binary mode
file.write((char*)&h, sizeof(h)); // write to file
file.close(); // close file
}

// load rooms from file
Hostel loadRooms() {
Hostel h; // create hostel object
ifstream file("rooms.dat", ios::binary); // open file in binary mode
if (file) { // if file exists
file.read((char*)&h, sizeof(h)); // read from file
file.close(); // close file
}
return h; // return hostel object
}

// file to store students in room and their details
void saveStudents(Hostel h) {
ofstream file("students.dat", ios::binary); // open file in binary mode
file.write((char*)&h, sizeof(h)); // write to file
file.close(); // close file
}

// load students from file
Hostel loadStudents() {
Hostel h; // create hostel object
ifstream file("students.dat", ios::binary); // open file in binary mode
if (file) { // if file exists
file.read((char*)&h, sizeof(h)); // read from file
file.close(); // close file
}
return h; // return hostel object
}


int main() {// Main function
Hostel h = loadRooms();
Admin a;
// Menu as admin or student
char choice;
while (true) {
system("cls");
cout << "\n\t\t\tWELCOME TO HOSTEL MANAGEMENT SYSTEM" << endl;
cout << "\t\t\t              Group 28               " << endl;
cout << "\t\t\t=====================================" << endl;
cout << "\t\t\t\tlogin as:" << endl;
cout << "\t\t\t\t1. Admin" << endl;
cout << "\t\t\t\t2. Student" << endl;
cout << "\t\t\t\t3. Exit" << endl;
cout << "\t\t\t\tEnter choice: ";
cin >> choice;
// Admin login

if (choice == '1'){
    string username,password;
    cout << "\t\t\t\tEnter username: ";
    cin >> username;
    cout << "\t\t\t\tEnter password: ";
    cin >> password;
    if (a.authenticate(username, password)){ // if username and password match
        system("cls");
        cout << "\t\t\tLogin successful!" << endl;

    }else{
        cout << "\t\t\t\tLogin Failed!" <<endl;
        break;
        }

    // Menu for admin
    while (true){
    cout << "\n\t\t\t----------------" << endl;
    cout << "\t\t\t welcome, Admin " << endl;
    cout << "\t\t\t----------------" << endl;
    cout << "\t\t\t\t1. Add room" << endl;
    cout << "\t\t\t\t2. Remove room" << endl;
    cout << "\t\t\t\t3. Display rooms" << endl;
    cout << "\t\t\t\t4. Assign student to a room" << endl;
    cout << "\t\t\t\t5. Unbook student from room" << endl;
    cout << "\t\t\t\t6. Display students in a room" << endl;
    cout << "\t\t\t\t7. Logout" << endl;
    cout << "\t\t\t\tEnter choice: ";
    cin >> choice;
    // Add room
    if (choice == '1') {
        char type[10];
        int price;
        int roomNo = h.getNumRooms() + 1; // get number of rooms and add 1
        cout << "\t\t\t\tEnter type(1in1, 2in1, 3in1 or 4in1): ";
        cin >> type;
        cout << "\t\t\t\tEnter price in GHc: ";
        cin >> price;
        h.addRoom(type, price); // add room
        saveRooms(h); // save rooms to file
        cout << "\t\t\t\tRoom added successfully!" << endl;
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input

    }
    // Remove room
    else if (choice == '2') {
        int roomNo;
        cout << "\t\t\t\tEnter room no.: ";
        cin >> roomNo;
        h.removeRoom(roomNo); // remove room
        saveRooms(h); // save rooms to file
        cout << "\t\t\t\tRoom removed successfully!" << endl;
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input
    }
    // Display rooms
    else if (choice == '3') {
        cout << "\n\t\t\t\tRooms:" << endl;
        cout << "\t\t\t\t-------------------------------------------------------" << endl;
        h.displayRooms(); // display rooms
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input
    }
    // Assign student to a room and saveStudent
    else if (choice == '4') {
        int roomNo;
        char studentName[50];
        int studentId;
        cout << "\t\t\t\tEnter room no.: ";
        cin >> roomNo;
        cout << "\t\t\t\tEnter student name: ";
        cin.ignore(); // ignore newline character
        cin.getline(studentName, 50); // get student name
        cout << "\t\t\t\tEnter student ID: ";
        cin >> studentId;
        h.bookRoom(roomNo, studentName, studentId); // book room
        saveRooms(h); // save rooms to file
        saveStudents(h); // save students to file
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input

    }
    // Unbook room with student details
    else if (choice == '5') {
        int roomNo;
        char studentName[50];
        int studentId;
        cout << "\t\t\t\tEnter room no.: ";
        cin >> roomNo;
        cout << "\t\t\t\tEnter student name: ";
        cin.ignore(); // ignore newline character
        cin.getline(studentName, 50); // get student name
        cout << "\t\t\t\tEnter student ID: ";
        cin >> studentId;
        h.unbookRoom(roomNo, studentName, studentId); // unbook room
        saveRooms(h); // save rooms to file
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input
    }
    //displayStudents
    else if (choice == '6') {
        h.displayStudents(); // display students
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input
    }

    // Logout
    else if (choice == '7') {
        cout << "\t\t\t\tLogging out..." << endl;
        Sleep(1500);
        cout << "\t\t\t\tLogged out successfully!" << endl;
        cout << "\t\t\t\tPress any key to continue..." << endl;
        getch(); // wait for user input

        break; // break out of loop
    }
    // Invalid choice
    else {
        cout << "\t\t\t\tInvalid choice! Try again" << endl;
        cout << endl;
    }}
    }
    // menu for student

else if (choice == '2') {
        cout << "\n\t\t\tWelcome, Student!" << endl;
        cout << "\t\t\t-----------------" << endl;
        cout << "\t\t\t\t1. Find room" << endl;
        cout << "\t\t\t\t2. Book room" << endl;
        cout << "\t\t\t\t3. Unbook room" << endl;
        cout << "\t\t\t\t4. Verify your room" << endl;
        cout << "\t\t\t\t5. Return to main menu" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> choice;
        // Find room
        if (choice == '1') {
            char type[10];
            int maxPrice;
            cout << "\t\t\t\tEnter type(1in1, 2in1, 3in1 or 4in1): ";
            cin >> type;
            cout << "\t\t\t\tEnter max price in GHc: ";
            cin >> maxPrice;
            h.findRoom(type, maxPrice);

        }
        // Book room
        else if (choice == '2') {
            int roomNo;
            char studentName[50];
            int studentId;
            cout << "\t\t\t\tEnter room no.: ";
            cin >> roomNo;
            cout << "\t\t\t\tEnter student name: ";
            cin.ignore(); // ignore newline character
            cin.getline(studentName, 50);
            cout << "\t\t\t\tEnter student ID: ";
            cin >> studentId;
            h.bookRoom(roomNo, studentName, studentId); // book room
            saveRooms(h); // save rooms to file
            saveStudents(h);// save students to file
        }
        // Unbook room with student details
        else if (choice == '3') {
            int roomNo;
            char studentName[50];
            int studentId;
            cout << "\t\t\t\tEnter room no.: ";
            cin >> roomNo;
            cout << "\t\t\t\tEnter student name: ";
            cin.ignore(); // ignore newline character
            cin.getline(studentName, 50);
            cout << "\t\t\t\tEnter student ID: ";
            cin >> studentId;
            h.unbookRoom(roomNo, studentName, studentId); // unbook room
            saveRooms(h); // save rooms to file
            saveStudents(h);// save students to file
        }
        // validate room
        else if (choice == '4') {
            int roomNo;
            char studentName[50];
            int studentId;
            cout << "\t\t\t\tEnter room no.: ";
            cin >> roomNo;
            cout << "\t\t\t\tEnter student name: ";
            cin.ignore(); // ignore newline character
            cin.getline(studentName, 50);
            cout << "\t\t\t\tEnter student ID: ";
            cin >> studentId;
            h.validateRoomBooking(roomNo, studentName, studentId); // validate room
        }
        else if (choice == '5') {
            cout << "\t\t\t\tPress any key to continue..." << endl;
            getch(); // wait for user input

        }
        // Invalid choice
        else {
            cout << "\t\t\t\tInvalid choice! Try again" << endl;
            cout << endl;
        }
    }
else if (choice == '3') { // exit
        break;
    }
    else {
        cout << "\n\t\t\t\tInvalid choice, Try again" << endl;
}
}
return 0;
}
