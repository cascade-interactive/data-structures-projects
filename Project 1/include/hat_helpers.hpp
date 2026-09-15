#pragma once

#include <iostream>
#include <string>

using namespace std;

#include "circularlinkedlist.hpp"
#include "hat.hpp"

// Helper file for the hat collection manager program. It contains functions for reading integers, searching for hats, adding hats, and capitalizing strings. It also contains the HatCarousel class for browsing through the hat collection.
bool read_integer(const std::string& prompt, int& value);
void prompt_hat_search(const CircularList<Hat>& hat_collection);
void add_hats(CircularList<Hat>& hat_collection, int& next_id);
void capitalize(std::string& str);

class HatCarousel {
    private:
        CircularList<Hat>& hat_collection;
        int index;
    
    public:
        explicit HatCarousel(CircularList<Hat>& collection);

        void run(size_t count);
        void next();
        void previous();
        void display_current();
};