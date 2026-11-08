#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Class that stores all the information about the book 
class Book {
    
private:
// These members are private so they can only be changed by the class methods
    string title;
    string author;
    int pages;
    string id;
    bool borrowed;

public:
// Constructor runs automatically when a new Book object is created
//
    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

   // Getter methods allow the rest of the program to read the private data
    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getPages() { return pages; }
    string getId() { return id; }
    bool isBorrowed() { return borrowed; }

    // Borrow / Return
    void borrowBook() {
        if (borrowed) {
            cout << "Sorry, \"" << title << "\" is already borrowed." << endl;
        } else {
            borrowed = true;
            cout << "You have borrowed \"" << title << "\"." << endl;
        }
    }
      void returnBook() {
        if (!borrowed) {
            cout << "\"" << title << "\" is not currently borrowed." << endl;
        } else {
            borrowed = false;
            cout << "Thank you for returning \"" << title << "\"." << endl;
        }
    }

    // Shows short information about the book
    void showShort() {
        cout << id << "  " << title << "  by " << author
             << "  (" << (borrowed ? "Borrowed" : "Available") << ")" << endl;
    }

    // Shows full information about the book
    void showFull() {
        cout << endl;
        cout << "Title  : " << title << endl;
        cout << "Author : " << author << endl;
        cout << "Pages  : " << pages << endl;
        cout << "ID     : " << id << endl;
        cout << "Status : " << (borrowed ? "Borrowed" : "Available") << endl;
        cout << endl;
    }
};

// Load books from the text file
vector<Book> loadBooks(string filename) {
    vector<Book> books;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open the book file" << endl;
        return books;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        stringstream ss(line);
        string title, author, pagesText, id, statusText;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pagesText, ',');
        getline(ss, id, ',');
        getline(ss, statusText, ',');

        // Remove possible spaces from the ID and status
        while (!id.empty() && id[0] == ' ') id.erase(0, 1);
        while (!statusText.empty() && statusText[0] == ' ') statusText.erase(0, 1);

        try {
            int pages = stoi(pagesText);
            bool isBorrowed = (statusText == "true");

            books.push_back(Book(title, author, pages, id, isBorrowed));
        }
        catch (...) {
            cout << "Skipping a bad line in the file..." << endl;
        }
    }
    file.close();
    return books;
}

// Outputs the main menu
void showMenu() {
    cout << endl;
    cout << "1. View all books" << endl;
    cout << "2. View one book" << endl;
    cout << "3. Borrow a book" << endl;
    cout << "4. Return a book" << endl;
    cout << "5. Add a new book" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

// Main function
int main() {
    vector<Book> library = loadBooks("bookData.txt");

    if (library.empty()) {
        cout << "No books were loaded." << endl;
        return 1;
    }

    cout << "Library Manager" << endl;
    cout << library.size() << " books loaded." << endl;

    int choice;
    string inputId;

    do {
        showMenu();
        // Idiot proofing the input to make sure the user enters a number
    while (!(cin >> choice)) {
        cin.clear();                 // clear the error
        cin.ignore(1000, '\n');      // throw away the bad input
        cout << "Please enter a number: ";
    }
    cin.ignore();   // clear the leftover Enter key

        if (choice == 1) {
            cout << endl;
            for (auto& book : library) {
                book.showShort();
            }
        }
        else if (choice == 2) {
            cout << "Enter book ID: ";
            getline(cin, inputId);

            bool found = false;
            try {
                int searchId = stoi(inputId);
                for (auto& book : library) {
                    if (stoi(book.getId()) == searchId) {
                        book.showFull();
                        found = true;
                        break;
                    }
                }
            }
            catch (...) {
                // Error if user typed something that is not a number
            }
            if (!found) cout << "Book not found." << endl;
        }
        else if (choice == 3) {
            cout << "Enter book ID to borrow: ";
            getline(cin, inputId);

            bool found = false;
            try {
                int searchId = stoi(inputId);
                for (auto& book : library) {
                    if (stoi(book.getId()) == searchId) {
                        book.borrowBook();
                        found = true;
                        break;
                    }
                }
            }
            catch (...) {
                // user typed something that is not a number
            }
            if (!found) cout << "Book not found." << endl;
        }
        else if (choice == 4) {
            cout << "Enter book ID to return: ";
            getline(cin, inputId);

            bool found = false;
            try {
                int searchId = stoi(inputId);
                for (auto& book : library) {
                    if (stoi(book.getId()) == searchId) {
                        book.returnBook();
                        found = true;
                        break;
                    }
                }
            }
            catch (...) {
                // user typed something that is not a number
            }
            if (!found) cout << "Book not found." << endl;
        }
        else if (choice == 5) {
            // Add a new book
            string newTitle, newAuthor, newId;
            int newPages;

            cout << "Enter title: ";
            getline(cin, newTitle);

            cout << "Enter author: ";
            getline(cin, newAuthor);

            cout << "Enter number of pages: ";
            cin >> newPages;
            cin.ignore();

            cout << "Enter ID (e.g. 013): ";
            getline(cin, newId);

            // Create the new book (starts as available)
            library.push_back(Book(newTitle, newAuthor, newPages, newId, false));
            cout << "Book added successfully!" << endl;
        }
        else if (choice == 6) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Please choose a number between 1 and 6." << endl;
        }

    } while (choice != 6);

    return 0;
}