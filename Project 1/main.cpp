#include <iostream>
#include <limits>
// #include "CircularLinkedList.hpp"

using namespace std;

class Hat {
private:
    int id;
    string color;
    string brand;
    int coolness_level;
public:
    Hat(string Color, string Brand, int Coolness_level, int id_num = 0) {
        id = id_num;
        color = Color;
        brand = Brand;
        coolness_level = Coolness_level;
    };
    void set_coolness_level(int coolness_level);
    int get_coolness_level() const {return coolness_level;};
    int set_id(int id_num);
    int get_id() const {return id;};
    string get_color() const {return color;};
    string get_brand() const {return brand;};
    // operator overloading
    bool operator==(const Hat& other) const {
        // essentially, this operator field tells the compiler how to compare values
        // of different objects.
        // "When someone compares a Hat object1 to Hat object2,
        // consider them equal when these two particular variables have the same value."
        return color == other.color
            && brand == other.brand
            && coolness_level == other.coolness_level;
    }
    // since values of hat are private, we use friend to allow us to retrieve values within that field
    friend ostream& operator<<(ostream& output, const Hat& hat) {
        output << "Hat ID: " << hat.id << '\n'
               << "Color: " << hat.color << '\n'
               << "Brand: " << hat.brand << '\n'
               << "Coolness level: " << hat.coolness_level;
        return output;
    }


};

template <typename T>
class Node
{
private:
    struct ListNode {
        T value;
        ListNode* next;

        explicit ListNode(const T& value) : value(value), next(nullptr) {}
    };

    ListNode* head = nullptr;
public:
    Node() = default;

    // destructor, calls delete on each node in the list
    ~Node() {
        if (head == nullptr) {
            return;
        }

        ListNode* current = head->next;
        while (current != head) {
            ListNode* next_node = current->next;
            delete current;
            current = next_node;
        }
        delete head;
    }

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;


    // insert address of typedef T hat
    void insert(const T& hat) {
        // create new node
        ListNode* new_node = new ListNode(hat);

        // of the list is empty, insert the new node at the head
        if (head == nullptr) {
            head = new_node;
            new_node->next = head;
            return;
        }

        // traverse the list and find the end of the list
        ListNode* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }

        // insert the new node at the end of the list then attach it to the head.
        tail->next = new_node;
        new_node->next = head;
    }

    void remove(const T& hat) {
        if (head == nullptr) {
            return;
        }

        // Start previous at the tail so removing the head works correctly.
        ListNode* previous = head;
        while (previous->next != head) {
            previous = previous->next;
        }

        ListNode* current = head;
        // single entry list edge-case
        do {
            if (current->value == hat) {
                // The only node in the list points to itself.
                if (current->next == current) {
                    head = nullptr;
                } else {
                    previous->next = current->next;

                    if (current == head) {
                        head = current->next;
                    }
                }

                delete current;
                return;
            }
            // traverse the list until you find the hat to remove
            previous = current;
            current = current->next;
        } while (current != head);
    }

    void display() const {
        // empty list edge-case
        if (head == nullptr) {
            cout << "The hat collection is empty." << endl;
            return;
        }

        const ListNode* current = head;
        do {
            cout << current->value << endl;
            current = current->next;
        } while (current != head);
    }
    //
    template <typename Predicate>
    size_t search(Predicate is_match) const {
        if (head == nullptr) {
            return 0;
        }

        size_t match_count = 0;
        const ListNode* current = head;
        do {
            if (is_match(current->value)) {
                cout << current->value << "\n\n";
                ++match_count;
            }
            current = current->next;
        } while (current != head);

        return match_count;
    }
};
// help function to double check use enter an integer and not something else
bool read_integer(const string& prompt, int& value) {
    while (true) {
        cout << prompt;

        if (cin >> value) {
            return true;
        }

        if (cin.eof()) {
            return false;
        }

        cout << "Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void prompt_hat_search(const Node<Hat>& hat_collection) {
    int field_choice;

    while (true) {
        cout << "\nSearch hats by:\n"
             << "1. ID\n"
             << "2. Color\n"
             << "3. Brand\n"
             << "4. Coolness level\n";

        if (!read_integer("Enter your choice (1-4): ", field_choice)) {
            return;
        }

        if (field_choice >= 1 && field_choice <= 4) {
            break;
        }

        cout << "Please choose a number from 1 through 4.\n";
    }

    size_t match_count = 0;

    switch (field_choice) {
        case 1: {
            int id;
            if (!read_integer("Enter the hat ID: ", id)) {
                return;
            }
            cout << "\nSearch results:\n";
            match_count = hat_collection.search(
                [id](const Hat& hat) { return hat.get_id() == id; });
            break;
        }
        case 2: {
            string color;
            cout << "Enter the hat color: ";
            getline(cin >> ws, color);
            cout << "\nSearch results:\n";
            match_count = hat_collection.search(
                [&color](const Hat& hat) { return hat.get_color() == color; });
            break;
        }
        case 3: {
            string brand;
            cout << "Enter the hat brand: ";
            getline(cin >> ws, brand);
            cout << "\nSearch results:\n";
            match_count = hat_collection.search(
                [&brand](const Hat& hat) { return hat.get_brand() == brand; });
            break;
        }
        case 4: {
            int coolness_level;
            if (!read_integer("Enter the coolness level: ", coolness_level)) {
                return;
            }
            cout << "\nSearch results:\n";
            match_count = hat_collection.search(
                [coolness_level](const Hat& hat) {
                    return hat.get_coolness_level() == coolness_level;
                });
            break;
        }
    }

    if (match_count == 0) {
        cout << "No matching hats found.\n";
    } else {
        cout << match_count << (match_count == 1 ? " match found.\n" : " matches found.\n");
    }
}

int main() {
// hat collection
    Node<Hat> hat_collection;

    cout << "Welcome to the hat collection simulator. \nEnter the amount of hats you have:";
    int hat_amount;
    cin >> hat_amount;
    for (int i = 0; i < hat_amount; i++) {

        cout << "Editing hat " << i + 1 << " \nEnter the hat color:";
        string hat_color;
        getline(cin >> ws, hat_color);
        cout << "Enter the hat brand:";
        string hat_brand;
        getline(cin >> ws, hat_brand);
        cout << "Enter the hat coolness level:";
        int hat_coolness_level;
        cin >> hat_coolness_level;
        Hat hat(hat_color, hat_brand, hat_coolness_level, i + 1);
        hat_collection.insert(hat);

    }

    hat_collection.display();
    prompt_hat_search(hat_collection);

    return 0;
}
