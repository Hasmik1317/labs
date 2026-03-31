#include <iostream>
#include <string>
#include <cctype>

// ------------------- RLE ENCODE (Այս մասը ճիշտ էր) -------------------
std::string rle_encode(const std::string& input) {
    if (input.empty()) return "";
    std::string output;
    int count = 1;
    for (size_t i = 1; i <= input.size(); ++i) {
        if (i < input.size() && input[i] == input[i - 1]) {
            count++;
        } else {
            output += std::to_string(count);
            output += input[i - 1];
            count = 1;
        }
    }
    return output;
}

// ------------------- RLE DECODE (Ուղղված) -------------------
std::string rle_decode(const std::string& input) {
    std::string output;
    int count = 0;

    for (char c : input) {
        if (std::isdigit(c)) {
            // Եթե սիմվոլը թիվ է, հավաքում ենք այն (օրինակ՝ 12)
            count = count * 10 + (c - '0');
        } else {
            // Եթե սիմվոլը տառ է, ավելացնում ենք այն 'count' անգամ
            if (count > 0) {
                output.append(count, c);
                count = 0; // Մաքրում ենք հաջորդի համար
            }
        }
    }
    return output;
}

// ------------------- INTERACTIVE SHELL -------------------
int main() {
    while (true) {
        std::cout << "\nRLE Interactive Shell\n";
        std::cout << "1. Encode (Սեղմել)\n";
        std::cout << "2. Decode (Ապասեղմել)\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose option: ";

        int choice;
        if (!(std::cin >> choice)) break;
        std::cin.ignore();

        if (choice == 3) break;

        std::string input;
        std::cout << "Enter string: ";
        std::getline(std::cin, input);

        if (choice == 1) {
            std::cout << "Encoded: " << rle_encode(input) << "\n";
        } else if (choice == 2) {
            std::cout << "Decoded: " << rle_decode(input) << "\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    }
    return 0;
}
