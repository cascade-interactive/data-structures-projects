#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

namespace TerminalUi {

constexpr std::size_t kInnerWidth = 70;

inline bool use_color() {
    return std::getenv("NO_COLOR") == nullptr;
}

inline const char* cyan() { return use_color() ? "\033[36m" : ""; }
inline const char* green() { return use_color() ? "\033[32m" : ""; }
inline const char* yellow() { return use_color() ? "\033[33m" : ""; }
inline const char* red() { return use_color() ? "\033[31m" : ""; }
inline const char* dim() { return use_color() ? "\033[2m" : ""; }
inline const char* bold() { return use_color() ? "\033[1m" : ""; }
inline const char* reset() { return use_color() ? "\033[0m" : ""; }

inline std::string fit(std::string text, std::size_t width = kInnerWidth) {
    if (text.size() > width) {
        text.resize(width > 3 ? width - 3 : width);
        if (width > 3) {
            text += "...";
        }
    }
    text.append(width - text.size(), ' ');
    return text;
}

inline void clear() {
    std::cout << "\033[2J\033[H";
}

inline void border(char fill = '-') {
    std::cout << dim() << '+' << std::string(kInnerWidth + 2, fill) << '+' << reset() << '\n';
}

inline void row(const std::string& text = "") {
    std::cout << dim() << '|' << reset() << ' ' << fit(text) << ' '
              << dim() << '|' << reset() << '\n';
}

inline void title(const std::string& name, const std::string& subtitle = "") {
    clear();
    border('=');
    std::cout << dim() << '|' << reset() << ' ' << bold() << cyan()
              << fit("HAT VAULT  ::  " + name) << reset() << ' '
              << dim() << '|' << reset() << '\n';
    if (!subtitle.empty()) {
        row(subtitle);
    }
    border('=');
}

inline void section(const std::string& label) {
    std::cout << '\n' << bold() << cyan() << "-- " << label << " "
              << std::string(kInnerWidth > label.size() + 4 ? kInnerWidth - label.size() - 4 : 1, '-')
              << reset() << '\n';
}

inline void menu_item(int key, const std::string& label, const std::string& hint) {
    std::cout << "  " << bold() << yellow() << '[' << key << ']' << reset() << ' '
              << bold() << label << reset();
    if (!hint.empty()) {
        std::cout << dim() << "  " << hint << reset();
    }
    std::cout << '\n';
}

inline void card(const std::string& heading, const std::string& line_one,
                 const std::string& line_two, const std::string& line_three) {
    border();
    row(heading);
    border();
    row(line_one);
    row(line_two);
    row(line_three);
    border();
}

inline void status(const std::string& text) {
    std::cout << '\n' << green() << "[ok] " << reset() << text << '\n';
}

inline void warning(const std::string& text) {
    std::cout << '\n' << yellow() << "[!] " << reset() << text << '\n';
}

inline void error(const std::string& text) {
    std::cout << '\n' << red() << "[x] " << reset() << text << '\n';
}

inline void prompt(const std::string& text) {
    std::cout << '\n' << bold() << cyan() << "> " << reset() << text;
}

inline bool pause() {
    prompt("Press Enter to return to the dashboard...");
    std::string line;
    return static_cast<bool>(std::getline(std::cin, line));
}

} // namespace TerminalUi
