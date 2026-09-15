#include <iostream>
#include <string>
#include <cctype>

#include "hat_helpers.hpp"

using namespace std;

// Helper function to double check user entered an integer and not something else
bool read_integer(const string& prompt, int& value) {

    // Keep repeating until return exits the function
    while (true) {

        // Print the question
        cout << prompt;

        if (cin >> value) {
            return true;
        }
        
        if (cin.eof()) {
            return false;
        }
        
        /* Input has failed */
        cout << "Invalid input. Please enter a whole number.\n";   
        /* Reset cin's error state to read again */
        cin.clear();    

        // Discard rest of the line
        string discarded;
        getline(cin, discarded);
    }
}

// Function for searching for hats in the collection by prompting the user for a search field and then asking for the value to search for. It will then call the search function on the hat collection and display the results.
void prompt_hat_search(const CircularList<Hat>& hat_collection) {

    int field_choice;

    while (true) {
           cout << "\nSearch Hats\n"
               << "-----------\n"
               << "Search by:\n"
             << "1. ID\n"
             << "2. Color\n"
             << "3. Brand\n"
             << "4. Coolness level\n";

        if (!read_integer("Select a search field (1-4): ", field_choice)) {
            return;
        }

        if (field_choice >= 1 && field_choice <= 4) {
            break;
        }

        cout << "Invalid selection. Please choose an option from 1 through 4.\n";
    }

    size_t match_count = 0;

    switch (field_choice) {
        case 1: {
            int id;
            if (!read_integer("Enter the hat ID: ", id)) {
                return;
            }
                cout << "\nSearch Results\n";
                cout << "--------------\n";
            match_count = hat_collection.search(
                [id](const Hat& hat) { return hat.get_id() == id; });
                cout << "--------------\n" << endl;
            break;
        }
        case 2: {
            string color;
                cout << "Enter a hat color: ";
            getline(cin >> ws, color);
			capitalize(color);
                cout << "\nSearch Results\n";
                cout << "--------------\n";
            match_count = hat_collection.search(
                [&color](const Hat& hat) { return hat.get_color() == color; });
                cout << "--------------\n" << endl;
            break;
        }
        case 3: {
            string brand;
                cout << "Enter a hat brand: ";
            getline(cin >> ws, brand);
			capitalize(brand);
                cout << "\nSearch Results\n";
                cout << "--------------\n";
            match_count = hat_collection.search(
                [&brand](const Hat& hat) { return hat.get_brand() == brand; });
                cout << "--------------\n" << endl;
            break;
        }
        case 4: {
            int coolness_level;
            if (!read_integer("Enter the coolness level: ", coolness_level)) {
                return;
            }
                cout << "\nSearch Results\n";
                cout << "--------------\n";
            match_count = hat_collection.search(
                [coolness_level](const Hat& hat) {
                    return hat.get_coolness_level() == coolness_level;
                });
                cout << "--------------\n" << endl;
            break;
        }
    }

    if (match_count == 0) {
            cout << "No hats matched your search.\n" << endl;
    } else {
            cout << "Found " << match_count
                 << (match_count == 1 ? " matching hat." : " matching hats.") << endl;
    }
}

// Function for adding hats to the collection by asking the user for the amount of hats and then prompting them for the color, brand, and coolness for each. It will then insert the hat into the collection and increment the next_id for the next hat to be added.
void add_hats(CircularList<Hat>& hat_collection, int& next_id) {

    int count = 0;

    if (!read_integer("How many hats would you like to add? ", count) || count <= 0) {
        cout << "No hats were added.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "\nAdding Hat " << next_id << "\n";

        cout << "Color: ";
        string color;
        if (!getline(cin >> ws, color)) {
            return;
        }
        capitalize(color);

        cout << "Brand: ";
        string brand;
        if (!getline(cin >> ws, brand)) {
            return;
        }
        capitalize(brand);

        int coolness_level;
        if (!read_integer("Coolness level: ", coolness_level)) {
            return;
        }

        Hat new_hat(color, brand, coolness_level, next_id++);
        hat_collection.insert(new_hat);
    }
    cout << "\nAdded " << count << (count == 1 ? " hat." : " hats.") << endl;
}

// Function that will capitalize the first letter of a string and make the rest lowercase mainly used for formatting for the color and brand
void capitalize(string& str) {
	if (str.empty()) {
		return;
	}
    // Type cast the char to unsigned to avoid any unwanted behavior
    str[0] = toupper(static_cast<unsigned char>(str[0]));

    for (size_t i = 1; i < str.length(); i++) {
        str[i] = tolower(static_cast<unsigned char>(str[i]));
    }
}

// The functions for the hat carousel class
HatCarousel::HatCarousel(CircularList<Hat>& collection)
    : hat_collection(collection), index(0) {
}

// A carousel for the hats that allows the user to view the hats in the collection and move through the linked list with the next and previous options. It will display the current hat and the total number of hats in the collection.
void HatCarousel::run(size_t count) {
    index = 0;
    if (hat_collection.count() == 0) {
        cout << "There are no hats to display.\n";
        return;
    }
    cout << "Hat Carousel" << endl;
    cout << "------------" << endl;
    cout << "Viewing hat 1 of " << count << ":" << endl;
    display_current();
    cout << "\nOptions:" << endl;
    cout << "1. Previous hat" << endl;
    cout << "2. Next hat" << endl;
    cout << "3. Return to main menu" << endl;
    
    int choice;
    do {
    if (!read_integer("\nSelect an option (1-3): ", choice)) {
    break; }
    switch(choice) {
        case 1: 
            previous();
            break;
        case 2: 
            next();
            break;
        case 3:
            cout << "Returning to the main menu." << endl;
            break;

        default:
            cout << "Invalid selection. Please choose an option from 1 through 3.\n";
            break;
    }
    } while (choice != 3);
}

void HatCarousel::next() {
    index = (index + 1) % hat_collection.count();
    display_current();
}

void HatCarousel::previous() {
    index = (index + hat_collection.count() - 1) % hat_collection.count();
    display_current();
}

void HatCarousel::display_current() {
    cout << hat_collection.get(index) << endl;
}
