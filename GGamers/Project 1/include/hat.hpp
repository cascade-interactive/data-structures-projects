#pragma once

#include <iostream>
#include <ostream>

using namespace std;

class Hat {

  private:
    // Member variables
    int m_id;
    string m_color;
    string m_brand;
    int m_coolness_level;

  public:
    // Hat Constructor
    Hat(string Color, string Brand, int Coolness_level, int id_num = 0);

    // Setters
    int set_id(int id_num);
    void set_coolness_level(int coolness_level);
    // Getters
    int get_id() const;
    string get_color() const;
    string get_brand() const;
    int get_coolness_level() const;

    bool operator==(const Hat &other) const;

    friend ostream &operator<<(ostream &output, const Hat &hat);
};