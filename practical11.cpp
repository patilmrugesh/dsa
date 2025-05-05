// 11Department maintains a student information. The file contains roll number, name, division and address.
// Allow user to add, delete information of student. Display information of particular employee.
// If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details.
// Use sequential file to main the data.

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Record {
    int rollno, subcode;
    char name[20], subject[20];
    float internal_marks, uni_marks;

public:
    Record() : rollno(0), subcode(0), internal_marks(0), uni_marks(0) {
        strcpy(name, "");
        strcpy(subject, "");
    }

    int getRollno() { return rollno; }

    void getData() {
        cout << "\nEnter Roll No: "; cin >> rollno;
        cout << "Name: "; cin >> name;
        cout << "Subject Code: "; cin >> subcode;
        cout << "Subject Name: "; cin >> subject;
        cout << "Internal Marks: "; cin >> internal_marks;
        cout << "University Marks: "; cin >> uni_marks;
    }

    void putData() const {
        cout << "\nRoll No: " << rollno << "\tName: " << name
             << "\nSubject Code: " << subcode << "\tSubject: " << subject
             << "\nInternal: " << internal_marks << "\tUniversity: " << uni_marks << "\n";
    }
};

class File {
    const char *fname = "Records.dat";

public:
    void insert() {
        Record r;
        r.getData();
        ofstream fout(fname, ios::app | ios::binary);
        fout.write(reinterpret_cast<char*>(&r), sizeof(r));
    }

    void display() {
        Record r;
        ifstream fin(fname, ios::binary);
        while (fin.read(reinterpret_cast<char*>(&r), sizeof(r)))
            r.putData();
    }

    void search(int rollno) {
        Record r;
        ifstream fin(fname, ios::binary);
        while (fin.read(reinterpret_cast<char*>(&r), sizeof(r))) {
            if (r.getRollno() == rollno) {
                r.putData();
                return;
            }
        }
        cout << "\nRecord not found.\n";
    }

    bool Delete(int rollno) {
        Record r;
        bool found = false;
        ifstream fin(fname, ios::binary);
        ofstream fout("Temp.dat", ios::binary);
        while (fin.read(reinterpret_cast<char*>(&r), sizeof(r))) {
            if (r.getRollno() == rollno) found = true;
            else fout.write(reinterpret_cast<char*>(&r), sizeof(r));
        }
        fin.close();
        fout.close();
        remove(fname);
        rename("Temp.dat", fname);
        return found;
    }

    bool edit(int rollno) {
        Record r;
        fstream fs(fname, ios::in | ios::out | ios::binary);
        while (fs.read(reinterpret_cast<char*>(&r), sizeof(r))) {
            if (r.getRollno() == rollno) {
                cout << "\nEnter new details:\n";
                r.getData();
                fs.seekp(static_cast<int>(fs.tellg()) - sizeof(r));
                fs.write(reinterpret_cast<char*>(&r), sizeof(r));
                return true;
            }
        }
        return false;
    }
};

int main() {
    File f;
    int choice, roll;

    do {
        cout << "\n--- MENU ---\n1. Insert\n2. Display\n3. Search\n4. Delete\n5. Edit\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: f.insert(); break;
            case 2: f.display(); break;
            case 3: 
                cout << "Enter Roll No: "; 
                cin >> roll; 
                f.search(roll); 
                break;
            case 4: 
                cout << "Enter Roll No to Delete: "; 
                cin >> roll;
                cout << (f.Delete(roll) ? "Deleted.\n" : "Not Found.\n");
                break;
            case 5: 
                cout << "Enter Roll No to Edit: "; 
                cin >> roll;
                cout << (f.edit(roll) ? "Updated.\n" : "Not Found.\n");
                break;
            case 6: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
