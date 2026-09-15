#include <iostream>
#include <string>
#include "hat_helpers.hpp"

using namespace std;

int main() {
    // hat collection
    CircularList<Hat> hat_collection;
    // hat carousel
    HatCarousel carousel(hat_collection);

    int next_id = 1;
    int choice = 0;

    cout << "Hat Collection Manager" << endl;
    cout << "======================" << endl;
	// Loop for allowing the user to add, remove, search, and display hats in the collection
    do {
        cout << "\nMain Menu\n"
            << "---------\n"
            << "1. Add hats\n"
            << "2. Display all hats\n"
            << "3. Search hats\n"
            << "4. Remove a hat\n"
            << "5. Browse hats\n"
            << "6. Exit\n";

        if (!read_integer("Select an option: ", choice)) {
			break;
        }
        switch (choice) {
        case 1:
            add_hats(hat_collection, next_id);
            break;

        case 2:
            cout << "\nHat Collection\n";
            cout << "--------------" << endl;
            hat_collection.display();
            break;

        case 3:
            prompt_hat_search(hat_collection);
            break;

        case 4: {
            cout << "\nRemove a Hat\n";
            cout << "------------\n";
            cout << "Enter the hat details.\n";
            cout << "Color: ";
            string color;
            if (!getline(cin >> ws, color)) {
                return 0;
            }
            capitalize(color);

            cout << "Brand: ";
            string brand;
            if (!getline(cin >> ws, brand)) {
                return 0;
            }
            capitalize(brand);

			int coolness_level;
			if (!read_integer("Coolness level: ", coolness_level)) {
                return 0;
            }

			Hat target_hat(color, brand, coolness_level);
            // Make use of bool to return true or false if the hat was found and removed
			bool find_hat = hat_collection.remove(target_hat);
            if (!find_hat) {
                cout << "------------\nHat not found under specified parameters.\n------------\n";
                break;
            }
            cout << "------------\nHat removal completed.\n------------\n";
            break;
            }

        case 5:
            // Clear the terminal
            std::cout << "\033[2J\033[H\n\n\n" << std::flush;
    
            // Run the carousel
            carousel.run(hat_collection.count());
            break;


        case 6:
            cout << "Exiting Hat Collection Manager.\n";
            break;
            
        default:
            cout << "Invalid selection. Please choose one of the listed options.\n";
            break;
        }
    } while (choice != 6);

    return 0;
}
