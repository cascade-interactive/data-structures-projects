#include "hat.hpp"

// Constructor for initializing a hat's information
Hat::Hat(std::string color, std::string brand, int coolness_level, int id_num) {
    m_id = id_num;
    m_color = color;
    m_brand = brand;
    m_coolness_level = coolness_level;
}

// Set the coolness level for the hat
void Hat::set_coolness_level(int coolness_level) {
    m_coolness_level = coolness_level;
}

// Set the ID for the hat
int Hat::set_id(int id_num) {
    m_id = id_num;
    return m_id;
}

// Get the coolness level for the hat
int Hat::get_coolness_level() const { return m_coolness_level; }

// Get the ID for the hat
int Hat::get_id() const { return m_id; }

// Get the color for the hat
std::string Hat::get_color() const { return m_color; }

// Get the brand for the hat
std::string Hat::get_brand() const { return m_brand; }

// Compare two hats by color, brand, and coolness level
bool Hat::operator==(const Hat &other) const {
    return m_color == other.m_color && m_brand == other.m_brand &&
           m_coolness_level == other.m_coolness_level;
}

// Display the hat's information in the output stream
std::ostream &operator<<(std::ostream &output, const Hat &hat) {
    output << "\nHat ID: " << hat.m_id << '\n'
           << "Color: " << hat.m_color << '\n'
           << "Brand: " << hat.m_brand << '\n'
           << "Coolness level: " << hat.m_coolness_level;

    return output;
}
