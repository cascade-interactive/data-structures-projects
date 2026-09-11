#include <iostream>
#include <string>

#include "hat_helpers.hpp"
#include "terminal_ui.hpp"

using namespace std;

namespace {

void show_dashboard(size_t hat_count) {
    TerminalUi::title("DASHBOARD", "A quiet place for a well-organized hat collection.");
    TerminalUi::row("Collection status: " + to_string(hat_count)
        + (hat_count == 1 ? " hat saved" : " hats saved"));
    TerminalUi::border();

    TerminalUi::section("COMMAND PALETTE");
    TerminalUi::menu_item(1, "ADD HATS", "Add one or more hats");
    TerminalUi::menu_item(2, "VIEW COLLECTION", "See every saved hat");
    TerminalUi::menu_item(3, "SEARCH", "Find a hat by its details");
    TerminalUi::menu_item(4, "REMOVE", "Remove one matching hat");
    TerminalUi::menu_item(5, "BROWSE", "Move through hats one at a time");
    TerminalUi::menu_item(6, "EXIT", "Close Hat Vault");
    TerminalUi::section("TIP");
    cout << TerminalUi::dim()
         << "  Every screen is keyboard-driven. Enter the number in brackets to continue."
         << TerminalUi::reset() << '\n';
}

void remove_hat(CircularList<Hat>& hat_collection) {
    TerminalUi::title("REMOVE HAT", "Remove a hat by its color, brand, and coolness level.");
    TerminalUi::section("HAT DETAILS");

    string color;
    TerminalUi::prompt("Color: ");
    if (!getline(cin >> ws, color)) return;

    string brand;
    TerminalUi::prompt("Brand: ");
    if (!getline(cin >> ws, brand)) return;

    int coolness_level;
    if (!read_integer("Coolness level [0-10]: ", coolness_level)) return;

    if (hat_collection.remove(Hat(color, brand, coolness_level))) {
        TerminalUi::status("Hat removed from the collection.");
    } else {
        TerminalUi::warning("No hat matched those details. Nothing was removed.");
    }
}

} // namespace

int main() {
    CircularList<Hat> hat_collection;
    HatCarousel carousel(hat_collection);
    int next_id = 1;
    bool running = true;

    while (running) {
        show_dashboard(hat_collection.count());

        int choice;
        if (!read_integer("Select a command [1-6]: ", choice)) {
            break;
        }

        switch (choice) {
            case 1:
                add_hats(hat_collection, next_id);
                if (!TerminalUi::pause()) running = false;
                break;
            case 2:
                display_hat_collection(hat_collection);
                if (!TerminalUi::pause()) running = false;
                break;
            case 3:
                prompt_hat_search(hat_collection);
                if (!TerminalUi::pause()) running = false;
                break;
            case 4:
                remove_hat(hat_collection);
                if (!TerminalUi::pause()) running = false;
                break;
            case 5:
                carousel.run(hat_collection.count());
                break;
            case 6:
                running = false;
                break;
            default:
                TerminalUi::error("Choose a command from 1 through 6.");
                if (!TerminalUi::pause()) running = false;
                break;
        }
    }

    TerminalUi::title("SESSION CLOSED", "Your collection is kept in memory until the program ends.");
    TerminalUi::status("Thanks for using Hat Vault.");
    return 0;
}
