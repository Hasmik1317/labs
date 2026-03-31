#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    // Տեքստի գույներով ցուցադրում (անհրաժեշտության դեպքում)
    static void printColor(const std::string& text, const std::string& color);

    // Ժամանակի ստացում տողային ֆորմատով
    static std::string getCurrentTime();

    // Տողի տոկենավորում
    static std::vector<std::string> split(const std::string& str, char delimiter);

    // Մաքրել էկրանը
    static void clearScreen();

    // Սպասել ստեղնաշարի սեղմման
    static void pressAnyKey();

    // Տեքստի կենտրոնացում
    static std::string center(const std::string& text, int width);

    // Ստանալ օգտագործողի մուտքագրումը
    static std::string getUserInput(const std::string& prompt);

    // Ստանալ գաղտնաբառ (առանց էկրանին ցուցադրելու)
    static std::string getPassword(const std::string& prompt);
};

// Գույների սահմանում (եթե աջակցվում է)
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

#endif
