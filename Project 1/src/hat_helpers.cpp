#include <iostream>
#include <limits>
#include <string>

#include "hat_helpers.hpp"
#include "terminal_ui.hpp"

using namespace std;

namespace {

bool read_text(const string& label, string& value) {
    TerminalUi::prompt(label);
    return static_cast<bool>(getline(cin >> ws, value));
}

void display_hat_card(const Hat& hat) {
    TerminalUi::card(
        "HAT #" + to_string(hat.get_id()),
        "Color     " + hat.get_color(),
        "Brand     " + hat.get_brand(),
        "Coolness  " + to_string(hat.get_coolness_level()) + " / 10");
}

template <typename Predicate>
size_t display_matches(const CircularList<Hat>& collection, Predicate is_match) {
    size_t match_count = 0;
    collection.for_each([&](const Hat& hat) {
        if (is_match(hat)) {
            display_hat_card(hat);
            ++match_count;
        }
    });
    return match_count;
}

} // namespace

bool read_integer(const string& prompt, int& value) {
    while (true) {
        TerminalUi::prompt(prompt);

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
        if (cin.eof()) {
            return false;
        }

        cin.clear();
        string discarded;
        getline(cin, discarded);
        TerminalUi::error("Please enter a whole number.");
    }
}

void display_hat_collection(const CircularList<Hat>& hat_collection) {
    TerminalUi::title("COLLECTION", "Your saved hats, displayed as cards.");
    TerminalUi::section("COLLECTION  " + to_string(hat_collection.count()) + " HAT(S)");

    if (hat_collection.count() == 0) {
        TerminalUi::warning("Your collection is empty. Add a hat to get started.");
        return;
    }

    hat_collection.for_each([](const Hat& hat) { display_hat_card(hat); });
}

void prompt_hat_search(const CircularList<Hat>& hat_collection) {
    TerminalUi::title("SEARCH", "Find hats by an exact detail.");
    TerminalUi::section("SEARCH FIELD");
    TerminalUi::menu_item(1, "ID", "Find one specific hat");
    TerminalUi::menu_item(2, "COLOR", "Match a color exactly");
    TerminalUi::menu_item(3, "BRAND", "Match a brand exactly");
    TerminalUi::menu_item(4, "COOLNESS", "Match a rating exactly");

    int field_choice;
    while (true) {
        if (!read_integer("Choose a field [1-4]: ", field_choice)) {
            return;
        }
        if (field_choice >= 1 && field_choice <= 4) {
            break;
        }
        TerminalUi::error("Choose a number from 1 through 4.");
    }

    size_t match_count = 0;
    switch (field_choice) {
        case 1: {
            int id;
            if (!read_integer("Hat ID: ", id)) return;
            match_count = display_matches(hat_collection,
                [id](const Hat& hat) { return hat.get_id() == id; });
            break;
        }
        case 2: {
            string color;
            if (!read_text("Color: ", color)) return;
            match_count = display_matches(hat_collection,
                [&color](const Hat& hat) { return hat.get_color() == color; });
            break;
        }
        case 3: {
            string brand;
            if (!read_text("Brand: ", brand)) return;
            match_count = display_matches(hat_collection,
                [&brand](const Hat& hat) { return hat.get_brand() == brand; });
            break;
        }
        case 4: {
            int coolness_level;
            if (!read_integer("Coolness level: ", coolness_level)) return;
            match_count = display_matches(hat_collection, [coolness_level](const Hat& hat) {
                return hat.get_coolness_level() == coolness_level;
            });
            break;
        }
    }

    TerminalUi::section("RESULT");
    if (match_count == 0) {
        TerminalUi::warning("No hats matched that search.");
    } else {
        TerminalUi::status("Found " + to_string(match_count)
            + (match_count == 1 ? " matching hat." : " matching hats."));
    }
}

void add_hats(CircularList<Hat>& hat_collection, int& next_id) {
    TerminalUi::title("ADD HATS", "Add one or more hats to the vault.");

    int count = 0;
    if (!read_integer("How many hats would you like to add? ", count)) {
        return;
    }
    if (count <= 0) {
        TerminalUi::warning("Nothing was added.");
        return;
    }

    for (int i = 0; i < count; ++i) {
        TerminalUi::section("HAT " + to_string(i + 1) + " OF " + to_string(count));

        string color;
        if (!read_text("Color: ", color)) return;

        string brand;
        if (!read_text("Brand: ", brand)) return;

        int coolness_level;
        if (!read_integer("Coolness level [0-10]: ", coolness_level)) return;

        hat_collection.insert(Hat(color, brand, coolness_level, next_id++));
    }

    TerminalUi::status("Added " + to_string(count) + (count == 1 ? " hat." : " hats."));
}

HatCarousel::HatCarousel(CircularList<Hat>& collection)
    : hat_collection(collection), index(0) {
}

void HatCarousel::run(size_t count) {
    index = 0;
    if (hat_collection.count() == 0) {
        TerminalUi::title("BROWSE", "Move through your collection one hat at a time.");
        TerminalUi::warning("There are no hats to browse yet.");
        TerminalUi::pause();
        return;
    }

    while (true) {
        TerminalUi::title("BROWSE", "Use the controls below to move through your collection.");
        TerminalUi::section("HAT " + to_string(index + 1) + " OF " + to_string(count));
        display_current();
        TerminalUi::section("NAVIGATION");
        TerminalUi::menu_item(1, "PREVIOUS", "Move left");
        TerminalUi::menu_item(2, "NEXT", "Move right");
        TerminalUi::menu_item(3, "RETURN", "Back to dashboard");

        int choice;
        if (!read_integer("Choose an action [1-3]: ", choice) || choice == 3) {
            return;
        }
        if (choice == 1) {
            previous();
        } else if (choice == 2) {
            next();
        } else {
            TerminalUi::error("Choose a number from 1 through 3.");
            TerminalUi::pause();
        }
    }
}

void HatCarousel::next() {
    index = (index + 1) % static_cast<int>(hat_collection.count());
}

void HatCarousel::previous() {
    index = (index + static_cast<int>(hat_collection.count()) - 1)
        % static_cast<int>(hat_collection.count());
}

void HatCarousel::display_current() {
    display_hat_card(hat_collection.get(index));
}
