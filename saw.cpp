#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct Book {
    string title;
    string author;
    string status;
};

vector<Book> books;

// Load data from file
void loadData() {
    ifstream file("library.txt");
    Book b;
    while(getline(file, b.title)) {
        getline(file, b.author);
        getline(file, b.status);
        books.push_back(b);
    }
    file.close();
}

// Save data to file
void saveData() {
    ofstream file("library.txt");
    for(auto &b : books) {
        file << b.title << endl;
        file << b.author << endl;
        file << b.status << endl;
    }
    file.close();
}

// Add Book
void addBook() {
    Book b;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    b.status = "Available";

    books.push_back(b);
    saveData();

    cout << "Book Added Successfully!\n";
}

// View Books
void viewBooks() {
    if(books.empty()) {
        cout << "No Books Available!\n";
        return;
    }

    cout << "\n--- Library Books ---\n";
    for(int i=0;i<books.size();i++) {
        cout << i+1 << ". " << books[i].title 
             << " | " << books[i].author 
             << " | " << books[i].status << endl;
    }
}

// Search Book
void searchBook() {
    cin.ignore();
    string key;
    cout << "Enter title to search: ";
    getline(cin, key);

    for(auto &b : books) {
        if(b.title.find(key) != string::npos) {
            cout << "Found: " << b.title << " | " << b.author << " | " << b.status << endl;
            return;
        }
    }
    cout << "Book not found!\n";
}

// Issue Book
void issueBook() {
    viewBooks();
    int n;
    cout << "Enter book number: ";
    cin >> n;

    if(n > 0 && n <= books.size()) {
        books[n-1].status = "Issued";
        saveData();
        cout << "Book Issued!\n";
    }
}

// Return Book
void returnBook() {
    viewBooks();
    int n;
    cout << "Enter book number: ";
    cin >> n;

    if(n > 0 && n <= books.size()) {
        books[n-1].status = "Available";
        saveData();
        cout << "Book Returned!\n";
    }
}

// Delete Book
void deleteBook() {
    viewBooks();
    int n;
    cout << "Enter book number to delete: ";
    cin >> n;

    if(n > 0 && n <= books.size()) {
        books.erase(books.begin() + (n-1));
        saveData();
        cout << "Book Deleted!\n";
    }
}

int main() {
    loadData();

    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: deleteBook(); break;
            case 7: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while(choice != 7);

    return 0;
}
