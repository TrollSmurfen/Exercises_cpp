#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Item {
protected:
    string title;
    string author;
    int year;
    bool is_borrowed;

public:
    Item(const string& title, const string& author, int year)
        : title(title), author(author), year(year), is_borrowed(false) {}

    virtual void display_info() const = 0; 
    virtual ~Item() = default;

    bool get_is_borrowed() const {
        return is_borrowed;
    }

    void set_is_borrowed(bool status) {
        is_borrowed = status;
    }

    string get_title() const {
        return title;
    }
};
class Book : public Item {
private:
    int pages;

public:
    Book(const string& title, const string& author, int year, int pages)
        : Item(title, author, year), pages(pages) {}

    void display_info() const override {
        cout << "Book: " << title << ", Author: " << author << ", Year: " << year << ", Pages: " << pages << endl;"\n";"\n";
    }
};
class Magazine : public Item {
private:
    string issue;

public:
    Magazine(const string& title, const string& author, int year, const string& issue)
        : Item(title, author, year), issue(issue) {}

    void display_info() const override {
        cout << "Magazine: " << title << ", Author: " << author << ", Year: " << year << ", Issue: " << issue << endl;"\n";"\n";
    }
};
class LibraryUser {
private:
    string name;
    vector<Item*> borrowed_items;

public:
    LibraryUser(const string& name) : name(name) {}

    void borrow(Item* item) {
        borrowed_items.push_back(item);
        item->set_is_borrowed(true);
    }

    void return_item(Item* item) {
        borrowed_items.erase(remove(borrowed_items.begin(), borrowed_items.end(), item), borrowed_items.end());
        item->set_is_borrowed(false);
    }

    void list_borrowed_items() const {
        cout << name << " has borrowed:" << endl;
        for (const auto& item : borrowed_items) {
            item->display_info();
        }
        cout << "\n";
    }

    string get_name() const {
        return name;
    }
};
class Library {
private:
    vector<Item*> items;
    vector<LibraryUser*> users;
    unordered_map<Item*, LibraryUser*> borrowed_items_map;

public:
    void add_item(Item* item) {
        items.push_back(item);
    }

    void remove_item(Item* item) {
        items.erase(remove(items.begin(), items.end(), item), items.end());
    }

    void register_user(LibraryUser* user) {
        users.push_back(user);
    }

    void borrow_item(LibraryUser* user, Item* item) {
        if (!item->get_is_borrowed()) {
            user->borrow(item);
            borrowed_items_map[item] = user;
        } else {
            cout << "Item is already borrowed." << endl;
        }
    }

    void return_item(LibraryUser* user, Item* item) {
        user->return_item(item);
        borrowed_items_map.erase(item);
    }

    void list_items() const {
        cout << "Library items:" << endl;
        for (const auto& item : items) {
            item->display_info();
        }
        cout << "\n";
    }

    void list_available_items_after_borrowing() const {
        cout << "Available items after borrowing: " << endl;
        for (const auto& item : items) {
            if (!item->get_is_borrowed()) {
                item->display_info();
            }
        }
        cout << "\n";
    }
    void list_available_items_after_return() const {
        cout << "Available items after return: " << endl;
        for (const auto& item : items) {
            if (!item->get_is_borrowed ()){
                item->display_info();
            }
        }
        cout << "\n";
    }

    void list_borrowed_items_summary() const {
        cout << "Borrowed items summary:" << endl;
        for (const auto& pair : borrowed_items_map) {
            cout << pair.second->get_name() << " has borrowed: ";
            pair.first->display_info();
        }
        cout << "\n";
    }
};
int main() {
    Library library;
    Book* book1 = new Book("The Gray", "F. Crosswood", 1999, 218);
    Book* book2 = new Book("The Red Moon", "George Orwell", 2002, 328);
    Magazine* magazine1 = new Magazine("Sassy", "Vague", 2022, "November");
    Magazine* magazine2 = new Magazine("The Swedish Times", "Various", 2023, "December");

    library.add_item(book1);
    library.add_item(book2);
    library.add_item(magazine1);
    library.add_item(magazine2);

    LibraryUser* user1 = new LibraryUser("Bella");
    LibraryUser* user2 = new LibraryUser("Andreas");

    library.register_user(user1);
    library.register_user(user2);

    library.list_items();

    library.borrow_item(user1, book1);
    library.borrow_item(user2, magazine1);

    library.list_available_items_after_borrowing();

    user1->list_borrowed_items();
    user2->list_borrowed_items();
    library.list_borrowed_items_summary();

    library.return_item(user1, book1);
    library.return_item(user2, magazine1);

    library.list_available_items_after_return();

    library.list_borrowed_items_summary();

    // Rensa upp dynamiskt allokerat minne
    delete book1;
    delete book2;
    delete magazine1;
    delete magazine2;
    delete user1;
    delete user2;

    return 0;
}
